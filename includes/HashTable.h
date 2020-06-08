#pragma once

#include "HashNode.h"
#include <cstddef>

template <typename KeyType, typename DataType>
class HashTable {
protected:
	std::size_t capacity;

public:
	HashTable(std::size_t capacity) : capacity{ capacity } {}

	virtual void insert(KeyType key, DataType* data) = 0;
	virtual bool set(KeyType key, DataType* newData) = 0;
	virtual DataType* search(KeyType key) = 0;
	virtual bool remove(KeyType key) = 0;
	virtual void clear() = 0;

};
