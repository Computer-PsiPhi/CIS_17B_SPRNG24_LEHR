/* 
 * File:   User.cpp
 * Author: Noel Perez
 * 
 * Created on March 23, 2024, 10:52 PM
 */
#include <iostream>
#include "User.h"
#include "Admin.h"
#include <regex>


using namespace std;

User::User() {
}

User::User(const User& orig) {
}

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
        not regex_search(str,specialChars) and 
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
    //    not regex_search(str, specialChars) and
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
    string usrName = "";
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
    string email="";
    bool isGood = false;
    
    while(not isGood){
        cout<<"\nEnter email: "<<endl;
        getline(cin,email);
        
        try{
            if( not User::isValEmail(email)){
                throw invalid_argument("Incorrect Email Requirements\n");
            }
            isGood = true;
        }catch(const invalid_argument &e){
            cerr << "Invalid Email: "<<e.what();
        }catch(...){
            cerr<<"Unknown exception"<<endl;
        }
    }
    this->_email=email;
}

void User::setPassWord() {
    string passwrd="";
    bool isGood=false;
    
    while(not isGood){
        cout<<"\nEnter Password: line 185 "<<endl;
        cin >>passwrd;
        cin.clear();
        try{
            if( not User::isValPass(passwrd)){
                throw invalid_argument("Incorrect Password Requirements\n");
            }
            isGood=true;
        }catch(const invalid_argument &e){
            cerr<<"Invalid Password: "<<e.what();
        }catch(...){
            cerr<<"Unknown exception"<<endl;
        }
    }
    this->User::_passWord=passwrd;
}

void User::setAddress() {
      string addrss="";
    bool isGood = false;
    
    while(not isGood){
        cout<<"\nEnter Address: "<<endl;
        cin.ignore();
        getline(cin,addrss);
        cout<<"entered: "<<addrss<<endl;
        try{
            if( not User::isValAddss(addrss)){
                throw invalid_argument("Incorrect Address Requirements\n");
            }
            isGood = true;
        }catch(const invalid_argument &e){
            cerr << "Invalid Address: "<<e.what();
        }catch(...){
            cerr<<"Unknown exception"<<endl;
        }
    }
    this->User::_address=addrss;
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