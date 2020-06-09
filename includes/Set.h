#pragma once

#include "Iterator.h"
#include "HashTable.h"
#include "SeparateChainingTable.h"
#include "LinearProbingTable.h"
#include "linkedlists.h"
#include "BinarySearchTree.h"
#include "RedBlackTree.h"
#include "SplayTree.h"
#include "AVLTree.h"
#include <cstddef>
#include <vector>
#include "enumerations.h"
//enum class HashTableType { SeparateChaining, LinearProbing };
//enum class BalancedTreeType { RedBlack, Splay, AVL };


template <typename KeyType, typename DataType>
class Set{
public:
	virtual void insert(KeyType key, DataType* data) = 0;
	virtual bool contains(KeyType key) = 0;
	virtual void remove(KeyType key) = 0;

	//virtual std::vector<KeyType> getAllKeys() = 0;
	//virtual std::vector<DataType*> getAllData() = 0;

	//static Set<KeyType, DataType> union(Set<KeyType, DataType> s1, Set<KeyType, DataType> s2);
};

template <typename KeyType, typename DataType>
class HashTableSet : public Set<KeyType, DataType> {
private:
	HashTable<KeyType, DataType>* table;

public:
    HashTableSet(HashTableTypeClass::HashTableType type, std::size_t size) {
		switch (type) {
        case HashTableTypeClass::HashTableType::SeparateChaining:
			this->table = new SeparateChainingTable<KeyType, DataType>{ size };
			break;

        case HashTableTypeClass::HashTableType::LinearProbing:
			this->table = new LinearProbingTable<KeyType, DataType>{ (int)size };
			break;

		default:
			this->table = new SeparateChainingTable<KeyType, DataType>{ size };
			break;
		}
	}

	~HashTableSet() { delete this->table; }
	void insert(KeyType key, DataType* data) override { table->insert(key, data); }
	bool contains(KeyType key) override { return table->search(key); }
	void remove(KeyType key) override { table->remove(key); }

};

template <typename KeyType, typename DataType>
class LinkedListSet : public Set<KeyType, DataType> {
private:
	AbstractList<KeyType, DataType>* list;

public:
	LinkedListSet() : list{ new Linked_List<KeyType, DataType> } {}

	~LinkedListSet() { delete this->list; }
	void insert(KeyType key, DataType* data) override { list->push_back(key, data); }
	bool contains(KeyType key) override { return list->search(key); }
	void remove(KeyType key) override { list->remove(key); }

};

template <typename KeyType, typename DataType>
class BalancedTreeSet : public Set<KeyType, DataType> {
private:
	BinarySearchTree<KeyType, DataType>* tree;

public:
    BalancedTreeSet(BalancedTreeTypeClass::BalancedTreeType type) {
		switch (type) {
        case BalancedTreeTypeClass::BalancedTreeType::RedBlack:
			this->tree = new RedBlackTree<KeyType, DataType>;
			break;

        case BalancedTreeTypeClass::BalancedTreeType::Splay:
			this->tree = new SplayTree<KeyType, DataType>;
			break;

        case BalancedTreeTypeClass::BalancedTreeType::AVL:
			this->tree = new AVLTree<KeyType, DataType>;
			break;

		default:
			this->tree = new RedBlackTree<KeyType, DataType>;
			break;
		}
	}

	~BalancedTreeSet() { delete this->tree; }
	void insert(KeyType key, DataType* data) override { tree->insert(key, data); }
	bool contains(KeyType key) override { return tree->search(key); }
	void remove(KeyType key) override { tree->remove(key); }

};
