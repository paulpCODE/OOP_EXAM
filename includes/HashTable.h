#pragma once

#include "HashNode.h"

template <typename KeyType, typename DataType>
class HashTable {
public:
	virtual void insert(KeyType key, DataType* data) = 0;
	virtual void remove(KeyType key) = 0;
	virtual HashNode<KeyType, DataType>* search(KeyType key) = 0;
	virtual void clear() = 0;

};
