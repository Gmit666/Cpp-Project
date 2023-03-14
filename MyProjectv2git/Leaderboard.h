//
// Created by amitg on 05/02/2023.
//

#ifndef MYPROJECT_LEADERBOARD_H
#define MYPROJECT_LEADERBOARD_H
#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>
using namespace std;

class Leaderboard {
public:
    Leaderboard();
    void todayDate();
    void LeaderboardUpdate(char *user1, int score1,int win);
    int chartoint(char *str);
    char *inttochar(int num);
    void LeaderboardSort();
    int GetMax(int *arr,int size);
    int GetStats(int num,char *Username);//0 for wins, 1 for score
    bool ThereisALeaderboard();
    bool TheisALeaderboardUpdate();
    bool TheisSort();
    void LeadPrint();
};


#endif //MYPROJECT_LEADERBOARD_H
