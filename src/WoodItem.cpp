/*
 * WoodItem.cpp
 *
 *  Created on: Aug 24, 2015
 *      Author: USER
 */

#include "WoodItem.h"
/*
 * Empty constructor
 */
WoodItem::WoodItem() {
	type = "";
	baseDeliveryTime = 0.0;
	price = 0.0;
}

/*
 * Method to initialize a tic tac toe game
 * Initializes board and turn
 */
WoodItem::WoodItem(std::string woodType, double deliveryTime, double itemPrice) {
	type = woodType;
	baseDeliveryTime = deliveryTime;
	price = itemPrice;
}

std::string WoodItem::getType()         const { return type; }
double WoodItem::getPrice()             const { return price; }
double WoodItem::getBaseDeliveryTime()  const { return baseDeliveryTime; }

