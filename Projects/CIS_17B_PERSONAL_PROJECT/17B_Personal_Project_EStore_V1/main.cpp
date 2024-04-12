
/* 
 * File:   main.cpp
 * Author: Noel Perez
 * Created on March 23, 2024, 10:48 PM
 * Purpose:
 */

#include <cstdlib>
#include <iostream>

using namespace std;

#include "User.h"
/*bob
 * 
 */
int main(int argc, char** argv) {

    
    User u;
    
    u.setName();
    cout<<u.getName()<<endl;
    
    u.setUsrName();
    cout<<u.getUsrName()<<endl;
    
    u.setPassWord();
    cout<<u.getPassWord()<<endl;
    
    u.setAddress();
    cout<<u.getAddress()<<endl;
    
    u.setEmail();
    cout<<u.getEmail()<<endl;
    
    return 0;
}

