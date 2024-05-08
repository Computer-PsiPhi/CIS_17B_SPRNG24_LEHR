/* 
 * File:   Cart.cpp
 * Author: Noel Perez
 * Created on March 23, 2024, 10:53 PM
 */

#include <iostream>
#include "Cart.h"
using namespace std;

Cart::Cart(const Cart& orig) {
}

Cart::~Cart() {
}

void Cart::addItem(const Item &item) {
    try {
        if (this->_itemCount > SIZE) {
            throw runtime_error("Cart is full!");
        }
        this->_items[this->_itemCount] = item;
        this->_itemCount++;
    } catch (const exception& e) {
        cout << e.what() << endl;
    } catch (...) {
        cout << "Unknown exception in Cart add item function" << endl;
    }
}

void Cart::removeItem() {
    if (_itemCount == 0) {
        cout << "Cart is empty. Nothing to remove." << endl;
        return;
    }

    bool isGood = false;
    char confirm;

    while (!isGood) {
        try {
            string itemName;
            int itemNum;

            cout << "Enter the name of the item you want to remove: ";
        
            getline(cin, itemName);

            cout << "Enter the item number of the item you want to remove: ";
            cin >> itemNum;
            cin.ignore();
            // Convert both item name and entered name to lowercase 
            transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);

            bool itemFound = false;

            for (int i = 0; i < this->_itemCount; i++) {
                string currentItem = this->_items[i].getName();
                transform(currentItem.begin(), currentItem.end(), currentItem.begin(), ::tolower);

                if (this->_items[i].getItemNum() == itemNum && currentItem == itemName) {
                    itemFound = true;
                    cout << "Are you sure you want to remove " << this->_items[i].getName()
                         << " (Item Number: " << itemNum << ")? (y/n): ";
                    cin >> confirm;

                    if (confirm == 'y' || confirm == 'Y') {
                        for (int j = i; j < this->_itemCount - 1; j++) {
                            this->_items[j] = this->_items[j + 1];
                        }
                        this->_itemCount--;
                        cout << this->_items[i].getName() << " removed from the cart." << endl;
                        isGood = true;
                        break;
                    } else {
                        cout << "Removal canceled." << endl;
                        isGood = true;
                        break;
                    }
                }
            }

            if (!itemFound) {
                throw runtime_error("Item not found in cart.");
            }
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }
}


void Cart::showCart() {
    cout << "Cart status: " << endl;
    if (this->_itemCount > 0) {
        for (short i = 0; i < this->_itemCount; i++) {
            cout << "-------------------------------------------\n";
            cout << left << setw(15) << "Item number:" << this->_items[i].getItemNum() << endl;
            cout << left << setw(15) << "Name of item:" << this->_items[i].getName() << endl;
            cout << left << setw(15) << "Price of item: $" << fixed << setprecision(2) << this->_items[i].getPrice() << endl;
            cout << left << setw(15) << this->_items[i].getQuant() << endl;
        }
    } else {
        cout << "Cart is empty!" << endl;
    }
}

float Cart::checkOut() {
    // Calculate total
    float total = 0.0f;
    for (short i = 0; i < this->_itemCount; i++) {
        total += this->_items[i].getPrice() * this->_items[i].getQuant();
    }
    // Clear the cart after checkout
    resetCount();
 
    return total;
}