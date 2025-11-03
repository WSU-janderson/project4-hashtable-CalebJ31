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
    cout<< ht.size() << endl;
    cout<< ht.capacity() << endl;
    cout<< ht.alpha() << endl;



    return 0;
}