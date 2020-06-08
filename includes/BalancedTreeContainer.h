#pragma once

#include "MapContainer.h"

template <typename KeyType, typename DataType>
class TreeAbstractFactory {
public:
	BinarySearchTree<KeyType, DataType>* createAVLTree() const {
		return new AVLTree<KeyType, DataType>;
	}
	BinarySearchTree<KeyType, DataType>* createSplayTree() const {
		return new SplayTree<KeyType, DataType>;
	}
	BinarySearchTree<KeyType, DataType>* createRBTree() const {
		return new RedBlackTree<KeyType, DataType>;
	}
};

template <typename KeyType, typename DataType>
class BalancedTreeContainer : public Container<KeyType, DataType> {
public:
	BinarySearchTree<KeyType, DataType>* tree;
	// TODO: ENUM!!
	BalancedTreeContainer(int index) {
		TreeAbstractFactory<KeyType, DataType> factory;
		switch (index)
		{
		case 0:
			this->tree = factory.createAVLTree();
			break;
		case 1:
			this->tree = factory.createSplayTree();
			break;
		case 2:
			this->tree = factory.createRBTree();
			break;
		default:
			throw std::string("Invalid parament");
		}
	}
	
	bool setValue(KeyType key, DataType* newData) override;
	DataType* getValue(KeyType key) override;
	void addValue(KeyType key, DataType* data) override;
	void remove(KeyType key) override;
	//std::vector<KeyType> getAllKeys();
	//std::vector<DataType*> getAllValues();
	//std::vector<std::pair<KeyType, DataType*>> getKeyValuesPairs();
};

template<typename KeyType, typename DataType>
inline bool BalancedTreeContainer<KeyType, DataType>::setValue(KeyType key, DataType* newData)
{
	if (newData == nullptr) return false;

	if (this->tree->search(key) != nullptr) {
		this->tree->remove(key);
		this->tree->insert(key, newData);
		return true;
	}

	return false;
}

template<typename KeyType, typename DataType>
inline DataType* BalancedTreeContainer<KeyType, DataType>::getValue(KeyType key)
{
	return this->tree->search(key)->data;
}

template<typename KeyType, typename DataType>
inline void BalancedTreeContainer<KeyType, DataType>::addValue(KeyType key, DataType* data)
{
	this->tree->insert(key, data);
}

template<typename KeyType, typename DataType>
inline void BalancedTreeContainer<KeyType, DataType>::remove(KeyType key)
{
	this->tree->remove(key);
}
