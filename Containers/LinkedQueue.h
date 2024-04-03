#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include <iostream>
#include "Node.h"
#include "QueueADT.h"

template <typename T>
class LinkedQueue : public QueueADT<T>
{
protected:
    Node<T>* backPtr;
    Node<T>* frontPtr;
    int itemCount;
public:
    LinkedQueue();
    bool isEmpty() const;
    bool enqueue(const T& newEntry);
    bool dequeue(T& frontEntry);
    bool peek(T& frontEntry)  const;
    void printList() const;
    int getCount() const;
    ~LinkedQueue();
};

template <typename T>
LinkedQueue<T>::LinkedQueue() :itemCount(0), backPtr(nullptr), frontPtr(nullptr)
{ }

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
    return (frontPtr == nullptr);
}

template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
    Node<T>* newNodePtr = new Node<T>(newEntry);
    // Insert the new node
    if (isEmpty())	//special case if this is the first node to insert
        frontPtr = newNodePtr; // The queue is empty
    else
    {
        backPtr->setNext(newNodePtr); // The queue was not empty
        newNodePtr->setPrev(backPtr);
    }

    backPtr = newNodePtr; // New node is the last node now
    itemCount++;
    return true;
}

template <typename T>
bool LinkedQueue<T>::dequeue(T& frontEntry)
{
    if (isEmpty())
        return false;

    Node<T>* nodeToDeletePtr = frontPtr;
    frontEntry = frontPtr->getItem();
    frontPtr = frontPtr->getNext();

    if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
        backPtr = nullptr;
    else
        frontPtr->setPrev(nullptr);

    // Free memory reserved for the dequeued node
    delete nodeToDeletePtr;

    itemCount--;
    return true;
}

template <typename T>
bool LinkedQueue<T>::peek(T& frontEntry) const
{
    if (isEmpty())
        return false;

    frontEntry = frontPtr->getItem();
    return true;
}

template<typename T>
inline void LinkedQueue<T>::printList() const
{
    if (isEmpty()) return;

    Node<T>* currentPtr = frontPtr;
    while (currentPtr)
    {
        std::cout << currentPtr->getItem();
        if (currentPtr != backPtr)
            std::cout << ", ";
        currentPtr = currentPtr->getNext();
    }
    std::cout << std::endl;
}

template<typename T>
inline int LinkedQueue<T>::getCount() const
{
    return itemCount;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    T temp;
    while (dequeue(temp));
}

#endif