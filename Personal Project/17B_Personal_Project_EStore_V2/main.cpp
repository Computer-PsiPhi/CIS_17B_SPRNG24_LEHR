
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
#include "Store.h"
/*
 * 
 */
int main(int argc, char** argv) {

    const string inventory = "inventory.txt";

    Store s;
    s.loadStore(inventory);
    s.displayStore();
    
    return 0;
}

