/**
* Title: Graphs
* Author : Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 4
* Description : Header file for ListNode class
*/
#ifndef LISTNODE_H
#define LISTNODE_H

template<class ItemType>
class ListNode{
private:
    ItemType* value;
    ListNode* nextNode;
public:
    ListNode();
    ListNode(ItemType* newValue, ListNode* newNextNode);
    ~ListNode();
    ItemType* getValue();
    void setValue(ItemType* newValue);
    ListNode* getNext();
    void setNext(ListNode*& newNode);
};
#endif
//#include "ListNode.cpp"