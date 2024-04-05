#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

template<typename T>
class Array
{
    enum { MAX_SIZE = 1000 };
private:
    T items[MAX_SIZE];
    int count;

public:
    Array();
    bool isEmpty() const;
    bool insert(const T newEntry);
    bool remove(int index);
    bool entryAt(T entry, int index) const;
    void printList() const;
    int getCount() const;
};


template <typename T>
inline Array<T>::Array() : count(0)
{}

template <typename T>
inline bool Array<T>::isEmpty() const
{
    return (count == 0);
}

template <typename T>
inline bool Array<T>::insert(const T newEntry)
{
    if (count == MAX_SIZE - 1) return false;

    items[count++] = newEntry;
    return true;
}

template <typename T>
inline bool Array<T>::remove(int index)
{
    if (index >= count) return false;

    items[index] = items[count - 1];
    items[count - 1] = nullptr;
    count--;

    return true;
}

template <typename T>
inline bool Array<T>::entryAt(T entry, int index) const
{
    if (isEmpty()) return false;

    entry = items[index];
    return true;
}

template <typename T>
inline void Array<T>::printList() const
{
    for (int i = 0; i < count; i++)
    {
        std::cout << items[i];
        if (i != count - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;
}

template <typename T>
inline int Array<T>::getCount() const
{
    return count;
}

#endif