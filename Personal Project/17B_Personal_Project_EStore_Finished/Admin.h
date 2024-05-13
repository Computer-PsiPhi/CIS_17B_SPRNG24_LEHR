
/* 
 * File:   Admin.h
 * Author: Noel Perez
 *
 * Created on March 23, 2024, 10:51 PM
 */

#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"

class Admin : public User{
private:
public:
    Admin();
    Admin(const string &userName, const string &password);
    Admin(const string &password, const string &userName, bool isAdmin, bool isLoggedIn );
    Admin(const string &password, const string &userName, bool isAdmin, bool isLoggedIn, int recNum );
    Admin(const Admin& orig);
    virtual ~Admin();


};

#endif /* ADMIN_H */

