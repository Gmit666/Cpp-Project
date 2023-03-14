//
// Created by amitg on 29/01/2023.
//

#ifndef MYPROJECT_USERS_H
#define MYPROJECT_USERS_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "Symbol.h"
using namespace std;
#define Size 20

class Users{
public:
    Users();
    bool ThereisUsers();
    int chooseTeam();
    char* Sign_up(int type);//First signup function.
    bool Login(char *Name);//Login - check credentials of user.
    int TypeOfUser(char *Name);
    char* GetCred(int num,char*Username);//To get credentials based on existing user.
    bool Check(char*username);//Function that checks if Username exists
private:

};



#endif //MYPROJECT_USERS_H
