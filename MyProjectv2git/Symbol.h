//
// Created by amitg on 29/01/2023.
//

#ifndef MYPROJECT_SYMBOL_H
#define MYPROJECT_SYMBOL_H
#include <iostream>
#include <fstream>
#include <string>
#include "Users.h"
#include <cstring>
#include "Leaderboard.h"
#define Size 20
using namespace std;


class Symbol {
public:
    Symbol(char *name);
    virtual void whatami() = 0;
    char *GetUser();
    char *GetPass();
    int GetTot();
    int GetCurr();
    void UpdateCurr();
    ~Symbol();

private:
   char *username,*password;
   int totalwins;
   int currentwins;
};

class Mammal :public Symbol{
public:
    void whatami(){cout<<"Im a Mammal."<<endl;};
    Mammal(char *name): Symbol(name){};
};

class Fish:public Symbol{
public:
    void whatami(){cout<<"Im a Fish."<<endl;};
    Fish(char *name): Symbol(name){};
};
class Insect:public Symbol{
public:
    void whatami(){cout<<"Im a Insect."<<endl;};
    Insect(char *name): Symbol(name){};
};

class Cat:public Mammal{
public:
    void whatami(){cout<<"Im a Cat."<<endl;};
    Cat(char *name): Mammal(name){};
    ~Cat(){cout<<"U rang?"<<endl,delete this;};//FIX ME
};
class Dog:public Mammal{
public:
    void whatami(){cout<<"Im a Dog."<<endl;};
    Dog(char *name): Mammal(name){};
};

class Dolphin:public Mammal{
public:
    void whatami(){cout<<"Im a Dolphin."<<endl;};
    Dolphin(char *name): Mammal(name){};
};

class Shark:public Fish{
public:
    void whatami(){cout<<"Im a Shark."<<endl;};
    Shark(char *name): Fish(name){};
};

class Barracuda:public Fish{
public:
    void whatami(){cout<<"Im a Barracuda."<<endl;};
    Barracuda(char *name): Fish(name){};
};

class Ant:public Insect{
public:
    void whatami(){cout<<"Im a Ant."<<endl;};
    Ant(char *name): Insect(name){};
};

class Grasshopper:public Insect{
public:
    void whatami(){cout<<"Im a Grasshopper."<<endl;};
    Grasshopper(char *name): Insect(name){};
};

class Wasp:public Insect{
public:
    void whatami(){cout<<"Im a Wasp."<<endl;};
    Wasp(char *name): Insect(name){};
};

#endif //MYPROJECT_SYMBOL_H
