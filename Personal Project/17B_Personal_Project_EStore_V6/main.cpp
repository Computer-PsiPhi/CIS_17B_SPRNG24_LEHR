/* 
 * File:   main.cpp
 * Author: Noel Perez
 * Created on March 23, 2024, 10:48 PM
 * Purpose:
 */

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;


#include "Menu.h"

int main(int argc, char** argv) {
    srand(static_cast<unsigned int> (time(nullptr)));

    const string products = "products.bin";

    Menu menu = Menu(products);

    menu.runMenu();
    return 0;
}

/* TODO Once user checks out update shopping history
 */