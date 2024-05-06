
/* 
 * File:   Menu.h
 * Author: Noel Perez
 *
 * Created on March 23, 2024, 10:54 PM
 */

#ifndef MENU_H
#define MENU_H
#include "Admin.h"
#include "Store.h"
#include "User.h"
class Menu {
private:
    Store _store;
    User *_customers;
    Admin _admin;
    
public:
    Menu();
    Menu(const string &binaryFile);
    Menu(User *customers , int n);
    Menu(const Menu& orig);
    virtual ~Menu();

void clearScreen();
void clearScreenChoice();

};

#endif /* MENU_H */

