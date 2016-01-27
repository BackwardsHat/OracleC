// Author: Joseph Furiate
// GitHub: BackwardsHat
// Summary: Class to hold customer info (i.e. Name, address, order)

#include <iostream>
#include <string.h>
#include <vector>
#include <tuple>
#include "WoodItem.h"

#ifndef RECORD_H_
#define RECORD_H_

class Record {
public:
    Record();
    Record(std::string, std::string, std::string);
//    ~Record();
    void AddItem(char *, int);
    const std::pair<char *, int>& getItem(int) const; 
    const std::vector< std::pair<char *, int> >& getItemList() const;

    
    std::string getName()    const;
    std::string getAddress() const;
    std::string getDate()    const;
//    double getTotalPrice()   const;
//    double getMaxDeliveryTime() const;

private:
    std::string m_name, m_address, m_date;
//    double m_totalPrice, m_maxDeliveryTime;
    
    // Contains customer's order list
    // Format: <item name, quantity ordered>
    std::vector< std::pair<char *, int> > v_items; 
};

#endif // RECORD_H_
