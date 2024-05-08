/* 
 * File:   Admin.cpp
 * Author: Noel Perez
 * Created on March 23, 2024, 10:51 PM
 */
#include <iostream>
#include "Admin.h"
using namespace std;

Admin::Admin() {
}

  Admin::Admin(const string &password, const string &userName, bool isAdmin, bool isLoggedIn) :
  User (password, userName, isAdmin, isLoggedIn )
  {
  }

   Admin::Admin(const string &password, const string &userName, bool isAdmin, bool isLoggedIn, int recNum ):
   User (password, userName, isAdmin, isLoggedIn) {
       this->Admin::setRecNum(recNum);
 }
   
  
Admin::Admin(const Admin& orig) {
}

Admin::~Admin() {
}

