#pragma once
#include "TreeNode.h"

template <typename KeyType, typename DataType>
class AVLNode : public BinaryTreeNode<KeyType, DataType, AVLNode<KeyType, DataType>> {
public:
	AVLNode(KeyType key, DataType* data) :
		BinaryTreeNode<KeyType, DataType, AVLNode<KeyType, DataType>>(key, data),
		height{ 1 } {}

	int getHeight() { return this->height; }
	void setHeight(int height) { this->height = height; }
private:
	int height;
};