/**
* Title: Game
* Author: Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 2
* Description : Solution for Q2
*/

#include "AVLTree.h"
#include <iostream>
#include <fstream>

using namespace std;
void play(AVLTree*& tree1, AVLTree*& tree2, const int n, ofstream& outputFile){
    int score1 = 0;
    int score2 = 0;
    int tree1Min,tree1Max,tree2Min,tree2Max;
    int chosen1, chosen2;
    bool isFinished = false;

    for(int i=0; i<n && !isFinished; i=i+2){
        //cout<<"ROUND" <<i<< ":"<<endl;
        tree1Max = tree1->getMaxNode()->getItem();

        int play1 = tree2->getLargestSmallerThan(tree1Max);
        if(play1>-1){
            //cout<<"Tree 1 removes: "<< tree1->remove(tree1Max)->getItem()<<endl;
            //cout<<"Tree 2 removes: "<< tree2->remove(play1)->getItem()<<endl;
            tree1->remove(tree1Max);
            tree2->remove(play1);
            score1++;
        }
        else{
            isFinished = true;
            score2 += n-i;
            //cout<<"No best move for A"<<endl;
        }

        if(!isFinished){    
            tree2Max = tree2->getMaxNode()->getItem();
            int play2 = tree1->getLargestSmallerThan(tree2Max);
            if(play2>-1){
                //cout<<"Tree 1 removes: "<< tree1->remove(play2)->getItem()<<endl;
                //cout<<"Tree 2 removes: "<<tree2->remove(tree2Max)->getItem()<<endl;
                tree1->remove(play2);
                tree2->remove(tree2Max);
                score2++;

            }
            else{
                isFinished = true;
                score1 += n-i;
                //cout<<"No best move for B"<<endl;
            }
        }
        //cout<<"-------SCORE: "<<score1<<" | "<<score2<<endl;
        
    }
    outputFile<<score1<<" "<<score2;
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

    AVLTree* bobo = new AVLTree();
    AVLTree* holo = new AVLTree();
    int argument;
    if(!(inputFile>>argument)){
        return 1;
    }
    int N = argument; //deck size

    for(int i=0; i<N; i++){
        if(!(inputFile>>argument)){
            return 1;
        }
        bobo->insert(argument);
    }
    for(int i=0; i<N; i++){
        if(!(inputFile>>argument)){
            return 1;
        }
        holo->insert(argument);
    }
    //cout<<"Insertion completed"<<endl;
    //bobo->displayTree();
    //holo->displayTree();

    play(bobo, holo, N, outputFile);

    inputFile.close();
    if (outputFile.is_open()) {
        outputFile.close();
    }

    delete holo;
    delete bobo;
    return 0;
}
