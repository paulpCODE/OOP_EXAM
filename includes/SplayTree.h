#pragma once

#include "TreeNode.h"
#include "RedBlackTree.h"
#include <stdexcept>
#include <iostream>

// Splay tree node
template <typename KeyType, typename DataType>
class STNode : public TreeNode<KeyType, DataType, STNode<KeyType, DataType>> {
public:
	STNode(KeyType key, DataType* data);

};

template <typename KeyType, typename DataType>
class SplayTree : public BinarySearchTree<KeyType, DataType, STNode<KeyType, DataType>>
{
private:
	void rotateLeft(STNode<KeyType, DataType>* x);
	void rotateRight(STNode<KeyType, DataType>* y);
	void splay(STNode<KeyType, DataType>* x);
	//! Combine trees tree1 and tree2 into a single tree.
	STNode<KeyType, DataType>* join(STNode<KeyType, DataType>* tree1, STNode<KeyType, DataType>* tree2);

	//! Prints the tree according to the inorder traversal.
	void print(const STNode<KeyType, DataType>* tree, std::ostream& out);
	void deleteTreeNode(STNode<KeyType, DataType>* node);

public:
	SplayTree();
	~SplayTree();

	void insert(KeyType key, DataType* data) override;
	//! Deletes the node with the key 'key'.
	void remove(KeyType key) override;
	//! Returns the pointer to the node with the key 'key'.
	STNode<KeyType, DataType>* search(KeyType key) override;
	//! Returns the pointer to the root.
	STNode<KeyType, DataType>* getRoot() override;

	//! Prints the tree according to the inorder traversal.
	void print(std::ostream& out = std::cout);
	//! Deletes all nodes.
	void clear() override;

};

template <typename KeyType, typename DataType>
inline STNode<KeyType, DataType>::STNode(KeyType key, DataType* data) :
	TreeNode<KeyType, DataType, STNode<KeyType, DataType>>(key, data)
{
}

template <typename KeyType, typename DataType>
inline void SplayTree<KeyType, DataType>::rotateLeft(STNode<KeyType, DataType>* x)
{
	if (!x || !x->right) {
		return;
	}

	STNode<KeyType, DataType>* y = x->right;
	x->right = y->left;
	if (y->left) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (!x->parent) {
		this->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

template <typename KeyType, typename DataType>
inline void SplayTree<KeyType, DataType>::rotateRight(STNode<KeyType, DataType>* y)
{
	if (!y || !y->left) {
		return;
	}

	STNode<KeyType, DataType>* x = y->left;
	y->left = x->right;
	if (x->right) {
		x->right->parent = y;
	}
	x->parent = y->parent;
	if (!y->parent) {
		this->root = x;
	}
	else if (y == y->parent->right) {
		y->parent->right = x;
	}
	else {
		y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
}

template <typename KeyType, typename DataType>
inline void SplayTree<KeyType, DataType>::splay(STNode<KeyType, DataType>* x)
{
	if (!x) {
		throw std::invalid_argument("The argument is nullptr.");
	}
	while (x->parent) {
		if (!x->parent->parent) {
			if (x->parent->left == x) {
				rotateRight(x->parent);
			}
			else {
				rotateLeft(x->parent);
			}
		}
		else if (x->parent->left == x && x->parent->parent->left == x->parent) {
			rotateRight(x->parent->parent);
			rotateRight(x->parent);
		}
		else if (x->parent->right == x && x->parent->parent->right == x->parent) {
			rotateLeft(x->parent->parent);
			rotateLeft(x->parent);
		}
		else if (x->parent->left == x && x->parent->parent->right == x->parent) {
			rotateRight(x->parent);
			rotateLeft(x->parent);
		}
		else {
			rotateLeft(x->parent);
			rotateRight(x->parent);
		}
	}
}

/*!
 * Combine trees tree1 and tree2 into a single tree containing all items from both trees and return
 * the resulting tree. This operation assumes that all items in tree1 are less than all those in tree2
 * and destroys both tree1 and tree2.
 *
 * As rotateLeft and rotateRight, used in the splay member function, change this->root
 * the join member function changes this->root and as a result can make the tree nodes of this object unaccesable.
 */
template <typename KeyType, typename DataType>
inline STNode<KeyType, DataType>* SplayTree<KeyType, DataType>::join(STNode<KeyType, DataType>* tree1, STNode<KeyType, DataType>* tree2)
{
	if (!tree1) {
		return tree2;
	}
	if (!tree2) {
		return tree1;
	}
	while (tree1->right) {
		tree1 = tree1->right;
	}
	splay(tree1);
	tree1->right = tree2;
	tree2->parent = tree1;
	return tree1;
}

template <typename KeyType, typename DataType>
inline void SplayTree<KeyType, DataType>::print(const STNode<KeyType, DataType>* tree, std::ostream& out)
{
	if (!tree) {
		return;
	}
	print(tree->left, out);
	out << tree->key << " ";
	print(tree->right, out);
}

template <typename KeyType, typename DataType>
inline void SplayTree<KeyType, DataType>::deleteTreeNode(STNode<KeyType, DataType>* node)
{
	if (!node) {
		return;
	}
	deleteTreeNode(node->left);
	deleteTreeNode(node->right);
	delete node;
}

template <typename KeyType, typename DataType>
inline SplayTree<KeyType, DataType>::SplayTree()
{
}

template <typename KeyType, typename DataType>
inline SplayTree<KeyType, DataType>::~SplayTree()
{
	deleteTreeNode(this->root);
}

template <typename KeyType, typename DataType>
inline void SplayTree<KeyType, DataType>::insert(KeyType key, DataType* data)
{
	// The splay tree takes ownership of z.
	STNode<KeyType, DataType>* z = new STNode<KeyType, DataType>(key, data);
	STNode<KeyType, DataType>* x = this->root;
	STNode<KeyType, DataType>* y = nullptr;
	while (x) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	z->parent = y;
	if (!y) {
		this->root = z;
	}
	else if (z->key < y->key) {
		y->left = z;
	}
	else {
		y->right = z;
	}
	splay(z);
}

template <typename KeyType, typename DataType>
inline void SplayTree<KeyType, DataType>::remove(KeyType key)
{
	STNode<KeyType, DataType>* node = search(key);
	if (!node) {
		return;
	}
	if (node->left) {
		node->left->parent = nullptr;
	}
	if (node->right) {
		node->right->parent = nullptr;
	}
	this->root = join(node->left, node->right);
	delete node;
}

template <typename KeyType, typename DataType>
inline STNode<KeyType, DataType>* SplayTree<KeyType, DataType>::search(KeyType key)
{
	STNode<KeyType, DataType>* x = this->root;
	STNode<KeyType, DataType>* y = nullptr;
	while (x) {
		y = x;
		if (key == x->key) {
			splay(x);
			return x;
		}
		else if (key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	if (y) {
		splay(y);
	}
	return nullptr;
}

template <typename KeyType, typename DataType>
inline void SplayTree<KeyType, DataType>::print(std::ostream& out)
{
	print(this->root, out);
	out << std::endl;
}

template <typename KeyType, typename DataType>
inline void SplayTree<KeyType, DataType>::clear()
{
	deleteTreeNode(this->root);
	this->root = nullptr;
}

template <typename KeyType, typename DataType>
inline STNode<KeyType, DataType>* SplayTree<KeyType, DataType>::getRoot()
{
	return this->root;
}
