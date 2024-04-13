
/* 
 * File:   Store.h
 * Author: Noel Perez
 *
 * Created on March 23, 2024, 10:56 PM
 */

#ifndef STORE_H
#define STORE_H
#include "Item.h"



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
    Item getItem(int itemNum);
    int getTotalItem(){return this->_totalItems; };
};

#endif /* STORE_H */

