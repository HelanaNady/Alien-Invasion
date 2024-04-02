#pragma once

#include <iostream>
#include "StackADT.h"

// The default size is 100
template<typename T>
class ArrayStack : public StackADT<T>
{

private:
	const int MAX_SIZE;
	T items[MAX_SIZE];
	int top;

public:
	ArrayStack();
	bool isEmpty() const;
	bool push(const T& newEntry);
	bool pop(T& TopEntry);
	bool peek(T& TopEntry) const;
	void printList() const;
	int getCount() const;
};

template<typename T>
inline ArrayStack<T>::ArrayStack() :MAX_SIZE(100), top(-1)
{}

template<typename T>
inline bool ArrayStack<T>::isEmpty() const
{
	return top == -1;
}

template<typename T>
inline bool ArrayStack<T>::push(const T& newEntry)
{
	if (top == MAX_SIZE - 1) return false;

	items[++top] = newEntry;
	return true;
}

template<typename T>
inline bool ArrayStack<T>::pop(T& TopEntry)
{
	if (isEmpty()) return false;

	TopEntry = items[top--];
	return true;
}

template<typename T>
inline bool ArrayStack<T>::peek(T& TopEntry) const
{
	if (isEmpty()) return false;

	TopEntry = items[top];
	return true;
}

template<typename T>
inline void ArrayStack<T>::printList() const
{
	for (int i = 0; i <= top; i++)
	{
		std::cout << items[i];
		if (i < top)
			std::cout << ", ";
	}
	std::cout << std::endl;
}

template<typename T>
inline int ArrayStack<T>::getCount() const
{
	return top + 1;
}


