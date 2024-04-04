#ifndef PRIORITY_NODE_H
#define PRIORITY_NODE_H

template <typename T>
class PriorityNode
{
	T item; // A data item (can be any data type)
	int priority; // The priority of the item
	PriorityNode<T>* next; // Pointer to next node

public:
	PriorityNode(const T& item, int priority);

	void setItem(const T& item, int priority);
	void setNext(PriorityNode<T>* nextNodePtr);

	T getItem(int& priority) const;
	PriorityNode<T>* getNext() const;
	int getPriority() const;
};

template <typename T>
inline PriorityNode<T>::PriorityNode(const T& item, int priority)
{
	setItem(item, priority);
	next = nullptr;
}

template <typename T>
inline void PriorityNode<T>::setItem(const T& item, int priority)
{
	this->item = item;
	this->priority = priority;
}

template <typename T>
void PriorityNode<T>::setNext(PriorityNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template <typename T>
inline T PriorityNode<T>::getItem(int& priority) const
{
	priority = this->priority;

	return item;
}

template <typename T>
inline PriorityNode<T>* PriorityNode<T>::getNext() const
{
	return next;
}

template <typename T>
inline int PriorityNode<T>::getPriority() const
{
	return priority;
}

#endif