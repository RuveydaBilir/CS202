/**
* Title: Least 5
* Author: Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 2
* Description : Solution for Q1
*/

#include "Heap.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <input_filename> [output_filename]" << std::endl;
        return 1;
    }

    //std::string inputFileName = argv[1];
    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
        return 1;
    }

    std::ofstream outputFile;
    bool hasOutputFile = (argc == 3);
    if (hasOutputFile) {
        //std::string outputFileName = argv[2];
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

    char argument;
    int argInt;
    if(!(inputFile>>argInt)){
        return 1;
    }
    int argumentSize = argInt;
    if(argumentSize>0){
        Heap heap = Heap(argumentSize);
        while (inputFile >> argument && argumentSize>0) { //reads until the first whitespace
            if(argument == 'a'){ //add operation
                if(!(inputFile>>argInt)){
                    return 1;
                }
                //cout<<"Adding: "<<argInt<<endl;
                heap.insert(argInt);
            }
            else if(argument == 'g'){
                if(heap.getSize()<5){
                    outputFile << -1 <<endl;
                }
                else{
                    heap.displayFive(outputFile);
                }
                
            }
            else if(argument == 'r'){
                if(heap.getSize()>0){
                    int removed = heap.deleteRoot();
                    //outputFile << removed <<endl;
                }
                else{
                    outputFile << -1 <<endl;
                }
            }
            else{
                //cerr<<"Invalid operation."<<endl;
                inputFile.close();
                if (outputFile.is_open()) {
                    outputFile.close();
                }
                return 1;
            }
            argumentSize--;
        }
    }
    else{
        //cout<<"Invalid operation."<<endl;
        inputFile.close();
        if (outputFile.is_open()) {
            outputFile.close();
        }
        return 1;
    }

    inputFile.close();
    if (outputFile.is_open()) {
        outputFile.close();
    }

    return 0;
}
