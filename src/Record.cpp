#include "Record.h"

Record::Record() {
    m_name = "";
    m_address = "";
    m_date = "01/01/0001";
//    m_totalPrice = 0.0;
//    m_maxDeliveryTime = 0.0;
}

Record::Record(
        std::string name,
        std::string address,
        std::string date) {
    m_name = name;
    m_address = address;
    m_date = date;
//    m_totalPrice = 0.0;
//    m_maxDeliveryTime = 0.0;
}
/*
Record::~Record() {
    for(std::vector< std::pair<char *, int> >::const_iterator
            it = v_items.begin(); it != v_items.end(); ++it) {
        delete it->first;
    }
}*/

void Record::AddItem(char * type, int quantity) {
    char * tmp = new char[strlen(type)];
    strcpy(tmp, type);
    v_items.push_back(std::pair<char *, int>(tmp, quantity));
}

const std::pair<char *, int>& Record::getItem(int index) const {
    return v_items.at(index);
}

const std::vector< std::pair<char *, int> >& Record::getItemList() const {
    return v_items;
}

std::ostream& operator<<(std::ostream& os, const Record& rec) {
    os << "Name:\t\t" << rec.m_name
       << "\nAddress:\t" << rec.m_address
       << "\nDate:\t\t" << rec.m_date
       << "\n\t---Orders---\n";
    for(std::vector< std::pair<char *, int> >::const_iterator
            it = rec.v_items.begin(); it != rec.v_items.end(); ++it) {
        os << "Wood Type: " << it->first << "\tBF: " << it->second << '\n';
    }
        
    return os;
}

std::string Record::getName()    const { return m_name;    }
std::string Record::getAddress() const { return m_address; }
std::string Record::getDate()    const { return m_date;    }
//double Record::getTotalPrice()   const { return m_totalPrice; }
//double Record::getMaxDeliveryTime() const { return m_maxDeliveryTime; }
