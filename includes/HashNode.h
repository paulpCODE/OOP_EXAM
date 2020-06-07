#pragma once

template <typename KeyType, typename DataType>
class HashNode {
public:
	KeyType key;
	DataType* data;

	HashNode(KeyType key, DataType* data) : key{ key }, data{ data } {}

};
