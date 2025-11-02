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

enum class BucketType {
    NORMAL,  // Has a key value pair
    ESS,     // Empty Since Start
    EAR      // Empty After Remove
};

// HashTableBucket stores a single key value pair
// Each bucket also tracks its state (NORMAL, ESS, or EAR)
class HashTableBucket {
private:
    std::string key;      // The key for this bucket
    size_t value;         // The value associated with the key
    BucketType type;      // Current state of the bucket

public:
    // Constructor
    HashTableBucket();

    // Getter methods
    std::string getKey() const;   // Returns the key stored in this bucket
    size_t getValue() const;       // Returns the value stored in this bucket
    bool isNormal() const;         // Returns true if bucket has valid data


    friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket);

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

    std::string printMe() const;


};
std::ostream& operator<<(std::ostream& os, const HashTable& hashTable);
std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket);

#endif