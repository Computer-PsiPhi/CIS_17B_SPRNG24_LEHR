/* 
 * File:   User.cpp
 * Author: Noel Perez
 * Created on March 23, 2024, 10:52 PM
 */
#include <iostream>
#include "User.h"
#include "Store.h"
#include "Admin.h"
#include <regex>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <string>
using namespace std;

int User::_users = 0;


User::User() : _name(),
_userName{},
_email{},
_passWord{},
_address{},
_cartSize{0}

,
_totalHistory(0),
_shoppingCart {
},
_recNum{0},
_isLoggedIn{false},
_isAdmin{false}
{ //Default Constructor
}

User::User(const string &password, const string &un, bool isAdmin, bool isLoggedIn) :
_passWord{password}, _userName{un}, _isAdmin{isAdmin}, _isLoggedIn{isLoggedIn}
{
}

User::User(const string& u, const string& a, int n) : _userName(u), _address(a), _recNum(n), _totalHistory(0) {
}

User::User(const User& orig) {
}

User::User(const string& name,
        const string& userName,
        const string& email,
        const string& password,
        const string& address) :
_name(name), _userName(userName),
_email(email), _passWord(password),
_address(address), _cartSize(0),
_totalHistory(0), _shoppingCart{}
{
};


User::User(const string & name,
        const string &userName,
        const string &email,
        const string &password,
        const string &address,
        bool isLogged,
        bool isAdmin,
        int recNum) :
_name{name},
_userName{userName},
_email{email},
_passWord{password},
_address{address},
_isLoggedIn{false},
_isAdmin{false},
_recNum{recNum}

,
_cartSize(0),
_totalHistory(0),
_shoppingCart {
},
_shoppingHistory{}
{
};

User::~User() {
}

bool User::isValName(string str, int minLen) {
    // Regular expressions to match special character or letter requirements
    regex specialChars("[!@#$%^&*()_+-={};:',.<>?/]");
    regex upperCase("[A-Z]");
    regex lowerCase("[a-z]");


    // Make sure the string contains all matches to the regular expressions
    return (
            str.length() >= minLen and
            not regex_search(str, specialChars) and
            regex_search(str, upperCase) and
            regex_search(str, lowerCase)
            );
}

bool User::isValUsrName(string str, int minLen) {
    // Regular expressions to match special character or letter requirements

    // Regular expressions to match valid username characters
    regex valid("[a-zA-Z0-9]");
    regex spaces("[\\s]");

    // Make sure the string contains all valid characters and no spaces
    return (str.length() >= minLen and
            regex_search(str, valid) and
            not regex_search(str, spaces)
            );
}

bool User::isValEmail(string str, int minLen) {
    // Regular expressions to match special character or letter requirements

    regex amp("[@]");
    regex dot("[.]");
    regex spaces("[\\s]");

    // Make sure the string contains all matches to the regular expressions
    return (
            str.length() >= minLen and
            regex_search(str, amp) and
            regex_search(str, dot) and
            not regex_search(str, spaces)
            );
}

bool User::isValPass(string str, int minLen) {
    // Regular expressions to match special character or letter requirements
    regex specialChars("[!@#$%^&*()_+-={};:',.<>?/]");
    regex upperCase("[A-Z]");
    regex lowerCase("[a-z]");
    regex numbers("[0-9]");
    regex spaces("[\\s]");

    // Make sure the string contains all matches to the regular expressions
    return (
            str.length() >= minLen and
            regex_search(str, specialChars) and
            regex_search(str, upperCase) and
            regex_search(str, lowerCase) and
            regex_search(str, numbers) and
            not regex_search(str, spaces)
            );
}

bool User::isValAddss(string str, int minLen) {
    regex lowerCase("[a-z]");
    regex numbers("[0-9]");
    regex spaces("[\\s]");

    // Make sure the string contains all matches to the regular expressions
    return (
            str.length() >= minLen and
            regex_search(str, lowerCase) and
            regex_search(str, numbers) and
            regex_search(str, spaces)
            );
}

void User::setName() {
    string name;
    bool isGood = false;

    while (!isGood) {
        cout << "\nEnter First and Last Name: " << endl;
        getline(cin, name);
        try {
            if (!isValName(name)) {
                throw invalid_argument("Follow First & Last Name Requirements!\n");
            }
            isGood = true;
        } catch (const invalid_argument& e) {
            cerr << "Invalid User first and last name: " << e.what();
        } catch (...) {
            cerr << "Unknown exception " << endl;
        }
    }
    this->_name = name;
}

void User::setUsrName() {
    string usrName;
    bool isGood = false;

    while (!isGood) {
        cout << "\nEnter Username: " << endl;
        // cin>>usrName;
        getline(cin, usrName);
        try {
            if (!User::isValUsrName(usrName)) {
                throw invalid_argument("Follow Username Requirements!\n");
            }
            isGood = true;
        } catch (const invalid_argument& e) {
            cerr << "Invalid Username: " << e.what();
        } catch (...) {
            cerr << "Unknown exception " << endl;
        }
    }
    this->_userName = usrName;

}

void User::setEmail() {
    string email = "";
    bool isGood = false;

    while (not isGood) {
        cout << "\nEnter email: " << endl;
        getline(cin, email);

        try {
            if (not User::isValEmail(email)) {
                throw invalid_argument("Incorrect Email Requirements\n");
            }
            isGood = true;
        } catch (const invalid_argument &e) {
            cerr << "Invalid Email: " << e.what();
        } catch (...) {
            cerr << "Unknown exception" << endl;
        }
    }
    this->_email = email;
}

void User::setPassWord() {
    string passwrd;
    bool isGood = false;

    while (not isGood) {
        cout << "\nEnter Password " << endl;
        getline(cin, passwrd);
        try {
            if (not User::isValPass(passwrd)) {
                throw invalid_argument("Incorrect Password Requirements\n");
            }
            isGood = true;
        } catch (const invalid_argument &e) {
            cerr << "Invalid Password: " << e.what();
        } catch (...) {
            cerr << "Unknown exception" << endl;
        }
    }
    this->User::_passWord = passwrd;
}

void User::setAddress() {
    string addrss = "";
    bool isGood = false;

    while (not isGood) {
        cout << "\nEnter Address: " << endl;
        getline(cin, addrss);

        try {
            if (not User::isValAddss(addrss)) {
                throw invalid_argument("Incorrect Address Requirements\n");
            }
            isGood = true;
        } catch (const invalid_argument &e) {
            cerr << "Invalid Address: " << e.what();
        } catch (...) {
            cerr << "Unknown exception" << endl;
        }
    }
    this->User::_address = addrss;
}

void User::setRecNum(int r) {
    if (r > this->User::_MAX) {
        cerr << "ERROR!" << endl;
        return;
    }
    this->User::_recNum = r;
};

const string & User::getName() const {
    return this->_name;
}

const string & User::getUsrName() const {
    return this->_userName;
}

const string & User::getEmail() const {
    return this->_email;
}

const string & User::getPassWord() const {
    return this->_passWord;
}

const string & User::getAddress() const {
    return this->_address;
}

const int User::getRecNum() const {
    return _recNum;
}

void User::fillRand(const Store &store) {
    //    // Create an array of item indices 
    int *itemIndices = new int[store.getTotalItems()];
    for (int i = 0; i < store.getTotalItems(); i++) {
        itemIndices[i] = i;
    }

    //    // Shuffle 
    for (int i = store.getTotalItems() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = itemIndices[i];
        itemIndices[i] = itemIndices[j];
        itemIndices[j] = temp;
    }
    //    // Randomly choose number of items 
    int numItems = 3; // min(rand() % 10 + 1, store.getTotalItems());

    // Temp array 
    int *selected = new int[numItems];

    for (int i = 0; i < numItems; i++) {
        int itemIndx = itemIndices[i];
        int itemNum = store.getItem(itemIndx).getItemNum();

        bool exists = false;
        for (int j = 0; j < i; j++) {
            if (selected[j] == itemNum) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            selected[i] = itemNum;
            _shoppingHistory[_totalHistory++] = store.getItem(itemIndx); // Add item to shopping history
        } else {
            _totalHistory--;
        }
    }
    User::increaseUsers();
    delete []itemIndices;
    delete []selected;
}

void User::displayHistory() {
    cout << endl;
    cout << endl;
    cout << "**********************" << endl;
    cout << "Record Number: " << this->getRecNum() + 1 << endl;
    cout << "**********************" << endl;
    User::displayContactInfo();
    cout << "Shopping History " << endl;
    cout << "Total items in history: " << this->User::_totalHistory << endl;
    cout << "======================" << endl;
    for (short i = 0; i < this->_totalHistory; i++) {
        this->_shoppingHistory[i].display();
        cout << "-------------------" << endl;
    }
}

bool User::verifyCred(const string &password, const string &userName) {
    if (this->_passWord == password && this->_userName == userName)
        return true;
    else
        return false;
}

void User::setLogStatus(bool status) {
    this->_isLoggedIn = status;
}

void User::setAdminStatus(bool status) {
    this->_isAdmin = status;
}

bool User::getlogStatus() {
    return _isLoggedIn;
}

bool User::getadminStatus() {
    return _isAdmin;
}

void User::displayContactInfo() {
    cout << "\nPersonal Information: " << endl;
    cout << "======================" << endl;
    cout << left << setw(11) << "Name:" << right << setw(9) << this->_name << endl;
    cout << left << setw(11) << "Username:" << right << setw(9) << this->_userName << endl;
    cout << left << setw(11) << "Password:" << right << setw(11) << this->_passWord << endl;
    cout << left << setw(11) << "Email:" << right << setw(11) << this->_email << endl;
    cout << left << setw(11) << "Address:" << right << setw(11) << this->_address << endl;
    cout << left << setw(11) << "Record number:" << right << setw(3) << this->_recNum + 1 << endl;
    cout << endl;
}

void User::displayShoppingHistory() {
    cout << "**************************" << endl;
    cout << "Record Number: " << _recNum + 1 << endl;
    cout << "**************************" << endl;

    cout << "Name: " << _name << endl;
    cout << "Username: " << _userName << endl;
    cout << "Email: " << _email << endl;
    cout << "Password: " << _passWord << endl;
    cout << "Address: " << _address << endl;
    //  cout << "Cart Size: " << _cartSize << endl;
    // cout << "Record Number: " << _recNum+1 << endl;
    cout << "Total History: " << _totalHistory << endl;
    cout << "Shopping History:" << endl;
    cout << endl;
    for (int i = 0; i < User::_totalHistory; ++i) {
        _shoppingHistory[i].display();
        cout << endl;
    }
    cout << "--------------------------" << endl;
    cout << endl;
}

void User::changeUserInfo(User* usersArray, int size, int index) {
    if (index >= 0 && index < size) {
        int choice;
        cout << "Choose an attribute to modify for user " << index + 1 << ":" << endl;
        cout << "1. Name" << endl;
        cout << "2. Username" << endl;
        cout << "3. Email" << endl;
        cout << "4. Password" << endl;
        cout << "5. Address" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            {
                cout << "Enter the new name for user " << index + 1 << ": ";
                usersArray[index].setName();
                break;
            }
            case 2:
            {
                cout << "Enter the new username for user " << index + 1 << ": ";
                usersArray[index].setUsrName();
                break;
            }
            case 3:
            {
                cout << "Enter the new email for user " << index + 1 << ": ";
                usersArray[index].setEmail();
                break;
            }
            case 4:
            {
                cout << "Enter the new password for user " << index + 1 << ": ";
                usersArray[index].setPassWord();
                break;
            }
            case 5:
            {
                cout << "Enter the new address for user " << index + 1 << ": ";
                usersArray[index].setAddress();
                break;
            }
            default:
                cerr << "Invalid choice!" << endl;
        }

        cout << "User " << index + 1 << endl;
        usersArray[index].displayContactInfo();
    } else {
        cerr << "Error: Invalid index!" << endl;
    }
}

// TODO : UNFINISHED

void User::addToHistory() {
    int itemCount = this->User::_shoppingCart.getCount();
    cout << "Number of Items in Cart to be added to shopping History: " << itemCount << endl;
    for (int i = 0; i < itemCount; i++) {
        this->_shoppingHistory[_totalHistory ] = _shoppingCart.getItem(i);
        _totalHistory++;
    }
}

/*TODO 
 *     ADD REMOVE ITEM/S FROM HISTORY
 */

// Serialize User function

//  void User::serializeUser(ofstream& binOutFile) {
//   //   cout<<"Enter serializatin for user: "<<User::_name<<endl; // debug
//      
//    if (!binOutFile.is_open()) {
//         ofstream binOutFile("users.bin", ios::binary);
//    }
//     
//      unsigned int nameLen = _name.length();
//      unsigned int usrNameLen = _userName.length();
//      unsigned int emailLen = _email.length();
//      unsigned int pwLen = _passWord.length();
//      unsigned int addressLen = _address.length();
//      
////    //  cout<<"484 debug "<<nameLen<<endl; // debug
//      binOutFile.write(reinterpret_cast<char *>(&nameLen ), sizeof(nameLen));
//     binOutFile.write(reinterpret_cast<char *>(&usrNameLen ), sizeof(usrNameLen));
//      binOutFile.write(reinterpret_cast<char *>(&emailLen ), sizeof(emailLen));
//      binOutFile.write(reinterpret_cast<char *>(&pwLen ), sizeof(pwLen));
//      binOutFile.write(reinterpret_cast<char *>(&addressLen ), sizeof(addressLen));
//      
////      cout<<endl;
////    cout << "Name Length: " << nameLen << endl;
////    cout << "Username Length: " << usrNameLen << endl;
////    cout << "Email Length: " << emailLen << endl;
////    cout << "Password Length: " << pwLen << endl;
////    cout << "Address Length: " << addressLen << endl;
////    cout<<endl;
////    
//      string itemName;
//      unsigned int itemNameLen;
//      
//      for (int i =0; i< User::_totalHistory; i++){    
//       itemName = _shoppingHistory[i].getName();
//   //  cout<<"\n149: "<<itemName<<endl; // debug
//      itemNameLen = itemName.length();
//     //  cout<<"\n itemNameLen:::: "<<itemNameLen<<endl; // debug
//       binOutFile.write(reinterpret_cast<char *>(&itemNameLen ), sizeof(itemNameLen));
//      // cout<<"debug: "<<_name.c_str()<<endl;
//      }
//      
//      binOutFile.write(_name.c_str(),nameLen );
//      binOutFile.write(_userName.c_str(), usrNameLen );
//      binOutFile.write(_email.c_str(), emailLen);
//      binOutFile.write(_passWord.c_str(), pwLen);
//      binOutFile.write(_address.c_str(), addressLen);
//      
//      string itemName_;
//      unsigned int itemNameL;
//       for (int i =0; i< User::_totalHistory; i++){
//            itemName_ = _shoppingHistory[i].getName();
//         //    cout<<"\n166: "<<itemName<<" \n c str: " <<itemName_.c_str()<<endl; // debug
//            itemNameL = itemName.length();
//        //    cout<<"\n 168 "<<itemNameLen<<endl; // debug
//           binOutFile.write(itemName_.c_str(), itemNameL);
//       }
//      
//      int itemN, quant;
//      float price;
//       for (int i =0; i< User::_totalHistory; i++){
//           itemN = _shoppingHistory[i].getItemNum();
//           price = _shoppingHistory[i].getPrice(); 
//           quant = _shoppingHistory[i].getQuant();
//       
//         binOutFile.write(reinterpret_cast< char *>(&itemN ) , sizeof(itemN) );
//         binOutFile.write(reinterpret_cast< char *>(&price) , sizeof(price)  );
//         binOutFile.write(reinterpret_cast< char *>(&quant) , sizeof(quant)  );
//       }
//      
//      binOutFile.write(reinterpret_cast< char *>(&_recNum ) , sizeof(_recNum) );
//      binOutFile.write(reinterpret_cast< char *>(&_totalHistory ) , sizeof(_totalHistory) );
//       
//  }
//  

// Deserialize User function 
//void User::deserializeUser(ifstream& binInFile)  {
//    cout << "enter deserialization" << endl;
//   
//    if (!binInFile) {
//         ifstream binInFile("users.bin", ios::binary);
//        cerr << "Error opening file for deserialization." << endl;
//        return;
//    }
//    
//     
//         unsigned int nameLen, usrNameLen, emailLen, pwLen, addressLen;
//        binInFile.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
//        binInFile.read(reinterpret_cast<char*>(&usrNameLen), sizeof(usrNameLen));
//        binInFile.read(reinterpret_cast<char*>(&emailLen), sizeof(emailLen));
//        binInFile.read(reinterpret_cast<char*>(&pwLen), sizeof(pwLen));
//        binInFile.read(reinterpret_cast<char*>(&addressLen), sizeof(addressLen));
//        
//    cout << "Name Length: " << nameLen << endl;
//    cout << "Username Length: " << usrNameLen << endl;
//    cout << "Email Length: " << emailLen << endl;
//    cout << "Password Length: " << pwLen << endl;
//    cout << "Address Length: " << addressLen << endl;
//    
//string itemName;
//unsigned int itemNameLen;
//
//for(int i =0; i< User::_totalHistory; i++){
//  //  cout<<"i is "<<i<<" "<<endl; 
//    
//}
//    
//       itemName;
//       itemNameLen;
//      unsigned int it[User::_totalHistory];
//      for (int i =0; i< User::_totalHistory; i++){    
//             binInFile.read(reinterpret_cast<char *>(&itemNameLen ), sizeof(itemNameLen));
//             cout<<"degug 569 -> "<<itemNameLen<<endl;
//             it[i] = itemNameLen;
//             cout<<"read data -> "<<it[i]<<endl;
//          
//        char* tempItemName = new char[itemNameLen + 1];  // Allocate space for itemNameLen + 1 (for null terminator)
//        binInFile.read(tempItemName, itemNameLen);
//        tempItemName[itemNameLen] = '\0';  // Null-terminate the string
//        itemName = tempItemName;
//        delete[] tempItemName;
//
//        cout << "Item name " << i << ": " << itemName << endl;  // Add debug output
//
////          cout<<" line 616: "<<itemNameLen[i]<<endl;
////       itemName = _shoppingHistory[i].getName();
////      cout<<"\n149: "<<itemName<<endl; // debug
////      itemNameLen = itemName.length();
////       cout<<"\n 152 "<<itemNameLen<<endl; // debug
//    
//      }
//       
//      /*
//                 unsigned int nameLen;
//        unsigned int descLen; // New
//        ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen)); // Read length of name
//        ifs.read(reinterpret_cast<char*>(&descLen), sizeof(descLen)); // Read length of description
//        name.resize(nameLen);
//        ifs.read(&name[0], nameLen); // Read name data
//        description.resize(descLen); // Resize description string
//        ifs.read(&description[0], descLen); // Read description data
//        ifs.read(reinterpret_cast<char*>(&price), sizeof(price)); // Read price
//        ifs.read(reinterpret_cast<char*>(&quantity), sizeof(quantity)); // Read quantity
//       */
//}
//  

/*
   
 */
//  
//  void User::serializeUser(ofstream& binOutFile) {
//   //   cout<<"Enter serializatin for user: "<<User::_name<<endl; // debug
//      
//    if (!binOutFile.is_open()) {
//         ofstream binOutFile("users.bin", ios::binary);
//    }
//    unsigned int nameLen = _name.length();
//    cout<<"Customer's name: "<< _name<<endl;
//    unsigned int usrNameLen = _userName.length();
//    unsigned int emailLen = _email.length();
//    unsigned int pwLen = _passWord.length();
//    unsigned int addressLen = _address.length();
//
//    binOutFile.write(reinterpret_cast<const char *>(&nameLen), sizeof(nameLen));
//    binOutFile.write(reinterpret_cast<const char *>(&usrNameLen), sizeof(usrNameLen));
//    binOutFile.write(reinterpret_cast<const char *>(&emailLen), sizeof(emailLen));
//    binOutFile.write(reinterpret_cast<const char *>(&pwLen), sizeof(pwLen));
//    binOutFile.write(reinterpret_cast<const char *>(&addressLen), sizeof(addressLen));
//
//   // cout<<" Customers name: "<<_name.c_str()<<endl;
//    binOutFile.write(_name.c_str(), nameLen);
//    binOutFile.write(_userName.c_str(), usrNameLen);
//    binOutFile.write(_email.c_str(), emailLen);
//    binOutFile.write(_passWord.c_str(), pwLen);
//    binOutFile.write(_address.c_str(), addressLen);
//
//    unsigned int totalHistory = _totalHistory;
//    binOutFile.write(reinterpret_cast<const char *>(&totalHistory), sizeof(totalHistory));
//
//    for (int i = 0; i < _totalHistory; i++) {
//        const string &itemName = _shoppingHistory[i].getName();
//        unsigned int itemNameLen = itemName.length();
//        binOutFile.write(reinterpret_cast<const char *>(&itemNameLen), sizeof(itemNameLen));
//        binOutFile.write(itemName.c_str(), itemNameLen);
//
//        unsigned int itemN = _shoppingHistory[i].getItemNum();
//        float price = _shoppingHistory[i].getPrice();
//        unsigned int quant = _shoppingHistory[i].getQuant();
//        binOutFile.write(reinterpret_cast<const char *>(&itemN), sizeof(itemN));
//        binOutFile.write(reinterpret_cast<const char *>(&price), sizeof(price));
//        binOutFile.write(reinterpret_cast<const char *>(&quant), sizeof(quant));
//    }
//
//    binOutFile.write(reinterpret_cast<const char *>(&_recNum), sizeof(_recNum));
//
//  
//}
//  


//  
//  void User::serializeUser(ofstream& binOutFile) {
//   //   cout<<"Enter serializatin for user: "<<User::_name<<endl; // debug
//   if (!binOutFile.is_open()) {
//        cerr << "Error: Output file is not open." << endl;
//        return;
//    }
//
//    // Write user information
//    unsigned int nameLen = _name.length();
//    
// //   cout<<"name in serialize "<<_name<<endl; // debug
//    binOutFile.write(reinterpret_cast<const char *>(&nameLen), sizeof(nameLen));
// //   cout<<"777-> "<<User::_name.c_str()<<endl; // debug
//    binOutFile.write(_name.c_str(), nameLen);
//
//    unsigned int usrNameLen = _userName.length();
//    binOutFile.write(reinterpret_cast<const char *>(&usrNameLen), sizeof(usrNameLen));
//    binOutFile.write(_userName.c_str(), usrNameLen);
//
//    unsigned int emailLen = _email.length();
//    binOutFile.write(reinterpret_cast<const char *>(&emailLen), sizeof(emailLen));
//    binOutFile.write(_email.c_str(), emailLen);
//
//    unsigned int pwLen = _passWord.length();
//    binOutFile.write(reinterpret_cast<const char *>(&pwLen), sizeof(pwLen));
//    binOutFile.write(_passWord.c_str(), pwLen);
//
//    unsigned int addressLen = _address.length();
//    binOutFile.write(reinterpret_cast<const char *>(&addressLen), sizeof(addressLen));
//    binOutFile.write(_address.c_str(), addressLen);
//   cout<<"777-> "<<User::_name.c_str()<<endl; // debug
//    // Write total history
//    unsigned int totalHistory = _totalHistory;
//    binOutFile.write(reinterpret_cast<const char *>(&totalHistory), sizeof(totalHistory));
//
//    // Write shopping history
//    for (int i = 0; i < _totalHistory; i++) {
//         string itemName = _shoppingHistory[i].getName();
//        cout<<"item name "<<itemName<<endl;
//        unsigned int itemNameLen = itemName.length();
//        binOutFile.write(reinterpret_cast<const char *>(&itemNameLen), sizeof(itemNameLen));
//        binOutFile.write(itemName.c_str(), itemNameLen);
//
//         int itemN = _shoppingHistory[i].getItemNum();
//        float price = _shoppingHistory[i].getPrice();
//        unsigned int quant = _shoppingHistory[i].getQuant();
//        binOutFile.write(reinterpret_cast<const char *>(&itemN), sizeof(itemN));
//        binOutFile.write(reinterpret_cast<const char *>(&price), sizeof(price));
//        binOutFile.write(reinterpret_cast<const char *>(&quant), sizeof(quant));
//    }
//
//    // Write record number
//    binOutFile.write(reinterpret_cast<const char *>(&_recNum), sizeof(_recNum));
//}
//
//void User::deserializeUser(ifstream& binInFile) {
//    if (!binInFile.is_open()) {
//        cerr << "Error: Input file is not open." << endl;
//        return;
//    }
//
//    // Read user information
//    unsigned int nameLen;
//    binInFile.read(reinterpret_cast<char *>(&nameLen), sizeof(nameLen));
//    string name(nameLen, '\0');
//    binInFile.read(reinterpret_cast<char *>(&name[0]), nameLen);
//    _name = name;
//
//    unsigned int usrNameLen;
//    binInFile.read(reinterpret_cast<char *>(&usrNameLen), sizeof(usrNameLen));
//    string userName(usrNameLen, '\0');
//    binInFile.read(reinterpret_cast<char *>(&userName[0]), usrNameLen);
//    _userName = userName;
//
//    unsigned int emailLen;
//    binInFile.read(reinterpret_cast<char *>(&emailLen), sizeof(emailLen));
//    string email(emailLen, '\0');
//    binInFile.read(reinterpret_cast<char *>(&email[0]), emailLen);
//    _email = email;
//
//    unsigned int pwLen;
//    binInFile.read(reinterpret_cast<char *>(&pwLen), sizeof(pwLen));
//    string password(pwLen, '\0');
//    binInFile.read(reinterpret_cast<char *>(&password[0]), pwLen);
//    _passWord = password;
//
//    unsigned int addressLen;
//    binInFile.read(reinterpret_cast<char *>(&addressLen), sizeof(addressLen));
//    string address(addressLen, '\0');
//    binInFile.read(reinterpret_cast<char *>(&address[0]), addressLen);
//    _address = address;
//
//    // Read total history
//    unsigned int totalHistory;
//    binInFile.read(reinterpret_cast<char *>(&totalHistory), sizeof(totalHistory));
//    _totalHistory = totalHistory;
//
//    // Read shopping history
//    for (unsigned int i = 0; i < _totalHistory; i++) {
//        unsigned int itemNameLen;
//        binInFile.read(reinterpret_cast<char *>(&itemNameLen), sizeof(itemNameLen));
//        string itemName(itemNameLen, '\0');
//        binInFile.read(reinterpret_cast<char *>(&itemName[0]), itemNameLen);
//        cout<<"778 itemName "<<itemName<<endl;
//        _shoppingHistory[i].setName(itemName);
//
//        unsigned int itemN;
//        binInFile.read(reinterpret_cast<char *>(&itemN), sizeof(itemN));
//        _shoppingHistory[i].setItemNum(itemN);
//
//        float price;
//        binInFile.read(reinterpret_cast<char *>(&price), sizeof(price));
//        _shoppingHistory[i].setPrice(price);
//
//        unsigned int quant;
//        binInFile.read(reinterpret_cast<char *>(&quant), sizeof(quant));
//        _shoppingHistory[i].setQuant(quant);
//    }
//
//    // Read record number
//    binInFile.read(reinterpret_cast<char *>(&_recNum), sizeof(_recNum));
//}

/*New Versions of serialize and deserialize 
 */

void User::serializeUser(ofstream& binOutFile) const {
    unsigned int nameLen = _name.length();
    unsigned int userNameLen = _userName.length();
    unsigned int emailLen = _email.length();
    unsigned int passWordLen = _passWord.length();
    unsigned int addressLen = _address.length();

    binOutFile.write(reinterpret_cast<const char*> (&nameLen), sizeof (nameLen));
    binOutFile.write(reinterpret_cast<const char*> (&userNameLen), sizeof (userNameLen));
    binOutFile.write(reinterpret_cast<const char*> (&emailLen), sizeof (emailLen));
    binOutFile.write(reinterpret_cast<const char*> (&passWordLen), sizeof (passWordLen));
    binOutFile.write(reinterpret_cast<const char*> (&addressLen), sizeof (addressLen));
    
    unsigned int itemNameLen;
    
    for (int i =0 ; i < User::_totalHistory; i++){
    cout<<"840: "<<    _shoppingHistory[i].getName().length()<<endl;
     itemNameLen = _shoppingHistory[i].getName().length();
       binOutFile.write(reinterpret_cast<const char*> (&itemNameLen), sizeof (itemNameLen));
    }
    
    //delete : for debug
//    cout<<_name<<_userName << _email << _passWord << _address <<endl;
//    
//    cout << nameLen << userNameLen << emailLen << passWordLen << addressLen <<endl;
//    
//    cout<<_name.c_str()<<_userName.c_str() << _email.c_str() << _passWord.c_str() << _address.c_str() <<endl;
 

    binOutFile.write(_name.c_str(), nameLen);

    binOutFile.write(_userName.c_str(), userNameLen);

    binOutFile.write(_email.c_str(), emailLen);

    binOutFile.write(_passWord.c_str(), passWordLen);

    binOutFile.write(_address.c_str(), addressLen);
    
    for (int i =0 ; i < User::_totalHistory; i++){
   // cout<<"840: "<<    _shoppingHistory[i].getName().length()<<endl;
      itemNameLen = _shoppingHistory[i].getName().length(); 
      
       binOutFile.write( _shoppingHistory[i].getName().c_str(), itemNameLen )
    }
    
    

   // binOutFile.write(reinterpret_cast<const char*> (&_cartSize), sizeof (_cartSize));
    binOutFile.write(reinterpret_cast<const char*> (&_recNum), sizeof (_recNum));
    binOutFile.write(reinterpret_cast<const char*> (&_totalHistory), sizeof (_totalHistory));
    
        for (int i =0 ; i < User::_totalHistory; i++){
   // cout<<"840: "<<    _shoppingHistory[i].getName().length()<<endl;
     //itemNameLen = _shoppingHistory[i].getName().length();        
    binOutFile.write(reinterpret_cast<const char*> (&_shoppingHistory[i].getPrice() ), sizeof (_shoppingHistory[i].getPrice() ));
    binOutFile.write(reinterpret_cast<const char*> (&_shoppingHistory[i].getQuant() ), sizeof (_shoppingHistory[i].getQuant() ));
   
    }
    

//            for (int i = 0; i < User::_totalHistory; ++i) {
//                _shoppingHistory[i].serialize(binOutFile);
//            }
}

void User::deserializeUser(ifstream& binInFile) {
    
    unsigned int nameLen;
    binInFile.read(reinterpret_cast<char*> (&nameLen), sizeof (nameLen));
    
    unsigned int userNameLen;
    binInFile.read(reinterpret_cast<char*> (&userNameLen), sizeof (userNameLen));
    
    unsigned int emailLen;
    binInFile.read(reinterpret_cast<char*> (&emailLen), sizeof (emailLen));
    
    unsigned int passWordLen;
    binInFile.read(reinterpret_cast<char*> (&passWordLen), sizeof (passWordLen));
    
    unsigned int addressLen;
    binInFile.read(reinterpret_cast<char*> (&addressLen), sizeof (addressLen));
    /*
     * 
    binOutFile.write(reinterpret_cast<const char*> (&nameLen), sizeof (nameLen));
    binOutFile.write(reinterpret_cast<const char*> (&userNameLen), sizeof (userNameLen));
    binOutFile.write(reinterpret_cast<const char*> (&emailLen), sizeof (emailLen));
    binOutFile.write(reinterpret_cast<const char*> (&passWordLen), sizeof (passWordLen));
    binOutFile.write(reinterpret_cast<const char*> (&addressLen), sizeof (addressLen));
     */
    
    string name(nameLen, '\0');
    binInFile.read(reinterpret_cast<char*> (&name[0]), nameLen);
    _name = name;
    cout<<"878 "<<_name<<endl;

    string userName(userNameLen, '\0');
    binInFile.read(reinterpret_cast<char*> (&userName[0]), userNameLen);
    _userName = userName;

 
    string email(emailLen, '\0');
    binInFile.read(reinterpret_cast<char*> (&email[0]), emailLen);
    _email = email;


    string passWord(passWordLen, '\0');
    binInFile.read(reinterpret_cast<char*> (&passWord[0]), passWordLen);
    _passWord = passWord;

   
    string address(addressLen, '\0');
    binInFile.read(reinterpret_cast<char*> (&address[0]), addressLen);
    _address = address;

   // binInFile.read(reinterpret_cast<char*> (&_cartSize), sizeof (_cartSize));
    binInFile.read(reinterpret_cast<char*> (&_recNum), sizeof (_recNum));
    binInFile.read(reinterpret_cast<char*> (&_totalHistory), sizeof (_totalHistory));

//            for (int i = 0; i < User::_totalHistory; ++i) {
//                _shoppingHistory[i].deserialize(binInFile);
//               // _shoppingHistory[i].display();
//            }
}