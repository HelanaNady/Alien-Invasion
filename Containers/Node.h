#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
private:
    T item; // A data item
    Node<T>* next; // Pointer to next node
    Node<T>* prev; // Pointer to prev node
public:
    Node();
    Node(const T& item);
    Node(const T& item, Node<T>* prevNodePtr, Node<T>* nextNodePtr);
    void setItem(const T& item);
    void setNext(Node<T>* nextNodePtr);
    void setPrev(Node<T>* prevNodePtr);

    T getItem() const;
    Node<T>* getPrev() const;
    Node<T>* getNext() const;
}; // end Node
#endif

template < typename T>
Node<T>::Node()
    : prev(nullptr), next(nullptr)
{ }

template < typename T>
Node<T>::Node(const T& item)
    : item(item), prev(nullptr), next(nullptr)
{ }

template < typename T>
Node<T>::Node(const T& item, Node<T>* prevNodePtr, Node<T>* nextNodePtr)
    : item(item), prev(prevNodePtr), next(nextNodePtr)
{

}
template < typename T>
void Node<T>::setItem(const T& item)
{
    this->item = item;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
    next = nextNodePtr;
}

template<typename T>
inline void Node<T>::setPrev(Node<T>* prevNodePtr)
{
    prev = prevNodePtr;
}


template < typename T>
T Node<T>::getItem() const
{
    return item;
}

template<typename T>
Node<T>* Node<T>::getPrev() const
{
    return prev;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
    return next;
}