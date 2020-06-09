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
#include <utility>

enum class HashTableType { SeparateChaining, LinearProbing };
enum class BalancedTreeType { RedBlack, Splay };

template <typename KeyType, typename DataType>
class Set {
public:
	virtual void insert(KeyType key, DataType* data) = 0;
	virtual bool contains(KeyType key) = 0;
	virtual void remove(KeyType key) = 0;

	virtual std::vector<KeyType> getAllKeys() = 0;
	virtual std::vector<DataType*> getAllData() = 0;
	virtual std::vector<std::pair<KeyType, DataType*>> getAllKeysData() = 0;

};

template <typename KeyType, typename DataType>
class HashTableSet : public Set<KeyType, DataType> {
private:
	HashTable<KeyType, DataType>* table;

public:
	HashTableSet(HashTableType type, std::size_t size) {
		switch (type) {
		case HashTableType::SeparateChaining:
			this->table = new SeparateChainingTable<KeyType, DataType>{ size };
			break;

		case HashTableType::LinearProbing:
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

	std::vector<KeyType> getAllKeys() override { return table->getAllKeys(); }
	std::vector<DataType*> getAllData() override { return table->getAllData(); }
	std::vector<std::pair<KeyType, DataType*>> getAllKeysData() override { return table->getAllKeysData(); }

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

	std::vector<KeyType> getAllKeys() override { return list->getAllKeys(); }
	std::vector<DataType*> getAllData() override { return list->getAllData(); }
	std::vector<std::pair<KeyType, DataType*>> getAllKeysData() override { return list->getAllKeysData(); }

};

template <typename KeyType, typename DataType>
class BalancedTreeSet : public Set<KeyType, DataType> {
private:
	BinarySearchTree<KeyType, DataType>* tree;

public:
	BalancedTreeSet(BalancedTreeType type) {
		switch (type) {
		case BalancedTreeType::RedBlack:
			this->tree = new RedBlackTree<KeyType, DataType>;
			break;

		case BalancedTreeType::Splay:
			this->tree = new SplayTree<KeyType, DataType>;
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

	std::vector<KeyType> getAllKeys() override { return tree->getAllKeys(); }
	std::vector<DataType*> getAllData() override { return tree->getAllData(); }
	std::vector<std::pair<KeyType, DataType*>> getAllKeysData() override { return tree->getAllKeysData(); }

};
