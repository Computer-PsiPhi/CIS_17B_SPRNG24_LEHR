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

#include "User.h"
#include "Store.h"
#include "Cart.h"
#include "Admin.h"

#include "Menu.h"


int main(int argc, char** argv) {
    srand(static_cast<unsigned int> (time(nullptr)));
  
    const string products = "products.bin";
    // Load store inventory and display
 //   Store store;
   Menu menu = Menu(products);
   menu.runMenu();
   // store.loadStore();

   // Admin admin = Admin("Password", "Admin123", true, false);
   

//    store.toBinaryFile(products);
//    store.fromBinaryFile(products);
//    store.serachStoreRecords();
//    
//    store.searchBinaryRecords();

//    const int SIZE {100};
   // User customers[SIZE] = {};
//    User *customers = new User[SIZE];
//    
//    int randomUsers (10);
  //  store.genRandomData(customers,randomUsers,SIZE);
    
    


//    for(int i =0; i< randomUsers ; i++){
//     
//        customers[i].displayHistory();
//    }
 


 //   delete []customers;
    return 0;
}

