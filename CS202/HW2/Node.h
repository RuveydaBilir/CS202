/**
* Title: AVL Tree's Node
* Author: Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 2
* Description : Node class header
*/

#ifndef __NODE_H
#define __NODE_H

class Node{
private:
    int item;
    Node* leftChildPtr;
    Node* rightChildPtr;
    int height;
    int counter;

public:
    Node();
    Node(const int& nodeItem, Node* left, Node* right);
    ~Node();
    int getItem();
    void setItem(int newItem);
    int getCounter();
    void increaseCounter();
    void decreaseCounter();
    int getHeight();
    int getBalance();
    void updateHeight();
    void setRightChild(Node* newChild);
    void setLeftChild(Node* newChild);
    Node*& getRightChild();
    Node*& getLeftChild();
};
#endif