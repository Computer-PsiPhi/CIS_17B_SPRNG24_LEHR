/* 
 * File:   User.cpp
 * Author: Noel Perez
 * 
 * Created on March 23, 2024, 10:52 PM
 */
#include <iostream>
#include "User.h"
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
    regex upperCase("[A-Z]");
    regex lowerCase("[a-z]");
    regex spaces("[\\s]");

    // Make sure the string contains all matches to the regular expressions
    return (
            str.length() >= minLen and
            regex_search(str, upperCase) and
            regex_search(str, lowerCase) and
            regex_search(str, spaces)
            );
}

bool User::isValUsrName(string str, int minLen) {
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

bool User::isValEmail(string str, int minLen) {
    // Regular expressions to match special character or letter requirements
    regex amp("[@]");
    regex specialChars("[!@#$%^&*()_+-={};:',.<>?/]");
    regex upperCase("[A-Z]");
    regex lowerCase("[a-z]");
    regex numbers("[0-9]");
    regex spaces("[\\s]");

    // Make sure the string contains all matches to the regular expressions
    return (
            str.length() >= minLen and
            regex_search(str, amp) and
            regex_search(str, specialChars) and
            regex_search(str, upperCase) and
            regex_search(str, lowerCase) and
            regex_search(str, numbers) and
            regex_search(str, spaces)
            );
}

bool User::isValPass(string str, int minLen) {
    // Regular expressions to match special character or letter requirements
    //regex specialChars("[!@#$%^&*()_+-={};:',.<>?/]");
    regex upperCase("[A-Z]");
    regex lowerCase("[a-z]");
    //regex numbers("[0-9]");
    regex spaces("[\\s]");

    // Make sure the string contains all matches to the regular expressions
    return (
            str.length() >= minLen and
            // regex_search(str, specialChars) and
            regex_search(str, upperCase) and
            regex_search(str, lowerCase) and
            //  regex_search(str, numbers) and
            regex_search(str, spaces)
            );
}

bool User::isValAddss(string str, int minLen) {
    // Regular expressions to match special character or letter requirements
    //regex specialChars("[!@#$%^&*()_+-={};:',.<>?/]");
    regex upperCase("[A-Z]");
    regex lowerCase("[a-z]");
    //regex numbers("[0-9]");
    regex spaces("[\\s]");

    // Make sure the string contains all matches to the regular expressions
    return (
            str.length() >= minLen and
            // regex_search(str, specialChars) and
            regex_search(str, upperCase) and
            regex_search(str, lowerCase) and
            //  regex_search(str, numbers) and
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
            this->_name = name;
            isGood = true;
        } catch (const invalid_argument& e) {
            cerr << "Invalid User first and last name: " << e.what();
        } catch (...) {
            cerr << "Unknown exception " << endl;
        }

    }
}

void User::setUsrName() {
    string usrName = "";
    bool isGood = false;

    while (!isGood) {

        cout << "\nEnter First Name & Last Name: " << endl;
        getline(cin, usrName);

        try {
            if (!isValName(usrName)) {
                throw invalid_argument("Follow Username Requirements!\n");
            }
            this->_userName = usrName;
            isGood = true;
        } catch (const invalid_argument& e) {
            cerr << "Invalid Username: " << e.what();
        } catch (...) {
            cerr << "Unknown exception " << endl;
        }

    }
}

void User::setEmail() {

}

void User::setPassWord() {

}

void User::setAddress() {

}

const string & User::getName() const {
    return this->_name;
}
const string & User::getUsrName() const{
    return this->_userName;
}
const string & User::getEmail() const{
    return this->_email;
}
const string & User::getPassWord() const{
    return this->_passWord;
}
const string & User::getAddress() const{
    return this->_address;
}