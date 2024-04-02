#ifndef PRIORITYNODE_H
#define PRIORITYNODE_H

template <typename T>
class PriorityNode
{
	T item; // A data item (can be any data type)
	int priority; // The priority of the item
	PriorityNode<T>* next; // Pointer to next node

public:
	PriorityNode(const T& _item, int _priority);

	void setItem(const T& _item, int _priority);
	void setNext(PriorityNode<T>* nextNodePtr);
		
	T getItem(int& _priority) const;
	PriorityNode<T>* getNext() const;
	int getPriority() const;
};
#endif

template <typename T>
PriorityNode<T>::PriorityNode(const T& _item, int _priority)
{
	setItem(_item, _priority);
	next = nullptr;
}

template <typename T>
void PriorityNode<T>::setItem(const T& _item, int _priority)
{
	item = _item;
	priority = _priority;
}

template <typename T>
void PriorityNode<T>::setNext(PriorityNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template <typename T>
T PriorityNode<T>::getItem(int& _priority) const
{
	_priority = priority;

	return item;
}

template <typename T>
PriorityNode<T>* PriorityNode<T>::getNext() const
{
	return next;
}

template <typename T>
int PriorityNode<T>::getPriority() const
{
	return priority;
}