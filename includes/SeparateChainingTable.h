#pragma once

#include "HashNode.h"
#include "HashTable.h"
#include "HashFunction.h"
#include <vector>
#include <list>
#include <cstddef>
#include <stdexcept>

template <typename KeyType, typename DataType>
class SeparateChainingTable : public HashTable<KeyType, DataType> {
private:
	std::vector<std::list<HashNode<KeyType, DataType>>> buckets;
	HashFunction hashFunction;

public:
	SeparateChainingTable(std::size_t capacity);

	void insert(KeyType key, DataType* data) override;
	bool set(KeyType key, DataType* newData) override;
	DataType* search(KeyType key) override;
	bool remove(KeyType key) override;	
	void clear() override;

};

template<typename KeyType, typename DataType>
inline SeparateChainingTable<KeyType, DataType>::SeparateChainingTable(std::size_t capacity) :
	HashTable<KeyType, DataType>(capacity), buckets(capacity), hashFunction(capacity)
{
}

template<typename KeyType, typename DataType>
inline void SeparateChainingTable<KeyType, DataType>::insert(KeyType key, DataType* data)
{
	if (!data) {
		throw std::invalid_argument("The data pointer can not be null pointer.");
	}

	std::size_t index = hashFunction.getHashValue(key);

	for (auto& hashNode : buckets[index]) {
		if (hashNode.key == key) {
			hashNode.data = data;
			return;
		}
	}
	buckets[index].emplace_back(key, data);
}

template<typename KeyType, typename DataType>
inline bool SeparateChainingTable<KeyType, DataType>::set(KeyType key, DataType* newData)
{
	if (!newData) {
		throw std::invalid_argument("The data pointer can not be null pointer.");
	}

	std::size_t index = hashFunction.getHashValue(key);

	for (auto& hashNode : buckets[index]) {
		if (hashNode.key == key) {
			hashNode.data = newData;
			return true;
		}
	}
	return false;
}

template<typename KeyType, typename DataType>
inline DataType* SeparateChainingTable<KeyType, DataType>::search(KeyType key)
{
	std::size_t index = hashFunction.getHashValue(key);

	for (auto& hashNode : buckets[index]) {
		if (hashNode.key == key) {
			return hashNode.data;
		}
	}
	return nullptr;
}

template<typename KeyType, typename DataType>
inline bool SeparateChainingTable<KeyType, DataType>::remove(KeyType key)
{
	std::size_t index = hashFunction.getHashValue(key);
	auto& bucket = buckets[index];

	for (auto it = bucket.begin(); it != bucket.end(); it++) {
		if (it->key == key) {
			bucket.erase(it);
			return true;
		}
	}
	return false;
}

template<typename KeyType, typename DataType>
inline void SeparateChainingTable<KeyType, DataType>::clear()
{
	buckets.clear();
	buckets.resize(capacity);
}
