
/* 
 * File:   Menu.cpp
 * Author: Noel Perez
 * 
 * Created on March 23, 2024, 10:54 PM
 */
#include <iostream>
#include "Menu.h"
using namespace std;

Menu::Menu() {
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
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