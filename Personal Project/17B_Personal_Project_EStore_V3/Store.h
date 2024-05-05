 
/* 
 * File:   Store.h
 * Author: Noel Perez
 *
 * Created on March 23, 2024, 10:56 PM
 */

#ifndef STORE_H
#define STORE_H
#include "Item.h"

#include "User.h"

class User;

class Store {
private:
    Item _inventory[SIZE];
    int _totalItems;

public:
    Store(): _totalItems{0}, _inventory{} {};
    Store(const Store& orig);
    virtual ~Store();

    void loadStore(const string &fileName);
    void displayStore();
   const Item &getItem(int itemNum)const;
    int getTotalItems() const {return this->_totalItems; } ;
    
    void genRandomData( User *customers,int randomUsers, int SIZE);
   
};

#endif /* STORE_H */

