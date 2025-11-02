/**
 * HashTable.cpp
 */
#include "HashTable.h"
using namespace std;

HashTableBucket::HashTableBucket() {
    key = "";
    value = 0;
    type = BucketType::ESS;
}

string HashTableBucket::getKey() const {
    return key;
}

size_t HashTableBucket::getValue() const {
    return value;
}

bool HashTableBucket::isNormal() const {
    return type == BucketType::NORMAL;
}

HashTable::HashTable(size_t initCapacity) {
    tableData.resize(initCapacity);
};


bool HashTable::insert(std::string key, size_t value){};
bool HashTable::remove(std::string key){};
bool HashTable::contains(const string& key) const{};
std::optional<size_t> HashTable::get(const string& key) const{};
size_t& HashTable::operator[](const string& key){};
std::vector<string> HashTable::keys() const{};
double HashTable::alpha() const{};
size_t HashTable::capacity() const{};
size_t HashTable::size() const{};



