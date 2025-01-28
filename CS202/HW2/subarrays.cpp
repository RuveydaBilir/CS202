/**
* Title: Subarrays
* Author: Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 2
* Description : Solution for Q4
*/

#include "AVLTree.h"
#include <iostream>
#include <fstream>
#include <climits>

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

void insertBetweenMax(int start, int end, int*& arr, AVLTree*& tree, const int maxSize){
    int min;
    for(int i=start; i<end; i++){
        //cout<<"Tree in max loop: ";
        //tree->displayTree();
        if(tree->getSize()<maxSize){
            tree->insert(arr[i]);
        }
        else{
            min = tree->getMinNode()->getItem();
            if(arr[i]>min){
                tree->insert(arr[i]);
                tree->remove(min);
            }
        }
    }
}
void insertBetweenMin(int start, int end, int*& arr, AVLTree*& tree, const int maxSize){
    int max;
    for(int i=start; i<end; i++){
        //cout<<"Tree in min loop: ";
        //tree->displayTree();
        if(tree->getSize()<maxSize){
            tree->insert(arr[i]);
        }
        else{
            max = tree->getMaxNode()->getItem();
            if(arr[i]<max){
                tree->insert(arr[i]);
                tree->remove(max);
            }
        }
    }
}
bool setAndCheck(int left, int right, int M, int K, int*& arrA, int*& arrB){
    AVLTree* A = new AVLTree();
    AVLTree* B = new AVLTree();
    //cout<<"Set and check"<<endl;
    insertBetweenMax(left, right, arrA, A, M);
    //cout<<"Tree A is: ";
    //A->displayTree();
    insertBetweenMin(left,right, arrB, B, K);
    //cout<<"Tree B is: ";
    //B->displayTree();
    int aMin = A->getMinNode()->getItem();
    int bMax = B->getMaxNode()->getItem();
    if(aMin>bMax){
        return true;
    }
    delete A;
    delete B;
    return false;
}

bool check(AVLTree*& treeA, AVLTree*& treeB){
    int counter = 0;
    int itemA = treeA->getMinNode()->getItem();
    int itemB = treeB->getMaxNode()->getItem();

    if(itemA>itemB){
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
            std::ifstream outputFile("output.txt");
        }
    }
    else{
        outputFile.open("output.txt"); // Default output file
        if (!outputFile) {
            std::cerr << "Error: Could not open default output file 'output.txt'" << std::endl;
            return 1;
        }
    }

    /// Use input file here
    int argInt;
    int N,M,K;
    if(!(inputFile>>N>>M>>K)){
        return 1;
    }
    int* arrA = new int[N];
    int* arrB = new int[N];
    if(fillArrays(arrA,arrB,N,inputFile)==false){
        return 1;
    }
    int L = 0;
    int left = 0;
    int right;
    int minLength;
    if(K>M){
        minLength = K;
    }
    else{
        minLength = M;
    }
    right = minLength;
    int smallestLenght = INT_MAX;
    bool isSecondIteration = false;
    while (right <= N && left <= N) {
        //cout<<"Right = "<<right<<endl;
        //cout<<"Left = "<<left<<endl;
        if(right-left>=minLength){
            bool isSatisfied = setAndCheck(left, right, M, K, arrA, arrB);
            if(isSatisfied){
                //isSecondIteration = true;
                if(right-left<smallestLenght){
                    L = right - left;
                    smallestLenght = L;
                }
                //cout<<"!!!! L = "<<L<< endl;
                left++;
            }
            else{
                right++;
            }
        }
        else{
            right++;
        }
    }

    outputFile<<L;
    delete[] arrA;
    delete[] arrB;

    inputFile.close();
    if (outputFile.is_open()) {
        outputFile.close();
    }

    return 0;
}

/*
for(int i=0; i<N; i++){
        if(arrA[i]<=arrB[i]){
            left++; //doesnt satisfy the condition swipe the window
            rightA = left+M;
            rightB = left+K;
        }
        else{
            insertBetween(left, rightA, arrA, treeA, M);
            insertBetween(left, rightB, arrB, treeB, M);
            bool isSatisfy = check(treeA, treeB);
            if(isSatisfy){
                L = rightA-left;
                left++; //now check for a smaller size
            }
            else{
                rightA ++; // expend the window by keeping left pointer the same
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (arrA[i] <= arrB[i]) {
            left++;
            rightA = left + M;
            rightB = left + K;
        } else {
            if (rightA < N) treeA->insert(arrA[rightA++]);
            if (rightB < N) treeB->insert(arrB[rightB++]);

            if (treeA->getSize() > M) treeA->remove(arrA[left - 1]);
            if (treeB->getSize() > K) treeB->remove(arrB[left - 1]);

            bool isSatisfy = check(treeA, treeB);
            if (isSatisfy) {
                L = rightA - left;
                left++;
            }
        }
    }
*/