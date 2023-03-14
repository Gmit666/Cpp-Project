//
// Created by amitg on 29/01/2023.
//

#include "Symbol.h"

Symbol::Symbol(char *name) {
    Users s;
    Leaderboard t;
    username = name;
    password = s.GetCred(0,name);
    totalwins = t.GetStats(0,name);
    currentwins = 0;
}

char *Symbol::GetUser() {
    return this->username;
}

char *Symbol::GetPass() {
    return this->password;
}

int Symbol::GetTot() {
    return this->totalwins;
}

int Symbol::GetCurr() {
    return this->currentwins;
}

Symbol::~Symbol() {

    if(username!= NULL)
    {
        delete this->username;
    }
    if(password!= NULL)
    {
     delete this->password;
    }

}

void Symbol::UpdateCurr() {
this->currentwins+=1;
}






