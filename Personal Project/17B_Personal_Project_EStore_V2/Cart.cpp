
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

void Cart::removeItem(int index) {
    bool isGood = false;
    while (!isGood) {
        try {
            if (index < 0 || index > this->_itemCount) {
                throw out_of_range("Invalid index!");
            }

            for (short int i = index; i < this->_itemCount - 1; i++) {
                this->_items[i] = this->_items[i + 1];
            }
            this->_itemCount--;
            isGood = true; // Set to true to exit the loop if the index is valid
        } catch (const exception& e) {
            cout << e.what() << endl;
            cout << "Enter a valid index: ";
            cin >> index;
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