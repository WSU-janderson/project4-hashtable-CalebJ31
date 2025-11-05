/**
 * HashTableDebug.cpp
 *
 * Write your tests in this file
 */
#include <iostream>
#include "HashTable.h"
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
     HashTable ht(9);

    ht.insert("Caleb", 100);
    ht.insert("Wilson", 200);
    cout << ht << endl;
    cout << "Size: " << ht.size() << endl;

    return 0;
}