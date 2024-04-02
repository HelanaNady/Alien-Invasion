#pragma once

#include <iostream>
#include "PriorityNode.h"

// This class implements the priority queue as a sorted list (Linked List)
// The item with highest priority is at the front of the queue
template <typename T>
class PriorityQueue
{
    PriorityNode<T>* head;

public:
    PriorityQueue(): head(nullptr) {}

    ~PriorityQueue()
    {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

    // Insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority)
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
    }

    bool dequeue(T& topEntry, int& pri)
    {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        PriorityNode<T>* temp = head;
        head = head->getNext();
        delete temp;

        return true;
    }

    bool peek(T& topEntry, int& priority)
    {
        if (isEmpty())
            return false;

        topEntry = head->getItem();
        priority = head->getPriority();

        return true;
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    void printList() const
    {
        PriorityNode<T>* current = head;
        int p = 0;

        while (current) {
            std::cout << current->getItem(p);

            if (current->getNext() != nullptr)
                std::cout << ", ";

			current = current->getNext();
		}

        std::cout << std::endl;
    }
};
