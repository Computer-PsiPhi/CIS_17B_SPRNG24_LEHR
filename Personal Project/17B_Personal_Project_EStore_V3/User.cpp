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
using namespace std;

User::User():  _name(),
        _userName{},
        _email{},
        _passWord{},
        _address{} ,
        _cartSize{0},
        _totalHistory(0),
        _shoppingCart{},
        _recNum{0},
        _isLoggedIn{false},
        _isAdmin{false}      
        {  //Default Constructor
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
_recNum{recNum},
_cartSize(0),
_totalHistory(0),
_shoppingCart {},
_shoppingHistory{}
{};

User::~User() {
}

bool User::isValName(string str, int minLen) {

    // Regular expressions to match special character or letter requirements
    regex specialChars("[!@#$%^&*()_+-={};:',.<>?/]");
    regex upperCase("[A-Z]");
    regex lowerCase("[a-z]");
    regex spaces("[\\s]");

    // Make sure the string contains all matches to the regular expressions
    return (
            str.length() >= minLen and
            not regex_search(str, specialChars) and
            regex_search(str, upperCase) and
            regex_search(str, lowerCase) and
            regex_search(str, spaces)
            );
}

bool User::isValUsrName(string str, int minLen) {
    // Regular expressions to match special character or letter requirements
    regex specialChars("[!#$%^&*()_+-={};:',<>?/]");
    regex lowerCase("[a-z]");
    regex numbers("[0-9]");
    regex spaces("[\\s]");

    // Make sure the string contains all matches to the regular expressions
    return (
            str.length() >= minLen and
            regex_search(str, specialChars) and
            regex_search(str, lowerCase) and
            regex_search(str, numbers) and
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
    // Regular expressions to match special character or letter requirements
    // regex specialChars("[!@#$%^&*()_+-={};:',.<>?/]");
    // regex upperCase("[A-Z]");
    regex lowerCase("[a-z]");
    regex numbers("[0-9]");
    regex spaces("[\\s]");

    // Make sure the string contains all matches to the regular expressions
    return (
            str.length() >= minLen and
            //  not regex_search(str, specialChars) and
            //   regex_search(str, upperCase) and
            regex_search(str, lowerCase) and
            regex_search(str, numbers) and
            regex_search(str, spaces)
            );
}

void User::setName() {
    string name = "";
    bool isGood = false;

    while (!isGood) {
        cout << "\nEnter First Name & Last Name: " << endl;
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
    string usrName = {};
    bool isGood = false;

    while (!isGood) {
        cout << "\nEnter Username: " << endl;
        cin >> usrName;

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
    string passwrd = "";
    bool isGood = false;

    while (not isGood) {
        cout << "\nEnter Password: line 185 " << endl;
        cin >>passwrd;
        cin.clear();
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
        cin.ignore();
        getline(cin, addrss);
        cout << "entered: " << addrss << endl;
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
 
    // Create an array of item indices 
    int *itemIndices = new int[store.getTotalItems()];
    for (int i = 0; i < store.getTotalItems(); i++) {
        itemIndices[i] = i;
    }

    // Shuffle 
    for (int i = store.getTotalItems() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = itemIndices[i];
        itemIndices[i] = itemIndices[j];
        itemIndices[j] = temp;
    }
// Randomly choose number of items 
    int numItems = min(rand() % 10 + 1, store.getTotalItems()); 

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

    delete []itemIndices;
    delete []selected;
}

void User::displayHistory() {
    cout<<endl;
    cout<<endl;
    cout<<"**********************"<<endl;
    cout << "Record Number: " << this->getRecNum() + 1 << endl;
    cout<<"**********************"<<endl;
    User::displayContactInfo();
    cout<<"Shopping History "<<endl;
    cout<<"======================"<<endl;
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

 void User::displayContactInfo(){
     cout<<"Personal Information: "<<endl;
     cout<<"======================"<<endl;
cout << left << setw(11) << "Name:" << right << setw(10) << this->_name << endl;
cout << left << setw(11) << "Username:" << right << setw(10) << this->_userName << endl;
cout << left << setw(11) << "Email:" << right << setw(10) << this->_email << endl;
cout << left << setw(11) << "Address:" << right << setw(10) << this->_address << endl;
cout<<endl;
 }
 