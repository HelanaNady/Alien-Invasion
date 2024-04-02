#ifndef STACKADT_H
#define STACKADT_H

template<typename T>
class StackADT
{
public:

    virtual bool isEmpty() const = 0;

    virtual bool push(const T& newEntry) = 0;

    virtual bool pop(T& TopEntry) = 0;

    virtual bool peek(T& TopEntry) const = 0;

    virtual ~StackADT() { }
};
#endif 

