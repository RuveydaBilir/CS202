/**
* Title: Graphs
* Author : Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 4
* Description : List Node template for Queue
*/
#include "ListNode.h"

template <class ItemType>
inline ListNode<ItemType>::ListNode(){
    nextNode = nullptr;
}

template <class ItemType>
inline ListNode<ItemType>::ListNode(ItemType* newValue, ListNode* newNextNode){
    value = newValue;
    nextNode = newNextNode;
}

template <class ItemType>
inline ListNode<ItemType>::~ListNode(){
    //delete value;
    //delete nextNode;
}

template <class ItemType>
inline ItemType* ListNode<ItemType>::getValue(){
    return value;
}

template <class ItemType>
inline void ListNode<ItemType>::setValue(ItemType* newValue){
    value = newValue;
}

template <class ItemType>
inline ListNode<ItemType>* ListNode<ItemType>::getNext(){
    return nextNode;
}

template <class ItemType>
inline void ListNode<ItemType>::setNext(ListNode *&newNode){
    nextNode = newNode;
}
