/**
* Title: Heap
* Author: Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 2
* Description : Implementation of Heap with an additional function of displayFive to get the smallest 5 elements in 
* an array
*/

#include "Heap.h"
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

Heap::Heap(){
    arr = nullptr;
    maxSize = 0;
    heapSize = 0;
}

Heap::Heap(int newSize){
    if(newSize<0){
        maxSize = 0;
        arr=nullptr;
    }
    else{
        maxSize=newSize;
        arr = new int[maxSize];
    }
    heapSize = 0;
}

Heap::~Heap(){
    delete[] arr;
}

void Heap::insert(int newItem){
    if (heapSize >= maxSize) {
        cout << "Heap overflow: Cannot insert more items." << endl;
        return;
    }
    arr[heapSize] = newItem;
    
    int place = heapSize;
    int parent = (place-1)/2; 
    while((place>0)&&(arr[place]<=arr[parent])){
        int temp = arr[parent];
        arr[parent] = arr[place];
        arr[place] = temp;

        place = parent;
        parent = (place-1)/2;
        //parent = parent+1;
    }
    heapSize++;
}

int Heap::deleteRoot(){
    if(heapSize==0){
        cout<<"The heap is empty."<<endl;
        return 0;
    }
    int returnItem = arr[0];
    heapSize--;
    arr[0] = arr[heapSize];
    heapify(0);
    return returnItem;
}

int Heap::getMin() const{
    return arr[0];
}

void Heap::displayFive(std::ofstream& outputFile) const{
    if(heapSize<5){
        outputFile<<-1<<endl;
        return;
    }
    int leastIndexArr[4]; //do not add root
    int arrCounter = 0;

    outputFile<<arr[0]<<endl;
    
    int curSmallest = INT_MAX;
    int prevSmallest = arr[0];
    
    int smallestIndex = 0;
    for(int counter = 0; counter<4; counter++){
        for(int i=1; i<heapSize && i<32; i++){
            if(arr[i]<curSmallest && arr[i]>=prevSmallest){
                bool isExistInArr = false;
                for(int k=0; k<4; k++){
                    if(leastIndexArr[k]==i){
                        isExistInArr = true;
                    }
                }
                if(!isExistInArr){
                    curSmallest = arr[i];
                    smallestIndex = i;
                }
            }
        }
        leastIndexArr[arrCounter] = smallestIndex;
        arrCounter++;
        outputFile<<curSmallest<<endl;
        prevSmallest = curSmallest;
        curSmallest = INT_MAX;
    }
}

void Heap::heapify(int rootIndex){
    int smallChildIndex = 2*rootIndex + 1;
    if(smallChildIndex<heapSize){
        int rightChildIndex = smallChildIndex+1;

        if((rightChildIndex<heapSize) && (arr[rightChildIndex]<arr[smallChildIndex])){ //find small child 
            smallChildIndex = rightChildIndex;
        }

        if(arr[rootIndex]>arr[smallChildIndex]){
            int temp = arr[rootIndex];
            arr[rootIndex] = arr[smallChildIndex];
            arr[smallChildIndex] = temp;

            heapify(smallChildIndex);
        }
    }
}

int Heap::getSize(){
    return heapSize;
}

void Heap::clear(){
    delete[] arr;
    arr = new int[maxSize];
    heapSize = 0;
}

void Heap::showHeap(){
    for(int i=0; i<heapSize; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

/*
void Heap::displayFive(std::ofstream& outputFile) const{
    if(heapSize<5){
        outputFile<<-1<<endl;
        return;
    }
    outputFile<<arr[0]<<endl;

    if(arr[1]<arr[2]){
        outputFile<<arr[1]<<endl;
        outputFile<<arr[2]<<endl;
    }
    else{
        outputFile<<arr[2]<<endl;
        outputFile<<arr[1]<<endl;
    }
    
    
    int min1 = arr[3];
    int min2 = arr[4];

    int checkedIndex;
    for(int i=3; i<7 && i<heapSize; i++){
        if(arr[i]<=min1){
            min1 = arr[i];
            checkedIndex = i;
        }
    }
    for(int i=3; i<7 && i<heapSize; i++){
        if(arr[i]<=min2 && i != checkedIndex){
            min2 = arr[i];
        }
    }

    outputFile<<min1<<endl;
    outputFile<<min2<<endl;
}
*/