#pragma once

#include "MapContainer.h"

template <typename KeyType, typename DataType>
class LinkedListAbstractFactory {
public:
	AbstractList<KeyType, DataType>* createSingularLinkedList() const {
		return new Linked_List<KeyType, DataType>;
	}
	AbstractList<KeyType, DataType>* createDoubleLinkedList() const {
		return new Linked_List<KeyType, DataType>;
	}
};

template <typename KeyType, typename DataType>
class LinkedListContainer : public Container<KeyType, DataType> {
public:
	AbstractList<KeyType, DataType>* list;

	LinkedListContainer(int index = 0) {
		LinkedListAbstractFactory<KeyType, DataType> factory;
		switch (index)
		{
		case 0:
			this->list = factory.createSingularLinkedList();
			break;
		case 1:
			this->list = factory.createDoubleLinkedList();
			break;
		default:
			throw std::string("Invalid parament");
		}
	}

	bool setValue(KeyType key, DataType* newData);
	DataType* getValue(KeyType key);
	void addValue(KeyType key, DataType* data);
	void remove(KeyType key);
	std::vector<KeyType> getAllKeys();
	std::vector<DataType*> getAllData();
	std::vector<std::pair<KeyType, DataType*>> getAllKeysData();
};

template<typename KeyType, typename DataType>
inline bool LinkedListContainer<KeyType, DataType>::setValue(KeyType key, DataType* newData)
{
	for (int i = 0; i < list->GetSize(); i++) {
		if (list->getNode(i)->key == key) {
			list->getNode(i)->value = newData;
			return true;
		}
	}
	return false;
}

template<typename KeyType, typename DataType>
inline DataType* LinkedListContainer<KeyType, DataType>::getValue(KeyType key)
{
	for (int i = 0; i < list->GetSize(); i++) {
		if (list->getNode(i)->key == key) {
			return list->getNode(i)->value;
		}
	}
	return nullptr;
}

template<typename KeyType, typename DataType>
inline void LinkedListContainer<KeyType, DataType>::addValue(KeyType key, DataType* data)
{
	this->list->push_back(key, data);
}

template<typename KeyType, typename DataType>
inline void LinkedListContainer<KeyType, DataType>::remove(KeyType key)
{
	for (int i = 0; i < list->GetSize(); i++) {
		if (list->getNode(i)->key == key) {
			list->removeAt(i);
		}
	}
}

template<typename KeyType, typename DataType>
inline std::vector<KeyType> LinkedListContainer<KeyType, DataType>::getAllKeys()
{
	return list->getAllKeys();
}

template<typename KeyType, typename DataType>
inline std::vector<DataType*> LinkedListContainer<KeyType, DataType>::getAllData()
{
	return list->getAllData();
}

template<typename KeyType, typename DataType>
inline std::vector<std::pair<KeyType, DataType*>> LinkedListContainer<KeyType, DataType>::getAllKeysData()
{
	return list->getAllKeysData();
}
