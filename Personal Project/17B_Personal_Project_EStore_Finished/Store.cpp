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
#include <iomanip>

using namespace std;

Store::Store(const Store& orig) {
}

Store::~Store() {
}
void Store::loadStore(){
 /*1,T-shirt,5.99
2,Pants,15.99
3,Dress Shoes,35.99
4,Black Umbrella,4.99
5,Denim Jacket,35
6,Blue shirt,7.99
7,Shorts,10.99
8,Sneakers,29.99
9,Black tie,4.99
10,Rain Jacket,40
     */
    
    if( Store::totItmsFrmFile() <= 0){
        cout<<"Inventory Empty!"<<endl;
    short s = 10;
    this->_totalItems=s;
    string names[s]= {"T-Shirt" , "Pants", "Dress Shoes", "Black Umbrella", 
                    "Denim Jacket", "Blue Shirt", "Shorts", 
                    "Sneakers", "Black Tie", "Rain Jacket",
                    };
                    
    float prices [s]=  {5.99, 15.99 , 35.99,
                    4.99 ,35.00, 7.99 ,10.99,
                    29.99, 4.99 ,40.00};
           
        for (int i = 0; i < _totalItems; ++i) {
           _inventory[i] = Item(i+1, names[i], prices[i]);
        }
    Store::invntryToTextFile();
    }else{
        cout<<"Going to load..."<<endl;
        Store::loadStore(this->_file);
    }
   
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
                username = "Username!",
                email = "email@gmail.com",
                password = "Password",
                address = to_string(num) += " A Street Somewhere ";
        address.insert(address.size(), to_string(zip));
        address += ", USA";


        name.append(to_string(i + 1));
        username.append(to_string(i + 1));
        email.insert(5, to_string(i+1)),
                password.append(to_string(i+1));

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

void Store::invntryToTextFile() {

    fstream txtOut;

    txtOut.open(this->_file, ios::trunc | ios::out);

    if (txtOut.is_open()) {
        txtOut << _totalItems << endl;
        for (int i = 0; i < _totalItems; ++i) {
            txtOut << _inventory[i].getItemNum() << ","
                    << _inventory[i].getName() << ","
                    << (float) _inventory[i].getPrice() << endl;
          //  cout << _inventory[i].getPrice() << endl;
        }
        txtOut << "End of File" << endl;
        cout << "Store inventory written to file successfully." << endl;
    } else {
        cerr << "Unable to open file: " << this->_file << endl;
    }
    txtOut.close();
}

void Store::invntryToBinaryFile(const string& file) const {
    ofstream outFile(file, ios::binary);

    if (outFile.is_open()) {
        unsigned int numProducts = _totalItems;
        outFile.write(reinterpret_cast<const char*> (&numProducts), sizeof (numProducts));

        for (short i = 0; i < this->_totalItems; i++) {
         //   cout << " inventory  " << _inventory[i].getName() << endl;
            this->_inventory[i].serialize(outFile);
        }
        outFile.close();
    } else {
        cerr << "Error in toBinaryFile() function" << endl;
    }
}

// Function definition 
void Store::invntryFromBinaryFile(const string& file) {
    ifstream inBinFile(file, ios::binary);

    if (inBinFile.is_open()) {
        unsigned int numProducts;
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
    inBinFile.close();
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
        return;
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

     srand(time(0)); // Seed the random number generator
        unsigned int random = rand() % numProducts;
        cout<<"Random index generated: "<<random+1<<endl;
        
    long long unsigned cursor = sizeof (numProducts);
    unsigned short count = 0;
    
    while (++count <= random) {
        inBinaryFile.seekg(cursor, ios::beg);
        unsigned int len;
        inBinaryFile.read(reinterpret_cast<char*> (&len), sizeof (len));
        cursor += sizeof (len) + len + sizeof (float) + sizeof (int) + sizeof (int);   
    }
    unsigned int nameLen = 0;
    string name;
    float price;
    int num;
    int quant;

    inBinaryFile.seekg(cursor);
    inBinaryFile.read(reinterpret_cast<char*> (&nameLen), sizeof (nameLen));
    name.resize(nameLen);
    inBinaryFile.read(&name[0], nameLen);
    inBinaryFile.read(reinterpret_cast<char*> (&price), sizeof (price));
    inBinaryFile.read(reinterpret_cast<char*> (&num), sizeof (num));
    inBinaryFile.read(reinterpret_cast<char*> (&quant), sizeof (quant));
  
    cout << "Item number: " << right <<num << endl;
    cout << "Name: "        << right <<name << endl;
    cout << "Price: "       << right <<price << endl;
    cout << "Quantity: "    << right <<quant << endl;
}

void Store::searchBinaryRecords() {
    ifstream inBinaryFile("products.bin", ios::binary);

    if (!inBinaryFile.is_open()) {
        cerr << "Error opening binary file in searchStoreRecords()" << endl;
        return;
    }

    unsigned int numProducts;
    inBinaryFile.read(reinterpret_cast<char*>(&numProducts), sizeof(numProducts));

    if (inBinaryFile.fail()) {
        cout << "Error in reading amount of products" << endl;
        return;
    }

    if (numProducts == 0) {
        cout << "ERROR: no items in binary file" << endl;
        return;
    }

    unsigned long long cursor = sizeof(numProducts);
    cout<<"******************************"<<endl;
    cout<<"From Binary File (products.bin)"<<endl;
    for (int i = 0; i < numProducts; ++i) {
        inBinaryFile.seekg(cursor, ios::beg);

        unsigned int nameLen;
        string name;
        float price;
        int num;
        int quant;

        inBinaryFile.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        name.resize(nameLen);
        inBinaryFile.read(&name[0], nameLen);
        inBinaryFile.read(reinterpret_cast<char*>(&price), sizeof(price));
        inBinaryFile.read(reinterpret_cast<char*>(&num), sizeof(num));
        inBinaryFile.read(reinterpret_cast<char*>(&quant), sizeof(quant));

        cout<< endl;
        cout<<fixed<<setprecision(2);
        cout << "Item number: " << right << num << endl;
        cout << "Name: " << right << name << endl;
        cout << "Price: " << right <<(float)price << endl;
        cout << "Quantity: " << right << quant << endl;
        cout<<"--------------------"<<endl;
        
        cursor += sizeof(nameLen) + nameLen + sizeof(float) + sizeof(int) + sizeof(int);
    }
    inBinaryFile.close();
}

void Store::addItem(const Item& newItem){
    if (_totalItems < SIZE) {
        _inventory[_totalItems++] = newItem;
        cout << "Item added successfully!" << endl;
    } else {
        cout << "Inventory is full. Cannot add more items." << endl;
    }
}

void Store::removeItem() {
    
    int itemNum;
    cout << "Enter the item number of the item you want to remove: ";
    cin >> itemNum;
    
    bool found = false;
    for (int i = 0; i < _totalItems; ++i) {
        if (_inventory[i].getItemNum() == itemNum) {
            found = true;
          
            for (int j = i; j < _totalItems - 1; ++j) {
                _inventory[j] = _inventory[j + 1];
            }
            // Decrement the total items count
            _totalItems--;
            cout << "Item removed successfully!" << endl;
            break;  
        }
    }
    if (!found) {
        cout << "Item not found in the inventory." << endl;
    }
}

