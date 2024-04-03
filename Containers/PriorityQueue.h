#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include "PriorityNode.h"

// This class implements the priority queue as a sorted list (Linked List)
// The item with highest priority is at the front of the queue
template <typename T>
class PriorityQueue
{
private:
    PriorityNode<T>* head;
    int itemCount;

public:
    PriorityQueue();

    void enqueue(const T& data, int priority);
    bool dequeue(T& topEntry, int& pri);
    bool peek(T& topEntry, int& priority);
    bool isEmpty() const;
    void printList() const;
    int getCount() const;

    ~PriorityQueue();
};

template <typename T>
inline PriorityQueue<T>::PriorityQueue(): head(nullptr), itemCount(0)
{ }

// Insert the new node in its correct position according to its priority
template <typename T>
inline void PriorityQueue<T>::enqueue(const T& data, int priority)
{
    PriorityNode<T>* newNode = new PriorityNode<T>(data, priority);

    if (head == nullptr || priority > head->getPriority())
    {
        newNode->setNext(head);
        head = newNode;
        return;
    }

    PriorityNode<T>* current = head;
    while (current->getNext() && priority <= current->getNext()->getPriority())
        current = current->getNext();

    newNode->setNext(current->getNext());
    current->setNext(newNode);
    itemCount++;
}

template <typename T>
inline bool PriorityQueue<T>::dequeue(T& topEntry, int& pri)
{
    if (isEmpty())
        return false;

    topEntry = head->getItem(pri);
    PriorityNode<T>* temp = head;
    head = head->getNext();
    delete temp;

    itemCount--;
    return true;
}

template <typename T>
inline bool PriorityQueue<T>::peek(T& topEntry, int& priority)
{
    if (isEmpty())
        return false;

    topEntry = head->getItem();
    priority = head->getPriority();

    return true;
}

template <typename T>
inline bool PriorityQueue<T>::isEmpty() const
{
    return head == nullptr;
}

template <typename T>
inline void PriorityQueue<T>::printList() const
{
    if (isEmpty()) return;

    PriorityNode<T>* current = head;
    int p = 0;

    while (current)
    {
        std::cout << current->getItem(p);

        if (current->getNext() != nullptr)
            std::cout << ", ";

        current = current->getNext();
    }

    std::cout << std::endl;
}

template <typename T>
inline int PriorityQueue<T>::getCount() const
{
    return itemCount;
}

template <typename T>
inline PriorityQueue<T>::~PriorityQueue()
{
    T tmp;
    int p;
    while (dequeue(tmp, p));
}

#endif