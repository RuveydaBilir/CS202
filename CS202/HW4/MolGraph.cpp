/**
* Title: Graphs
* Author : Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 4
* Description : Molgraph class with bfs functionality
*/
#include "MolGraph.h"
#include "Queue.cpp"
#include "Atom.h"
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

MolGraph::MolGraph(const std::string &filename){
    diameter = 0;
    std::fstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error: Could not open input file " << filename << std::endl;
    }

    inputFile>>arrSize;
    atomArr = new Atom*[arrSize];

    for(int i=0; i<arrSize; i++){
        atomArr[i] = new Atom(i, 0);
    }
    int id, nNum, nID;

    for(int i=0; i<arrSize; i++){
        inputFile>>id;
        inputFile>>nNum; // holds komsu num
        //cout<<"Processing: "<<id<<" Bond num: "<<nNum<<endl;
        atomArr[i]->setBondNum(nNum);

        for(int j=0; j<nNum; j++){
            inputFile>>nID;
            atomArr[i]->addBond(atomArr[nID]);
        }
    }
}

MolGraph::~MolGraph(){
    for(int i=0; i<arrSize; i++){
        delete atomArr[i];
    }
    delete[] atomArr;
}

void MolGraph::minBondPath(int source, int destination){ //BFS logic
    int distance[arrSize];
    int parent[arrSize];
    if(source>=arrSize || source<0 || destination>=arrSize || destination<0){
        cout<<"Invalid source or destination"<<endl;
        return;
    }
    int pathSize = bfs(source, destination, distance, parent);
    /*
    cout<<"Path size: "<<pathSize<<endl;
    for(int i=0; i<arrSize; i++){
        cout<<"i: "<<distance[i]<<endl;
    }
    */
   if (pathSize == INT_MAX) {
        cout << "No path exists between atom " << source << " and atom " << destination << endl;
        return;
    }

    cout<<"Minimum number of bonds to traverse from atom "<<source<<" to atom "<<destination<<": "<<pathSize<<endl;
    cout<<"Path: ";

    printPath(parent, destination, pathSize);

    clearAllVisited();

}

void MolGraph::printPath(int parent[], int destination, int size){
    int path[size];
    int current = destination;
    int pathLength = 0;

    while (current != -1) { 
        path[pathLength] = current;//dest ten source a path 
        pathLength++;

        current = parent[current];

    }
    if(size==0){
        cout<<destination<<endl;
        return;
    }

    // now printing path reversely
    for(int i=pathLength-1; i>-1; i--){
        if(i!=0){
            cout<<path[i]<<" -> ";
        }
        else{
            cout<<path[i]<<endl;
        }
    }

}

int MolGraph::bfs(int source, int destination, int distance[], int parent[]) {
    clearAllVisited();

    Queue<Atom> q;
    Atom* src = atomArr[source];

    for (int i = 0; i < arrSize; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }
    int maxDist = 0;
    distance[source] = 0;
    q.enqueque(src);
    src->setIsVisited(true);

    Atom* current, *neighbor;
    while (!q.isEmpty()) {
        current = q.dequeque();

        if (current->getId() == destination) {
            break;
        }

        neighbor = current->getNextUnvisited();
        while (neighbor != nullptr) {
            if (!neighbor->getIsVisited()) {
                q.enqueque(neighbor);
                neighbor->setIsVisited(true);
                distance[neighbor->getId()] = distance[current->getId()] + 1;
                if(distance[neighbor->getId()]>maxDist){
                    maxDist = distance[neighbor->getId()];
                }
                parent[neighbor->getId()] = current->getId();
            }
            neighbor = current->getNextUnvisited();
        }
    }

    if(destination!=-1){
        return distance[destination];
    }

    return maxDist;
    
}


void MolGraph::getDiameter(){
    int longest = 0;
    int farthestAtomID;
    if(arrSize<=0){
        cout<<"Diameter of the molecule: "<<longest<<endl;
        return;
    }
    int parent[arrSize];
    int distance[arrSize];
    //Longest of the shoetest paths

    longest = bfs(0,-1, distance,parent);
    //cout<<"Longest: "<<longest<<endl;
    //cout<<"Arr size: "<<arrSize<<endl;
    for (int i = 0; i < arrSize; i++) {
        //cout<<"Distance of atom"<<i<<"; "<<distance[i]<<endl;
        if (distance[i]!=INT_MAX && distance[i] >= longest) {
            longest = distance[i];
            farthestAtomID = i;
            //cout<<"Farthest atom id: "<<farthestAtomID<<endl;

        }
    }
    //cout<<"Farthest atom id: "<<farthestAtomID<<endl;
    longest = 0;
    bfs(farthestAtomID,-1, distance,parent);
    for (int i = 0; i < arrSize; i++) {
        if (distance[i] > longest) {
            longest = distance[i];
        }
    }

    cout<<"Diameter of the molecule: "<<longest<<endl;
}

void MolGraph::getMST(){
    clearAllVisited();
    Queue<Atom> q;
    //int mst[arrSize-1][2]; //start-end
    if(arrSize<=0){
        cout<<"Invalid size"<<endl;
        return;
    }
    MST mst[arrSize-1];
    int edgeCounter = 0;

    Atom* start = atomArr[0];
    q.enqueque(start);
    start->setIsVisited(true);

    Atom *current, *neighbor;
    while(!q.isEmpty() && edgeCounter<arrSize-1){
        current = q.dequeque();
        neighbor = current->getNextUnvisited();
        while(neighbor!=nullptr){
            //mst[edgeCounter][0] = current->getId(); // Start vertex
            //mst[edgeCounter][1] = neighbor->getId(); // End vertex
            mst[edgeCounter] = {current->getId(), neighbor->getId()};
            edgeCounter++;
            q.enqueque(neighbor);
            neighbor->setIsVisited(true);
            neighbor = current->getNextUnvisited();

            if(edgeCounter == arrSize-1){
                break;
            }
        }
    }

    cout<<"Minimum Spanning Tree:"<<endl;
    cout<<"Cost: "<<edgeCounter<<endl;
    cout<<"Edges:"<<endl;
    
    insertionSort(mst, edgeCounter);

    for(int i=0; i<edgeCounter; i++){
        cout<<mst[i].edge0<<" - "<<mst[i].edge1<<endl;
    } 
}

void MolGraph::printGraph(){
    for(int i=0; i< arrSize; i++){
        atomArr[i]->printAtom();
    }
}

void MolGraph::clearAllVisited(){
    for(int i=0; i<arrSize; i++){
        atomArr[i]->setIsVisited(false);
    }
}

void MolGraph::insertionSort(MST arr[], int arrSize){
    int finalIndex;
    //first sort by edge0
    for (int i = 1; i < arrSize; i++) {
        MST key = arr[i];
        finalIndex = i-1;
        for (int j = i - 1; j >= 0; j--) {
            if(arr[j].edge0 > key.edge0){
                arr[j + 1] = arr[j]; 
                finalIndex = j;
            }
        }
        arr[finalIndex + 1] = key;
    }

    //sort by edge1
    for (int i = 1; i < arrSize; i++) {
        MST key = arr[i];
        finalIndex = i-1;
        for (int j = i - 1; j >= 0; j--) {
            if(arr[j].edge0 == key.edge0 && arr[j].edge1 > key.edge1){
                arr[j + 1] = arr[j]; 
                finalIndex = j;
            }
        }
        arr[finalIndex + 1] = key;
    }
}
