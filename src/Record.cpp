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

void Record::AddItem(char * type, int quantity) {
    v_items.push_back(std::pair<char *, int>(type, quantity));
}

const std::pair<char *, int>& Record::getItem(int index) const {
    return v_items.at(index);
}

std::string Record::getName()    const { return m_name;    }
std::string Record::getAddress() const { return m_address; }
std::string Record::getDate()    const { return m_date;    }
