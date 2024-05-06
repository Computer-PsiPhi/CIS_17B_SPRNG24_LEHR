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

/*
 * 
 */
int main(int argc, char** argv) {
    srand(static_cast<unsigned int> (time(nullptr)));
  
    const string products = "products.bin";
    // Load store inventory and display
    Store store;
    store.displayStore();
   store.loadStore();
   store.displayStore();
   // store.toTextFile();
   

    store.toBinaryFile(products);
    store.fromBinaryFile(products);
     store.serachStoreRecords();

    const int SIZE {100};
   // User customers[SIZE] = {};
    User *customers = new User[SIZE];
    
    int randomUsers (10);
    store.genRandomData(customers,randomUsers,SIZE);
    
    


    for(int i =0; i< randomUsers ; i++){
     
      //  customers[i].displayHistory();
    }
 

//    User user;
//        int choice;
//        double total = 0.0;
//        bool found = false;
//        do {
//            // Display menu
//            cout << "\nWelcome to the Store!" << endl;
//            cout << "1. Display Store Inventory" << endl;
//            cout << "2. Add Item to Cart" << endl;
//            cout << "3. View Cart" << endl;
//            cout << "4. Checkout" << endl;
//            cout << "5. Exit" << endl;
//            cout << "Enter your choice: ";
//            cin >> choice;
//            cin.ignore();
//         
//            switch (choice) {
//                case 1: // Display Store Inventory
//                    store.displayStore();
//                    break;
//                case 2: // Add Item to Cart
//                    int itemNum;
//                    found = false;
//                    cout << "Enter the item number to add to your cart: ";
//                    cin >> itemNum;
//                    cout<<"Item num entered: "<<itemNum<<endl;
//                    // Find item in store inventory
//                    for (int i = 0; i < store.getTotalItems(); ++i) {
//                        if (store.getItem(i).getItemNum() == itemNum) {
//                            user.getCart().addItem(store.getItem(i));
//                            cout << "Item added to cart." << endl;
//                            found = true;
//                            break;
//                        }
//                    }
//                    if (!found) {
//                        cout << "Item not found in store inventory." << endl;
//                    }
//                    break;
//                case 3: // View Cart
//                   
//                    user.getCart().showCart();
//                    break;
//                case 4: // Checkout
//                    total = user.getCart().checkOut();
//                    cout << "Total amount: $" << total << endl;
//                    cout << "Thank you for your purchase!" << endl;
//                    break;
//                case 5: // Exit
//                    cout << "Exiting program." << endl;
//                    break;
//                default:
//                    cout << "Invalid choice. Please try again." << endl;
//            }
//        } while (choice != 5);

    delete []customers;
    return 0;
}

