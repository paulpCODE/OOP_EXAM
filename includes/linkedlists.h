#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>

using std::pair;
using std::vector;

template <class KeyT,class ValueT>
class Node {
public:
    KeyT key;
    ValueT *value;
    Node *next;
    Node *prev;
};

template <class KeyT,class ValueT>
class AbstractList{

public:



};

template <class KeyT,class ValueT>
class DoubleLinkedList:public AbstractList<KeyT,ValueT>
{
private:

public:
    DoubleLinkedList();
    ~DoubleLinkedList();

};

