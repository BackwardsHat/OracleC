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
#include <cmath>
#include <iomanip>
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
typedef vector< pair<char *, int> > ItemList;

int readInputFile(char *, vector<Record>&);
void populateLookUpTable(LUT&);
void processAndDisplay(const vector<Record>&, const LUT&);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Error, usage: <program> <inputfile>\n";
        return 1;
    }
    
    vector<Record> records; 
    LUT lookUpTable;
    populateLookUpTable(lookUpTable);
    if( !readInputFile(argv[1], records) )
        processAndDisplay(records, lookUpTable);

	return 0;
}

void createRecord(char * line, vector<Record>& records) {
    size_t index = 0;
    char * rec_info[4];

    rec_info[index] = strtok(line, ";");

    while(rec_info[index++] != NULL) 
        rec_info[index] = strtok(NULL, ";");
    
    records.push_back( Record(rec_info[0], rec_info[1], rec_info[2]) ); 
}

void readItems(char * line, vector<Record>& records) {
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
        int boardFeet = atoi( strtok(NULL, ":") );
        records.back().AddItem(type, boardFeet); 
    }
}

// Fills the table with WoodItem objects
// Format: Name, baseDeliveryTime, price
void populateLookUpTable(LUT& lookUpTable) {
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
    
    if(!inFile) {
        cout << "Could not open " << inputFilePath << "\n";
        return 1; 
    }

    while(inFile.getline(line, MAX_BUFFER, '\n')) 
        if(!strchr(line, ':'))
            createRecord(line, records);
        else
            readItems(line, records);
    
    inFile.close();
    return 0;
}


/*
 * Method to compute the deliveryTime
 */
double deliveryTime(
        const ItemList& itemList, 
        const LUT& lookUpTable) {
	double deliveryETA = 0.0; 

    // Find max delivery time 
    for(ItemList::const_iterator it = itemList.begin();
           it != itemList.end(); ++it) {
        char * woodType = it->first;
        double baseDT = lookUpTable.find(woodType)->second.getBaseDeliveryTime();
        double unitDT = 0;
        int boardFeet = it->second;
        boardFeet = ceil(boardFeet/100.0);  // per 100 BF
        boardFeet <= 5 ? unitDT = boardFeet * baseDT : unitDT = 5.5 * baseDT;
        if(deliveryETA < unitDT)
            deliveryETA = unitDT; 
    } 

	return deliveryETA;
}

double calcTotalPrice(
        const ItemList& itemList, 
        const LUT& lookUpTable) {
    double sumPrice = 0.0;
    for(ItemList::const_iterator it = itemList.begin();
        it != itemList.end(); ++it ) {
        char * woodType = it->first;
        double woodPrice = lookUpTable.find(woodType)->second.getPrice(); 
        int boardFeet = it->second;
        sumPrice += boardFeet * woodPrice; 
    }
    return sumPrice;
}

void printItems(
        const ItemList& itemList,
        const LUT& lookUpTable) {
    cout << setw(18) << "Wood Type"
         << setw(12) << "BF"
         << setw(15) << "Price Per BF"
         << "Cost" << '\n';
    for(ItemList::const_iterator it = itemList.begin();
            it != itemList.end(); ++it) {
        double woodPrice = lookUpTable.find(it->first)->second.getPrice();
        cout << fixed << setprecision(2) << left << setw(18) << it->first 
             << setw(12) << it->second
             << setw(15) << woodPrice
             << it->second * woodPrice
             << '\n'; 
    }
}


void processAndDisplay(const vector<Record>& records, const LUT& lookUpTable) {
    double totalPrice = 0, maxDeliveryTime =  0;

    for(vector<Record>::const_iterator it = records.begin();
            it != records.end(); ++it) {
        totalPrice = calcTotalPrice(it->getItemList(), lookUpTable);
        maxDeliveryTime = deliveryTime(
                it->getItemList(), lookUpTable);
        cout << "\n\n" 
             << left << setw(12) << "Name:" << it->getName() << '\n'
             << setw(12) << "Address:"  << it->getAddress()  << '\n'
             << setw(12) << "Date:"     << it->getDate()     << '\n'
             << "\t-----------Order------------\n";
        printItems(it->getItemList(), lookUpTable);
        cout << "\nTotal Price:\t$" << totalPrice
             << "\nDelivery ETA:\t" << maxDeliveryTime << " hours\n";
    }

}
