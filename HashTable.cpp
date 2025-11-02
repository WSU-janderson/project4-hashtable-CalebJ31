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
std::vector<string> HashTable::keys() const{};
double HashTable::alpha() const{};
size_t HashTable::capacity() const{};
size_t HashTable::size() const{};



