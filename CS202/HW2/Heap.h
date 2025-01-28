/**
* Title: Heap
* Author: Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 2
* Description : Heap class header
*/

#ifndef __HEAP_H
#define __HEAP_H

#include <iostream>
#include <fstream>
class Heap{
public:
    Heap();
    Heap(int size);
    ~Heap();
    void insert(int newItem);
    int deleteRoot();
    int getMin() const;
    void displayFive(std::ofstream& outputFile) const;
    void heapify(int index);
    int getSize();
    void clear();
    void showHeap();

private:
    int* arr;
    int maxSize;
    int heapSize;
};
#endif