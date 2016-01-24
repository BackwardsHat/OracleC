//============================================================================
// Name        : HardwoodSellerC.cpp
// Author      : Esteban Parra
// Version     : 1
// Copyright   : It's free
// Description : Main class for the Hardwood Seller
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

#define MAX_BUFFER 256

int readInputFile(char *);
double deliveryTime();

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Error, usage: <program> <inputfile>\n";
        return 1;
    }
    
    if(!readInputFile(argv[1]))

	return 0;
}

/*
 * Method to read the input file
 */
int readInputFile(char *inputFilePath) {
    ifstream inFile(inputFilePath, ios::in);
    char line[MAX_BUFFER];

    if(!inFile) return 1; 

    cout << inputFilePath << " opened\n";

    int db_count = 0;
    while(inFile.getline(line, MAX_BUFFER, '\n'))
    {

        cout << db_count++ << ' ' << line << '\n';
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
