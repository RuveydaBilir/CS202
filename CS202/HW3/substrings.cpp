/**
* Title: Hashing
* Author : Ruveyda Bilir
* ID: 22203082
* Section : 1
* Homework : 3
* Description : Substrings question
*/
using namespace std;
#include <iostream>
#include <fstream>
#include <algorithm>

struct Tuple{
    long long hash1;
    long long hash2;
    int occuranceNum;
    int length;
};

int pow(const int base, const int power){
    int result = 1;
    for (int i = 0; i < power; i++) {
        result = (result * base);
    }
    return result;
}

long long powMod(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long hashFunction(char* text, int length, int base, int prime) {
    long long hash = 0;
    for (int i = 0; i < length; i++) {
        int value = (text[i] - 'a' + 1);  
        hash = (base * hash + value) % prime;
        if (hash < 0) hash += prime;
    }
    return hash;
}

int robinKarp(char* text, long long patternHash, long long patternHash2, const int textSize, const int patternSize, const int prime1, const int prime2) {
    int d = 4;  // it consists of a, b, c, d
    long long hashMult1 = powMod(d, patternSize - 1, prime1);
    long long hashMult2 = powMod(d, patternSize - 1, prime2);

    long long curWindowHash = hashFunction(text, patternSize, d, prime1);
    long long curWindowHash2 = hashFunction(text, patternSize, d, prime2);

    int finalWindow = textSize - patternSize;
    int counter = 0;

    for (int i = 0; i <= finalWindow; i++) {
        if (patternHash == curWindowHash && patternHash2 == curWindowHash2) {
            //cout << "Pattern found at index " << i << endl;
            counter++;
        }

        if (i != finalWindow) {
            curWindowHash = (d * (curWindowHash - (long long)(text[i] - 'a' + 1) * hashMult1) + (text[i + patternSize] - 'a' + 1)) % prime1;
            curWindowHash2 = (d * (curWindowHash2 - (long long)(text[i] - 'a' + 1) * hashMult2) + (text[i + patternSize] - 'a' + 1)) % prime2;

            if (curWindowHash < 0) curWindowHash += prime1;
            if (curWindowHash2 < 0) curWindowHash2 += prime2;
        }
    }
    return counter;
}

//binary searchle sorted arrayde degeri arayip indexi returnluyo
int findHashIndex(Tuple* arr, const int arrSize, const long long value, const long long value2){
    if (arrSize <= 0) {
        return -1; // Value not found
    }

    int mid = arrSize / 2; // Middle index
    long long midValue = arr[mid].hash1;

    if (midValue == value) {
        if(arr[mid].hash2 == value2){
            return mid; // Value found at the middle
        }
    } else if (midValue > value) {
        // Search in the left half
        return findHashIndex(arr, mid, value, value2);
    } else {
        // Search in the right half
        int rightResult = findHashIndex(arr + mid + 1, arrSize - mid - 1, value, value2);
        if (rightResult == -1) {
            return -1; // Value not found
        }
        return mid + 1 + rightResult; // Adjust index for the right half
    }

    return -1; //test amacli bunu degistir
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

    int prime1 = pow(10,9) + 7;
    int prime2 = pow(10,9) + 9;
    int size = 0;
    char* text = new char[100000];

    // initialize text:
    char argument;
    /*if(!(inputFile>>argument)){
                cout<<"Error in 190"<<endl;

        return 1;
    }
    */

    while(inputFile.get(argument) && argument != '\n'){
        text[size] = argument;
        size++;
    }
    //cout<<"Size: "<<size<<endl;

    int patternNum;
    //std::streampos thirdLinePos = inputFile.tellg();
    
    if(!(inputFile>>patternNum)){
        cout<<"Error in 133"<<endl;
        delete[] text;
        return 1;
    }
    // burada positionu storela
    
    inputFile.get(argument); //jumps to next line directly
    //std::streampos thirdLinePos = inputFile.tellg();
    //cout<<"Jump argument: "<<argument;
    char* pattern = new char[100000];
    //int patternHash[patternNum];
    //int patternHash2[patternNum];
    //int patternLengths[patternNum];
    Tuple patternArr[patternNum];
    int patHashCtr = 0;
    //cout<<" Pattern num: "<<patternNum<<endl;
    for(int i=0; i<patternNum; i++){
        int patternSize = 0;
        //initializes current patterns char array
        while(inputFile.get(argument) && argument != '\n'){
            pattern[patternSize] = argument;
            patternSize++;
            //cout<<argument;
        }
        //cout<<"Pattern size: "<<patternSize<<endl;
        long long hash1p = hashFunction(pattern,patternSize, 4,prime1);
        long long hash2p = hashFunction(pattern,patternSize, 4,prime2);

        //cout<<"Hash 1.1: "<<hash1p<<endl;
        //cout<<"Hash 1.2: "<<hash2p<<endl;
        int occur = robinKarp(text, hash1p, hash2p, size, patternSize, prime1, prime2);
        //cout<<"Occur num: "<<occur<<endl;
        patternArr[patHashCtr] = {hash1p, hash2p, occur, patternSize};
        //patternLengths[patHashCtr] = patternSize;
        //patternHash[patHashCtr] = hashFunction(pattern,size, patternSize,prime1);
        //patternHash2[patHashCtr] = hashFunction(pattern,size, patternSize,prime2);
    
        patHashCtr++;
    }

    //cout<<"Pat hash ctr: "<<patHashCtr<<endl;
    std::sort(patternArr, patternArr + patternNum, [](const Tuple& a, const Tuple& b) {
        return a.hash1 < b.hash1;
    });
    
    inputFile.clear();
    inputFile.seekg(0);
    string line;
    int lineCounter = 0;

    // Read and skip the first two lines
    while (lineCounter < 2 && getline(inputFile,line)) {
        lineCounter++;
    }

    for(int i=0; i<patternNum; i++){
        long long hash1, hash2;
        int patternSize = 0;
        //initializes current patterns char array
        //inputFile>>argument;
        while(inputFile.get(argument) && argument != '\n'){
            pattern[patternSize] = argument;
            patternSize++;
            //cout<<argument;
        }
        //cout<<"2. Pattern size: "<<patternSize<<endl;

        hash1 = hashFunction(pattern, patternSize, 4, prime1);
        hash2 = hashFunction(pattern, patternSize, 4, prime2);

        int index = findHashIndex(patternArr,patternNum,hash1,hash2);
        //cout<<"Index: "<< index<<endl;
        if(/*indexhash1 == indexhash2 &&*/ index!= -1){
            outputFile<<patternArr[index].occuranceNum<<endl;
        }
        //else{
        //    outputFile<<"Index -1"<<endl;
        //}
    }

    inputFile.close();
    if (outputFile.is_open()) {
        outputFile.close();
    }

    //Delete statements
    delete[] pattern;
    delete[] text;
    return 0;
}

/*
int findHash1(Tuple* arr, const int arrSize, const int value){
    if (arrSize <= 0) {
        return -1; // Value not found
    }

    int mid = arrSize / 2; // Middle index
    int midValue = arr[mid].hash1;

    if (midValue == value) {
        return mid; // Value found at the middle
    } else if (midValue > value) {
        // Search in the left half
        return findHash1(arr, mid, value);
    } else {
        // Search in the right half
        int rightResult = findHash1(arr + mid + 1, arrSize - mid - 1, value);
        if (rightResult == -1) {
            return -1; // Value not found
        }
        return mid + 1 + rightResult; // Adjust index for the right half
    }
}

int findHash2(Tuple* arr, const int arrSize, const int value){
    if (arrSize <= 0) {
        return -1; // Value not found
    }

    int mid = arrSize / 2; // Middle index
    int midValue = arr[mid].hash2;

    if (midValue == value) {
        return mid; // Value found at the middle
    } else if (midValue > value) {
        // Search in the left half
        return findHash2(arr, mid, value);
    } else {
        // Search in the right half
        int rightResult = findHash2(arr + mid + 1, arrSize - mid - 1, value);
        if (rightResult == -1) {
            return -1; // Value not found
        }
        return mid + 1 + rightResult; // Adjust index for the right half
    }
}
int powMod(const int base, const int power, const int prime){
    int result = 1;
    for (int i = 0; i < power; i++) {
        result = (result * base) % prime;
    }
    return result;
}

int hashFunction(char* text, int length, int base, int prime) {
    int hash = 0;
    for (int i = 0; i < length; i++) {
        int value = (text[i] - 'a' + 1);  
        hash = (base * hash + value) % prime;
        if (hash < 0) hash += prime;
    }
    return hash;
}

int robinKarp(char* text, int patternHash, int patternHash2, const int textSize, const int patternSize, const int prime1, const int prime2){
    int d = 4; //it consists of a, b, c, d
    int hashMult1 = powMod(d, patternSize - 1, prime1);
    int hashMult2 = powMod(d, patternSize - 1, prime2);

    int curWindowHash = hashFunction(text, patternSize, d, prime1);
    int curWindowHash2 = hashFunction(text, patternSize, d, prime2);

    int finalWindow = textSize - patternSize;
    int counter = 0;

    for (int i = 0; i <= finalWindow; i++) {
        //cout<<"* ";
        if (patternHash == curWindowHash && patternHash2 == curWindowHash2) {
            cout << "Pattern found at index " << i << endl;
            counter++;
        }

        if (i != finalWindow) {
            //cout<<"@";
            //TODO: Here is a mistake
            curWindowHash = (d * (curWindowHash - (text[i]-'a'+1) * hashMult1) + (text[i + patternSize]-'a'+1)) % prime1;
            curWindowHash2 = (d * (curWindowHash2 - (text[i]-'a'+1) * hashMult2) + (text[i + patternSize]-'a'+1)) % prime2;

            if (curWindowHash < 0) curWindowHash += prime1;
            if (curWindowHash2 < 0) curWindowHash2 += prime2;
        }
    }
    return counter;
}
*/