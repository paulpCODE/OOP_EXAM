#include "includes/linkedlists.h"


template<class KeyT, class ValueT>
DoubleLinkedList<KeyT,ValueT>::DoubleLinkedList()
{
    m_pHeadNode = new Node<KeyT,ValueT>();
    m_pTailNode = new Node<KeyT,ValueT>();

    m_pHeadNode->pNext = m_pTailNode;
    m_pHeadNode->pPrev = nullptr;

    m_pTailNode->pNext = nullptr;
    m_pTailNode->pPrev = m_pHeadNode;

    m_NodeSize = 0;
}

template<class KeyT, class ValueT>
DoubleLinkedList<KeyT,ValueT>::~DoubleLinkedList()
{
    m_pHeadNode->pNext = nullptr;
    m_pHeadNode->pPrev = nullptr;

    m_pTailNode->pNext = nullptr;
    m_pTailNode->pPrev = nullptr;

    if (m_pHeadNode)
    {
        delete m_pHeadNode;
        m_pHeadNode = nullptr;
    }

    if (m_pTailNode)
    {
        delete m_pTailNode;
        m_pTailNode = nullptr;
    }

    m_NodeSize = 0;
}

template<class KeyT, class ValueT>
bool DoubleLinkedList<KeyT,ValueT>::empty()
{
    if ((m_pTailNode == m_pHeadNode->pNext) && (m_pHeadNode == m_pTailNode->pPrev))
    {
        return true;
    }
    return false;
}

template<class KeyT, class ValueT>
size_t DoubleLinkedList<KeyT,ValueT>::size()
{
    return m_NodeSize;
}

template<class KeyT, class ValueT>
void DoubleLinkedList<KeyT,ValueT>::clear()
{
    m_NodeSize = 0;
    if (empty())  return;

    for (Iterator<KeyT,ValueT> it = this->begin(); it != this->end(); ++it)
    {
        Node<KeyT,ValueT>* pCurrentNode = it.node();
        delete pCurrentNode;
        pCurrentNode = nullptr;
    }

    m_pHeadNode->pNext = m_pTailNode;
    m_pTailNode->pPrev = m_pHeadNode;
}

template<class KeyT, class ValueT>
void DoubleLinkedList<KeyT,ValueT>::push_back(const Node<KeyT, ValueT> & value)
{
    Iterator<KeyT,ValueT> iter(m_pTailNode);
    InsertNodeBeforePosition(value, iter);
}

template<class KeyT, class ValueT>
void DoubleLinkedList<KeyT,ValueT>::push_front(const Node<KeyT, ValueT> & value )
{
    Iterator<KeyT,ValueT> iter(m_pHeadNode->pNext);
    InsertNodeBeforePosition(value, iter);
}

template<class KeyT, class ValueT>
void DoubleLinkedList<KeyT,ValueT>::InsertNodeBeforePosition(const ValueT &value, const Iterator<KeyT, ValueT> &position)
{
    Node<KeyT,ValueT> *pNewNode = new Node<KeyT,ValueT>();
    Node<KeyT,ValueT> *pCurNode = position.node();

    pNewNode->pNext = pCurNode;
    pNewNode->pPrev = pCurNode->pPrev;
    pCurNode->pPrev = pNewNode;
    pNewNode->pPrev->pNext = pNewNode;

    pNewNode->value = value;
    //setKey

    ++m_NodeSize;
}
