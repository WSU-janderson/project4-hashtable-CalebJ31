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

// Constructor, initializes the hash table with a given capacity
// Creates a vector of empty buckets
HashTable::HashTable(size_t initCapacity) {
    tableData.resize(initCapacity);  // Create initCapacity empty buckets
}


bool HashTable::insert(std::string key, size_t value){};
bool HashTable::remove(std::string key){};
bool HashTable::contains(const string& key) const{};
std::optional<size_t> HashTable::get(const string& key) const{};
size_t& HashTable::operator[](const string& key){};
std::vector<string> HashTable::keys() const{};
double HashTable::alpha() const{};
size_t HashTable::capacity() const{};
size_t HashTable::size() const{};



