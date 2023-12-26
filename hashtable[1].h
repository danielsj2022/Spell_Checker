#ifndef COP4530_HASHTABLE_H
#define COP4530_HASHTABLE_H

#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>

using namespace std;
// used when improper size is given (for example
// size is 0 or negatiave)
static const unsigned int default_capacity = 11;
static const unsigned int max_prime = 1301081;


namespace cop4530{

template <typename T>
class HashTable {
 public:
	HashTable(size_t size=101);   //create hash table of size prime
	~HashTable();
	bool contains(const T &x) const;   //check if x in hash
	bool insert(const T &x);   //add x if not alr in table, T/F
	bool insert(T &&x);   //move
	bool remove(const T &x);   //delete x if in table
	void clear();   //delete elements
	bool load(const char*filename);   //load content into hash
	void dump() const;   //display all entries
	bool write_to_file(const char*filename) const;   //write elements to file
	int getSize() const;   //num elements
        size_t tableSize() const;

 private:
	std::vector<list<T>> table;
	int currSize;
	void makeEmpty();   //delete all
	void rehash();   //when num elements in table > vec size
	size_t myhash(const T &x) const;   //return ind where x should be stored

	unsigned long prime_below(long);
	void setPrimes(std::vector<long> &);
	
};
#include "hashtable.hpp"
}
#endif
