#pragma once

#include "HashNode.h"
#include <cstddef>

template <typename KeyType, typename DataType>
class HashTable {
protected:
	std::size_t size;

public:
	HashTable(std::size_t size) : size{ size } {}

	virtual void insert(KeyType key, DataType* data) = 0;
	virtual void remove(KeyType key) = 0;
	virtual HashNode<KeyType, DataType>* search(KeyType key) = 0;
	virtual void clear() = 0;

};
