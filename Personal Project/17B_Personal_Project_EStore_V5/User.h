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

class Store;

class User {
private:
    string _name;
 
    string _userName;
    
    string _email;
    
    string _passWord;
    
    string _address;
    

    int _cartSize;

    int _recNum;
    Item _shoppingHistory[SIZE];
    int _totalHistory;
    Cart _shoppingCart;

    bool _isLoggedIn;
    bool _isAdmin;
    
    int _MAX =100;
    static int _users;
public:

    User();

    User(const User& orig);

    virtual ~User();

    User(const string& u, const string& a, int num);
    User (const string &n, const string &un, bool isAdmin, bool isLoggedin );

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
         
     int getTotItemInHist()const{return this->User::_totalHistory; };
 const Item &getShopHist(int index)const{ return this->User::_shoppingHistory[index]; };
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
    void setRecNum(int r); 

    void setMaxUsers(int N){this->_MAX = N;}
    
    const int &getMaxUsers(){return this->_MAX;};
    
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
    
    void displayContactInfo();
    
    void changeUserInfo(User* usersArray, int size, int index) ;
    
  static void increaseUsers(){ _users++; };
  static void decreaseUsers(){ _users++; };
  
  static int getNumUsers(){ return _users;  };
  
  void addToHistory();
  
  void serializeUser( const string &file);
  void deserializeUser( const string &file);
      
};
#endif /* USER_H */

