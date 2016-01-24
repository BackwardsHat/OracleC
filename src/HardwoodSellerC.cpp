//============================================================================
// Name        : HardwoodSellerC.cpp
// Author      : Esteban Parra
// Version     : 1
// Copyright   : It's free
// Description : Main class for the Hardwood Seller
//============================================================================

#include <iostream>
#include <fstream>
#include <string.h>
#include "Record.h"

using namespace std;

#define MAX_BUFFER 256

int readInputFile(char *, vector<Record>&);
double deliveryTime();

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Error, usage: <program> <inputfile>\n";
        return 1;
    }
    
    std::vector<Record> records; 
    if( !readInputFile(argv[1], records) )

	return 0;
}

void createRecord(char * line, vector<Record>& records) {
    size_t index = 0;
    char * rec_info[4];

    rec_info[index] = strtok(line, ";");

    while(rec_info[index++] != NULL) {
        cout << rec_info[index-1] << '\n';
        rec_info[index] = strtok(NULL, ";");
    }
    
    records.push_back( Record(rec_info[0], rec_info[1], rec_info[2]) ); 
}

void readItems(char * line, vector<Record>& records) {
    size_t index = 0;
    char * token;
    char * type;
    int quantity;

    token = strtok(line, ";");
    while(token != NULL) {

        cout << token << '\n';
        token = strtok(NULL, ";"); 
    }
}

/*
 * Method to read the input file
 */
int readInputFile(char *inputFilePath, vector<Record>& records) {
    ifstream inFile(inputFilePath, ios::in);
    char line[MAX_BUFFER]; 

    if(!inFile) {
        cout << "Could not open " << inputFilePath << "\n";
        return 1; 
    }

    while(inFile.getline(line, MAX_BUFFER, '\n')) {
        if(!strchr(line, ':'))
            createRecord(line, records);
        else
            readItems(line, records);
        cout << '\n';
    }
    
    inFile.close();
    return 0;
}

/*
 * Method to compute the deliveryTime
 */
double deliveryTime() {
	double deliveryETA = 0.0;
	return deliveryETA;
}
