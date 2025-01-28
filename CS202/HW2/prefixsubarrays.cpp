/**
* Title: Prefix Subarrays
* Author: Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 2
* Description : Solution for Q3
*/

#include "AVLTree.h"
#include <iostream>
#include <fstream>

using namespace std;

bool fillArrays(int*& arrA, int*& arrB, int N, ifstream& inputFile){
    int argInt;
    for(int i=0; i<N; i++){
        if(!(inputFile>>argInt)){
            delete[] arrA;
            delete[] arrB;
            return false;
        }
        arrA[i] = argInt;
    }
    for(int i=0; i<N; i++){
        if(!(inputFile>>argInt)){
            delete[] arrA;
            delete[] arrB;
            return false;
        }
        arrB[i] = argInt;
    }
    return true;
}
void showArr(int*& arr, int size){
    for(int i=0; i<size; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
void insertUntilIndexKeepMax(int index, int*& arr, AVLTree*& tree, const int maxSize){
    for(int i=0; i<index; i++){
        //cout<<"Inserting: "<<arr[i]<<endl;
        tree->insert(arr[i]);
        //cout<<"AVLTree size: "<<tree->getSize()<<endl;
        if(tree->getSize()>maxSize){
            //cout<<"Deleting: "<< tree->deleteMin() <<endl;
            tree->deleteMin();
        }
    }
}

void insertUntilIndexKeepMin(int index, int*& arr, AVLTree*& tree, const int maxSize){
    for(int i=0; i<index; i++){
        //cout<<"Inserting: "<<arr[i]<<endl;
        tree->insert(arr[i]);
        //cout<<"AVLTree size: "<<tree->getSize()<<endl;
        if(tree->getSize()>maxSize){
            //cout<<"Deleting: "<< tree->deleteMax() <<endl;
            tree->deleteMax();
        }
    }
}

bool check(AVLTree*& treeA, AVLTree*& treeB, const int M){
    //cout<<"Entered check"<<endl;
    int counter = 0;
    int itemA, itemB;
    while(treeA->getSize()!=0 /*&& counter<M*/){
        itemA = treeA->getMinNode()->getItem(); 
        itemB = treeB->getMinNode()->getItem();
        //cout<<"Comparing: "<<itemA<<", "<<itemB<<endl;
        if(itemA<=itemB){
            treeA->deleteMin();
        }
        else{
            treeA->deleteMin();
            treeB->deleteMin();
            counter++;
            //cout<<"Counter: "<<counter<<endl;
        }
    }
    if(counter == M){
        return true;
    }
    return false;
}

int main(int argc, char* argv[]){
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <input_filename> [output_filename]" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
        return 1;
    }

    std::ofstream outputFile;
    bool hasOutputFile = (argc == 3);
    if (hasOutputFile) {
        outputFile.open(argv[2]);
        if (!outputFile) {
            std::ofstream outputFile("output.txt");
        }
    }
    else{
        outputFile.open("output_prefixsubarrays.txt"); // Default output file
        if (!outputFile) {
            std::cerr << "Error: Could not open default output file 'output.txt'" << std::endl;
            return 1;
        }
    }

    /// Code locig begins hereee
    int N, M;
    int* arrA;
    int* arrB;
    int counter = 0;

    int argInt;
    if(!(inputFile>>N>>M)){
        return 1;
    }
    arrA = new int[N];
    arrB = new int[N];

    if(fillArrays(arrA,arrB,N,inputFile)==false){
        return 1;
    }

    AVLTree* treeA = new AVLTree();
    AVLTree* treeB = new AVLTree();

    //showArr(arrA, N);
    //showArr(arrB, N);
    int left = 0, right = N - 1;
    int L = 0;

    for (int i = 0; left <= right; i++) {
        int mid = left + (right - left) / 2;
        //cout<<"Mid: "<<mid<<endl;
        treeA -> clear();
        treeB -> clear();

        insertUntilIndexKeepMax(mid, arrA, treeA, M); //fix size
        insertUntilIndexKeepMin(mid, arrB, treeB, M);
        //treeA->showAVLTree();
        //treeB->showAVLTree();

        if (check(treeA, treeB, M)) {
            //cout<<"AVLTree size: "<<treeA->getSize()<<endl;
            L = mid; //belki burayi da degistirmem gerekir
            right = mid - 1;
        } else {
            left = mid + 1; 
        }
    }

    outputFile<<L;
    inputFile.close();
    if (outputFile.is_open()) {
        outputFile.close();
    }

    delete[] arrA;
    delete[] arrB;
    delete treeA;
    delete treeB;

    return 0;
}