/**
* Title: Graphs
* Author : Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 4
* Description : Atom header class
*/
#ifndef ATOM_H
#define ATOM_H
#include <iostream>

class Atom{
    public:
        Atom();
        Atom(int atomId, int neighborNum);
        ~Atom();
        int getId();
        int getBondNum();
        void setId(int newId);
        void setBondNum(int num);
        void addBond(Atom* neighbor);
        Atom* findBond(int bondID);
        void printAtom();
        bool getIsVisited();
        void setIsVisited(bool visit);
        //void setDistToDest(int dist);
        //int findMinDistance();
        //int getDistToDest();
        Atom* getNextUnvisited();

    private:
        //BondList* bondList;
        Atom** bondArr;
        int id;
        int bondNum;
        int arrSize;
        //int distToDestination;
        bool isVisited;
};

#endif