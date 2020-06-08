#pragma once

#include "TreeNode.h"
#include "BinarySearchTree.h"
#include <iostream>
#include <stdexcept>

enum Color {
	COLOR_RED,
	COLOR_BLACK
};

// Red-black tree node
template <typename KeyType, typename DataType>
class RBTreeNode : public BinaryTreeNode<KeyType, DataType, RBTreeNode<KeyType, DataType>> {
public:
	Color color;

	RBTreeNode(KeyType key, DataType* data);
};

template<typename KeyType, typename DataType>
inline RBTreeNode<KeyType, DataType>::RBTreeNode(KeyType key, DataType* data) : 
	BinaryTreeNode<KeyType, DataType, RBTreeNode<KeyType, DataType>>(key, data),
	color(COLOR_RED)
{
}

template <typename KeyType, typename DataType>
class RedBlackTree : public BinarySearchTree<KeyType, DataType, RBTreeNode<KeyType, DataType>>
{
private:
	void fixup(RBTreeNode<KeyType, DataType>* z);
	void rotateLeft(RBTreeNode<KeyType, DataType>* x);
	void rotateRight(RBTreeNode<KeyType, DataType>* y);

	void remove(RBTreeNode<KeyType, DataType>* z);
	void removeFixup(RBTreeNode<KeyType, DataType>* x);

	//! Prints the tree according to the inorder traversal.
	void print(const RBTreeNode<KeyType, DataType>* tree, std::ostream& out);
	void deleteRBTreeNode(RBTreeNode<KeyType, DataType>* node);

public:
	RedBlackTree();
	~RedBlackTree();

	//! Inserts the key 'key' into the tree.
	void insert(KeyType key, DataType* data) override;
	//! Deletes the node with the key 'key'.
	void remove(KeyType key) override;
	//! Returns the pointer to the node with the key 'key'.
	RBTreeNode<KeyType, DataType>* search(KeyType key) override;
	//! Returns the pointer to the root.
	RBTreeNode<KeyType, DataType>* getRoot() override;

	//! Prints the tree according to the inorder traversal.
	void print(std::ostream& out = std::cout);
	//! Deletes (free the memory) all nodes.
	void clear() override;

};

template <typename KeyType, typename DataType>
inline void RedBlackTree<KeyType, DataType>::fixup(RBTreeNode<KeyType, DataType>* z)
{
	if (!z) {
		throw std::invalid_argument("The argument z is nullptr.");
	}
	while (z->parent && z->parent->color == COLOR_RED) {
		if (z->parent == z->parent->parent->left) {
			RBTreeNode<KeyType, DataType>* y = z->parent->parent->right;
			if (y && y->color == COLOR_RED) {
				z->parent->color = Color::COLOR_BLACK;
				y->color = COLOR_BLACK;
				z->parent->parent->color = COLOR_RED;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					rotateLeft(z);
				}
				z->parent->color = COLOR_BLACK;
				z->parent->parent->color = COLOR_RED;
				rotateRight(z->parent->parent);
			}
		}
		else {
			RBTreeNode<KeyType, DataType>* y = z->parent->parent->left;
			if (y && y->color == COLOR_RED) {
				z->parent->color = COLOR_BLACK;
				y->color = COLOR_BLACK;
				z->parent->parent->color = COLOR_RED;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					rotateRight(z);
				}
				z->parent->color = COLOR_BLACK;
				z->parent->parent->color = COLOR_RED;
				rotateLeft(z->parent->parent);
			}
		}
	}
	this->root->color = COLOR_BLACK;
}

template<typename KeyType, typename DataType>
inline void RedBlackTree<KeyType, DataType>::rotateLeft(RBTreeNode<KeyType, DataType>* x)
{
	if (!x || !x->right) {
		return;
	}

	RBTreeNode<KeyType, DataType>* y = x->right;
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

template<typename KeyType, typename DataType>
inline void RedBlackTree<KeyType, DataType>::rotateRight(RBTreeNode<KeyType, DataType>* y)
{
	if (!y || !y->left) {
		return;
	}

	RBTreeNode<KeyType, DataType>* x = y->left;
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

template<typename KeyType, typename DataType>
inline void RedBlackTree<KeyType, DataType>::remove(RBTreeNode<KeyType, DataType>* z)
{
	if (!z) {
		return;
	}

	RBTreeNode<KeyType, DataType>* x = nullptr;
	RBTreeNode<KeyType, DataType>* y = nullptr;
	if (!z->left || !z->right) {
		y = z;
	}
	else {
		y = z->right;
		while (y->left) {
			y = y->left;
		}
	}

	if (y->left) {
		x = y->left;
	}
	else {
		x = y->right;
	}

	if (x) {
		x->parent = y->parent;
	}

	if (y->parent) {
		if (y == y->parent->left) {
			y->parent->left = x;
		}
		else {
			y->parent->right = x;
		}
	}
	else {
		this->root = x;
	}

	if (y != z) {
		z->key = y->key;
	}

	if (y->color == COLOR_BLACK) {
		removeFixup(x);
	}

	delete y;
}

template<typename KeyType, typename DataType>
inline void RedBlackTree<KeyType, DataType>::removeFixup(RBTreeNode<KeyType, DataType>* x)
{
	if (!x) {
		return;
	}

	while ((x != this->root) && (x->color == COLOR_BLACK)) {
		if (x == x->parent->left) {
			RBTreeNode<KeyType, DataType>* w = x->parent->right;
			if (w->color == COLOR_RED) {
				w->color = COLOR_BLACK;
				x->parent->color = COLOR_RED;
				rotateLeft(x->parent);
				w = x->parent->right;
			}
			if ((w->left->color == COLOR_BLACK) && (w->right->color == COLOR_BLACK)) {
				w->color = COLOR_RED;
				x = x->parent;
			}
			else {
				if (w->right->color == COLOR_BLACK) {
					w->left->color = COLOR_BLACK;
					w->color = COLOR_RED;
					rotateRight(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = COLOR_BLACK;
				w->right->color = COLOR_BLACK;
				rotateLeft(x->parent);
				x = this->root;
			}
		}
		else {
			RBTreeNode<KeyType, DataType>* w = x->parent->left;
			if (w->color == COLOR_RED) {
				w->color = COLOR_BLACK;
				x->parent->color = COLOR_RED;
				rotateRight(x->parent);
				w = x->parent->left;
			}
			if ((w->right->color == COLOR_BLACK) && (w->left->color == COLOR_BLACK)) {
				w->color = COLOR_RED;
				x = x->parent;
			}
			else {
				if (w->left->color == COLOR_BLACK) {
					w->right->color = COLOR_BLACK;
					w->color = COLOR_RED;
					rotateLeft(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = COLOR_BLACK;
				w->left->color = COLOR_BLACK;
				rotateRight(x->parent);
				x = this->root;
			}
		}
	}
	x->color = COLOR_BLACK;
}

template<typename KeyType, typename DataType>
inline void RedBlackTree<KeyType, DataType>::print(const RBTreeNode<KeyType, DataType>* tree, std::ostream& out)
{
	if (!tree) {
		return;
	}
	print(tree->left, out);
	out << tree->key << " ";
	print(tree->right, out);
}

template<typename KeyType, typename DataType>
inline void RedBlackTree<KeyType, DataType>::deleteRBTreeNode(RBTreeNode<KeyType, DataType>* node)
{
	if (!node) {
		return;
	}
	deleteRBTreeNode(node->left);
	deleteRBTreeNode(node->right);
	delete node;
}

template<typename KeyType, typename DataType>
inline RedBlackTree<KeyType, DataType>::RedBlackTree()
{
}

template<typename KeyType, typename DataType>
inline RedBlackTree<KeyType, DataType>::~RedBlackTree()
{
	clear();
}

template<typename KeyType, typename DataType>
inline void RedBlackTree<KeyType, DataType>::insert(KeyType key, DataType* data)
{
	// The red-black tree takes ownership of z.
	RBTreeNode<KeyType, DataType>* z = new RBTreeNode<KeyType, DataType>(key, data);
	RBTreeNode<KeyType, DataType>* x = this->root;
	RBTreeNode<KeyType, DataType>* y = nullptr;
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
	fixup(z);
}

template<typename KeyType, typename DataType>
inline void RedBlackTree<KeyType, DataType>::remove(KeyType key)
{
	RBTreeNode<KeyType, DataType>* foundNode = search(key);
	if (foundNode) {
		remove(foundNode);
	}
}

/*!
 * If the node with the key 'key' exists, returns the not null pointer to that node.
 * Otherwise, returns null pointer.
 */
template<typename KeyType, typename DataType>
inline RBTreeNode<KeyType, DataType>* RedBlackTree<KeyType, DataType>::search(KeyType key)
{
	RBTreeNode<KeyType, DataType>* x = this->root;
	while (x && (key != x->key)) {
		if (key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	return x;
}

/*!
 * If the tree is not empty, returns the not null pointer to the root node.
 * Otherwise, returns null pointer.
 */
template<typename KeyType, typename DataType>
inline RBTreeNode<KeyType, DataType>* RedBlackTree<KeyType, DataType>::getRoot()
{
	return this->root;
}

template<typename KeyType, typename DataType>
inline void RedBlackTree<KeyType, DataType>::print(std::ostream& out)
{
	print(this->root, out);
	out << std::endl;
}

template<typename KeyType, typename DataType>
inline void RedBlackTree<KeyType, DataType>::clear()
{
	deleteRBTreeNode(this->root);
	this->root = nullptr;
}
