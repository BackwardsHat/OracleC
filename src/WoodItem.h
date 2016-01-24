/*
 * WoodItem.h
 *
 *  Created on: Aug 24, 2015
 *      Author: Esteban
 */


#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

#ifndef WOODITEM_H_
#define WOODITEM_H_

class WoodItem {

public:

	// Member functions declaration
	WoodItem();
	WoodItem(std::string woodType, double deliveryTime, double itemPrice);

private:
    std::string type;
	double baseDeliveryTime;
	double price;
};

#endif /* WOODITEM_H_ */
