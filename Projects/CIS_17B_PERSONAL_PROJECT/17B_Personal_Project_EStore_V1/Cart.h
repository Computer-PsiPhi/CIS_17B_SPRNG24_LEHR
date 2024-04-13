
/* 
 * File:   Cart.h
 * Author: Noel Perez
 * Created on March 23, 2024, 10:53 PM
 */

#ifndef CART_H
#define CART_H

#include "Item.h"

class Cart {
private:
    Item _items[SIZE];
    int _itemCount;
    

public:
    Cart(): _itemCount{0}, _items{} {};
    Cart(const Cart& orig);
    virtual ~Cart();

    void resetCount(){this->_itemCount = 0;};
    int getCount()const {return this->_itemCount;};
    const Item &getItem(int index)const{ return this->_items[index]; };
    
    void addItem(const Item &item);
    void removeItem(int index);
    void showCart();
    float checkOut();
    

};
#endif /* CART_H */

