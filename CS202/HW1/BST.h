/**
* Title: Binary Search Trees
* Author : Rüveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 1
* Description : Header file for BST class
*/
#ifndef BST_H
#define BST_H

#include "TreeNode.h"
#include "Queue.h"

class BST {
public:
    BST();
    BST(int keys[], int size);
    ~BST();
    bool isEmpty() const;
    void insertKey(int key);
    void insertKeySilent(int key);
    void insertKeyRecursion(TreeNode*& treePtr,const int newItem);
    void deleteKey(int key);
    void deleteKey(TreeNode*& treePtr);
    void deleteKeySilent(int key);
    void deleteRecursion(TreeNode*& treePtr, int key);
    void deleteAndRearrange(TreeNode*& treePtr);
    void goLeft(TreeNode*& treePtr, int& key);
    TreeNode* find(int key);
    TreeNode* findRecursion(TreeNode*& treePtr, int key);
    void displayInorder();
    void inorderRecursion(TreeNode*& treePtr, Queue<TreeNode>*& queue);
    void findFullBTLevel();
    void findFullBTLevelSilent();
    void levelRecursion(TreeNode*& treePtr, int& counter);
    void lowestCommonAncestor(int A, int B);
    TreeNode* lCARecursion(TreeNode*& tempRoot, int a, int b);
    void maximumSumPath();
    void sumPathRecursion(TreeNode*& treePtr, int& sum, Queue<TreeNode>*& queue);
    void maximumWidth();
    void maxWidthRecursion(Queue<TreeNode>*& queue, Queue<TreeNode>*& maxQueue, int& maxWidth);
    void pathFromAtoB(int A, int B);
    void findPathFromRootToNode(TreeNode*& tempRoot, int dest);
    void findPathFromNodeToRoot(TreeNode*& tempRoot, int dest, Queue<TreeNode>* queue);
    void reversePathQueue(Queue<TreeNode>* queue);
    void printPathQueue(Queue<TreeNode>* queue);
    int getHeight(TreeNode*& node);
    int getHeight();

private:
    TreeNode* root;
    int treeSize;
    int fullBTLevel;
};

#endif