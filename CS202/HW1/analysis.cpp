/**
* Title: Binary Search Trees
* Author : Rüveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 1
* Description : Class for calculating time analysis for BST insertion for random and sorted arrays
*/

#include "analysis.h"
#include "BST.h"
#include <ctime>
#include <iostream>
using namespace std;

analysis::analysis(){}

analysis::~analysis(){}

void analysis::timeAnalysis(){
    BST* bst = new BST();
    int array[10000];
    int random;
    for(int i=0; i<10000; i++){
        random = rand();
        array[i] = random;
    }
    
    int i;
    clock_t start = clock();
    for(i=0; i<10000; i++){
        bst->insertKeySilent(array[i]);
        //bst->insertKeySilent(i); // to illustrate the effect of a sorted BST.
        if(i%1000 == 0 && i!=0){
            clock_t end = clock();
            double duration = (end - start) / (double) CLOCKS_PER_SEC;
            cout << "Completed: " << i << ", Duration: " << duration;
            cout << ", Height: " << bst->getHeight() << endl;
            start = clock();

        }
    }
    clock_t end = clock()-start;
    //cout<<"Duration: "<<(float)end / CLOCKS_PER_SEC<<endl;
    cout<<"Completed: "<<i<<", Duration: "<<(float)end / CLOCKS_PER_SEC;
    cout<<", Height: "<<bst->getHeight()<<endl;
    delete bst;
}
