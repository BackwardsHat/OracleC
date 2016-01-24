#include <iostream>
#include <string.h>
#include <vector>
#include "WoodItem.h"

#ifndef RECORD_H_
#define RECORD_H_

class Record {
    public:
        Record();
        Record(std::string, std::string, std::string);
        void AddItem(const WoodItem&);

        std::string getName();
        std::string getAddress();
        std::string getDate();
    private:
        std::string m_name, m_address, m_date;
        std::vector<WoodItem> v_items; 
};

#endif // RECORD_H_
