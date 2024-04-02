#ifndef QUEUE_ADT_
#define QUEUE_ADT_

template<class T>
class QueueADT
{
public:
   
    virtual bool isEmpty() const = 0;

    virtual bool enqueue(const T& newEntry) = 0;

    virtual bool dequeue(T& FrontEntry) = 0;

    virtual bool peek(T& FrontEntry) const = 0;

    virtual ~QueueADT() { }
}; 
#endif