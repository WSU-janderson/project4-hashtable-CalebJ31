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
    cout << ht.contains("Alice") << endl;

    cout << "Size: " << ht.size() << endl;
    cout << ht.contains("Caleb") << endl;

    auto result1 = ht.get("Caleb");
    cout << result1.value() << endl;
    ht.remove("Caleb");
    cout << "Size: " << ht.size() << endl;


    return 0;
}