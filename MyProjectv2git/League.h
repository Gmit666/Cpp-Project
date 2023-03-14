//
// Created by amitg on 19/02/2023.
//

#ifndef MYPROJECT_LEAGUE_H
#define MYPROJECT_LEAGUE_H
#include "Game.h"
#include "Symbol.h"
#include "Leaderboard.h"
#include <fstream>
#include <string>
#include <string.h>

class League {
public:
    League();
    bool ThereisaLeague();
    void Stats(int Playernum,Symbol *p1 = NULL,Symbol *p2 = NULL,Symbol *p3 = NULL,Symbol *p4 = NULL);
    void Winner(Symbol *winner);
    char **Read(int *gamenum,int *playernum,int *Curr,int *Boardsize);
    void End(Symbol *winner);
    void Boardsizeprint(int size);
    void Gamenum(int Gamenum);
    void Reset();
    void LeagueChoose(Symbol** Players,int NumberofPlayers,int BoardSize = 0,int gamenum = 0,int mode = 0);
    void NextBattle();
    Symbol * Winner(Symbol* P1,Symbol *P2,int BoardSize);
};


#endif //MYPROJECT_LEAGUE_H
