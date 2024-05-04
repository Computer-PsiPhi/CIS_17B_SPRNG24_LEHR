
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
    Item shopHistory[SIZE];
    int _totalHistory;
    Cart shoppingCart;


public:
    
    
    User();
   
    User(const User& orig);
    virtual ~User();

    User(const string& name, const string& userName, const string& email,
         const string& password, const string& address ) :
        _name(name), _userName(userName), _email(email), _passWord(password),
        _address(address),  _cartSize(0), _totalHistory(0),
        shoppingCart{} {
        
        }
   User(const string& u, const string& a, int num ) ;


    
    
    
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
    const int getRecNum() const ;


    Cart& getCart() { return shoppingCart; }
    

    
    void displayHistory(){
        for(short i =0; i < this->_totalHistory; i++){
            cout<<"recNum "<<this->getRecNum()<<endl;
            this->shopHistory[i].display();
            cout<<"-------------------"<<endl;
        }
    }
    
    void fillRand( const Store &store){
      srand(time(nullptr)); // Seed random number generator
    cout << endl;
    int numItems = rand() % 10 + 1; // Randomly choose number of items (1-10)
    cout << "random numItems: " << numItems << endl;
    cout << "num items in store: " << store.getTotalItems() << endl;
    
    // Temporary array to store selected item numbers
    int selected[numItems];
    
    for (int i = 0; i < numItems; i++) {
        int itemIndx = rand() % store.getTotalItems();
        int itemNum = store.getItem(itemIndx).getItemNum();
        
        // Check if itemNum is already in selected array
        bool exists = false;
        for (int j = 0; j < i; j++) {
            if (selected[j] == itemNum) {
                exists = true;
                break;
            }
        }
        
        if (!exists) {
            selected[i] = itemNum;
            shopHistory[_totalHistory++] = store.getItem(itemIndx); // Add item to shopping history
        } else {
            // Item already selected, decrement _totalHistory as it wasn't incremented
            _totalHistory--;
        }
    }
    cout<<"Total items in hisotry "<<_totalHistory<<endl;
    }
    

};

#endif /* USER_H */

