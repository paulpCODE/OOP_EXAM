#pragma once

template <typename KeyType, typename DataType>
class TreeNode {
public:
	KeyType key;
	DataType* data;

	TreeNode(KeyType key, DataType* data) : key{ key }, data{ data } {}
};

template <typename KeyType, typename DataType, typename NodeType>
class BinaryTreeNode : public TreeNode<KeyType, DataType> {
public:
	NodeType* parent;
	NodeType* left;
	NodeType* right;

	BinaryTreeNode(KeyType key, DataType* data) :
		TreeNode<KeyType, DataType>(key, data), parent{ nullptr }, left{ nullptr }, right{ nullptr } {}

};
