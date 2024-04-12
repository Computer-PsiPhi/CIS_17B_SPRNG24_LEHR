
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
    Store(): _totalItems(0){};
    Store(const Store& orig);
    virtual ~Store();

    void loadStore(const string &fileName);
    void displayStore();
  
};

#endif /* STORE_H */

