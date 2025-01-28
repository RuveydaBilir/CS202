/**
* Title: Binary Search Trees
* Author : Rüveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 1
* Description : Queue class with enqueue, dequeue and peekfront functionalities
*/
#include "Queue.h"
#include <iostream>
using namespace std;
template <class ItemType>
inline Queue<ItemType>::Queue(){
    frontPtr = nullptr;
    endPtr = nullptr;
    queueSize= 0;
}

template <class ItemType>
inline bool Queue<ItemType>::isEmpty(){
    if(queueSize==0){
        return true;
    }
    return false;
}

template <class ItemType>
inline bool Queue<ItemType>::enqueque(ItemType*& entry){
    ListNode<ItemType>* newNode = new ListNode<ItemType>(entry, nullptr);
    if (isEmpty()) {
        frontPtr = newNode; 
        endPtr = newNode;
    } else {
        endPtr->setNext(newNode); 
        endPtr = endPtr->getNext();
    }
    queueSize++;
    return true;
}

template <class ItemType>
inline ItemType* Queue<ItemType>::dequeque(){
    if (isEmpty()) {
        return nullptr;
    }
    
    ListNode<ItemType>* nodeToDelete = frontPtr;
    ItemType* dequeued = nodeToDelete->getValue();
    frontPtr = frontPtr->getNext();
    
    queueSize--;
    
    if (queueSize == 0) {
        endPtr = nullptr;
    }
    delete nodeToDelete;
    return dequeued;
}

template <class ItemType>
int Queue<ItemType>::getSize(){
    return queueSize;
}

template <class ItemType>
inline ItemType Queue<ItemType>::peekFront(){
    if (!isEmpty()) {
        return frontPtr->getValue();
    }
    throw std::out_of_range("Queue is empty");
}

template <class ItemType>
inline Queue<ItemType>::~Queue(){
    while (!isEmpty()) {
        dequeque();
    }
}
