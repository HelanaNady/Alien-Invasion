#pragma once

template <typename T>
class PriorityNode
{
	T item; // A data item (can be any data type)
	int priority; // The priority of the item
	PriorityNode<T>* next; // Pointer to next node

public:
	PriorityNode(const T& _item, int _priority)
	{
		setItem(_item, _priority);
		next = nullptr;
	}

	void setItem(const T& _item, int _priority)
	{
		item = _item;
		priority = _priority;
	}
	void setNext(PriorityNode<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}
	
	T getItem(int& _priority) const
	{
		_priority = priority;

		return item;
	}
	
	PriorityNode<T>* getNext() const
	{
		return next;
	}
	
	int getPriority() const
	{
		return priority;
	}
};
