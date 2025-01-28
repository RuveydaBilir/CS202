/**
* Title: Hashing
* Author : Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 3
* Description : Insertion order question
*/
#include <fstream>
#include <iostream>
using namespace std;

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
        outputFile.open("lexicographicOut.txt"); // Default output file
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
    int* beforeArr = new int[size];
    int argument;

    for(int i=0; i<size; i++){
        inputFile>>argument;
        hashTable[i] = argument;
    }

    //int howFarMoved[size];
    bool isOrigPos;
    int beforeCtr, pos, adjPos;
    int validCtr = 0;

    for(int i=0; i<size; i++){
        if(hashTable[i] != -1){
            validCtr++;
            isOrigPos = 1;
            beforeCtr = 0;
            pos = hashTable[i] % size;
            if(pos!=i){
                adjPos = pos;
                for(int j=pos; j<pos+2; j++){ //O(3)
                    //cout<<"For "<<hashTable[i]<<" checking: "<<hashTable[adjPos]<<endl;
                    if(hashTable[adjPos] != -1 && j!=i){
                        beforeCtr++;
                    }
                    adjPos = (j+1)%size;
                }
                
            }
            //cout<<"For "<<hashTable[i]<<" beforeCtr: "<<beforeCtr<<endl;
            beforeArr[i] = beforeCtr;
        }
        else{
            beforeArr[i] = 0;
        }
    }
    if(validCtr==0){
        outputFile<<0<<endl;
        delete[] hashTable;
        delete[] beforeArr;

        return 0;
    }

    int divBy3 = 0;
    int divBy2 = 0;
    int bef0,bef1,bef2;
    bool didSth;

    for(int i=0; i<size; i++){
        didSth = 0;
        bef1 = beforeArr[(i-1+size)%size];
        bef2 = beforeArr[(i-2+size)%size];
        //cout<<bef1<<" "<<bef2<<endl;

        if(beforeArr[i]==2){
            //cases
            //cout<<bef1<<" "<<bef2<<endl;
            if(bef1==1 && bef2==0){
                didSth = 1;
                divBy2++;
                divBy3++;
            }
            else if(bef1==0 && bef2==0){
                didSth = 1;
                //divBy2++;
                divBy3++;
            }
            else if(bef1==0 && bef2==2){
                didSth = 1;
                //cout<<"1 before: "<<bef1<<", 2 before: "<<bef2<<endl;
                divBy2++;
                divBy3++;
            }
            else if(bef1==2 && bef2==0){ //this could be the same as 1 before
                //cout<<"1 before: "<<bef1<<", 2 before: "<<bef2<<endl;
                didSth = 1;
                divBy2++;
                divBy3++;
            }
            else if(bef1==2 && bef2==2){ //this could be the same as 1 before
                //cout<<"1 before: "<<bef1<<", 2 before: "<<bef2<<endl;
                didSth = 1;
                divBy2++;
                divBy3++;
            }
            if(didSth){
                beforeArr[(i-1+size)%size] = 0;
                beforeArr[(i-2+size)%size] = 0;
                beforeArr[i] = 0;
            }
            
        }
        else if(beforeArr[i]==1 && bef1==1){
            divBy3++;
            divBy2++;
            beforeArr[i]=0;
            beforeArr[(i-1+size)%size] = 0;
        }
    }

    for(int i=0; i<size; i++){
        if(beforeArr[i]==1){
            //cout<<"Case 2 ";
            divBy2++;
            beforeArr[i] = 0;
        }
    }
    
    //cout<<"It needs to be divided by 2 *: "<<divBy2<<endl;
    //cout<<"It needs to be divided by 3 *: "<<divBy3<<endl;

    // initialize permutasyon array
    int perm[validCtr];
    for(int i=0; i<validCtr; i++){
        perm[i] = i+1;
    }

    // get rid of unnecessary numbers of 2k
    int index = 1;
    while(divBy2>0){
        while(perm[index]%2==0 && divBy2>0){
            perm[index] = perm[index]/2;
            divBy2--;
            if(perm[index]==0){
                //cout<<"div by zero in 2k"<<endl;
            }
        }
        index = index+2;
    }

    // get rid of unnecessary numbers of 3k
    index = 2;
    while(divBy3>0){
        while(perm[index]%3==0 && divBy3>0){
            perm[index] = perm[index]/3;
            divBy3--;
            if(perm[index]==0){
                //cout<<"div by zero in 3k"<<endl;
            }
        }
        index = index+3;
    }

    //calculate perm
    long long int permResult = 1;
    for(int i=0; i<validCtr; i++){
        permResult = (permResult*perm[i])%1000000009;
    }

    //cout<<"Result = "<<permResult<<endl;
    outputFile<<permResult<<endl;

    
    inputFile.close();
    if (outputFile.is_open()) {
        outputFile.close();
    }

    delete[] hashTable;
    delete[] beforeArr;

    return 0;
}

/*
for(int i=0; i<size; i++){
        if(hashTable[i]!=-1){
            bef0 = beforeArr[i];
            bef1 = beforeArr[(i+1)%size];
            bef2 = beforeArr[(i+2)%size];
            didSth = 0;

            //cases - hope i didnt forget anything :(
            //if(bef2>0){
                cout<<"Checking: "<<hashTable[(i+1)%size]<<" and "<<hashTable[(i+2)%size]<<endl;
                cout<<bef1<<" "<<bef2<<endl;

                if(bef1==1 && bef2==2){
                    didSth = 1;
                    divBy3++;
                    divBy2++;
                }
                else if(bef1==1 && bef2==1){
                    didSth = 1;
                    divBy3++;
                    divBy2++;
                }
                else if(bef1==0 && bef2==2){
                    didSth = 1;
                    divBy3++;
                }
                else if(bef1==0 && bef2==1){
                    didSth = 1;
                    divBy2++;
                }
                else if(bef1==1 && bef2==0){
                    didSth = 1;
                    divBy2++;
                }
                else if(bef1==2 && bef2==0){
                    didSth = 1;
                    divBy2++;
                }

                if(didSth){
                    beforeArr[(i+1)%size] = 0;
                    beforeArr[(i+2)%size] = 0;
                    //beforeArr[i] = -1;
                }

            //}
            
        }
    }
*/