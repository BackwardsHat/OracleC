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
        void AddItem(char *, int); // leaks memory
        const std::pair<char *, int>& getItem(int) const; 
        const std::vector< std::pair<char *, int> >& getItemList() const;

        friend std::ostream& operator<<(std::ostream&, const Record&);
        
        std::string getName()    const;
        std::string getAddress() const;
        std::string getDate()    const;
    //    double getTotalPrice()   const;
    //    double getMaxDeliveryTime() const;

    private:
        std::string m_name, m_address, m_date;
    //    double m_totalPrice, m_maxDeliveryTime;
        std::vector< std::pair<char *, int> > v_items; 
};

#endif // RECORD_H_
