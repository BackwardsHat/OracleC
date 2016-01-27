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

// Comparison object for map object
struct charCompare {
    bool operator() (const char * s1, const char * s2) const {
       return strcmp(s1, s2) < 0;
    }
};

typedef map<char *, WoodItem, charCompare> LUT;
typedef vector< pair<char *, int> > ItemList;
typedef vector<Record> RecordList;

// -------- Prototypes --------
void createRecord   (char *, RecordList&);
void readItems      (char *, RecordList&);
int  readInputFile  (char *, RecordList&);
void populateInventory(LUT&);
double deliveryTime (const ItemList::const_iterator&, const LUT&);
void printBuyerInfo (const RecordList::const_iterator&);
void printOrderInfo (const ItemList&, const LUT&);
void processAndPrint(const RecordList&, const LUT&);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Error, usage: <program> <inputfile>\n";
        return 1;
    }
    
    RecordList records;     // Holds customer info and orders 
    LUT inventory;          // Holds shop inventory and prices 

    populateInventory(inventory);
    if( !readInputFile(argv[1], records) )
        processAndPrint(records, inventory);

	return 0;
}

// Adds new record to customer list
void createRecord(char * line, RecordList& records) {
    size_t index = 0;
    char * rec_info[4];

    // Tokenize based off ';'
    rec_info[index] = strtok(line, ";");
    while(rec_info[index++] != NULL) 
        rec_info[index] = strtok(NULL, ";");
    
    // Format: Record(Name, Address, Date)
    records.push_back( Record(rec_info[0], rec_info[1], rec_info[2]) ); 
}

void readItems(char * line, RecordList& records) {
    size_t numTokens;
    vector<char *> tokens;
    char * token;

    // Tokenize based off ';'
    token = strtok(line, ";");
    while(token != NULL) {
        tokens.push_back(token);
        token = strtok(NULL, ";"); 
    }

    // Adds order items to corresponding record entry
    numTokens = tokens.size();
    for(size_t i = 0; i < numTokens; i++) {
        char * type = strtok(tokens.at(i), ":"); 
        int boardFeet = abs(atoi( strtok(NULL, ":") )); 
        if(boardFeet > 1000)    // Only allow orders from 0 to 1000
            boardFeet = 1000;
        records.back().AddItem(type, boardFeet); 
    }
}

/*
 * Method to read the input file
 */
int readInputFile(char *inputFilePath, RecordList& records) {
    ifstream inFile(inputFilePath, ios::in);
    char line[MAX_BUFFER]; 
    
    if(!inFile) {
        cout << "Could not open " << inputFilePath << "\n";
        return 1;   // Failure 
    }

    while(inFile.getline(line, MAX_BUFFER, '\n')) 
        if(!strchr(line, ':'))  // Orders contain ':'
            createRecord(line, records);
        else
            readItems(line, records);
    
    inFile.close();
    return 0;       // Success
}

// Fills the inventory with WoodItem objects
// Format: <key, WoodItem(Name, baseDeliveryTime, price)>
void populateInventory(LUT& inventory) {
    inventory.insert(LUT::value_type((char *)"Cherry",
        WoodItem("Cherry", 2.5, 5.95)));
    inventory.insert(LUT::value_type((char *)"Curly Maple",
        WoodItem("Curly Maple", 1.5, 6.00)));
    inventory.insert(LUT::value_type((char *)"Genuine Mahogany",
        WoodItem("Genuine Mahogany", 3.0, 9.60)) );
    inventory.insert(LUT::value_type((char *)"Wenge",
        WoodItem("Wenge", 5.0, 22.35)) );
    inventory.insert(LUT::value_type((char *)"White Oak",
        WoodItem("White Oak", 2.3, 6.70)) );
    inventory.insert(LUT::value_type((char *)"Sawdust",
        WoodItem("Sawdust", 1.0, 1.5)) );
}

/*
 * Method to compute the deliveryTime
 */
double deliveryTime(
        const ItemList::const_iterator& item,
        const LUT& inventory) {
	double deliveryETA = 0.0; 

    char * woodType = item->first;
    double baseDT = inventory.find(woodType)->second.getBaseDeliveryTime();
    int boardFeet = item->second;

    boardFeet = ceil(boardFeet/100.0);  // per 100 BF
    boardFeet <= 5 ? deliveryETA = boardFeet * baseDT :
                     deliveryETA = 5.5 * baseDT;

	return deliveryETA;
}

void printBuyerInfo(const RecordList::const_iterator& buyer) {
    cout << "\n\n" 
         << left << setw(12) << "Name:" << buyer->getName() << '\n'
         << setw(12) << "Address:"  << buyer->getAddress()  << '\n'
         << setw(12) << "Date:"     << buyer->getDate()     << '\n';
}   

void printOrderInfo(const ItemList& itemList, const LUT& inventory) {
    double totalPrice = 0, maxDeliveryTime =  0;

    cout << "\t-----------Order------------\n"
         << setw(18) << "Wood Type"
         << setw(12) << "BF"
         << setw(15) << "Price Per BF"
         << "Cost" << '\n';
    for(ItemList::const_iterator it = itemList.begin();
            it != itemList.end(); ++it) {
        int BF = it->second;
        double woodPrice = inventory.find(it->first)->second.getPrice();
        double itemDT = deliveryTime(it, inventory);

        totalPrice += BF * woodPrice;
        if(maxDeliveryTime < itemDT)
            maxDeliveryTime = itemDT; 

        cout << fixed << setprecision(2) << left << setw(18) << it->first 
             << setw(12) << it->second
             << setw(15) << woodPrice
             << BF * woodPrice
             << '\n'; 
    }

    cout << "\nTotal Price:\t$" << totalPrice
         << "\nDelivery ETA:\t" << maxDeliveryTime << " hours\n";
}

void processAndPrint(const RecordList& records, const LUT& inventory) {
    for(RecordList::const_iterator it = records.begin();
            it != records.end(); ++it) {
        printBuyerInfo(it);
        printOrderInfo(it->getItemList(), inventory);
   }
}
