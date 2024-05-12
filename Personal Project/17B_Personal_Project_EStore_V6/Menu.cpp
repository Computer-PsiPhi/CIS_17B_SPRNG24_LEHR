
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

Menu::Menu(User *customers, int n) {
    this->_customers = customers;

}

Menu::Menu(const string &binaryFile) {
    this->_admin = Admin("Password", "Admin123", true, false, -1);
    this->_numCusts = 100;
    this->_randomUsers = 10;

    this->_customers = new User[ this->_numCusts ];

    this->_store.loadStore();
    _store.invntryToBinaryFile(binaryFile);
    _store.invntryFromBinaryFile(binaryFile);
    _store.genRandomData(_customers, _randomUsers, _numCusts);


    // for(int i =0; i< _randomUsers ; i++) _customers[i].displayHistory();

    //    _store.serachStoreRecords();
    //    _store.searchBinaryRecords();

    cout<<endl<<endl;
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
    delete []_customers;
    // cout<<"\nDestructor finished";
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

void Menu::startMenu() {
    cout<<endl;
   
    cout << "\nMenu Options:" << endl;
    cout <<"ADMIN LOGIN CREDENTIALS: Username: Admin123, Password: Password "<<endl;
    cout << "1. Log in" << endl;
    cout << "2. Sign up" << endl;
    cout << "3. Exit" << endl;
}

void Menu::userLogin() {

}

void Menu::userSignUp() {

}

void Menu::adminLogin() {

}

void Menu::adminMenu() {
    cout<<"\nAdministrator Menu"<<endl;
    cout<<"1. Add Items to Store Inventory "<<endl;
    cout<<"2. Remove Items from Store Inventory "<<endl;
    cout<<"3. Modify User Information & Records "<<endl;
    cout<<"4. Add Items to Store Inventory "<<endl;
}

void Menu::userMenu() {
    // Display menu
    cout << "\nWelcome to the Store!" << endl;
    cout << "1. Display Store Inventory" << endl;
    cout << "2. Add Item to Cart" << endl;
    cout << "3. View Cart" << endl;
    cout << "4. Remove Item from Cart "<<endl;
    cout << "5. Checkout" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

User Menu::*findUser(const string &userName, const string &password) {

    return nullptr;
}

void Menu::runMenu() {
   // const string users ="users.bin";
     
   ofstream outFile("users.bin", std::ios::binary | std::ios::out | std::ios::trunc);
   ifstream inFile("users.bin", ios::binary);
   
if (!outFile.is_open() || !inFile.is_open() ) {
    cerr << "Error: Output file is not open." << endl;
    cerr << "Error: Input file is not open." << endl;
}



    cout << boolalpha;
    int currentUsers = User::getNumUsers();
    int choice(0);


    int userIndex = 0;
    Admin admin;


//    for (int i = 0; i < currentUsers; ++i) {
//        _customers[i].displayShoppingHistory();
//    }
//

for (int i=0; i< currentUsers; i++ ) _customers[i].serializeUser( outFile);
    
 for (int i=0; i< currentUsers; i++ ) {
 
     _customers[i].deserializeUser(inFile);
     

  _customers[i].displayHistory();   
 }
    
    
    do {
        currentUsers = User::getNumUsers();
        Menu::startMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore();

        switch (choice) {
            case 1:
            { // Log in case

                bool userIn = false;
                bool adminIn = false;
               for (int i = 0; i < currentUsers; i++) this->_customers[i].displayContactInfo(); // debugging
              //  _admin.displayShoppingHistory();
                string username, password;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);

                for (int i = 0; i < currentUsers; i++) {
                  cout << "145 status: " << _customers[i].getlogStatus(); // debug
                    if (_customers[i].verifyCred(password, username)) {

                        userIndex = i;
                        _customers[userIndex].setLogStatus(true);
                        cout << "146 status: " << _customers[i].getlogStatus();
                        _customers[userIndex].displayContactInfo();
                        cout << "User Found " << endl; // debugging
                        userIn = true;
                        break;
                    } else if (!adminIn && !this->_admin.getlogStatus() && !userIn) {
                        if (_admin.verifyCred(password, username)) {
                            this->_admin.setLogStatus(true);
                            cout << "IS admin: " << _admin.getadminStatus();
                            cout << "is loggin in " << _admin.getlogStatus();
                            cout << "Logged in as Admin: " << endl; // debugging
                            break;
                        }
                    }
                }

                break;
            }
            case 2:
            { // Sign up case 

                Menu::signUp();

                break;
            }
            case 3:
            {
                // Exit
                cout << "Exiting program." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }


        if (_customers[userIndex].getlogStatus()  ) {

        
        cout << _customers[userIndex].getUsrName() << " is logged in" << endl;
_customers[userIndex].displayHistory();
        string s;
        for(int i =0; i< _customers[userIndex].getTotItemInHist(); i++){
           // _customers[i].getShopHist(i).getName();
            s = _customers[userIndex].getShopHist(i).getName();
           
        }
        int ch;
        float total = 0.0;
        bool found = false;
        do {
            Menu::userMenu();
            cin >> ch;
            cin.ignore();

            
            switch (ch) {
                case 1: // Display Store Inventory
                    _store.displayStore();
                    break;
                case 2: // Add Item to Cart
                    int itemNum;
                    found = false;
                    cout << "Enter the item number to add to your cart: ";
                    cin >> itemNum;
                    cout << "Item num entered: " << itemNum << endl;
                    // Find item in store inventory
                    for (int i = 0; i < _store.getTotalItems(); ++i) {
                        if (_store.getItem(i).getItemNum() == itemNum) {
                            _customers[userIndex].getCart().addItem(_store.getItem(i));
                            cout << "Item added to cart." << endl;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Item not found in store inventory." << endl;
                    }
                    break;
                case 3: // View Cart

                     _customers[userIndex].getCart().showCart();
                    break;
                case 4: // Remove Item
                     _customers[userIndex].getCart().removeItem();
                     _customers[userIndex];
                    break;
                case 5: // Checkout
                        for(int i =0; i< currentUsers ; i++){
                            cout<<"Customer "<<i+1<<endl;
                _customers[i].displayHistory();
                  }
                      cout<<"BEFORE the purchase "<<endl;
                    _customers[userIndex].displayHistory();
                    cout<<"&&&&&&&&&&&&&&&&&&&&&&"<<endl;
                    
                     _customers[userIndex].addToHistory();
                    total =  _customers[userIndex].getCart().checkOut();
                    cout << "Total amount: $" << total << endl;
                    cout << "Thank you for your purchase!" << endl;
                    cout<<"^^^^^^^^^^^^^"<<endl;
                    cout<<"After the purchase "<<endl;
                    _customers[userIndex].displayHistory();
                    break;
                case 6: // Exit
                    cout << "Exiting program." << endl;
                    cout<<"Was logged in: "<<_customers[userIndex].getlogStatus()<<endl;
                    _customers[userIndex].setLogStatus(false);
                     cout<<"Now logged in: "<<_customers[userIndex].getlogStatus()<<endl;
                    
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (ch != 6);
  }
    

    if (_admin.getadminStatus() && _admin.getlogStatus()) {
        cout << "ADMIN LOGGED IN " << endl;
       
         int c;
        do{
             
            Menu::adminMenu();
            
            
        }while(c != 5 );
    }


}
while (choice != 3);

inFile.close(); // Close the file stream after reading

outFile.close(); // Close the file stream after writing
cout<<"END!!!"<<endl;
}

void Menu::signUp() {
    cout<<endl;
    cout<<endl;
    User::increaseUsers();
    int currentCusts = User::getNumUsers() - 1;

    cout << "Number of Customers: " << User::getNumUsers() << endl;

    this->_customers[ currentCusts ] = User();

    this->_customers[ currentCusts ].setName();
    this->_customers[ currentCusts ].setUsrName();
    this->_customers[ currentCusts ].setPassWord();
    this->_customers[ currentCusts ].setEmail();
    this->_customers[ currentCusts ].setAddress();
    cout<<"Setting to record number: "<<User::getNumUsers()<<endl;
    this->_customers[ currentCusts ].setRecNum(currentCusts);

    cout << "Signup successful!" << endl;
    this->_customers[ currentCusts ].displayContactInfo();
}