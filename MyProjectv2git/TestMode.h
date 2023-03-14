//
// Created by amitg on 21/02/2023.
//

#ifndef MYPROJECT_TESTMODE_H
#define MYPROJECT_TESTMODE_H
#include "Game.h"
#include "Leaderboard.h"
#include "League.h"
#include "Symbol.h"
#include "Users.h"

class TestMode {
public:
bool TestGame();
bool TestLeaderboard();
bool TestLeague();
bool TestUsers();
bool TestSymbol();
bool TestAll();

};


#endif //MYPROJECT_TESTMODE_H
