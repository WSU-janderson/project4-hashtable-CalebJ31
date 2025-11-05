[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7RAFczHS)
# Project 4 - HashTable

Project description can be found [in the repo](Project4_HashTable.pdf)

Place your complexity analysis below.

# Time Complexity Analysis

## insert()
**Time Complexity:** O(1) 

**Justification:**
The hash function computes O(1) time  summing ASCII values. 

## remove()
**Time Complexity:** O(1) 

**Justification:**
Uses findBucket() which performs hash computation and probing in constant time with a low load factor. 
Marking  bucket as EAR and decrementing  counter are both O(1) operations.

## contains()
**Time Complexity:** O(1) 

**Justification:**
Calls findBucket() which computes the hash in O(1) time. Pseudo-random probing finds key in constant time with good hash and load management.

## get()
**Time Complexity:** O(1) 

**Justification:**
Uses findBucket() internally for searching. Hash computation and bucket access are both O(1). 

## operator[]
**Time Complexity:** O(1) 

**Justification:**
Calls findBucket() to locate the key, then returns a reference to the value in O(1). Same probing behavior as get() and contains() makes this constant time.

## keys()
**Time Complexity:** O(n)

**Justification:**
Must iterate through every bucket in tableData to collect keys from NORMAL buckets. This requires a linear scan of the entire table.

## alpha()
**Time Complexity:** O(1)

**Justification:**
Simple division of numElements by tableData.size(). Both values are stored as member variables with no iteration or searching required.

## capacity()
**Time Complexity:** O(1)

**Justification:**
Simply returns tableData.size(). Vector's size() method is O(1) with no computation or iteration.

## size()
**Time Complexity:** O(1)

**Justification:**
Returns the numElements member variable directly. We maintain this counter during insert and remove operations.

---