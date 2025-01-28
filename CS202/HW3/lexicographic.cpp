/**
* Title: Hashing
* Author : Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 3
* Description : Lexicographic question
*/
#include <fstream>
#include <iostream>
#include <climits>
using namespace std;

int findSmallestNonDepIndex(int* arr, int* hashTable, int arrSize){
    int index = -1;
    int curSmallest = INT_MAX;
    for(int i=0; i<arrSize; i++){
        if(arr[i] == 0 && hashTable[i] != -1){
            if(hashTable[i] < curSmallest){
                curSmallest = hashTable[i];
                //cout<<"Current smallest: "<<curSmallest<<endl;
                //cout<<"Its index: "<<i<<endl<<endl;
                index = i;
            }
        }
    }
    return index;
}
/*
bool detectCycleDFS(int node, bool* visited, bool* recStack, bool** isBefore, int size) {
    if (!visited[node]) {
        visited[node] = true;
        recStack[node] = true;

        // Check all neighbors
        for (int neighbor = 0; neighbor < size; neighbor++) {
            if (isBefore[node][neighbor]) {
                if (!visited[neighbor] && detectCycleDFS(neighbor, visited, recStack, isBefore, size)) {
                    return true;
                } else if (recStack[neighbor]) {
                    return true;
                }
            }
        }
    }
    recStack[node] = false; // Remove the node from recursion stack
    return false;
}

bool hasCycle(bool** isBefore, int size) {
    bool* visited = new bool[size]();
    bool* recStack = new bool[size]();

    for (int i = 0; i < size; i++) {
        if (detectCycleDFS(i, visited, recStack, isBefore, size)) {
            delete[] visited;
            delete[] recStack;
            return true;
        }
    }

    delete[] visited;
    delete[] recStack;
    return false;
}
*/
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
        outputFile.open("lexOut.txt"); // Default output file
        if (!outputFile) {
            std::cerr << "Error: Could not open default output file 'output.txt'" << std::endl;
            return 1;
        }
    }

    int size;
    if(!(inputFile>>size)){
        return 1;
    }
    //cout<<"size: "<<size<<endl;
    int* hashTable = new int[size];
    int argument;

    for(int i=0; i<size; i++){
        inputFile>>argument;
        hashTable[i] = argument;
    }
    //bool isBefore[size][size] = {0}; // I lastly added new two functions, to test them I need to properly initialize this.
    bool** isBefore = new bool*[size];
    int* beforeArr = new int[size];

    for (int i = 0; i < size; i++) {
        beforeArr[i] = 0;
        isBefore[i] = new bool[size];
        for (int j = 0; j < size; j++) {
            isBefore[i][j] = 0;
        }
    }
    int beforeCtr;
    bool isOriginalPos;
    int pos;
    int validCtr = 0;

    for(int i=0; i<size; i++){
        if(hashTable[i]!=-1){
            validCtr++;
            isOriginalPos = 1;
            beforeCtr = 0;
            pos = hashTable[i] % size;
            if(pos!=i){
                isOriginalPos = 0;
            }
            if(!isOriginalPos){
                for(int j=pos; j!=i; j = (j+1)%size ){
                    if(hashTable[j]!=-1){
                        isBefore[j][i] = 1;
                        //cout<< hashTable[j] <<" must be before "<<hashTable[i]<<endl;
                        beforeCtr ++;
                    }
                }
            }
            beforeArr[i] = beforeCtr;
        }
        else{
            beforeArr[i] = 0;
        }
    }

    int answer[size];
    int ctr=0;
    int smallestIndex = 0;

    if(validCtr==0){
        outputFile << "Impossible" << endl;
        //cout << "Impossible" << endl;
        delete[] hashTable;
        delete[] beforeArr;
        for(int i=0; i<size; i++){
            delete[] isBefore[i];
        }
        delete[] isBefore;
        return 0;
    }
    
    for(int i=0; i<validCtr; i++){
        smallestIndex = findSmallestNonDepIndex(beforeArr, hashTable, size);
        if(smallestIndex == -1){
            //cout<<"Found an invalid case"<<endl;
            outputFile << "Impossible" << endl;
            //cout << "Impossible" << endl;
            delete[] hashTable;
            delete[] beforeArr;
            for(int i=0; i<size; i++){
                delete[] isBefore[i];
            }
            delete[] isBefore;
            return 0;
        }
        else{
            answer[ctr++] = hashTable[smallestIndex];
            //beforeArr[smallestIndex] = beforeArr[smallestIndex] -1;
            beforeArr[smallestIndex] = -1;

            for (int j = 0; j < size; j++) {
                if (isBefore[smallestIndex][j]) {
                    //if(beforeArr[j]>=0){
                        beforeArr[j]--;
                    //}
                    isBefore[smallestIndex][j] = 0;
                    //cout<<hashTable[smallestIndex]<<" is be before "<<hashTable[j]<<endl;
                    
                }
            }
        }
    }
    /*
    while ((smallestIndex = findSmallestNonDepIndex(beforeArr, hashTable, size)) != -1) {
        answer[ctr++] = hashTable[smallestIndex];
        beforeArr[smallestIndex] = -1;

        for (int j = 0; j < size; j++) {
            if (isBefore[smallestIndex][j]) {
                //if(beforeArr[j]>=0){
                    beforeArr[j]--;
                //}
                isBefore[smallestIndex][j] = 0;
                //cout<<hashTable[smallestIndex]<<" is be before "<<hashTable[j]<<endl;
                
            }
        }
    }
    */
    //cout<<"CTR: "<<ctr<<endl;
    for (int i = 0; i < size; i++) {
        if (beforeArr[i] >= 0 && hashTable[i]!=-1) {
            outputFile << "Impossible" << endl;
            //cout << "Impossible" << endl;
            delete[] hashTable;
            delete[] beforeArr;
            for(int i=0; i<size; i++){
                delete[] isBefore[i];
            }
            delete[] isBefore;
            return 0;
        }
    }

    for(int i=0; i<ctr; i++){
        if(i!=ctr-1)
        outputFile<<answer[i]<<" ";
        else{
            outputFile<<answer[i];
        }
    }

    inputFile.close();
    if (outputFile.is_open()) {
        outputFile.close();
    }

    delete[] hashTable;
    delete[] beforeArr;
    for(int i=0; i<size; i++){
        delete[] isBefore[i];
    }
    delete[] isBefore;

    return 0;
}