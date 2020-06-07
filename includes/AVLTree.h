#pragma once
#include <algorithm>
#include "BinarySearchTree.h"
#include "AVLTreeNode.h"

template <typename KeyType, typename DataType>
class AVLTree : public BinarySearchTree<KeyType, DataType, AVLNode<KeyType, DataType>> {
public:
	AVLTree() {}

	void insert(KeyType key, DataType* data) { this->root = insertNode(this->root, key, data); }
	void remove(KeyType key) { this->root = removeNode(this->root, key); }
	void clear() { clearTree(this->root); }
	AVLNode<KeyType, DataType>* search(KeyType key) { return searchNode(this->root, key); }
	AVLNode<KeyType, DataType>* getRoot() { return this->root; }
private:
	void clearTree(AVLNode<KeyType, DataType>* node);
	int getNodeHeight(AVLNode<KeyType, DataType>* node);
	int getBalance(AVLNode<KeyType, DataType>* node);
	AVLNode<KeyType, DataType>* rightRotate(AVLNode<KeyType, DataType>* node);
	AVLNode<KeyType, DataType>* leftRotate(AVLNode<KeyType, DataType>* node);
	AVLNode<KeyType, DataType>* insertNode(AVLNode<KeyType, DataType>* node, KeyType key, DataType* data);
	AVLNode<KeyType, DataType>* minValueNode(AVLNode<KeyType, DataType>* node);
	AVLNode<KeyType, DataType>* removeNode(AVLNode<KeyType, DataType>* node, KeyType key);
	AVLNode<KeyType, DataType>* searchNode(AVLNode<KeyType, DataType>* node, KeyType key);
};

template<typename KeyType, typename DataType>
inline void AVLTree<KeyType, DataType>::clearTree(AVLNode<KeyType, DataType>* node)
{
	if (node == nullptr) return;

	clearTree(node->left);
	clearTree(node->right);

	delete node->data;
	delete node;
}

template<typename KeyType, typename DataType>
inline int AVLTree<KeyType, DataType>::getNodeHeight(AVLNode<KeyType, DataType>* node)
{
	if (node == nullptr) return 0;
	return node->getHeight();
}

template<typename KeyType, typename DataType>
inline int AVLTree<KeyType, DataType>::getBalance(AVLNode<KeyType, DataType>* node)
{
	if (node == nullptr) return 0;
	return getNodeHeight(node->left) - getNodeHeight(node->right);
}

template<typename KeyType, typename DataType>
inline AVLNode<KeyType, DataType>* AVLTree<KeyType, DataType>::rightRotate(AVLNode<KeyType, DataType>* node)
{
	AVLNode<KeyType, DataType>* x = node->left;
	AVLNode<KeyType, DataType>* z = x->right;

	x->right = node;
	node->left = z;

	node->setHeight(std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1);
	x->setHeight(std::max(getNodeHeight(x->left), getNodeHeight(x->right)) + 1);

	return x;
}

template<typename KeyType, typename DataType>
inline AVLNode<KeyType, DataType>* AVLTree<KeyType, DataType>::leftRotate(AVLNode<KeyType, DataType>* node)
{
	AVLNode<KeyType, DataType>* y = node->right;
	AVLNode<KeyType, DataType>* z = y->left;

	y->left = node;
	node->right = z;

	node->setHeight(std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1);
	y->setHeight(std::max(getNodeHeight(y->left), getNodeHeight(y->right)) + 1);

	return y;
}

template<typename KeyType, typename DataType>
inline AVLNode<KeyType, DataType>* AVLTree<KeyType, DataType>::insertNode(AVLNode<KeyType, DataType>* node, KeyType key, DataType* data)
{
	if (node == nullptr)
		return new AVLNode<KeyType, DataType>(key, data);

	if (key < node->key)
		node->left = insertNode(node->left, key, data);
	else if (key > node->key)
		node->right = insertNode(node->right, key, data);
	else
		return node;

	node->setHeight(1 + std::max(getNodeHeight(node->left),getNodeHeight(node->right)));

	int balance = getBalance(node);

	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

template<typename KeyType, typename DataType>
inline AVLNode<KeyType, DataType>* AVLTree<KeyType, DataType>::minValueNode(AVLNode<KeyType, DataType>* node)
{
	AVLNode<KeyType, DataType>* current = node;

	while (current->left != nullptr)
		current = current->left;

	return current;
}

template<typename KeyType, typename DataType>
inline AVLNode<KeyType, DataType>* AVLTree<KeyType, DataType>::removeNode(AVLNode<KeyType, DataType>* node, KeyType key)
{
	if (node == nullptr)
		return node;

	if (key < node->key)
		node->left = removeNode(node->left, key);

	else if (key > node->key)
		node->right = removeNode(node->right, key);

	else
	{
		if ((node->left == nullptr) || (node->right == nullptr))
		{
			AVLNode<KeyType, DataType>* temp = node->left ? node->left : node->right;

			if (temp == nullptr)
			{
				temp = node;
				node = nullptr;
			}
			else
				*node = *temp;
			free(temp);
		}
		else
		{
			AVLNode<KeyType, DataType>* temp = minValueNode(node->right);

			node->key = temp->key;
			node->right = removeNode(node->right, temp->key);
		}
	}

	if (node == nullptr)
		return node;

	node->setHeight(1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right)));

	int balance = getBalance(node);

	if (balance > 1 && getBalance(node->left) >= 0)
		return rightRotate(node);

	if (balance > 1 && getBalance(node->left) < 0)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && getBalance(node->right) <= 0)
		return leftRotate(node);

	if (balance < -1 && getBalance(node->right) > 0)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

template<typename KeyType, typename DataType>
inline AVLNode<KeyType, DataType>* AVLTree<KeyType, DataType>::searchNode(AVLNode<KeyType, DataType>* node, KeyType key)
{
	if (node == nullptr || node->key == key) return node;
	if (node->key < key) return searchNode(node->right, key);
	return searchNode(node->left, key);
}
