/**
* Title: Binary Search Trees
* Author : Rüveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 1
* Description : Header file for TreeNode class
*/
#ifndef __TREENODE_H
#define __TREENODE_H

class TreeNode{
private:
    int item;
    TreeNode* leftChildPtr;
    TreeNode* rightChildPtr;

public:
    TreeNode();
    TreeNode(const int& nodeItem, TreeNode* left, TreeNode* right);
    ~TreeNode();
    int getItem();
    void setItem(int newItem);
    void setRightChild(TreeNode* newChild);
    void setLeftChild(TreeNode* newChild);
    TreeNode*& getRightChild();
    TreeNode*& getLeftChild();
};
#endif