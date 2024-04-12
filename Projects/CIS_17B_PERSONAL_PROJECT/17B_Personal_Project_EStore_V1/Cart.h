
/* 
 * File:   Cart.h
 * Author: Noel Perez
 *
 * Created on March 23, 2024, 10:53 PM
 */

#ifndef CART_H
#define CART_H

#include "Item.h"

class Cart {
private:
    Item _items[SIZE];
    int _cartItems;
    

public:
    Cart();
    Cart(const Cart& orig);
    virtual ~Cart();


};

#endif /* CART_H */

