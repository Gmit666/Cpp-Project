//
// Created by amitg on 21/02/2023.
//

#include "TestMode.h"

bool TestMode::TestAll() {
    int score = 0;
    if(TestGame())
    {
        cout<<"Game class passed.."<<endl;
        score++;
    }
    if(TestLeaderboard())
    {
        cout<<"Leaderboard class passed.."<<endl;
        score++;
    }
    if(TestSymbol())
    {
        cout<<"Symbol class passed.."<<endl;
        score++;
    }
    if(TestUsers())
    {
        cout<<"Users class passed.."<<endl;
        score++;
    }
    if(TestLeague())
    {
        cout<<"League class passed.."<<endl;
        score++;
    }
    if(score == 5)
        return true;
    return false;
}

bool TestMode::TestGame() {
    Game G;
    int score = 0,gamerun = 0;
    int size = 6;

    gamerun = G.GameRun("T1","T2",size,1);

    if (gamerun == 2||gamerun == 1 ||gamerun == 0)
        score++;

    gamerun = G.GameRunCPU("T1",size,1);

    if (gamerun == 2||gamerun == 1 ||gamerun == 0)
        score++;
    if(score == 2)
    {
        return true;
    }
    return false;
}

bool TestMode::TestLeaderboard() {
    Leaderboard L;
    int score = 0,num = 5,Num[4] = {1,2,3,4};
     if (L.ThereisALeaderboard())
         score++;
     if(L.TheisALeaderboardUpdate())
         score++;
     if(L.TheisSort())
         score++;
     if(L.chartoint("5") == num)
         score++;
     if(L.GetMax(Num,4) == 4)
         score++;
     if(L.GetStats(0,"qwe") == L.GetStats(0,"ewq"))
         score++;
     if(L.GetStats(1,"qwe") == L.GetStats(1,"ewq"))
         score++;
     if(score == 7)
     {
         return true;
     }
     return false;
}

bool TestMode::TestLeague() {
    League L;
    int score = 0;
    if(L.ThereisaLeague() || !L.ThereisaLeague())
        score++;
    if(score == 1)
    {
        return true;
    }
    return false;
}

bool TestMode::TestUsers() {
Users U;
int score = 0;
if(U.ThereisUsers())
    score++;
if(U.GetCred(0,"qwe") == NULL)
    score++;
if(U.GetCred(1,"qwe") == NULL)
    score++;
if(score == 3)
{
    return true;
}
return false;
}

bool TestMode::TestSymbol() {
    int size = 8,i,score = 0;
    Symbol *S[size];
    char *Names[size];
    for(i=0;i<size;i++)
    {
        Names[i] = NULL;
        S[i] = NULL;
    }
    for(i=0;i<size;i++)
    {
        Names[i] = new char[2];
        Names[i][0] = 'A'+i;
        Names[i][1] = '\0';
    }
    S[0] = new Cat(Names[0]);
    S[1] = new Dog(Names[1]);
    S[2] = new Dolphin(Names[2]);
    S[3] = new Ant(Names[3]);
    S[4] = new Grasshopper(Names[4]);
    S[5] = new Wasp(Names[5]);
    S[6] = new Shark(Names[6]);
    S[7] = new Barracuda(Names[7]);
    for(i=0;i<size;i++)
    {
        if(S[i] != NULL)
        {
            score++;
        }
    }
    for(i=0;i<size;i++)
    {
        delete S[i];
    }
    if(score == 8)
    {
        return true;
    }
    return false;
}



