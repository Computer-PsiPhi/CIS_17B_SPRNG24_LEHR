/* 
 * File:   Store.cpp
 * Author: Noel Perez
 * Created on March 23, 2024, 10:56 PM
 */
#include <iostream>
#include "Store.h"

#include <fstream>
#include <string>
#include <sstream>

using namespace std;

Store::Store(const Store& orig) {
}

Store::~Store() {
}

void Store::loadStore(const string &fileName) {

    fstream invntryFile;

    invntryFile.open(fileName, ios::in);

    if (invntryFile.is_open()) {
        cout << "Loading store inventory from file..." << endl;
        invntryFile >> this->_totalItems;
        invntryFile.ignore();
        cout << "Items in file: " << _totalItems << endl;

        string line;
        unsigned short i = 0;
        int num = 0;
        float p = 0.0f;
        string str = {};

        while (getline(invntryFile, line) and i < _totalItems) {
            stringstream stream(line);

            stream >> num;
            stream.ignore();
            getline(stream, str, ',');
            stream >> p;
          
//            this->_inventory[i].setItemNum(num);
//            this->_inventory[i].setName(str);
//            this->_inventory[i].setPrice(p);
            this->_inventory[i]=Item(num, str, p );
            i++;
        }

    } else {
        cerr << "Error could not open file in loadStore function" << endl;
    }
    invntryFile.close();
    cout<<"Inventory file closed."<<endl;
}

void Store::displayStore() {
    cout << "\n";
    if (this->_totalItems > 0){
        cout<<"Inventory: "<<this->_totalItems<<" items."<<endl;
       for (unsigned int i = 0; i < this->_totalItems; i++) {
        cout<< "-------------------------------------------\n";
        cout  <<left<<setw(15)<< "Item number:" << this->_inventory[i].getItemNum() << endl;
        cout  <<left<<setw(15)<< "Name of item:" << this->_inventory[i].getName() << endl;
        cout  <<left<<setw(15)<< "Price of item: $" <<fixed<<setprecision(2)<< this->_inventory[i].getPrice() << endl;
       }
    }
    else cout<<"Store is empty!"<<endl;
}

const Item &Store::getItem(int itemNum)const{
//    bool isGood=false;
//       for (short i = 0; i < this->_totalItems && !isGood; i++) {
////           cout<<"storecpp Enter item number: "<<endl;
////           cin>>itemNum;
////           cin.ignore();
//            if (this->_inventory[i].getItemNum() == itemNum) {
//                isGood = true;
//                break;
//            }
//        }
//    return this->_inventory[itemNum];
    
      try {
        while (true) {
            if (itemNum < 0 or itemNum > _totalItems) {
                throw out_of_range("Invalid Item Number");
            }
            return _inventory[itemNum];
            break;
        }
    } catch (const exception& e) {
        cerr << e.what() << " Please enter a valid number between 1 and " << _totalItems << ": ";
        cin >> itemNum;
        return this->_inventory[itemNum]; 
    }
}