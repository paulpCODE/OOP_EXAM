#pragma once

#include "HashNode.h"
#include <cstddef>

template <typename KeyType, typename DataType>
class HashTable {
protected:
	std::size_t capacity;

public:
	HashTable(std::size_t capacity) : capacity{ capacity } {}

	/** Inserts the key 'key' associated with the data 'data'.
	 * It assumes that pointer to the data is NOT a null pointer.
	 * Otherwise (if 'data' is a null pointer), it throws an exception.
	 */
	virtual void insert(KeyType key, DataType* data) = 0;
	
	/** Set the new data 'newData' to be associated with the 'key'.
	 * Returns true if the key was found and the data, associated with this key, was replaced with 'newData'.
	 * Otherwise (if there is not the key 'key' in the hash table), this method does nothing and returns false.
	 */
	virtual bool set(KeyType key, DataType* newData) = 0;
	
	/** Searches for the data associated with the key 'key'.
	 * Returns the NOT null pointer to data if the search is successful.
	 * Otherwise, returns null pointer.
	 */
	virtual DataType* search(KeyType key) = 0;
	
	/** Removes the the key 'key'.
	 * Returns true if the key was found and removed from the table.
	 * Returns false if the key was NOT found in the table.
	 */
	virtual bool remove(KeyType key) = 0;
	
	//! Clears the hash table. Removes all keys from the table.
	virtual void clear() = 0;

};
