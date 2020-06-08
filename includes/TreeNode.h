#pragma once

template <typename KeyType, typename DataType, typename NodeType>
class BinaryTreeNode {
public:
	KeyType key;
	DataType* data;

	NodeType* parent;
	NodeType* left;
	NodeType* right;

	BinaryTreeNode(KeyType key, DataType* data) :
		key{ key }, data{ data }, parent{ nullptr }, left{ nullptr }, right{ nullptr } {}
};
