
/* 
 * File:   Menu.h
 * Author: Noel Perez
 *
 * Created on March 23, 2024, 10:54 PM
 */

#ifndef MENU_H
#define MENU_H

class Menu {
private:

public:
    Menu();
    Menu(const Menu& orig);
    virtual ~Menu();

void clearScreen();
void clearScreenChoice();

};

#endif /* MENU_H */

