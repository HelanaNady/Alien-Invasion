#ifndef DEQUE_H
#define DEQUE_H

#include "LinkedQueue.h"

template <typename T>
class Deque: public LinkedQueue<T>
{
public:
    bool dequeueBack(T& backEntry);
    bool peekBack(T& backEntry);
    bool enqueueFront(const T& newEntry);
};

template<typename T>
inline bool Deque<T>::dequeueBack(T& backEntry)
{
    if (LinkedQueue<T>::isEmpty())
        return false;

    Node<T>* nodeToDeletePtr = LinkedQueue<T>::backPtr;
    Node<T>*& front = LinkedQueue<T>::frontPtr;
    Node<T>*& back = LinkedQueue<T>::backPtr;

    backEntry = back->getItem();
    back = back->getPrev();

    if (nodeToDeletePtr == front)
        front = nullptr;
    else
        back->setNext(nullptr);

    delete nodeToDeletePtr;
    LinkedQueue<T>::itemCount--;
    return true;
}

template<typename T>
inline bool Deque<T>::peekBack(T& backEntry)
{
    if (LinkedQueue<T>::isEmpty())
        return false;

    backEntry = LinkedQueue<T>::backPtr->getItem();
    return true;
}

template<typename T>
inline bool Deque<T>::enqueueFront(const T& newEntry)
{
    Node<T>* newNodePtr = new Node<T>(newEntry);

    Node<T>*& front = LinkedQueue<T>::frontPtr;
    Node<T>*& back = LinkedQueue<T>::backPtr;

    if (LinkedQueue<T>::isEmpty())
        back = newNodePtr;
    else
    {
        newNodePtr->setNext(front);
        front->setPrev(newNodePtr);
    }

    front = newNodePtr;

    LinkedQueue<T>::itemCount++;

    return true;
}

#endif

