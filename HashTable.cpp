/**
 * HashTable.cpp
 * Caleb Wilson
 * Project 4 - Hash Table
 * Methods defined here
 */
#include "HashTable.h"
#include <algorithm>
#include <random>

using namespace std;

//----------------------------------------------------------------
// HashTableBucket (default constructor): Creates an empty bucket
//             in ESS (Empty Since Start) state.
//---------------------------------------------------------------
HashTableBucket::HashTableBucket() {
    key = "";
    value = 0;
    type = BucketType::ESS;
}

//----------------------------------------------------------------
// HashTableBucket (parameterized constructor): Creates a bucket
//             with data in NORMAL state.
//    Parameters:
//       key (string) - the key for this bucket
//       value (size_t) - the value associated with the key
//---------------------------------------------------------------
HashTableBucket::HashTableBucket(std::string key, size_t value) {
    this->key = key;
    this->value = value;
    this->type = BucketType::NORMAL;
}

//----------------------------------------------------------------
// load: Load a key-value pair into the bucket and mark as NORMAL.
//    Returns:  void
//    Parameters:
//       key (string) - the key to load
//       value (size_t) - the value to load
//---------------------------------------------------------------
void HashTableBucket::load(std::string key, size_t value) {
    this->key = key;
    this->value = value;
    this->type = BucketType::NORMAL;
}

//----------------------------------------------------------------
// getKey: Returns the key stored in this bucket.
//    Returns:  key (string)
//---------------------------------------------------------------
string HashTableBucket::getKey() const {
    return key;
}

//----------------------------------------------------------------
// getValue: Returns the value stored in this bucket.
//    Returns:  value (size_t)
//---------------------------------------------------------------
size_t HashTableBucket::getValue() const {
    return value;
}

//----------------------------------------------------------------
// getValueRef: Returns a reference to the value in this bucket.
//    Returns:  reference to value
//---------------------------------------------------------------
size_t& HashTableBucket::getValueRef() {
    return value;
}

//----------------------------------------------------------------
// isNormal: Checks if this bucket contains valid data.
//    Returns:  true if bucket is NORMAL, false otherwise
//---------------------------------------------------------------
bool HashTableBucket::isNormal() const {
    return type == BucketType::NORMAL;
}

//----------------------------------------------------------------
// isEmpty: Checks if bucket is empty, ESS or EAR.
//    Returns:  true if empty, false otherwise (bool)
//---------------------------------------------------------------
bool HashTableBucket::isEmpty() const {
    return type == BucketType::ESS || type == BucketType::EAR;
}

//----------------------------------------------------------------
// isEmptySinceStart: Checks if bucket has never been used.
//    Returns:  true if ESS, false otherwise (bool)
//---------------------------------------------------------------
bool HashTableBucket::isEmptySinceStart() const {
    return type == BucketType::ESS;
}

//----------------------------------------------------------------
// isEmptyAfterRemove: Checks if bucket had data that was removed.
//    Returns:  true if EAR, false otherwise (bool)
//---------------------------------------------------------------
bool HashTableBucket::isEmptyAfterRemove() const {
    return type == BucketType::EAR;
}

//----------------------------------------------------------------
// makeNormal: Sets bucket state to NORMAL.
//    Returns:  void
//---------------------------------------------------------------
void HashTableBucket::makeNormal() {
    type = BucketType::NORMAL;
}

//----------------------------------------------------------------
// makeESS: Sets bucket state to ESS
//    Returns:  void
//---------------------------------------------------------------
void HashTableBucket::makeESS() {
    type = BucketType::ESS;
}

//----------------------------------------------------------------
// makeEAR: Sets bucket state to EAR
//    Returns:  void
//---------------------------------------------------------------
void HashTableBucket::makeEAR() {
    type = BucketType::EAR;
}

//----------------------------------------------------------------
// HashTable (constructor): Initializes the hash table with a
//             given capacity. Creates a vector of empty buckets.
//    Parameters:
//       initCapacity (size_t) - initial number of buckets
//---------------------------------------------------------------
HashTable::HashTable(size_t initCapacity) {
    tableData.resize(initCapacity);
    numElements = 0;
    generateOffsets(initCapacity);
}

//----------------------------------------------------------------
// hashFunction: Computes home position for a key using sum of
//             ASCII values mod table size.
//    Returns:  bucket index (size_t)
//    Parameters:
//       key (string) - the key to hash
//---------------------------------------------------------------
size_t HashTable::hashFunction(const std::string& key) const {
    size_t hash = 0;
    for (char c : key) {
        hash += static_cast<size_t>(c);
    }
    return hash % tableData.size();
}

//----------------------------------------------------------------
// generateOffsets: Generates pseudo-random probe offsets by
//             creating array [1, 2, ..., capacity-1] then
//             shuffling it using std::shuffle.
//    Returns:  void
//    Parameters:
//       capacity (size_t) - the table capacity
//https://en.cppreference.com/w/cpp/numeric/random.html
//---------------------------------------------------------------
void HashTable::generateOffsets(size_t capacity) {
    offsets.clear();
    offsets.resize(capacity - 1);

    for (size_t i = 0; i < capacity - 1; i++) {
        offsets[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 g(rd()); // https://en.cppreference.com/w/cpp/numeric/random.html
    std::shuffle(offsets.begin(), offsets.end(), g);
}

//----------------------------------------------------------------
// findBucket: Finds the bucket containing a key using hash
//             function and pseudo-random probing.
//    Returns:  bucket index if found, SIZE_MAX if not found (size_t)
//    Parameters:
//       key (string) - the key to search for
//---------------------------------------------------------------
size_t HashTable::findBucket(const std::string& key) const {
    size_t home = hashFunction(key);
    size_t cap = tableData.size();

    if (tableData[home].isNormal() && tableData[home].getKey() == key) {
        return home;
    }

    if (tableData[home].isEmptySinceStart()) {
        return SIZE_MAX;
    }

    for (size_t i = 0; i < offsets.size(); i++) {
        size_t probeIdx = (home + offsets[i]) % cap;

        if (tableData[probeIdx].isNormal() && tableData[probeIdx].getKey() == key) {
            return probeIdx;
        }

        if (tableData[probeIdx].isEmptySinceStart()) {
            return SIZE_MAX;
        }
    }

    return SIZE_MAX;
}

//----------------------------------------------------------------
// findInsertBucket: Finds an empty bucket to insert a key using
//             hash function and probing. Checks for duplicates.
//    Returns:  bucket index if found, SIZE_MAX if duplicate or full (size_t)
//    Parameters:
//       key (string) - the key to insert
//---------------------------------------------------------------
size_t HashTable::findInsertBucket(const std::string& key) {
    size_t home = hashFunction(key);
    size_t cap = tableData.size();

    if (tableData[home].isNormal() && tableData[home].getKey() == key) {
        return SIZE_MAX;
    }
    if (tableData[home].isEmpty()) {
        return home;
    }

    for (size_t i = 0; i < offsets.size(); i++) {
        size_t probeIdx = (home + offsets[i]) % cap;

        if (tableData[probeIdx].isNormal() && tableData[probeIdx].getKey() == key) {
            return SIZE_MAX;
        }

        if (tableData[probeIdx].isEmpty()) {
            return probeIdx;
        }
    }

    return SIZE_MAX;
}

//----------------------------------------------------------------
// resize: Doubles the table size, rehashes elements when
//             load factor reaches 0.5 or greater.
//    Returns:  void
//---------------------------------------------------------------
void HashTable::resize() {
    std::vector<HashTableBucket> oldData = tableData;

    size_t newCapacity = tableData.size() * 2;
    tableData.clear();
    tableData.resize(newCapacity);
    numElements = 0;

    generateOffsets(newCapacity);

    for (const auto& bucket : oldData) {
        if (bucket.isNormal()) {
            insert(bucket.getKey(), bucket.getValue());
        }
    }
}

//----------------------------------------------------------------
// insert: Inserts a key value pair into the table. Rejects
//             duplicates and the reserved value 9999. Resizes
//             table if load factor >= 0.5.
//    Returns:  true if successful, false if duplicate or value is 9999 (bool)
//    Parameters:
//       key (string) - the key to insert
//       value (size_t) - the value to associate with the key
//---------------------------------------------------------------
bool HashTable::insert(std::string key, size_t value) {
    if (value == 9999) {
        return false;
    }

    if (alpha() >= 0.5) {
        resize();
    }

    size_t bucketIdx = findInsertBucket(key);

    if (bucketIdx == SIZE_MAX) {
        return false;
    }

    tableData[bucketIdx].load(key, value);
    numElements++;
    return true;
}

//----------------------------------------------------------------
// remove: Removes a key value pair from the table by marking
//             the bucket as EAR.
//    Returns:  true if removed, false if key not found (bool)
//    Parameters:
//       key (string) - the key to remove
//---------------------------------------------------------------
bool HashTable::remove(std::string key) {
    size_t bucketIdx = findBucket(key);

    if (bucketIdx == SIZE_MAX) {
        return false;
    }

    tableData[bucketIdx].makeEAR();
    numElements--;
    return true;
}

//----------------------------------------------------------------
// contains: Checks if a key exists in the table.
//    Returns:  true if key in table, false otherwise (bool)
//    Parameters:
//       key (string) - the key to search for
//---------------------------------------------------------------
bool HashTable::contains(const string& key) const {
    return findBucket(key) != SIZE_MAX;
}

//----------------------------------------------------------------
// get: Gets the value associated with a key.
//    Returns:  value if found, std::nullopt if not found
//    Parameters:
//       key (string) - the key to search for
//---------------------------------------------------------------
std::optional<size_t> HashTable::get(const string& key) const {
    size_t bucketIdx = findBucket(key);

    if (bucketIdx == SIZE_MAX) {
        return std::nullopt;
    }

    return tableData[bucketIdx].getValue();
}

//----------------------------------------------------------------
// operator[]: Bracket operator. Returns reference for reading
//   Undefined behavior if key not in table.
//    Returns:  reference to value (size_t&)
//    Parameters:
//       key (string) - the key to access
//---------------------------------------------------------------
size_t& HashTable::operator[](const string& key) {
    size_t bucketIdx = findBucket(key);
    return tableData[bucketIdx].getValueRef();
}

//----------------------------------------------------------------
// keys: Returns a vector containing all keys currently stored
//             in the table.
//    Returns:  vector of all keys (vector<string>)
//---------------------------------------------------------------
std::vector<string> HashTable::keys() const {
    std::vector<string> result;

    for (size_t i = 0; i < tableData.size(); i++) {
        if (tableData[i].isNormal()) {
            result.push_back(tableData[i].getKey());
        }
    }

    return result;
}

//----------------------------------------------------------------
// alpha: Calculates and returns the load factor (size/capacity).
//    Returns:  load factor (double)
//---------------------------------------------------------------
double HashTable::alpha() const {
    return static_cast<double>(numElements) / static_cast<double>(tableData.size());
}

//----------------------------------------------------------------
// capacity: Returns the total number of buckets in the table.
//    Returns:  capacity (size_t)
//---------------------------------------------------------------
size_t HashTable::capacity() const {
    return tableData.size();
}

//----------------------------------------------------------------
// size: Returns the number of key-value pairs currently stored.
//    Returns:  size (size_t)
//---------------------------------------------------------------
size_t HashTable::size() const {
    return numElements;
}

//----------------------------------------------------------------
// printMe: Helper method that creates a string representation
//             of the table showing all occupied buckets.
//    Returns:  string representation of table (string)
//---------------------------------------------------------------
std::string HashTable::printMe() const {
    std::string result = "";

    for (size_t i = 0; i < tableData.size(); i++) {
        if (tableData[i].isNormal()) {
            result += "Bucket " + std::to_string(i) + ": <" +
                      tableData[i].getKey() + ", " +
                      std::to_string(tableData[i].getValue()) + ">\n";
        }
    }

    return result;
}

//----------------------------------------------------------------
// operator<< (HashTableBucket):  operator for
//             printing a bucket in format <key, value>.
//    Returns:  output stream
//    Parameters:
//       os (ostream&) - output stream
//       bucket (HashTableBucket&) - bucket to print
//---------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {
    os << "<" << bucket.getKey() << ", " << bucket.getValue() << ">";
    return os;
}

//----------------------------------------------------------------
// operator<< (HashTable):  operator for printing
//             the entire hash table by calling printMe().
//    Returns:  output stream (ostream&)
//    Parameters:
//       os (ostream&) - output stream
//       hashTable (HashTable&) - hash table to print
//---------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const HashTable& hashTable) {
    os << hashTable.printMe();
    return os;
}



