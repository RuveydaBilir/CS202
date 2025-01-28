/**
* Title: Binary Search Trees
* Author : Rüveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 1
* Description : TreeNode class for Binary Search Tree, hold left and right child pointers and an integer item
*/
#include <iostream>
#include "TreeNode.h"
using namespace std;

TreeNode::TreeNode(){
    item = 0;
    rightChildPtr = nullptr;
    leftChildPtr = nullptr;    
}

TreeNode::TreeNode(const int& nodeItem, TreeNode* left=nullptr, TreeNode* right=nullptr)
    :item(nodeItem),leftChildPtr(left),rightChildPtr(right){

}

TreeNode::~TreeNode(){
    if(rightChildPtr!=nullptr){
        delete rightChildPtr;
    }
    if(leftChildPtr!=nullptr){
        delete leftChildPtr;
    }
}

int TreeNode::getItem(){
    return item;
}

void TreeNode::setItem(int newItem){
    item = newItem;
}

void TreeNode::setRightChild(TreeNode *newChild){
    rightChildPtr = newChild;
}

void TreeNode::setLeftChild(TreeNode *newChild){
    leftChildPtr = newChild;
}

TreeNode*& TreeNode::getRightChild(){
    return rightChildPtr;
}

TreeNode*& TreeNode::getLeftChild(){
    return leftChildPtr;
}
