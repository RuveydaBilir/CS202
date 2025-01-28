/**
* Title: AVL Tree's Node
* Author: Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 2
* Description : Node class that can also handle multiple occurances.
*/

#include <iostream>
#include "Node.h"
using namespace std;

Node::Node(){
    item = 0;
    rightChildPtr = nullptr;
    leftChildPtr = nullptr;
    height = 0; //????
    counter = 1;
}

Node::Node(const int &nodeItem, Node *left, Node *right){
    item = nodeItem;
    leftChildPtr = left;
    rightChildPtr = right;
    height = 1;
    counter = 1;
}

Node::~Node(){
    if(rightChildPtr!=nullptr){
        delete rightChildPtr;
    }
    if(leftChildPtr!=nullptr){
        delete leftChildPtr;
    }
}

int Node::getItem(){
    return item;
}

void Node::setItem(int newItem){
    item = newItem;
}

int Node::getCounter(){
    return counter;
}

void Node::increaseCounter(){
    counter++;
}

void Node::decreaseCounter(){
    counter--;
}

int Node::getHeight(){
    return height;
}

int Node::getBalance(){
    int leftHeight = 0;
    int rightHeight = 0;

    if(leftChildPtr!=nullptr){
        leftHeight = leftChildPtr->getHeight();
    }
    if(rightChildPtr!=nullptr){
        rightHeight = rightChildPtr->getHeight();
    }

    return (leftHeight-rightHeight);
}

void Node::updateHeight(){
    int leftHeight = 0;
    int rightHeight = 0;

    if(leftChildPtr!=nullptr){
        leftHeight = leftChildPtr->getHeight();
    }
    if(rightChildPtr!=nullptr){
        rightHeight = rightChildPtr->getHeight();
    }

    height = 1+std::max(leftHeight,rightHeight);
}

void Node::setRightChild(Node *newChild){
    rightChildPtr = newChild;
}

void Node::setLeftChild(Node *newChild){
    leftChildPtr = newChild;
}

Node *&Node::getRightChild(){
    return rightChildPtr;
}

Node *&Node::getLeftChild(){
    return leftChildPtr;
}
