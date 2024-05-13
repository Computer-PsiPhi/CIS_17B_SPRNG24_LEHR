
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
    this->_store.loadStore();

    this->_admin = Admin("Password", "Admin123", true, false, -1);
    this->_numCusts = 100;
    this->_randomUsers = 10;

    this->_customers = new User[ this->_numCusts ];

    this->_store.loadStore();
    _store.invntryToBinaryFile(binaryFile);
    _store.invntryFromBinaryFile(binaryFile);
    _store.genRandomData(_customers, _randomUsers, _numCusts);


    ifstream numFile("number.bin", ios::binary);
    if (!numFile.is_open()) {
        cerr << "Error: -number.bin- file is not open." << endl;
        return;
    }

    ifstream inFile("users.bin", ios::binary);
    if (!inFile.is_open()) {
        cerr << "Error: -users.bin- file is not open." << endl;
        return;
    }
    // Deserialize users from the binary file
    int numUsers;
    numFile.read(reinterpret_cast<char*> (&numUsers), sizeof (numUsers));
   // cout << "58 number read from file:->  " << numUsers << endl;


    if (numUsers > 0) {
        // this->_customers = new User[numUsers];
        for (int i = 0; i < numUsers; ++i) {
            this->_customers[i].deserializeUser(inFile);

        }
        User::setNumUsers(numUsers);
    }

    inFile.close();
    numFile.close();

    cout << endl << endl;
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {

    int currentCusts = this->Menu::readNumFile();

    ofstream outFile("users.bin", std::ios::binary | std::ios::trunc); // Open in append mode
    if (outFile.is_open()) {

        for (int i = 0; i < currentCusts; i++) {
            this->_customers[i].serializeUser(outFile);
        }
       // cout << "Current users written to file: " << currentCusts << endl;
        Menu::writeNumFile(currentCusts);
        outFile.close();
    } else {
        cerr << "Error: Could not open file for appending." << endl;
    }

   // debug
//    for (int i = 0; i < currentCusts; i++) {
//        this->_customers[i].displayContactInfo();
//    }

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
    cout << endl;

    cout << "\nMenu Options:" << endl;
    cout << "ADMIN LOGIN CREDENTIALS: Username: Admin123, Password: Password " << endl;
    cout << "1. Log in" << endl;
    cout << "2. Sign up" << endl;
    cout << "3. Exit" << endl;
}



void Menu::adminMenu() {
    cout << "\nAdministrator Menu" << endl;
    cout << "1. Add to Store Inventory " << endl;
    cout << "2. Remove from Store Inventory " << endl;
    cout << "3. Modify User Information & Records " << endl;
    cout << "4. Remove User " << endl;
    cout << "5. Exit" << endl;
}

void Menu::userMenu() {
    // Display menu
    cout << "\nWelcome to the Store!" << endl;
    cout << "1. Display Store Inventory" << endl;
    cout << "2. Add Item to Cart" << endl;
    cout << "3. View Cart" << endl;
    cout << "4. Remove Item from Cart " << endl;
    cout << "5. Checkout" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}


void Menu::runMenu() {
    // const string users ="users.bin";

    ofstream outFile("users.bin", std::ios::binary | std::ios::out | std::ios::trunc);
    ifstream inFile("users.bin", ios::binary);

    if (!outFile.is_open() || !inFile.is_open()) {
        cerr << "Error: Output file is not open." << endl;
        cerr << "Error: Input file is not open." << endl;
    }

    cout << boolalpha;
    int currentUsers = User::getNumUsers();

    //for (int i=0; i< currentUsers; i++ ) _customers[i].serializeUser( outFile);
    //    
    // for (int i=0; i< currentUsers; i++ ) {
    //     _customers[i].deserializeUser(inFile);    
    // }


    int choice(0);


    int record = 0;
    Admin admin;


    for (int i = 0; i < User::getNumUsers(); ++i) {
        //  _customers[i].displayShoppingHistory();
        _customers[i].displayContactInfo();
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
              //  for (int i = 0; i < User::getNumUsers(); i++) this->_customers[i].displayContactInfo(); // debugging
                //  _admin.displayShoppingHistory();
                string username, password;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);

                for (int i = 0; i < currentUsers; i++) {
                 //   cout << "145 status: " << _customers[i].getlogStatus(); // debug
                    if (_customers[i].verifyCred(password, username)) {

                        record = i;
                        _customers[record].setLogStatus(true);
                  //      cout << "146 status: " << _customers[i].getlogStatus();
                        _customers[record].displayContactInfo();
                        cout << "User Found " << endl; // debugging
                        userIn = true;
                        break;
                    } else if (!adminIn && !this->_admin.getlogStatus() && !userIn) {
                        if (_admin.verifyCred(password, username)) {
                            this->_admin.setLogStatus(true);
                     //       cout << "IS admin: " << _admin.getadminStatus();
                      //      cout << "is loggin in " << _admin.getlogStatus();
                    //        cout << "Logged in as Admin: " << endl; // debugging
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


        if (_customers[record].getlogStatus()) {


            cout << _customers[record].getUsrName() << " is logged in" << endl;
            _customers[record].displayHistory();
            string s;
            for (int i = 0; i < _customers[record].getTotItemInHist(); i++) {
                // _customers[i].getShopHist(i).getName();
                s = _customers[record].getShopHist(i).getName();

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
                                _customers[record].getCart().addItem(_store.getItem(i));
                                _customers[record].getShopHist(_customers[record].getTotItemInHist()).serialize(outFile);
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

                        _customers[record].getCart().showCart();
                        break;
                    case 4: // Remove Item
                        _customers[record].getCart().removeItem();
                        _customers[record];
                        break;
                    case 5: // Checkout
                        for (int i = 0; i < currentUsers; i++) {
                            cout << "Customer " << i + 1 << endl;
                            _customers[i].displayHistory();
                        }
                        cout << "BEFORE the purchase " << endl;
                        _customers[record].displayHistory();
                      

                        _customers[record].addToHistory();
                        total = _customers[record].getCart().checkOut();
                        cout << "Total amount: $" << total << endl;
                        cout << "Thank you for your purchase!" << endl;
                       
                       cout<<endl; 
                        cout << "After the purchase " << endl;
                        _customers[record].displayHistory();
                        break;
                    case 6: // Exit
                        cout << "Exiting program." << endl;
                        cout << "Was logged in: " << _customers[record].getlogStatus() << endl;
                        _customers[record].setLogStatus(false);
                        cout << "Now logged in: " << _customers[record].getlogStatus() << endl;

                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
            } while (ch != 6);
            Menu::clearScreen();
        }


        if (_admin.getadminStatus() && _admin.getlogStatus()) {
            cout << "ADMIN LOGGED IN " << endl;


            int adminChoice = 0;
            do {
                Menu::adminMenu();
                cout << "Enter your choice: ";
                cin >> adminChoice;
                cin.ignore();

                switch (adminChoice) {
                    case 1: // Add to Store Inventory
                    {
                        int itemNum;
                        string itemName;
                        float itemPrice;
                        cout << "\nEnter item number: ";
                        cin >> itemNum;
                        cout << "Enter item name: ";
                        cin.ignore();
                        getline(cin, itemName);
                        cout << "Enter item price: $";
                        cin >> itemPrice;
                        cin.ignore();

                        Item item(itemNum, itemName, itemPrice, 1);
                        _store.addItem(item);
                    }

                        break;
                    case 2: // Remove from Store Inventory
                        _store.displayStore();
                        _store.removeItem();
                        _store.displayStore();

                        break;
                    case 3:
                     //modifying user information and records
                        Menu::modifyUserInfo();
                        break;
                    case 4: // Remove User
                        Menu::removeUser();
                        break;
                    case 5: // Exit Admin Menu
                        cout << "Exiting ADMINISTRATOR menu." << endl;
                        _admin.setLogStatus(false);
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
            } while (adminChoice != 5 && _admin.getlogStatus());
            Menu::clearScreen();
        }

    } while (choice != 3);

    inFile.close(); // Close the file stream after reading
    outFile.close(); // Close the file stream after writing

    cout << "Thank you for vistiting!!!" << endl;
}

void Menu::signUp() {
    cout << endl;
    cout << endl;
    User::increaseUsers();
    int currentCusts = User::getNumUsers() - 1;

    cout << "Number of Customers: " << User::getNumUsers() << endl;

    this->_customers[ currentCusts ] = User();

    this->_customers[ currentCusts ].setName();
    this->_customers[ currentCusts ].setUsrName();
    this->_customers[ currentCusts ].setPassWord();
    this->_customers[ currentCusts ].setEmail();
    this->_customers[ currentCusts ].setAddress();
    cout << "Setting to record number: " << User::getNumUsers() << endl;
    this->_customers[ currentCusts ].setRecNum(currentCusts);

    cout << "Signup successful!" << endl;

    ofstream outFile("users.bin", std::ios::binary | std::ios::trunc);
    if (outFile.is_open()) {

        for (int i = 0; i < currentCusts + 1; i++) {
            this->_customers[i].serializeUser(outFile);
        }
      //  cout << "Current users written to file in signup func->: " << currentCusts + 1 << endl;
        Menu::writeNumFile(currentCusts + 1);
      
        outFile.close();
    } else {
        cerr << "Error: Could not open file for appending." << endl;
    }

    for (int i = 0; i < currentCusts + 1; i++) {
        this->_customers[i].displayContactInfo();
    }
}

void Menu::writeNumFile(int n) {
    ofstream outFile("number.bin", ofstream::binary | ofstream::trunc);
    if (!outFile) {
        cerr << "Error: Unable to open the file for writing." << endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*> (&n), sizeof (n));
    outFile.close();
}

int Menu::readNumFile() {
    int num = 0;
    ifstream inFile("number.bin", ifstream::binary);
    if (!inFile) {
        cerr << "Error: Unable to open the file for reading." << endl;
        return num;
    }
    inFile.read(reinterpret_cast<char*> (&num), sizeof (num));
    inFile.close();
    return num;
}

void Menu::modifyUserInfo() {
    int record;
    cout << "Enter the record of the user you want to modify: ";
    cin >> record;
    cin.ignore(); // Clear the input buffer

    if (record >= 0 && record < _numCusts) {
        // Display options for modifying user information
        cout << "1. Modify Name\n"
                << "2. Modify Username\n"
                << "3. Modify Email\n"
                << "4. Modify Password\n"
                << "5. Modify Address\n"
                << "6. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice) {
            case 1:
            {
                _customers[record].setName();
                break;
            }
            case 2:
            {
                _customers[record].setUsrName();
                break;
            }
            case 3:
            {
                _customers[record].setEmail();
                break;
            }
            case 4:
            {
                _customers[record].setPassWord();

                break;
            }
            case 5:
            {
                _customers[record].setAddress();
                break;
            }
            case 6:
                cout << "Exiting menu." << endl;
                break;
            default:
                cout << "Invalid." << endl;
        }
    } else {
        cout << "Invalid user record." << endl;
    }
}


void Menu::removeUser() {
    cout<<"List of users"<<endl;
    for(int i =0; i< User::getNumUsers(); i++) _customers[i].displayContactInfo();
    
    int record;
    cout << "Enter the record of the user you want to remove: ";
    cin >> record;

    bool found = false;
    for (int i = 0; i < User::getNumUsers(); ++i) {
        if (_customers[i].getRecNum() == record - 1 ) {
            found = true;
        
            for (int j = i; j < User::getNumUsers() - 1; ++j) {
                _customers[j] = _customers[j + 1];
            }
           
            User::decreaseUsers();
            cout << "User with record number " << record << " removed successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "User record: " << record << " not found." << endl;
    }
    
    cout<<"After removing"<<endl;
     for(int i =0; i< User::getNumUsers()-1; i++) _customers[i].displayContactInfo();
}