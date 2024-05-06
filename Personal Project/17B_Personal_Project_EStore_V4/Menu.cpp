
/* 
 * File:   Menu.cpp
 * Author: Noel Perez
 * 
 * Created on March 23, 2024, 10:54 PM
 */
#include <iostream>
#include "Menu.h"
using namespace std;

Menu::Menu() : _customers{nullptr}, _admin{}
{
    cout << "Enter default menu constructor";
    this->_store.loadStore();
    cout << "exit default menu constructor";
}
Menu:: Menu(User *customers , int n){
    this->_customers = customers;
    
}
Menu::Menu(const string &binaryFile) {
    const int s = 100;
 
    this->_customers = new User[ s ];
    
    this->_store.loadStore();
    _store.toBinaryFile(binaryFile);
    _store.fromBinaryFile(binaryFile);

    cout << "exit 1 PARAM menu constructor";
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
    delete []_customers;
}


// Function to clear screen

void Menu::clearScreen() {
    cout << "\033c";
};

// Function to clear screen with user input for choice

void Menu::clearScreenChoice() {
    char choice = 0;
    cout << "\n";
    cout << "Do you want to clear screen(Y/N)?" << endl;
    cin>>choice;
    choice = toupper(choice);

    if (choice == 'Y') {
        cout << "\033c";
    }
    cout << endl;
};