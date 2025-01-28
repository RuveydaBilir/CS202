/**
* Title: AVL Trees
* Author: Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 2
* Description : AVL Tree class header
*/

#ifndef __AVLTREE_H
#define __AVLTREE_H
#include "Node.h"

class AVLTree{
private:
    Node* root;
    int size;
public:
    AVLTree();
    ~AVLTree();        
    Node* find(int key);
    Node* findRecursion(Node*& nodePtr, int key);
    Node* rotateRight(Node* y);                
    Node* rotateLeft(Node* x);                 
    void insert(int value);
    void insertRecursion( Node*& nodePtr, int newItem);       
    Node* remove(int value); 
    void removeRecursion(Node*& nodePtr, int key);
    void removeAndRearrange(Node*& nodePtr);
    void goLeft(Node*& nodePtr, int& key);
    Node* getMinNode();
    Node* getMaxNode();
    int getLargestSmallerThan(const int key);
    int deleteMax();
    int deleteMin();        
    Node* minValueNode(Node* node) const;
    Node* maxValueNode(Node* node) const;     
    void display(Node* node) const;
    void displayTree();
    int getSize();
    void clear();
};


#endif