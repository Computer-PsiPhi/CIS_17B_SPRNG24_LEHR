
/* 
 * File:   User.h
 * Author: Noel Perez
 *
 * Created on March 23, 2024, 10:52 PM
 */

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

#include "Item.h"
#include "Cart.h"

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
    int _recNum;
    int _cartSize;
    Item shopHistory[SIZE];
    int _totalHistoy;
    Cart shoppingCart[SIZE];


public:
    User();
    User(const User& orig);
    virtual ~User();

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


    unsigned int l = User::_name.length();
};

#endif /* USER_H */

