/* 
 * File:   Item.h
 * Author: Noel Perez
 * Created on March 23, 2024, 10:52 PM
 */

#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

static const unsigned short SIZE = 100;

class Item {
private:
    string _name;
    float _price;
    int _itemNum;
    int _quantity;

public:
    Item(): _name(""), _price(0), _quantity(0), _itemNum(0){};
    Item(int itemNum, const string &name, float price, int quantity=1  );
    Item(const Item& orig);
    virtual ~Item();

    void setItemNum(const int &num)   { this->_itemNum = num; };
    void setName(const string & name) {this->_name = name; };
    void setPrice(const float &price) {this->_price = price; };
    void setQuant(const int &quant)   {this->_quantity = quant; } 
    
    int getItemNum()const {return this->_itemNum; }
    string getName()const {return this->_name; }
    float getPrice()const {return this->_price; }
    int getQuant()const {return this->_quantity; }
    
    void serialize(ofstream& ofs) const ;
    void deserialize(ifstream& ifs) ;
    
    void display();
    
};

#endif /* ITEM_H */

