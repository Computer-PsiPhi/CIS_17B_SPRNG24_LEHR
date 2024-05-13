
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
    int _numCusts;
    int _randomUsers;
    
public:
    Menu();
   Menu(const string &binaryFile);
    Menu(User *customers , int n);
    Menu(const Menu& orig);
    virtual ~Menu();

void clearScreen();
void clearScreenChoice();

void setNumCusts(int n){this->_numCusts = n;};
int getNumCusts()const {return this->_numCusts;};

void startMenu();

void adminMenu();
void userMenu();
void runMenu();

void signUp() ;

void writeNumFile(int n);
int  readNumFile();

void modifyUserInfo();
void removeUser();

};

#endif /* MENU_H */

