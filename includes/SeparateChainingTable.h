#pragma once

#include "Iterator.h"
#include "HashNode.h"
#include "HashTable.h"
#include "HashFunction.h"
#include <vector>
#include <cstddef>
#include <stdexcept>

template <typename KeyType, typename DataType>
class SeparateChainingTable : public HashTable<KeyType, DataType> {

	template <typename KeyType, typename DataType>
	class SeparateChainingIterator : public Iterator<HashNode<KeyType, DataType>, SeparateChainingIterator<KeyType, DataType>> {
	private:
		SeparateChainingTable<KeyType, DataType>& table;
		std::size_t rowIndex;
		std::size_t columnIndex;

	public:
		SeparateChainingIterator(HashNode<KeyType, DataType>* current, SeparateChainingTable<KeyType,DataType>& table,
			std::size_t rowIndex, std::size_t columnIndex)
			: Iterator<HashNode<KeyType, DataType>, SeparateChainingIterator<KeyType, DataType>>(current),
			table{ table }, rowIndex{ rowIndex }, columnIndex{ columnIndex } {}

		SeparateChainingIterator<KeyType, DataType>& operator++() override {
			bool isFirst = false;
			while (rowIndex < table.capacity) {
				if (!isFirst) {
					columnIndex++;
					isFirst = false;
				}
				
				if (columnIndex >= table.buckets[rowIndex].size()) {
					rowIndex++;
					columnIndex = 0;
					isFirst = true;
				}
				else {
					break;
				}
			}

			if (rowIndex >= table.capacity) {
				this->current = nullptr;
			}
			else {
				this->current = &(table.buckets[rowIndex][columnIndex]);
			}

			return *this;
		}

		bool operator!=(const SeparateChainingIterator<KeyType, DataType>& other) override {
			if ((rowIndex >= table.capacity) && (other.rowIndex >= table.capacity)) {
				return false;
			}

			return ((rowIndex != other.rowIndex) || (columnIndex != other.columnIndex));
		}

	};

private:
	std::vector<std::vector<HashNode<KeyType, DataType>>> buckets;
	HashFunction hashFunction;

public:
	SeparateChainingTable(std::size_t capacity);

	void insert(KeyType key, DataType* data) override;
	bool set(KeyType key, DataType* newData) override;
	DataType* search(KeyType key) override;
	bool remove(KeyType key) override;	
	void clear() override;

	SeparateChainingIterator<KeyType, DataType> begin() {
		std::size_t tableSize = buckets.size();
		std::size_t bucketSize = 0;
		for (std::size_t i = 0; i < tableSize; i++) {
			bucketSize = buckets[i].size();
			for (std::size_t j = 0; j < bucketSize; j++) {
				return SeparateChainingIterator<KeyType, DataType> {&buckets[i][j], * this, i, j};
			}
		}

		return SeparateChainingIterator<KeyType, DataType> {nullptr, * this, this->capacity, 0};
	}

	SeparateChainingIterator<KeyType, DataType> end() {
		return SeparateChainingIterator<KeyType, DataType> {nullptr, * this, this->capacity, 0};
	}

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
