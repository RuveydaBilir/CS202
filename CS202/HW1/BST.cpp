/**
* Title: Binary Search Trees
* Author : Rüveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 1
* Description : Class of binary search tree with insertion, deletion, inorder recursion, finding full bt level, finding max width functionalities
*/
#include <iostream>
#include "BST.h"
#include "Queue.cpp"
using namespace std;

BST::BST(){
    root = nullptr;
    treeSize = 0;
    fullBTLevel = 0;
}

BST::BST(int keys[], int size){
    root = nullptr;
    //treeSize = size;
    fullBTLevel = 0;
    int current;
    for(int i=0; i<size; i++){
        current = keys[i];
        insertKeySilent(current);
    }
    cout<<"BST with size "<<size<< " is created."<<endl;
}

BST::~BST(){
    while(root!=nullptr){
        deleteKey(root);
    }
}

bool BST::isEmpty() const{
    if(root==nullptr){
        return true;
    }
    return false;
}

void BST::insertKey(int key){
    if(find(key)==nullptr){
        insertKeyRecursion(root, key);
        cout<<"Key "<<key<<" is added."<<endl;
        treeSize++;
        return;
    }
    cout<<"Key "<<key<<" is not added. It exists!"<<endl;
}

void BST::insertKeySilent(int key){
    if(find(key)==nullptr){
        insertKeyRecursion(root, key);
        treeSize++;
        return;
    }
}

void BST::insertKeyRecursion(TreeNode *&treePtr, const int newItem){
    if (treePtr == nullptr){
        treePtr = new TreeNode(newItem, nullptr, nullptr);
    }
    else if(newItem<treePtr->getItem()){
        insertKeyRecursion(treePtr->getLeftChild(),newItem);
    }
    else{
        insertKeyRecursion(treePtr->getRightChild(),newItem);
    }
}

void BST::deleteKey(int key){
    if(find(key)==nullptr){
        cout<<"Key "<<key<<" is not deleted. It does not exist!"<<endl;
        return;
    }
    deleteRecursion(root, key);
    cout<<"Key "<<key<<" is deleted."<<endl;

}

void BST::deleteKey(TreeNode *&treePtr){
    deleteKeySilent(treePtr->getItem());
}

void BST::deleteKeySilent(int key){
    if(find(key)==nullptr){
        return;
    }
    deleteRecursion(root, key);
}

void BST::deleteRecursion(TreeNode *&treePtr, int key){
    if(treePtr!=nullptr){
        if(treePtr->getItem()==key){
            deleteAndRearrange(treePtr);
        }
        else if(treePtr->getItem()>key){
            deleteRecursion(treePtr->getLeftChild(),key);
        }
        else{
            deleteRecursion(treePtr->getRightChild(),key);
        }
    }
}

void BST::deleteAndRearrange(TreeNode*& treePtr){
    TreeNode* del;
    int replaceKey;

    //If it is a leaf:
    if(treePtr->getLeftChild()==nullptr && treePtr->getRightChild()==nullptr){
        delete treePtr;
        treePtr = nullptr;
    }

    // If it has only a right child
    else if(treePtr->getLeftChild()==nullptr){
        del = treePtr;
        treePtr = treePtr->getRightChild();
        del->setRightChild(nullptr);
        delete del;
    }

    // If it has only a left child
    else if(treePtr->getRightChild()==nullptr){
        del = treePtr;
        treePtr = treePtr->getLeftChild();
        del->setLeftChild(nullptr);
        delete del;
    }

    //if it has both child:
    else{
        goLeft(treePtr->getRightChild(), replaceKey);
        treePtr->setItem(replaceKey);
    }

}

void BST::goLeft(TreeNode *&treePtr, int &key){
    if(treePtr->getLeftChild()==nullptr){
        key = treePtr->getItem();
        TreeNode* del = treePtr;
        treePtr = treePtr->getRightChild();
        del->setRightChild(nullptr);
        delete del;
    }
    else{
        goLeft(treePtr->getLeftChild(), key);
    }
}

TreeNode* BST::find(int key){
    TreeNode* answer = findRecursion(root, key);
    return answer;
}

TreeNode *BST::findRecursion(TreeNode*& treePtr, int key){
    if (treePtr != nullptr) {
        //cout<<"Checking node for finding func.: "<<treePtr->getItem()<<endl;
        if (treePtr->getItem() == key) {
            return treePtr;
        }
        if (key < treePtr->getItem()) {
            return findRecursion(treePtr->getLeftChild(), key);
        } 
        else{
            return findRecursion(treePtr->getRightChild(), key);
        }
    }
    return nullptr;
}

void BST::displayInorder(){
    cout<<"Inorder display is: ";
    Queue<TreeNode>* q = new Queue<TreeNode>();
    inorderRecursion(root, q);
    printPathQueue(q);
    cout<<endl;
    delete q;
}

void BST::inorderRecursion(TreeNode*& treePtr, Queue<TreeNode>*& queue){
    if (treePtr != nullptr) {
        inorderRecursion(treePtr->getLeftChild(), queue);
        queue->enqueque(treePtr);
        inorderRecursion(treePtr->getRightChild(), queue);
    }
}

void BST::findFullBTLevel(){
    findFullBTLevelSilent();
    if(fullBTLevel == 0){
        cout<<"BST is empty."<<endl;
        return;
    }
    cout<<"Full binary tree level is: "<<fullBTLevel<<endl;
}

void BST::findFullBTLevelSilent(){
    int rightCounter = 1;
    int leftCounter = 1;
    int levelCouter = 0;
    if(isEmpty()){
        return;
    }
    if(root->getLeftChild()!=nullptr && root->getRightChild()!=nullptr){
        levelRecursion(root->getRightChild(),rightCounter);
        levelRecursion(root->getLeftChild(), leftCounter);
        if(rightCounter>leftCounter){
            levelCouter = leftCounter;
        }
        else{
            levelCouter = rightCounter;
        }
    }
    else{
        levelCouter = rightCounter;
    }
    fullBTLevel = levelCouter;
}

void BST::levelRecursion(TreeNode *&treePtr, int& counter){
    int rightCounter = 1;
    int leftCounter = 1;
    if(treePtr != nullptr){
        if(treePtr->getLeftChild()!=nullptr && treePtr->getRightChild()!=nullptr){
            levelRecursion(treePtr->getRightChild(),rightCounter);
            levelRecursion(treePtr->getLeftChild(), leftCounter);
            if(rightCounter>leftCounter){
                counter += leftCounter;
            }
            else{
                counter += rightCounter;
            }
        }
        else{
            counter += rightCounter;
        }
    }
}

void BST::lowestCommonAncestor(int A, int B){
    TreeNode* lca;
    if(isEmpty()){
        cout<<"BST is empty."<<endl;
        return;
    }
    int rootItem = root->getItem();
    if(find(A)!=nullptr && find(B)!=nullptr){
        if(A==B){
            lca = find(A);
        }
        if(A>rootItem && B> rootItem){ // if both numbers greater than root number, move to right child
            lca = lCARecursion(root->getRightChild(), A, B);
        }
        else if(A<rootItem && B< rootItem){ // if both numbers smaller than root number, move to left child
            lca = lCARecursion(root->getLeftChild(), A, B);
        }
        else{ // if one is greater and one is smaller, it is the LCA
            lca = root;
        }
        cout<<"Lowest common ancestor of "<<A <<" and "<<B<< " is: "<<lca->getItem()<<endl;
        return;
    }
    cout<<"Error: One or both keys ("<<A<<", "<<B<<") do not exist in the tree."<<endl;
}

TreeNode* BST::lCARecursion(TreeNode*& tempRoot, int a, int b){
    TreeNode* lca;
    int rootItem = tempRoot->getItem();
    if(a>rootItem && b> rootItem){ // if both numbers greater than root number, move to right child
        lca = lCARecursion(tempRoot->getRightChild(), a, b);
    }
    else if(a<rootItem && b< rootItem){ // if both numbers smaller than root number, move to left child
        lca = lCARecursion(tempRoot->getLeftChild(), a, b);
    }
    else{ // if one is greater and one is smaller, it is the LCA
        lca =  tempRoot;
    }
    return lca;
}

void BST::maximumSumPath(){
    if(isEmpty()){
        cout<<"BST is empty."<<endl;
        return;
    }
    int maxSum = 0;
    Queue<TreeNode>* queue = new Queue<TreeNode>();
    if (root != nullptr) {
        sumPathRecursion(root, maxSum, queue);
    }

    cout << "Maximum sum path is: ";
    reversePathQueue(queue);
    printPathQueue(queue);
    cout<<endl;
    delete queue;
}

void BST::sumPathRecursion(TreeNode*& treePtr, int& sum, Queue<TreeNode>*& queue){
    if (treePtr == nullptr) {
        sum = 0;
        return;
    }

    if (treePtr->getLeftChild() == nullptr && treePtr->getRightChild() == nullptr) {
        sum = treePtr->getItem();
        queue->enqueque(treePtr);
        return;
    }

    int leftSum = 0, rightSum = 0;
    Queue<TreeNode>* leftQueue = new Queue<TreeNode>;
    Queue<TreeNode>* rightQueue = new Queue<TreeNode>;
    sumPathRecursion(treePtr->getLeftChild(), leftSum, leftQueue);
    sumPathRecursion(treePtr->getRightChild(), rightSum, rightQueue);

    if (leftSum > rightSum) {
        sum = leftSum + treePtr->getItem();
        delete queue;  
        queue = leftQueue; 
        queue->enqueque(treePtr); 
        delete rightQueue; 
    } else {
        sum = rightSum + treePtr->getItem();
        delete queue;  
        queue = rightQueue;  
        queue->enqueque(treePtr); 
        delete leftQueue; 
    }
}


void BST::maximumWidth() {
    if (isEmpty()) {
        cout << "BST is empty." << endl;
        return;
    }
    
    Queue<TreeNode>* q = new Queue<TreeNode>();
    Queue<TreeNode>* maxQueue = new Queue<TreeNode>(); // To store the queue with maximum width
    int maxWidth = 1;
    
    q->enqueque(root);
    maxWidthRecursion(q, maxQueue, maxWidth); // Passing maxQueue and maxWidth by reference
    
    cout << "Maximum level is: ";
    printPathQueue(maxQueue);
    cout << endl;
    
    delete q;
    delete maxQueue;
}

void BST::maxWidthRecursion(Queue<TreeNode>*& queue, Queue<TreeNode>*& maxQueue, int& maxWidth) {
    int queueSize = queue->getSize();
    if (queueSize == 0) {
        return; 
    }
    
    Queue<TreeNode>* tempQueue = new Queue<TreeNode>();

    for (int i = 0; i < queueSize; i++) {
        TreeNode* node = queue->dequeque();
        
        if (node->getLeftChild() != nullptr) {
            queue->enqueque(node->getLeftChild());
            tempQueue->enqueque(node->getLeftChild());
            
        }
        if (node->getRightChild() != nullptr) {
            queue->enqueque(node->getRightChild());
            tempQueue->enqueque(node->getRightChild());
        }
    }
    
    if (tempQueue->getSize() > maxWidth) {
        maxWidth = tempQueue->getSize();
        
        delete maxQueue;
        maxQueue = tempQueue; 
    }
    else{
        delete tempQueue;
    }
    
    if (!queue->isEmpty()) {
        maxWidthRecursion(queue, maxQueue, maxWidth);
    }
}

void BST::pathFromAtoB(int A, int B){
    TreeNode* nodeA = find(A);
    TreeNode* nodeB = find(B);
    TreeNode* lca;
    Queue<TreeNode>* queue = new Queue<TreeNode>();

    if(nodeA != nullptr && nodeB != nullptr){
        cout<<"Path from "<<A<<" to "<<B<<" is: ";
        if(A==B){
            cout<<A;
        }
        else{
            lca = lCARecursion(root, A, B);
            findPathFromNodeToRoot(lca, A, queue);
            reversePathQueue(queue);
            printPathQueue(queue);
            if(B>lca->getItem()){
                cout<<", ";
                findPathFromRootToNode(lca->getRightChild(), B);
            }
            else if(B<lca->getItem()){
                cout<<", ";
                findPathFromRootToNode(lca->getLeftChild(), B);
            }
        }
        cout<<endl;
        delete queue;
        return;

    }
    cout<<"Error: One or both keys ("<<A<<", "<<B<<") do not exist in the tree."<<endl;
    delete queue;
}

void BST::findPathFromRootToNode(TreeNode*& tempRoot, int dest){ //add root and node
    if(tempRoot == nullptr){
        return;
    }
    int tempItem = tempRoot->getItem();

    cout<<tempItem;
    if(tempItem == dest){
        return; 
    }
    else if(dest>tempItem){
        cout<<", ";
        findPathFromRootToNode(tempRoot->getRightChild(),dest);
    }
    else{
        cout<<", ";
        findPathFromRootToNode(tempRoot->getLeftChild(), dest);
    }
}

void BST::findPathFromNodeToRoot(TreeNode *&tempRoot, int dest, Queue<TreeNode>* queue){
    if(tempRoot == nullptr){
        return;
    }
    int tempItem = tempRoot->getItem();

    queue ->enqueque(tempRoot);
    if(tempItem == dest){
        return; 
    }
    else if(dest>tempItem){
        findPathFromNodeToRoot(tempRoot->getRightChild(),dest,queue);
    }
    else{
        findPathFromNodeToRoot(tempRoot->getLeftChild(), dest, queue);
    }
}

void BST::reversePathQueue(Queue<TreeNode> *queue){
    int size = queue->getSize();
    int arr[size];
    TreeNode* cur;
    for(int i=0; i<size; i++){
        arr[i]=queue->dequeque()->getItem();
    }
    for(int i=size-1; i>=0; i--){
        cur = find(arr[i]);
        queue->enqueque(cur);
    }

}

void BST::printPathQueue(Queue<TreeNode> *queue){
    TreeNode* cur;
    int size = queue->getSize();
    for(int i=0; i<size; i++){
        cur = queue->dequeque();
        if(i==size-1){
            cout<<cur->getItem();
        }
        else{
            cout<<cur->getItem()<<", ";
        }
        
    }
}

int BST::getHeight(TreeNode*& node) {
    if (node == nullptr) {
        return 0; // Height of an empty tree is 0
    } else {
        int leftHeight = getHeight(node->getLeftChild());
        int rightHeight = getHeight(node->getRightChild());
        if(leftHeight>rightHeight){
            return 1+ leftHeight;
        }
        return 1+rightHeight;
    }
}

int BST::getHeight(){
    return getHeight(root);
}
