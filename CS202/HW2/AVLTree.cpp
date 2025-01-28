/**
* Title: AVL Tree
* Author: Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 2
* Description : AVL tree class implementation with modifications in insert, delete functions to perform 
* for duplicate numbers and additional getLargestSmallerThan() method.
*/

#include <iostream>
#include "AVLTree.h"
using namespace std;

AVLTree::AVLTree(){
    root = nullptr;
    size = 0;
}

AVLTree::~AVLTree(){
    while(root!=nullptr){
        remove(root->getItem());
    }
}

Node *AVLTree::find(int key){
    return findRecursion(root, key);
}

Node *AVLTree::findRecursion(Node *&nodePtr, int key){
    //cout<<"Entered recursion"<<endl;
    if (nodePtr != nullptr) {
        if (nodePtr->getItem() == key) {
            return nodePtr;
        }
        if (key < nodePtr->getItem()) {
            return findRecursion(nodePtr->getLeftChild(), key);
        } 
        else{
            return findRecursion(nodePtr->getRightChild(), key);
        }
    }
    //cout<<"At the end of find recursion"<<endl;
    return nullptr;
}


Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->getLeftChild();
    Node* T2 = x->getRightChild();

    // Perform rotation
    x->setRightChild(y);
    y->setLeftChild(T2);

    // Update heights
    y->updateHeight();
    x->updateHeight();

    return x;  // new root
}

Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->getRightChild();
    Node* T2 = y->getLeftChild();

    // Perform rotation
    y->setLeftChild(x);
    x->setRightChild(T2);

    // Update heights
    x->updateHeight();
    y->updateHeight();

    return y;  // new root
}

void AVLTree::insert(int value){
    Node* found = find(value);
    if(found==nullptr){
        insertRecursion(root, value);
    }
    else{
        found->increaseCounter();
    }
    size++;
}

void AVLTree::insertRecursion(Node*& nodePtr, int newItem) {
    if (nodePtr == nullptr) {
        nodePtr = new Node(newItem, nullptr, nullptr);
    } else if (newItem < nodePtr->getItem()) {
        insertRecursion(nodePtr->getLeftChild(), newItem);
    } else {
        insertRecursion(nodePtr->getRightChild(), newItem);
    }

    // Update height of this node
    nodePtr->updateHeight();

    // Get the balance factor
    int balance = nodePtr->getBalance();

    // Left-Left Case
    if (balance > 1 && newItem < nodePtr->getLeftChild()->getItem()) {
        nodePtr = rotateRight(nodePtr);
    }
    // Right-Right Case
    else if (balance < -1 && newItem > nodePtr->getRightChild()->getItem()) {
        nodePtr = rotateLeft(nodePtr);
    }
    // Left-Right Case
    else if (balance > 1 && newItem > nodePtr->getLeftChild()->getItem()) {
        nodePtr->setLeftChild(rotateLeft(nodePtr->getLeftChild()));
        nodePtr = rotateRight(nodePtr);
    }
    // Right-Left Case
    else if (balance < -1 && newItem < nodePtr->getRightChild()->getItem()) {
        nodePtr->setRightChild(rotateRight(nodePtr->getRightChild()));
        nodePtr = rotateLeft(nodePtr);
    }
}


Node *AVLTree::remove(int value){
    Node* delNode = find(value);
    if(delNode!=nullptr){
        if(delNode->getCounter()>1){
            delNode->decreaseCounter();
        }
        else{
            removeRecursion(root, value);
        }
        size--;
    }
    return delNode;
}

void AVLTree::removeRecursion(Node *&nodePtr, int key){
    //cout<<"In remove recursion!!"<<endl;
    if(nodePtr!=nullptr){
        if(nodePtr->getItem()==key){
            removeAndRearrange(nodePtr);
        }
        else if(nodePtr->getItem()>key){
            removeRecursion(nodePtr->getLeftChild(),key);
        }
        else{
            removeRecursion(nodePtr->getRightChild(),key);
        }

        if(nodePtr!= nullptr){
            nodePtr -> updateHeight();
            int balance = nodePtr->getBalance();
            //cout<<"In rec insert, after updateHeight and balance"<<endl;

            if(balance>1 && nodePtr->getLeftChild()!=nullptr
                && nodePtr->getLeftChild()->getBalance()>=0){
                    nodePtr = rotateRight(nodePtr);
            }
            else if(balance <-1 && nodePtr->getRightChild()!=nullptr
                && nodePtr->getRightChild()->getBalance() <= 0){
                    nodePtr = rotateLeft(nodePtr);
            }
            else if(balance>1 && nodePtr->getLeftChild()!=nullptr 
                && nodePtr->getLeftChild()->getBalance()<0){
                    nodePtr->setLeftChild(rotateLeft(nodePtr->getLeftChild()));
                    nodePtr = rotateRight(nodePtr);
            }
            else if(balance<-1 && nodePtr->getRightChild()!=nullptr
                && nodePtr->getRightChild()->getBalance()>0){
                    nodePtr->setRightChild(rotateRight(nodePtr->getRightChild()));
                    nodePtr = rotateLeft(nodePtr);
            }
            nodePtr -> updateHeight();
            balance = nodePtr->getBalance();
        }
    }
}

void AVLTree::removeAndRearrange(Node *&nodePtr){
    //cout<<"In r a rearrange!!"<<endl;
    Node* del;
    int replaceKey;
    //If it is a leaf:
    if(nodePtr->getLeftChild()==nullptr && nodePtr->getRightChild()==nullptr){
        delete nodePtr;
        nodePtr = nullptr;
    }
    // If it has only a right child
    else if(nodePtr->getLeftChild()==nullptr){
        del = nodePtr;
        nodePtr = nodePtr->getRightChild();
        del->setRightChild(nullptr);
        delete del;
    }
    // If it has only a left child
    else if(nodePtr->getRightChild()==nullptr){
        del = nodePtr;
        nodePtr = nodePtr->getLeftChild();
        del->setLeftChild(nullptr);
        delete del;
    }

    //if it has both child:
    else{
        goLeft(nodePtr->getRightChild(), replaceKey);
        nodePtr->setItem(replaceKey);
        nodePtr->updateHeight();
    }
}

void AVLTree::goLeft(Node *&nodePtr, int &key){
    if(nodePtr->getLeftChild()==nullptr){
        key = nodePtr->getItem();
        Node* del = nodePtr;
        nodePtr = nodePtr->getRightChild();
        del->setRightChild(nullptr);
        delete del;
    }
    else{
        goLeft(nodePtr->getLeftChild(), key);
    }
}

Node *AVLTree::getMinNode(){
    return minValueNode(root);
}

Node *AVLTree::getMaxNode(){
    return maxValueNode(root);
}

int AVLTree::getLargestSmallerThan(const int key){
    int output = -1;
    Node* curNode = root;
    while (curNode != nullptr) {
        if (curNode->getItem() < key) {
            output = curNode->getItem();
            curNode = curNode->getRightChild();
        } else {
            curNode = curNode->getLeftChild();
        }
    }
    return output;
}

int AVLTree::deleteMax(){
    Node* del = maxValueNode(root);
    int value = del->getItem();
    remove(value);
    return value;
}

int AVLTree::deleteMin(){
    Node* del = minValueNode(root);
    int value = del->getItem();
    remove(value);
    return value;
}

Node *AVLTree::minValueNode(Node *node) const{
    while (node && node->getLeftChild() != nullptr) {
        node = node->getLeftChild();
    }
    return node;
}

Node *AVLTree::maxValueNode(Node *node) const{
    while (node && node->getRightChild() != nullptr) {
        node = node->getRightChild();
    }
    return node;
}

void AVLTree::display(Node *node) const{
    if(node != nullptr){
        display(node->getLeftChild());
        cout<<node->getItem()<<" ";
        display(node->getRightChild());
    }
}

void AVLTree::displayTree(){
    display(root);
    cout<<endl;
}

int AVLTree::getSize(){
    return size;
}

void AVLTree::clear(){
    while(root!=nullptr){
        remove(root->getItem());
    }
}
