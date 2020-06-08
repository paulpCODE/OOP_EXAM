#pragma once

template <typename KeyType, typename DataType>
class HashNode {
public:
	KeyType key;
	DataType* data{ nullptr };

	HashNode() {}
	HashNode(KeyType key, DataType* data) : key{ key }, data{ data } {}

};
