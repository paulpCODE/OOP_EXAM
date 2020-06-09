#pragma once
#include <vector>
#include <tuple>

#include "SplayTree.h"
#include "AVLTree.h"
#include "RedBlackTree.h"

#include "HashFunction.h"
#include "LinearProbingTable.h"
#include "SeparateChainingTable.h"
#include "Iterator.h"
#include "linkedlists.h"


template <typename KeyType, typename DataType>
class Container {
public:
	virtual bool setValue(KeyType key, DataType* newData) = 0;
	virtual DataType* getValue(KeyType key) = 0;
	virtual void addValue(KeyType key, DataType* data) = 0;
	virtual void remove(KeyType key) = 0;
	//virtual std::vector<KeyType> getAllKeys() = 0;
	//virtual std::vector<DataType*> getAllValues() = 0;
	//virtual std::vector<std::pair<KeyType, DataType*>> getKeyValuesPairs() = 0;
};
