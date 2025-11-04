/**
 * HashTable.cpp
 */
#include "HashTable.h"
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

bool HashTable::insert(std::string key, size_t value){};
bool HashTable::remove(std::string key){};
bool HashTable::contains(const string& key) const{};
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



