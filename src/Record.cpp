#include "Record.h"

Record::Record() {
    m_name = "";
    m_address = "";
    m_date = "01/01/0001";
}

Record::Record(
        std::string name,
        std::string address,
        std::string date) {
    m_name = name;
    m_address = address;
    m_date = date;
}

void Record::AddItem(const WoodItem& item) {
    v_items.push_back(item);
}

std::string Record::getName()    { return m_name;    }
std::string Record::getAddress() { return m_address; }
std::string Record::getDate()    { return m_date;    }
