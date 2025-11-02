/**
 * HashTable.h
 *
 */
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <optional>
#include <iostream>

// Add this enum first
enum class BucketType {
    NORMAL,  // Has a key-value pair
    ESS,     // Empty Since Start
    EAR      // Empty After Remove
};

// Add this class before HashTable
class HashTableBucket {
private:
    std::string key;
    size_t value;
    BucketType type;

public:
    HashTableBucket();
    std::string getKey() const;
    size_t getValue() const;
    bool isNormal() const;
};


class HashTable {
private:
    std::vector<HashTableBucket> tableData;


public:
    HashTable(size_t initCapacity = 8);
    bool insert(std::string key, size_t value);
    bool remove(std::string key);
    bool contains(const std::string& key) const;
    std::optional<size_t> get(const std::string& key) const;
    size_t& operator[](const std::string& key);
    std::vector<std::string> keys() const;
    double alpha() const;
    size_t capacity() const;
    size_t size() const;
};
#endif