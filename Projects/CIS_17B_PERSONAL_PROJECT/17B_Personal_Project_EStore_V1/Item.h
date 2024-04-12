
/* 
 * File:   Item.h
 * Author: Noel Perez
 *
 * Created on March 23, 2024, 10:52 PM
 */

#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>

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
    Item(const Item& orig);
    virtual ~Item();


};

#endif /* ITEM_H */

