//============================================================================
// Name        : HardwoodSellerC.cpp
// Author      : Esteban Parra 
// Editor      : Joseph Furiate
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
#include "WoodItem.h"

using namespace std;

#define MAX_BUFFER 256

// Contains customer information
struct Record {
    Record(const string& name, const string& address, const string& date) {
        this->name = name;
        this->address = address;
        this->date = date;
    }
    string name, address, date;
    vector< pair<string, int> > orderList; 
};

typedef map<string, WoodItem> LUT;
typedef vector< pair<string, int> > OrderList;
typedef vector<Record> RecordList;

// -------- Prototypes --------
void createRecord   (char *, RecordList&);
void readItems      (char *, RecordList&);
int  readInputFile  (char *, RecordList&);
void populateInventory(LUT&);
double deliveryTime (const OrderList::const_iterator&, const LUT&);
void printBuyerInfo (const RecordList::const_iterator&);
void printOrderInfo (const OrderList&, const LUT&);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Error, usage: ./<program> <inputfile>\n";
        return 1;
    }
    
    int exit_status;        // Holds file status, succuss = 0, failure = 1 
    RecordList records;     // Holds customer info and orders 
    LUT inventory;          // Holds shop inventory and prices 

    populateInventory(inventory);
    exit_status = readInputFile(argv[1], records);
    if(!exit_status)
        for(RecordList::const_iterator it = records.begin();
            it != records.end(); ++it) {
            printBuyerInfo(it);
            printOrderInfo(it->orderList, inventory);
        } 

    return exit_status;
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
    records.push_back(Record(rec_info[0], rec_info[1], rec_info[2])); 
}

// Seperates order info from line in form <type>:<BF>;...;<type>:<BF>
//    and stores in to the customer record
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
        // More tokenization
        char * type = strtok(tokens.at(i), ":"); 
        int boardFeet = abs(atoi( strtok(NULL, ":") )); 
        if(boardFeet > 1000)    // Only allow orders from 0 to 1000
            boardFeet = 1000;
        records.back().orderList.push_back(
            OrderList::value_type(type, boardFeet));
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
//  note: Inventory could be read from a file, but hard-coding was simplier
void populateInventory(LUT& inventory) {
    // Format: <key, WoodItem(Name, baseDeliveryTime, price)>
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
        const OrderList::const_iterator& item,
        const LUT& inventory) {
	double deliveryETA = 0.0; 

    string woodType = item->first;
    double baseDT = inventory.find(item->first)->second.getBaseDeliveryTime();
    int boardFeet = item->second;

    boardFeet = ceil(boardFeet/100.0);  // per 100 BF
    boardFeet <= 5 ? deliveryETA = boardFeet * baseDT :
                     deliveryETA = 5.5 * baseDT;

	return deliveryETA;
}

void printBuyerInfo(const RecordList::const_iterator& buyer) {
    cout << "\n\n" 
         << left << setw(12) << "Name:" << buyer->name << '\n'
         << setw(12) << "Address:"  << buyer->address  << '\n'
         << setw(12) << "Date:"     << buyer->date     << '\n';
}   

void printOrderInfo(const OrderList& itemList, const LUT& inventory) {
    double totalPrice = 0, maxDeliveryTime = 0;

    cout << "\t-----------Order------------\n"
         << setw(18) << "Wood Type"
         << setw(12) << "BF"
         << setw(15) << "Price Per BF"
         << "Cost" << '\n';

    for(OrderList::const_iterator it = itemList.begin();
            it != itemList.end(); ++it) {
        int BF = it->second;
        double woodPrice = inventory.find(it->first)->second.getPrice();
        double itemDT = deliveryTime(it, inventory);

        totalPrice += BF * woodPrice;   // Add to rolling sum
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

