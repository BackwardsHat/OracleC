/*
 * WoodItem.cpp
 *
 *  Created on: Aug 24, 2015
 *      Author: Joseph Furiate
 */

#include "WoodItem.h"

// Default Constructor
WoodItem::WoodItem() {
	type = "";
	baseDeliveryTime = 0.0;
	price = 0.0;
}

WoodItem::WoodItem(std::string woodType, double deliveryTime, double itemPrice) {
	type = woodType;
	baseDeliveryTime = deliveryTime;
	price = itemPrice;
}

std::string WoodItem::getType()         const { return type; }
double WoodItem::getPrice()             const { return price; }
double WoodItem::getBaseDeliveryTime()  const { return baseDeliveryTime; }

