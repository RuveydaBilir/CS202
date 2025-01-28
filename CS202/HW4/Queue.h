/**
* Title: Graphs
* Author : Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 4
* Description : Header file for Queue class
*/
#ifndef QUEUE_H
#define QUEUE_H
#include "ListNode.cpp"
#include <stdexcept>

template<class ItemType>
class Queue{
private:
    ListNode<ItemType>* frontPtr;
    ListNode<ItemType>* endPtr;
    int queueSize;
public:
    Queue();
    bool isEmpty();
    bool enqueque(ItemType*& entry);
    ItemType* dequeque();
    int getSize();
    ItemType peekFront();
    ~Queue();

};
#endif
//#include "Queue.cpp"
