/**
* Title: Graphs
* Author : Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 4
* Description : Molgraph header class
*/
#ifndef MOLGRAPH_H
#define MOLGRAPH_H

#include <string>
#include <iostream>
#include "Atom.h"

class MolGraph{
    struct MST{
        int edge0;
        int edge1;
    };
    public:
        MolGraph(const std::string& filename);
        ~MolGraph();
        void minBondPath(int source, int destination);
        void printPath(int parent[], int destination, int size);
        int bfs(int source, int destination, int distance[], int parent[]);
        void getDiameter();
        void getMST();
        //Atom* addAtom(int atomId);
        void printGraph();
        void clearAllVisited();
        void insertionSort(MST arr[], int arrSize);
    
    private:
        Atom** atomArr;
        int arrSize;
        int diameter;
};

#endif