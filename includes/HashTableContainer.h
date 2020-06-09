#pragma once

#include "MapContainer.h"

template <typename KeyType, typename DataType>
class HashTableAbstractFactory {
public:
	HashTable<KeyType, DataType>* createSeparateChainingHT(int size) const {
		return new SeparateChainingTable<KeyType, DataType>(size);
	}
	HashTable<KeyType, DataType>* createLinearProbingHT(int size) const {
		return new LinearProbingTable<KeyType, DataType>(size);
	}
};

template <typename KeyType, typename DataType>
class HashTableContainer : public Container<KeyType, DataType> {
public:
	HashTable<KeyType, DataType>* table;

	HashTableContainer(int index, int size) {
		HashTableAbstractFactory<KeyType, DataType> factory;
		switch (index)
		{
		case 0:
			this->table = factory.createLinearProbingHT(size);
			break;
		case 1:
			this->table = factory.createSeparateChainingHT(size);
			break;
		default:
			throw std::string("Invalid parament");
		}
	}


	bool setValue(KeyType key, DataType* newData);
	DataType* getValue(KeyType key);
	void addValue(KeyType key, DataType* data);
	void remove(KeyType key);
	//std::vector<KeyType> getAllKeys();
	std::vector<DataType*> getAllValues();
	std::vector<std::pair<KeyType, DataType*>> getKeyValuesPairs();
};

template<typename KeyType, typename DataType>
inline bool HashTableContainer<KeyType, DataType>::setValue(KeyType key, DataType* newData)
{
	if (table->set(key, newData)) return true;
	return false;
}

template<typename KeyType, typename DataType>
inline DataType* HashTableContainer<KeyType, DataType>::getValue(KeyType key)
{
	return table->search(key);
}

template<typename KeyType, typename DataType>
inline void HashTableContainer<KeyType, DataType>::addValue(KeyType key, DataType* data)
{
	table->insert(key, data);
}

template<typename KeyType, typename DataType>
inline void HashTableContainer<KeyType, DataType>::remove(KeyType key)
{
	this->table->remove(key);
}

//template<typename KeyType, typename DataType>
//inline std::vector<KeyType> HashTableContainer<KeyType, DataType>::getAllKeys()
//{
//	std::vector<KeyType> res;
//
//	for (auto item : table) {
//		res.push_back(item.key);
//	}
//
//	return res;
//}
