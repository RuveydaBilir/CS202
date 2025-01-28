/**
* Title: Graphs
* Author : Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 4
* Description : Atom Class
*/
#include "Atom.h"
#include <iostream>
#include <climits>

using namespace std;

Atom::Atom(){
    id=-1;
    bondNum = 0;
    bondArr = nullptr;
    arrSize = 0;
    isVisited = false;
    //distToDestination = INT_MAX;
}

Atom::Atom(int atomId, int neighborNum){
    id = atomId;
    bondNum = neighborNum;
    //bondArr = new Atom*[bondNum];
    arrSize = 0;
    isVisited = false;
    //distToDestination = INT_MAX;
}

Atom::~Atom(){
    delete[] bondArr;
}

int Atom::getId(){
    return id;
}

int Atom::getBondNum(){
    return bondNum;
}

void Atom::setId(int newId){
    id = newId;
}

void Atom::setBondNum(int num){
    bondNum = num;
    bondArr = new Atom*[bondNum];    
}

void Atom::addBond(Atom* neighbor){
    if (arrSize < bondNum && findBond(neighbor->getId())==nullptr) {
        bondArr[arrSize] = neighbor;
        arrSize++;
    } 
    /*
    else {
        std::cerr << "Error: Cannot add more bonds to Atom " << id 
                  << ". Maximum bond number (" << bondNum << ") reached." << std::endl;
    }
    */
}

Atom *Atom::findBond(int bondID){
    for(int i=0; i<arrSize; i++){
        if(bondArr[i]->getId()==bondID){
            return bondArr[i];
        }
    }
    return nullptr;
}

void Atom::printAtom(){
    cout<<"ID: "<<id<<" BOND NUM: "<<bondNum<< " HAVE BONDS WITH: ";
    for(int i=0; i<bondNum; i++){
        cout<<bondArr[i]->getId()<<" ";
    }
    cout<<endl;
}

bool Atom::getIsVisited(){
    return isVisited;
}

void Atom::setIsVisited(bool visit){
    isVisited = visit;
}

Atom *Atom::getNextUnvisited(){
    for(int i=0; i<arrSize; i++){
        if(bondArr[i]->getIsVisited()==false){
            return bondArr[i];
        }
    }
    return nullptr;
}

/*
void Atom::setDistToDest(int dist){
    distToDestination = dist;
}

int Atom::findMinDistance(){
    int minDist = INT_MAX;
    for(int i=0; i<arrSize; i++){
        if(bondArr[i]->getDistToDest()<minDist){
            minDist = bondArr[i]->getDistToDest();
        }
    }
    distToDestination = minDist;
    return minDist;
}

int Atom::getDistToDest(){
    return distToDestination;
}

*/
