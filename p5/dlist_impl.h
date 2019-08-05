#ifndef _DLIST_IMPL_H
#define _DLIST_IMPL_H
#include "dlist.h"
#include <iostream>
using namespace std;

template <class T>
bool Dlist<T>::isEmpty() const
{
    return (first->next == last);
}

// EFFECTS: returns true if list is empy, false otherwise
template <class T>
void Dlist<T>::insertFront(T *op)
{
    node *tmp = new node;
    tmp->next = first->next;
    tmp->prev = first;
    tmp->op = op;
    first->next->prev = tmp;
    first->next = tmp;
}
// MODIFIES this
// EFFECTS inserts o at the front of the list
template <class T>
void Dlist<T>::insertBack(T *op)
{
    node *tmp = new node;
    tmp->next = last;
    tmp->prev = last->prev;
    tmp->op = op;
    last->prev->next = tmp;
    last->prev = tmp;
}
// MODIFIES this
// EFFECTS inserts o at the last of the list
template <class T>
T *Dlist<T>::removeFront()
{
    if (isEmpty())
    {
        emptyList eL;
        throw eL;
    }
    else
    {
        node *p, *q;
        p = first->next;
        T *tmp = p->op;
        q = p->next;
        first->next = q;
        q->prev = first;
        delete p;
        return tmp;
    }
}
// MODIFIES this
// EFFECTS removes and returns first object from non-empty list
//         throws an instance of emptyList if empty
template <class T>
T *Dlist<T>::removeBack()
{

    if (isEmpty())
    {
        emptyList eL;
        throw eL;
    }
    else
    {
        node *p, *q;
        p = last->prev;
        T *tmp = p->op;
        q = p->prev;
        last->prev = q;
        q->next = last;
        delete p;
        return tmp;
    }
}

// MODIFIES this
// EFFECTS removes and returns last object from non-empty list
//         throws an instance of emptyList if empty
template <class T>
Dlist<T>::Dlist()
{
    first = new node;
    last = new node;
    first->next = last;
    first->prev = NULL;
    last->prev = first;
    last->next = NULL;
} // constructor

template <class T>
Dlist<T>::Dlist(const Dlist &l)
{
    first = new node;
    last = new node;
    first->next = last;
    first->prev = NULL;
    last->prev = first;
    last->next = NULL;
    copyAll(l);
}

// copy constructor
template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist<T> &l)
{
    removeAll();
    copyAll(l);
    return *this;
} // assignment operator

template <class T>
Dlist<T>::~Dlist()
{
    removeAll();
    delete first;
    delete last;
} // destructor

template <class T>
void Dlist<T>::removeAll()
{
    node *p = first->next, *q;
    first->next = last;
    last->prev = first;
    while (p != last)
    {
        q = p->next;
        delete p->op;
        delete p;
        p = q;
    }
}
// EFFECT: called by destructor/operator= to remove and destroy
//         all list elements

template <class T>
void Dlist<T>::copyAll(const Dlist<T> &l)
{
    removeAll();
    if(l.isEmpty())
    {
        return;
    }
    node *l_itr = l.first->next;
    while (l_itr != l.last)
    {
        T *_t = new T(*(l_itr->op));
        insertBack(_t);
        l_itr = l_itr->next;
    }
}
// EFFECT: called by copy constructor/operator= to copy elements
//         from a source instance l to this instance

#endif