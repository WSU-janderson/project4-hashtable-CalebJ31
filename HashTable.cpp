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

// Prints a single bucket in format: <key, value>
std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {
    // Print the bucket's key value pair
    os << "<" << bucket.key << ", " << bucket.value << ">";
    return os;
}

// Prints the entire hash table
// Only prints buckets that are NORMAL
// Format: Bucket [index]: <key, value>
std::ostream& operator<<(std::ostream& os, const HashTable& hashTable) {
    // Loop through all buckets in the table
    for (size_t i = 0; i < hashTable.tableData.size(); i++) {
        // Only print buckets that have data
        if (hashTable.tableData[i].isNormal()) {
            os << "Bucket " << i << ": " << hashTable.tableData[i] << "\n";
        }
    }
    return os;
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



