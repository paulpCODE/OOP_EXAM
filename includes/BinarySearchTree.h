#pragma once

#include "TreeNode.h"

template <typename KeyType, typename DataType, typename NodeType>
class BinarySearchTree {
protected:
	NodeType* root{ nullptr };

public:
	virtual void insert(KeyType key, DataType* data) = 0;
	virtual void remove(KeyType key) = 0;
	virtual void clear() = 0;

	virtual NodeType* search(KeyType key) = 0;
	virtual NodeType* getRoot() = 0;

};
