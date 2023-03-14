//
// Created by amitg on 30/01/2023.
//

#ifndef MYPROJECT_GAME_H
#define MYPROJECT_GAME_H
#include "Symbol.h"
#include "Leaderboard.h"
#include <iostream>
using namespace std;

class Game {
public:
    int GameRun(char* p1,char* p2,int size = 0,int test = 0);//0 for p1 win 1 for p2 win 2 for draw
    int GameRunCPU(char *p1,int size = 0,int test = 0);
    int MinMax(char **Board,int lvl,char turn,int size,int*player,int*cpu);
    void Assign(int *from,int *to);
    int BoardEval(char **Board,char turn,int *move,int size);
    char ** Boardini(int size);
    void print(char **b,int size);
    void Update(char **Board,int Pos[],int size,char symbol);
    bool TestUpdate(char **Board,int Pos[],int size,char symbol);
    bool const CheckifValid(char **Board,int Pos[],int size,char symbol,int activate);//0 = not,1 = activate
    void Flip(char **Board,int Pos[],int size,char symbol);
    bool Horizontal(char **Board,int Pos[],int size,char symbol,int flip,int *ptr);//flip = 0 ->check
    bool Vertical(char **Board,int Pos[],int size,char symbol,int flip,int *ptr);//flip = 1 -> flip
    bool Diagonals(char **Board,int Pos[],int size,char symbol,int flip,int *ptr);
    bool GameOver(char **Board,int size,char symbol);
    bool Up(char **Board,int Pos[],int size,char symbol,int flip,int *ptr);
    bool Down(char **Board,int Pos[],int size,char symbol,int flip,int *ptr);
    bool Left(char **Board,int Pos[],int size,char symbol,int flip,int *ptr);
    bool Right(char **Board,int Pos[],int size,char symbol,int flip,int *ptr);
    bool UpRight(char **Board,int Pos[],int size,char symbol,int flip,int *ptr);
    bool UpLeft(char **Board,int Pos[],int size,char symbol,int flip,int *ptr);
    bool DownRight(char **Board,int Pos[],int size,char symbol,int flip,int *ptr);
    bool DownLeft(char **Board,int Pos[],int size,char symbol,int flip,int *ptr);
private:

};


#endif //MYPROJECT_GAME_H
