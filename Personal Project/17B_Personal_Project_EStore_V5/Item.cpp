
/* 
 * File:   Item.cpp
 * Author: Noel Perez
 * Created on March 23, 2024, 10:52 PM
 */
#include <iostream>
#include <string>
#include "Item.h"
using namespace std;

//Item::Item() {
//}

Item::Item(const Item& orig) {
}

Item::~Item() {
}

Item::Item(int itemNum, const string &name, float price, int quantity ):
_itemNum{itemNum}, _name{name}, _price{price} , _quantity{quantity}{ }


// Item serialize function definition 
void Item::serialize(ofstream& ofs) const {
        unsigned int nameLen = _name.length();
        ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen)); // Write length of name
        ofs.write(_name.c_str(), nameLen); // Write name data
        ofs.write(reinterpret_cast<const char*>(&_price), sizeof(_price)); // Write price
        ofs.write(reinterpret_cast<const char*>(&_itemNum), sizeof(_itemNum)); // Write item number
        ofs.write(reinterpret_cast<const char*>(&_quantity), sizeof(_quantity)); // Write quantity
    }

// Item deserialize function definition 
  void Item::deserialize(ifstream& ifs){
      unsigned int nameLength;
      ifs.read(reinterpret_cast<char*> (&nameLength), sizeof (nameLength));
      _name.resize(nameLength);
      ifs.read(&_name[0], nameLength);
      ifs.read(reinterpret_cast<char*>(&_price), sizeof(_price));
      ifs.read(reinterpret_cast<char*>(&_itemNum), sizeof(_itemNum));
      ifs.read(reinterpret_cast<char*>(&_quantity), sizeof(_quantity));     
}