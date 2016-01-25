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
#include <map>
#include <vector>
#include "Record.h"

using namespace std;

#define MAX_BUFFER 256

struct charCompare {
    bool operator() (const char * s1, const char * s2) const {
       return strcmp(s1, s2) < 0;
    }
};

typedef map<char *, WoodItem, charCompare> LUT;

int readInputFile(char *, vector<Record>&);
double deliveryTime(char *);

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

void readItems(char * line, vector<Record>& records, LUT& lookUpTable) {
    size_t numTokens;
    vector<char *> tokens;
    char * token;

    token = strtok(line, ";");
    while(token != NULL) {
        tokens.push_back(token);
        token = strtok(NULL, ";"); 
    }
    numTokens = tokens.size();
    for(size_t i = 0; i < numTokens; i++) {
        char * type = strtok(tokens.at(i), ":"); 
        int quantity = atoi( strtok(NULL, ":") );
        cout << "Type: " << type << "\nQuantity: " << quantity << '\n';
        cout << "Delivery Time: " 
             << (float) lookUpTable.find(type)->second.getBaseDeliveryTime()
             << " hours\n";
        records.back().AddItem(type, quantity); 
    }
}

void createLookUpTable(LUT& lookUpTable) {
    lookUpTable.insert(LUT::value_type((char *)"Cherry",
        WoodItem("Cherry", 2.5, 5.95)));
    lookUpTable.insert(LUT::value_type((char *)"Curly Maple",
        WoodItem("Curly Maple", 1.5, 6.00)));
    lookUpTable.insert(LUT::value_type((char *)"Genuine Mahogany",
        WoodItem("Genuine Mahogany", 3.0, 9.60)) );
    lookUpTable.insert(LUT::value_type((char *)"Wenge",
        WoodItem("Wenge", 5.0, 22.35)) );
    lookUpTable.insert(LUT::value_type((char *)"White Oak",
        WoodItem("White Oak", 2.3, 6.70)) );
    lookUpTable.insert(LUT::value_type((char *)"Sawdust",
        WoodItem("Sawdust", 1.0, 1.5)) );
}

/*
 * Method to read the input file
 */
int readInputFile(char *inputFilePath, vector<Record>& records) {
    ifstream inFile(inputFilePath, ios::in);
    char line[MAX_BUFFER]; 
    LUT lookUpTable;
    createLookUpTable(lookUpTable);

    if(!inFile) {
        cout << "Could not open " << inputFilePath << "\n";
        return 1; 
    }

    while(inFile.getline(line, MAX_BUFFER, '\n')) {
        if(!strchr(line, ':'))
            createRecord(line, records);
        else
            readItems(line, records, lookUpTable);
        cout << '\n';
    }
    
    inFile.close();
    return 0;
}



/*
 * Method to compute the deliveryTime
 */
double deliveryTime(char * woodType) {
	double deliveryETA = 0.0; 
	return deliveryETA;
}
