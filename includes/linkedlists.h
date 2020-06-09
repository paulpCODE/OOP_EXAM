#pragma once

#include "Iterator.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>

using std::pair;
using std::vector;

template <class KeyT,class ValueT>
class Node {
public:
    KeyT key;
    ValueT *value;
    Node *pNext;
    Node():key(KeyT{}),value(nullptr),pNext(nullptr){}
    Node(KeyT newKey, ValueT *newValue, Node *newPNext = nullptr):key(newKey),value(newValue),pNext(newPNext){}

    // DO WE NEED DEEP COPY?
//    // assumes data is initialized
//    void deepCopy(const Node& source)
//    {
//        // first we need to deallocate any value that we are holding!
//        delete value;
//        delete pNext;

//        // because key is not a pointer, we can shallow copy it
//        key = source.key;


//        // value and pNext are pointers, so we need to deep copy it if it is non-null

//        // value
//        if (source.value)
//        {
//            // allocate memory for our copy
//            value = new ValueT();

//            // do the copy
//            value = source.value;
//        }
//        else
//            value = nullptr;

//        // pNext
//        if (source.pNext)
//        {
//            // allocate memory for our copy
//            pNext = new Node();

//            // do the copy
//            pNext = source.pNext;
//        }
//        else
//            pNext = nullptr;

//    }

//    // Copy constructor
//    Node(const Node& source)
//    {
//        deepCopy(source);
//    }
//    // Assignment operator
//   Node &operator=(const Node & source)
//    {
//        // check for self-assignment
//        if (this == &source)
//            return *this;

//        // now do the deep copy
//        deepCopy(source);

//        return *this;
//    }
};

template <typename KeyType, typename DataType>
class ListIterator : public Iterator<Node<KeyType, DataType>, ListIterator<KeyType, DataType>> {
public:
    ListIterator(Node<KeyType, DataType>* current)
        : Iterator<Node<KeyType, DataType>, ListIterator<KeyType, DataType>>(current) {}

    ListIterator<KeyType, DataType>& operator++() override {
        current = current->pNext;
        return *this;
    }

    bool operator!=(const ListIterator<KeyType, DataType>& other) override {
        return (this->current != other.current);
    }

};

template <class KeyT,class ValueT, class IteratorType = ListIterator<KeyT, ValueT>>
class AbstractList{

public:
    virtual void pop_front() = 0;

    virtual void push_back(KeyT key,ValueT* value) = 0;

    virtual void clear() = 0;

    virtual int GetSize() = 0;

    // RETURNS POINTER ? review requested Timur plz
    virtual ValueT* & operator[](const int index) = 0;

    virtual void push_front(KeyT key,ValueT* value) = 0;

    virtual void insert(KeyT key,ValueT* value, int index) = 0;

    virtual void removeAt(int index) = 0;

    virtual void pop_back() = 0;

    /** Searches for the value associated with the key 'key'.
     * Returns the NOT null pointer to value if the search is successful.
     * Otherwise, returns null pointer.
     */
    virtual ValueT* search(KeyT key) = 0;
    virtual void remove(KeyT key) = 0;

    virtual IteratorType begin() = 0;
    virtual IteratorType end() = 0;

    virtual std::vector<KeyT> getAllKeys() = 0;
    virtual std::vector<ValueT*> getAllData() = 0;
    virtual std::vector<std::pair<KeyT, ValueT*>> getAllKeysData() = 0;

};

template<class KeyT , class ValueT >
class Linked_List : public AbstractList<KeyT,ValueT>
{
public:
    Linked_List() ;
    Linked_List(const vector<std::pair<KeyT, ValueT>> &nodes) ;
    ~Linked_List() {
        clear();
    }
    void pop_front() override ;
    void push_back(KeyT key,ValueT* value) override ;
    void clear() override ;
    int GetSize() override { return Size; }
    ValueT* & operator[](const int index) override;
    void push_front(KeyT key,ValueT* value) override ;
    void insert(KeyT key,ValueT* value, int index) override ;
    void removeAt(int index) override ;
    void pop_back() override;
    ValueT* search(KeyT key) override;
    void remove(KeyT key) override;

    ListIterator<KeyT, ValueT> begin() override {
        return ListIterator<KeyT, ValueT>{this->head};
    }

    ListIterator<KeyT, ValueT> end() override {
        return ListIterator<KeyT, ValueT>{nullptr};
    }

    std::vector<KeyT> getAllKeys() override {
        std::vector<KeyT> keys;
        for (auto& item : *this) {
            keys.push_back(item.key);
        }
        return keys;
    }

    std::vector<ValueT*> getAllData() override {
        std::vector<ValueT*> data;
        for (auto& item : *this) {
            data.push_back(item.value);
        }
        return data;
    }

    std::vector<std::pair<KeyT, ValueT*>> getAllKeysData() override {
        std::vector<std::pair<KeyT, ValueT*>> pairs;
        for (auto& pair : *this) {
            pairs.emplace_back(std::pair<KeyT, ValueT*>{pair.key, pair.value});
        }
        return pairs;
    }

private:
    int Size;
    Node<KeyT, ValueT> *head;
};

template <class KeyT,class ValueT>
Linked_List<KeyT,ValueT>::Linked_List()
{
    Size = 0;
    head = nullptr;
}

template <class KeyT,class ValueT>
Linked_List<KeyT,ValueT>::Linked_List(const vector<std::pair<KeyT, ValueT>> &nodes)
{
    for (int i = 0; i < nodes.size(); i++) {
        this->push_back(nodes[i].first,nodes[i].second);
    }
}

template <class KeyT,class ValueT>
void Linked_List<KeyT,ValueT>::pop_front()
{
    Node<KeyT,ValueT> *temp = head;

    head = head->pNext;

    delete temp;

    Size--;

}

template <class KeyT,class ValueT>
void Linked_List<KeyT,ValueT>::push_back(KeyT key,ValueT* value)
{
    if (head == nullptr)
    {
        head = new Node<KeyT,ValueT>(key,value);
    }
    else
    {
        Node<KeyT,ValueT> *current = this->head;

        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pNext = new Node<KeyT,ValueT>(key,value);

    }
    Size++;
}

template <class KeyT,class ValueT>
void Linked_List<KeyT,ValueT>::clear()
{
    while (Size)
    {
        pop_front();
    }
}


template<class KeyT, class ValueT>
ValueT* & Linked_List<KeyT,ValueT>::operator[](const int index)
{
    int counter = 0;

    Node<KeyT,ValueT> *current = this->head;

    while (current != nullptr)
    {
        if (counter == index)
        {
            return current->value;
        }
        current = current->pNext;
        counter++;
    }
}

template <class KeyT,class ValueT>
void Linked_List<KeyT,ValueT>::push_front(KeyT key,ValueT* value)
{
    head = new Node<KeyT,ValueT>(key,value, head);
    Size++;
}
template <class KeyT,class ValueT>
void Linked_List<KeyT,ValueT>::insert(KeyT key,ValueT* value, int index)
{
    if (index == 0)
    {
        push_front(key,value);
    }
    else
    {
        Node<KeyT,ValueT> *previous = this->head;

        for (int i = 0; i < index - 1; i++)
        {
            previous = previous->pNext;
        }

        Node<KeyT,ValueT> *newNode = new Node<KeyT,ValueT>(key,value, previous->pNext);

        previous->pNext = newNode;

        Size++;
    }
}

template <class KeyT,class ValueT>
void Linked_List<KeyT,ValueT>::removeAt(int index)
{
    if (index == 0)
    {
        pop_front();
    }
    else
    {
        Node<KeyT, ValueT> *previous = this->head;
        for (int i = 0; i < index - 1; i++)
        {
            previous = previous->pNext;
        }


        Node<KeyT, ValueT> *toDelete = previous->pNext;

        previous->pNext = toDelete->pNext;

        delete toDelete;

        Size--;
    }

}

template <class KeyT,class ValueT>
void Linked_List<KeyT,ValueT>::pop_back()
{
    removeAt(Size - 1);
}

template<class KeyT, class ValueT>
inline ValueT* Linked_List<KeyT, ValueT>::search(KeyT key)
{
    Node<KeyT, ValueT>* current = this->head;
    while (current) {
        if (current->key == key) {
            return current->value;
        }

        current = current->pNext;
    }
    return nullptr;
}

template<class KeyT, class ValueT>
inline void Linked_List<KeyT, ValueT>::remove(KeyT key)
{
    int index = 0;
    Node<KeyT, ValueT>* current = this->head;  

    while (current) {
        if (current->key == key) {
            removeAt(index);
            return;
        }

        index++;
        current = current->pNext;
    }

}

