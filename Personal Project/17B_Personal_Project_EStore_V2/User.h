
/* 
 * File:   User.h
 * Author: Noel Perez
 * Created on March 23, 2024, 10:52 PM
 */

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

#include "Item.h"
#include "Cart.h"
#include "Store.h"

class User {
private:
    string _name;
    unsigned int _nameLen;
    string _userName;
    unsigned int _usrnameLen;
    string _email;
    unsigned int _emailLen;
    string _passWord;
    unsigned int _pswrdLen;
    string _address;
    unsigned int _adrsLen;

    int _cartSize;

    int _recNum;
    Item _shoppingHistory[SIZE];
    int _totalHistory;
    Cart _shoppingCart;

    bool _isLoggedIn;
    bool _isAdmin;

public:

    User();

    User(const User& orig);

    virtual ~User();

    User(const string& u, const string& a, int num);

    User(const string& name,
            const string& userName,
            const string& email,
            const string& password,
            const string& address);

    User(const string & name,
         const string &userName,
         const string &email,
         const string &password,
         const string &address,
         bool isLogged,
         bool isAdmin,
         int recNum);
         

    bool isValName(string str, int minLen = 5);
    bool isValUsrName(string str, int minLen = 5);
    bool isValEmail(string str, int minLen = 5);
    bool isValPass(string str, int minLen = 5);
    bool isValAddss(string str, int minLen = 5);

    void setName();
    void setUsrName();
    void setEmail();
    void setPassWord();
    void setAddress();

    const string & getName() const;
    const string & getUsrName() const;
    const string & getEmail() const;
    const string & getPassWord() const;
    const string & getAddress() const;
    const int getRecNum() const;

    Cart& getCart() {
        return _shoppingCart;
    }

    void fillRand(const Store &store);

    void displayHistory();

    bool verifyCred(const string &password, const string &userName);
    
    void setLogStatus(bool status);
    
    void setAdminStatus(bool status);
    bool getlogStatus();
    bool getadminStatus();
};

#endif /* USER_H */

