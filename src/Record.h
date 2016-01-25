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
        void AddItem(char *, int);
        const std::pair<char *, int>& getItem(int) const; 

        std::string getName()    const;
        std::string getAddress() const;
        std::string getDate()    const;
    private:
        std::string m_name, m_address, m_date;
        std::vector< std::pair<char *, int> > v_items; 
};

#endif // RECORD_H_
