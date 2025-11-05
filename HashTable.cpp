/**
 * HashTable.cpp
 */
#include "HashTable.h"
#include <algorithm>
#include <random>

using namespace std;

// Default constructor that creates an empty bucket in ESS state
HashTableBucket::HashTableBucket() {
    key = "";                    // Empty key
    value = 0;                   // Default value
    type = BucketType::ESS;      // Mark as Empty Since Start
}

// Returns the key stored in this bucket
string HashTableBucket::getKey() const {
    return key;
}


// Returns the value stored in this bucket
size_t HashTableBucket::getValue() const {
    return value;
}

// Checks if this bucket contains valid data
bool HashTableBucket::isNormal() const {
    return type == BucketType::NORMAL;
}
// Parameterized constructor creates a bucket with data in NORMAL state
HashTableBucket::HashTableBucket(std::string key, size_t value) {
    this->key = key;
    this->value = value;
    this->type = BucketType::NORMAL;
}

// Load a key value pair into the bucket and mark as NORMAL
void HashTableBucket::load(std::string key, size_t value) {
    this->key = key;
    this->value = value;
    this->type = BucketType::NORMAL;
}

// Returns a reference to the value
size_t& HashTableBucket::getValueRef() {
    return value;
}

// Checks if bucket is empty. ESS or EAR
bool HashTableBucket::isEmpty() const {
    return type == BucketType::ESS || type == BucketType::EAR;
}

// Checks if bucket has never been used
bool HashTableBucket::isEmptySinceStart() const {
    return type == BucketType::ESS;
}

// Checks if bucket had data that was removed
bool HashTableBucket::isEmptyAfterRemove() const {
    return type == BucketType::EAR;
}

// Sets bucket state to NORMAL
void HashTableBucket::makeNormal() {
    type = BucketType::NORMAL;
}

// Sets bucket state to ESS
void HashTableBucket::makeESS() {
    type = BucketType::ESS;
}

// Sets bucket state to EAR
void HashTableBucket::makeEAR() {
    type = BucketType::EAR;
}
// Constructor, initializes the hash table with a given capacity
// Creates a vector of empty buckets
HashTable::HashTable(size_t initCapacity) {
    tableData.resize(initCapacity);  // Create initCapacity empty buckets
    numElements = 0;
     generateOffsets(initCapacity);
}

// Helper method to create a string representation of the table
// This IS a member method, so it CAN access private data
std::string HashTable::printMe() const {
    std::string result = "";

    // Loop through all buckets
    for (size_t i = 0; i < tableData.size(); i++) {
        // Only print buckets that have data
        if (tableData[i].isNormal()) {
            result += "Bucket " + std::to_string(i) + ": <" +
                      tableData[i].getKey() + ", " +
                      std::to_string(tableData[i].getValue()) + ">\n";
        }
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {
    os << "<" << bucket.getKey() << ", " << bucket.getValue() << ">";
    return os;
}

std::ostream& operator<<(std::ostream& os, const HashTable& hashTable) {
    os << hashTable.printMe();
    return os;
}

// Hash function. computes home position for a key
// Uses sum of ASCII values mod table size
size_t HashTable::hashFunction(const std::string& key) const {
    size_t hash = 0;
    // Sum ASCII values of all characters
    for (char c : key) {
        hash += static_cast<size_t>(c);
    }
    // Mod by table size to get valid index
    return hash % tableData.size();
}

// Generates pseudo random probe offsets
// Creates array of [1, 2, ... capacity-1] then shuffles it
//https://en.cppreference.com/w/cpp/numeric/random.html
void HashTable::generateOffsets(size_t capacity) {
    offsets.clear();
    offsets.resize(capacity - 1);

    // Fill with capacity-1
    for (size_t i = 0; i < capacity - 1; i++) {
        offsets[i] = i + 1;
    }

    // Shuffle using C++ random
    std::random_device rd;      //  random number generator
    std::mt19937 g(rd());       // Mersenne Twister seeded
    std::shuffle(offsets.begin(), offsets.end(), g);
}

// Finds an empty bucket to insert a key, or returns SIZE_MAX if key exists
size_t HashTable::findInsertBucket(const std::string& key) {
    size_t home = hashFunction(key);
    size_t cap = tableData.size();

    // Check home position first
    if (tableData[home].isNormal() && tableData[home].getKey() == key) {
        return SIZE_MAX;  // Duplicate key
    }
    if (tableData[home].isEmpty()) {
        return home;  // Home is empty, use it
    }

    // Probe using offsets
    for (size_t i = 0; i < offsets.size(); i++) {
        size_t probeIdx = (home + offsets[i]) % cap;

        // Check for duplicate
        if (tableData[probeIdx].isNormal() && tableData[probeIdx].getKey() == key) {
            return SIZE_MAX;
        }

        // Found empty bucket
        if (tableData[probeIdx].isEmpty()) {
            return probeIdx;
        }
    }

    return SIZE_MAX;  // if Table full
}

// Doubles the table size and rehashes all elements
void HashTable::resize() {
    // Save old data
    std::vector<HashTableBucket> oldData = tableData;

    // Double capacity and reset
    size_t newCapacity = tableData.size() * 2;
    tableData.clear();
    tableData.resize(newCapacity);
    numElements = 0;

    // Generate new offsets for new capacity
    generateOffsets(newCapacity);

    // Reinsert all elements from old table
    for (const auto& bucket : oldData) {
        if (bucket.isNormal()) {
            insert(bucket.getKey(), bucket.getValue());
        }
    }
}

// Find the bucket containing a key
// Returns the bucket index if found, SIZE_MAX if not found
size_t HashTable::findBucket(const std::string& key) const {
    size_t home = hashFunction(key);
    size_t cap = tableData.size();

    // Check home position
    if (tableData[home].isNormal() && tableData[home].getKey() == key) {
        return home;
    }

    // If home is ESS, key is not in table
    if (tableData[home].isEmptySinceStart()) {
        return SIZE_MAX;  // Not found
    }

    // Probe using offsets
    for (size_t i = 0; i < offsets.size(); i++) {
        size_t probeIdx = (home + offsets[i]) % cap;

        // Found the key
        if (tableData[probeIdx].isNormal() && tableData[probeIdx].getKey() == key) {
            return probeIdx;
        }

        // If we hit ESS, key is not in table
        if (tableData[probeIdx].isEmptySinceStart()) {
            return SIZE_MAX;
        }
    }

    return SIZE_MAX;  // Not found after checking all positions
}

// Inserts a key value pair into the table
// Returns true if successful, false if duplicate or value is 9999
bool HashTable::insert(std::string key, size_t value) {
    // Check if value is reserved (9999 cannot be stored)
    if (value == 9999) {
        return false;
    }

    // Resize if load factor >= 0.5
    if (alpha() >= 0.5) {
        resize();
    }
    // Find bucket to insert into
    size_t bucketIdx = findInsertBucket(key);

    if (bucketIdx == SIZE_MAX) {
        return false;  // Duplicate key or table full
    }

    // Insert the key value pair
    tableData[bucketIdx].load(key, value);
    numElements++;
    return true;
}

bool HashTable::remove(std::string key){};
bool HashTable::contains(const string& key) const {
    return findBucket(key) != SIZE_MAX;

};
std::optional<size_t> HashTable::get(const string& key) const{};
size_t& HashTable::operator[](const string& key){};


// Creates a vector that stores keys
// loop thru data, if it has data then add
std::vector<string> HashTable::keys() const {
    std::vector<string> result;
    // Loop through all buckets in the table
    for (size_t i = 0; i < tableData.size(); i++) {
        // Only add keys from buckets that have data
        if (tableData[i].isNormal()) {
            result.push_back(tableData[i].getKey());
        }
    }

    return result;
};
// Will return the load factor. Basically size/capaccity
double HashTable::alpha() const {
    return static_cast<double>(numElements)/ static_cast<double>(tableData.size());
};
//returns the number of buckets in the table
size_t HashTable::capacity() const {
    return tableData.size();
};
//Returns the number of key value pairs
size_t HashTable::size() const {
    return numElements;
};



