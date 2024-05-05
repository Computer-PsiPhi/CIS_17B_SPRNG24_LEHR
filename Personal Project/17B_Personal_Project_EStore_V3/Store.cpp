/* 
 * File:   Store.cpp
 * Author: Noel Perez
 * Created on March 23, 2024, 10:56 PM
 */
#include <iostream>
#include "Store.h"
#include "Item.h"
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
            this->_inventory[i] = Item(num, str, p);
            i++;
        }
    } else {
        cerr << "Error could not open file in loadStore function" << endl;
    }
    invntryFile.close();
    cout << "Inventory file closed." << endl;
}

void Store::displayStore() {
    cout << "\n";
    if (this->_totalItems > 0) {
        cout << "Inventory: " << this->_totalItems << " items." << endl;
        for (unsigned int i = 0; i < this->_totalItems; i++) {
            cout << "-------------------------------------------\n";
            cout << left << setw(15) << "Item number:" << this->_inventory[i].getItemNum() << endl;
            cout << left << setw(15) << "Name of item:" << this->_inventory[i].getName() << endl;
            cout << left << setw(15) << "Price of item: $" << fixed << setprecision(2) << this->_inventory[i].getPrice() << endl;
        }
    } else cout << "Store is empty!" << endl;
}

const Item &Store::getItem(int itemNum)const {
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

void Store::genRandomData(User *customers, int randomUsers, int SIZE) {

    for (int i = 0; i < randomUsers; i++) {
        int num = rand() % 900 * 5 + 1000;
        int zip = rand() % 9999 * 5 + 9999;

        string name = "Customer",
                username = "!UserName",
                email = "email@gmail.com",
                password = "PassWord_",
                address = to_string(num) += " A Street Somewhere ";
        address.insert(address.size(), to_string(zip));
        address += ", USA";


        name.append(to_string(i + 1));
        username.append(to_string(i + 1));
        email.insert(5, to_string(i)),
                password.append(to_string(i));

        customers[i] = User(
                name,
                username,
                email,
                password,
                address,
                false,
                false,
                i);

        customers[i].fillRand(*this);
    }
}

void Store::toTextFile(const string &file) {

    fstream txtOut;

    txtOut.open(file, ios::trunc | ios::out);

    if (txtOut.is_open()) {
        txtOut << _totalItems << endl;
        for (int i = 0; i < _totalItems; ++i) {
            txtOut << _inventory[i].getItemNum() << ","
                    << _inventory[i].getName() << ","
                    << (float) _inventory[i].getPrice() << endl;
            cout << _inventory[i].getPrice() << endl;
        }
        txtOut << "End of File" << endl;
        cout << "Store inventory written to file successfully." << endl;
    } else {
        cerr << "Unable to open file: " << file << endl;
    }
    txtOut.close();
}

void Store::toBinaryFile(const string &file)const {
    ofstream outFile(file, ios::binary);

    if (outFile.is_open()) {
        unsigned int numProducts = _totalItems;
        outFile.write(reinterpret_cast<const char*> (&numProducts), sizeof (numProducts));

        for (short i = 0; i < this->_totalItems; i++) {
            cout << " inventory  " << _inventory[i].getName() << endl;
            this->_inventory[i].serialize(outFile);
        }
        outFile.close();
    } else {
        cerr << "Error in toBinaryFile() function" << endl;
    }
}

// Function definition 

void Store::fromBinaryFile(const string &file) {
    ifstream inBinFile(file, ios::binary);

    if (inBinFile.is_open()) {
        unsigned int numProducts = 0;
        inBinFile.read(reinterpret_cast<char*> (&numProducts), sizeof (numProducts));
        if (inBinFile.fail()) cerr << "Error in fromBinaryFile() function " << endl;

        if (numProducts <= this->Store::totItmsFrmFile()) {
            for (short i = 0; i< this->_totalItems; i++) {
                _inventory[i].deserialize(inBinFile);
                if (inBinFile.fail()) cerr << "Error in fromBinaryFile()" << endl;
            }
        } else {
            cout << "Number of products exceeds what is in file" << endl;
        }
    } else {
        cerr << "File not opened in fromBinaryFile() function" << endl;
    }

}

int Store::totItmsFrmFile() {
    fstream text;
    int tot = 0;
    text.open("inventory.txt", ios::in);

    if (text.is_open()) {
        text >> tot;
    } else {
        cerr << "File Operation FAILED!" << endl;
    }
    text.close();
    return tot;
}

void Store::setTotalItems(int n) {
    (n > Store::totItmsFrmFile()) ?
            (this->Store::_totalItems == Store::totItmsFrmFile()) :
            (this->_totalItems == n);
}

void Store::serachStoreRecords() {
    ifstream inBinaryFile("products.bin", ios::binary);

    if (!inBinaryFile.is_open()) {
        cerr << "Error opening binary file in searchStoreRecords()" << endl;
    }
    unsigned int numProducts;

    inBinaryFile.read(reinterpret_cast<char*> (&numProducts), sizeof (numProducts));
    if (inBinaryFile.fail()) {
        cout << "Error in reading amount of products" << endl;
        return;
    }
    if (numProducts == 0) {
        cout << "ERROR: no items in binary file" << endl;
        return;
    }

    long long unsigned cursor = sizeof (numProducts);
    unsigned short count = 0;

    while (count++ < numProducts) {
        inBinaryFile.seekg(cursor, ios::beg);
        unsigned int len;
        inBinaryFile.read(reinterpret_cast<char*> (&len), sizeof (len));
        cursor += sizeof (len) + len + sizeof (float) + sizeof (int) + sizeof (int);
    }

    cout << "246: " << cursor << endl;


    unsigned int nameLen = 0;
    string name;
    float price;
    int quant;
    int num;
    inBinaryFile.seekg(cursor);
    inBinaryFile.read(reinterpret_cast<char*> (&nameLen), sizeof (nameLen));
    name.resize(nameLen);
    inBinaryFile.read(&name[0], nameLen);
    inBinaryFile.read(reinterpret_cast<char*> (&price), sizeof (price));
    inBinaryFile.read(reinterpret_cast<char*> (&quant), sizeof (quant));
    inBinaryFile.read(reinterpret_cast<char*> (&num), sizeof (num));

    cout << "Name " << name << endl;
    cout << "Price" << price << endl;
    cout << "quant" << quant << endl;
    cout << "number" << num << endl;

}