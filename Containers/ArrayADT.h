#ifndef ARRAY_ADT_H
#define ARRAY_ADT_H

template<typename T>
class ArrayADT
{
public:

    virtual bool isEmpty() const = 0;

    virtual bool insert(const T& newEntry) = 0;

    virtual bool remove(int index, T& entry) = 0;

    virtual bool entryAt(T& entry, int index) const = 0;

    virtual ~ArrayADT() {}
};
#endif 

