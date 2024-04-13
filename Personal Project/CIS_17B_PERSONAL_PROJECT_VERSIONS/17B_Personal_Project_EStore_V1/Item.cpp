
/* 
 * File:   Item.cpp
 * Author: Noel Perez
 * 
 * Created on March 23, 2024, 10:52 PM
 */
#include <iostream>
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