# Study-Of-The-Hash-Table-Data-Structure
Computer Science. Year 1. Algorithms and Data structures. Lab 6

# Task
Translated via ChatGPT

Write a program to implement a data structure called hash table, that allows for fast data retrieval in a set of structures according to your variant.

1. Implement the generateRandLong() function:  
1.1 The function should generate and return a random large number to be used as a unique key-identifier for data in the hash table. Function signature: long long generateRandLong().  

2. Implement a static hash table using the chaining method:  
2.1 Create a "Data" structure to store various data according to your variant (for example, if your structure is "Bomb," it might have fields like weight, color, and quantity of TNT in kg). This structure will be used as values for the hash table. Implement generating random data for the structure fields in the Data() constructor.  
2.2 Create a "HashNode" structure to store the key and value.  
2.3 Create a "LinkedList" structure with support for adding elements, and separate it into header and cpp files.  
2.4 Create a "HashTable" structure that contains an array of linked lists called bucketsArray with a static size of M = 10000. Implement the following basic functions:  
hash(key) – calculate the hash function from the key.  
insert(key, value) – add a value under the corresponding key (replace if the key already exists).  
find(key) – find the value under the given key; the function returns a pointer to the found element or nullptr.  
erase(key) – delete the value under the given key.  
size() – find the number of elements in the hash table.

3. Add dynamic resizing to the hash table:  
3.1 At each step, calculate the loadFactor (current table load) and change the size of the bucketsArray based on maxLoadFactor (maximum allowable table load).  
3.2 Start with a small initial size for the bucketsArray, and dynamically increase the size when the maxLoadFactor is exceeded.  
3.3 When reallocating memory for all elements of the hash table, recalculate their new positions based on the changed hash function.  

4. Perform testing of the hash table:  
4.1 Use several different values of maxLoadFactor (e.g., 9, 4, and 0.5) and different hash functions.  
4.2 Use the provided testHashTable() function for testing with time measurements and select the optimal hash function and maxLoadFactor.  
4.3 Investigate the use of the ready-made STL unordered_map library solution, and compare the results obtained with your solution.  

Also GitHub has some issues with Cyrillic symbols, therefore, some comments and lines of code may not be displayed correctly.
