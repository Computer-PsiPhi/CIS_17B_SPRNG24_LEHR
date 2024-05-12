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
        getline(cin,usrName);
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
        getline(cin,email);
        
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
        cout<<"\nEnter Password "<<endl;       
   getline(cin,passwrd);
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
       if( r > this->User::_MAX) {
           cerr<<"ERROR!"<<endl;
                   return; 
       }
       this->User::_recNum = r ;
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
    int numItems =3 ;// min(rand() % 10 + 1, store.getTotalItems());

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
    cout << "Total items in history: " << this->User::_totalHistory <<endl;
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
    cout << left << setw(11) << "Name:" << right << setw(10) << this->_name << endl;
    cout << left << setw(11) << "Username:" << right << setw(10) << this->_userName << endl;
    cout << left << setw(11) << "Password:" << right << setw(10) << this->_passWord << endl;
    cout << left << setw(11) << "Email:" << right << setw(10) << this->_email << endl;
    cout << left << setw(11) << "Address:" << right << setw(10) << this->_address << endl;
      cout << left << setw(11) << "Record number:" << right << setw(10) << this->_recNum << endl;
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
  void User::addToHistory(){
       int itemCount = this->User::_shoppingCart.getCount();
       cout<<"Number of Items in Cart to be added to shopping History: "<<itemCount<<endl;
      for (int i =0; i< itemCount; i++){
           this->_shoppingHistory[_totalHistory ] = _shoppingCart.getItem(i);
           _totalHistory++;
      } 
  }

/*TODO 
 *     ADD REMOVE ITEM/S FROM HISTORY
 */
  
  // Serialize User function
  void User::serializeUser( const string &file){//ofstream &binOutFile){
      
       ofstream binOutFile(file, ios::binary);
     
      unsigned int nameLen = _name.length();
      unsigned int usrNameLen = _userName.length();
      unsigned int emailLen = _email.length();
      unsigned int pwLen = _passWord.length();
      unsigned int addressLen = _address.length();
      
      
      binOutFile.write(reinterpret_cast<char *>(&nameLen ), sizeof(nameLen));
      binOutFile.write(reinterpret_cast<char *>(&usrNameLen ), sizeof(usrNameLen));
      binOutFile.write(reinterpret_cast<char *>(&emailLen ), sizeof(emailLen));
      binOutFile.write(reinterpret_cast<char *>(&pwLen ), sizeof(pwLen));
      binOutFile.write(reinterpret_cast<char *>(&addressLen ), sizeof(addressLen));
      
      
      string itemName;
      unsigned int itemNameLen;
      
      for (int i =0; i< User::_totalHistory; i++){    
       itemName = _shoppingHistory[i].getName();
      cout<<"\n149: "<<itemName<<endl; // debug
      itemNameLen = itemName.length();
       cout<<"\n 152 "<<itemNameLen<<endl; // debug
       binOutFile.write(reinterpret_cast<char *>(&itemNameLen ), sizeof(itemNameLen));
      }
      
      binOutFile.write(_name.c_str(),nameLen );
      binOutFile.write(_userName.c_str(), usrNameLen );
      binOutFile.write(_email.c_str(), emailLen);
      binOutFile.write(_passWord.c_str(), pwLen);
      binOutFile.write(_address.c_str(), addressLen);
      
      string itemName_;
      unsigned int itemNameL;
       for (int i =0; i< User::_totalHistory; i++){
            itemName_ = _shoppingHistory[i].getName();
          //    cout<<"\n166: "<<itemName<<" \n c str: " <<itemName_.c_str()<<endl; // debug
            itemNameL = itemName.length();
          //  cout<<"\n 168 "<<itemNameLen<<endl; // debug
           binOutFile.write(itemName_.c_str(), itemNameL);
       }
      
      int itemN, quant;
      float price;
       for (int i =0; i< User::_totalHistory; i++){
           itemN = _shoppingHistory[i].getItemNum();
           price = _shoppingHistory[i].getPrice(); 
           quant = _shoppingHistory[i].getQuant();
       
         binOutFile.write(reinterpret_cast< char *>(&itemN ) , sizeof(itemN) );
         binOutFile.write(reinterpret_cast< char *>(&price) , sizeof(price)  );
         binOutFile.write(reinterpret_cast< char *>(&quant) , sizeof(quant)  );
       }
      
      binOutFile.write(reinterpret_cast< char *>(&_recNum ) , sizeof(_recNum) );
      binOutFile.write(reinterpret_cast< char *>(&_totalHistory ) , sizeof(_totalHistory) );
      
      
  }
  
  // Deserialize User function 
  void User::deserializeUser(const string &file) {
    ifstream binInFile(file, ios::binary);
    if (!binInFile.is_open()) {
        cerr << "Error opening file for deserialization." << endl;
        return;
    }

    unsigned int nameLen, usrNameLen, emailLen, pwLen, addressLen;
    binInFile.read(reinterpret_cast<char *>(&nameLen), sizeof(nameLen));
    binInFile.read(reinterpret_cast<char *>(&usrNameLen), sizeof(usrNameLen));
    binInFile.read(reinterpret_cast<char *>(&emailLen), sizeof(emailLen));
    binInFile.read(reinterpret_cast<char *>(&pwLen), sizeof(pwLen));
    binInFile.read(reinterpret_cast<char *>(&addressLen), sizeof(addressLen));

    if (!binInFile.good()) {
        cerr << "Error reading data lengths." << endl;
        binInFile.close();
        return;
    }

    char *nameBuffer = new char[nameLen + 1];
    char *userNameBuffer = new char[usrNameLen + 1];
    char *emailBuffer = new char[emailLen + 1];
    char *pwBuffer = new char[pwLen + 1];
    char *addressBuffer = new char[addressLen + 1];

    binInFile.read(nameBuffer, nameLen);
    binInFile.read(userNameBuffer, usrNameLen);
    binInFile.read(emailBuffer, emailLen);
    binInFile.read(pwBuffer, pwLen);
    binInFile.read(addressBuffer, addressLen);

    if (!binInFile.good()) {
        cerr << "Error reading string data." << endl;
        delete[] nameBuffer;
        delete[] userNameBuffer;
        delete[] emailBuffer;
        delete[] pwBuffer;
        delete[] addressBuffer;
        binInFile.close();
        return;
    }

    nameBuffer[nameLen] = '\0';
    userNameBuffer[usrNameLen] = '\0';
    emailBuffer[emailLen] = '\0';
    pwBuffer[pwLen] = '\0';
    addressBuffer[addressLen] = '\0';

    _name = string(nameBuffer);
    _userName = string(userNameBuffer);
    _email = string(emailBuffer);
    _passWord = string(pwBuffer);
    _address = string(addressBuffer);

    delete[] nameBuffer;
    delete[] userNameBuffer;
    delete[] emailBuffer;
    delete[] pwBuffer;
    delete[] addressBuffer;

    string itemName;
    unsigned int itemNameLen;
    for (int i = 0; i < _totalHistory; i++) {
        binInFile.read(reinterpret_cast<char *>(&itemNameLen), sizeof(itemNameLen));
        char *itemNameBuffer = new char[itemNameLen + 1];
        binInFile.read(itemNameBuffer, itemNameLen);
        itemNameBuffer[itemNameLen] = '\0';
        itemName = string(itemNameBuffer);
        delete[] itemNameBuffer;
        // You can use itemName here as needed
    }

    int itemN, quant;
    float price;
    for (int i = 0; i < _totalHistory; i++) {
        binInFile.read(reinterpret_cast<char *>(&itemN), sizeof(itemN));
        binInFile.read(reinterpret_cast<char *>(&price), sizeof(price));
        binInFile.read(reinterpret_cast<char *>(&quant), sizeof(quant));
        // You can use itemN, price, and quant here as needed
    }

    binInFile.read(reinterpret_cast<char *>(&_recNum), sizeof(_recNum));
    binInFile.read(reinterpret_cast<char *>(&_totalHistory), sizeof(_totalHistory));

    binInFile.close();
}

  