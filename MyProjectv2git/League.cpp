//
// Created by amitg on 19/02/2023.
//

#include "League.h"

void League::LeagueChoose(Symbol **Players, int NumberofPlayers,int BoardSize,int gamenum,int mode)
{
    //0 for p1 win 1 for p2 win 2 for tie -1 for not played
    //mode 0 = from start,1 after first print,2 after
    Symbol *Winner1 = NULL, *Winner2 = NULL, *Winner3 = NULL, *Winner4 = NULL, *Loser1 = NULL, *Loser2 = NULL;
    int gate = 0, i = 0,games = 1,sumwins = 0,gate1 = 0;
    while(BoardSize == 0)
    {
        cout<<"Enter board size for league:";
        cin>>BoardSize;
    }
    switch (NumberofPlayers) {
        case 2://2 players
        {
            if(mode == 0)
            {
                //Base func
                Boardsizeprint(BoardSize);
                Stats(2,Players[0],Players[1]);
                Gamenum(games);
                Winner1 = Winner(Players[0], Players[1],BoardSize);
                Winner1->UpdateCurr();
                Winner(Winner1);
                Stats(2,Players[0],Players[1]);
                cout << Winner1->GetUser() << " is the League champion!" << endl;
                End(Winner1);
            }
            if(mode == 1)//Resume
            {
                if(gamenum == 0)
                {
                    Reset();
                    Boardsizeprint(BoardSize);
                    Stats(2,Players[0],Players[1]);
                    Gamenum(games);
                    Winner1 = Winner(Players[0], Players[1],BoardSize);
                    Winner1->UpdateCurr();
                    Winner(Winner1);
                    Stats(2,Players[0],Players[1]);
                    cout << Winner1->GetUser() << " is the League champion!" << endl;
                    End(Winner1);
                }
                if(gamenum == 1 && Players[0]->GetCurr() == 0 & Players[1]->GetCurr() == 0)
                {
                    Winner1 = Winner(Players[0], Players[1],BoardSize);
                    Winner1->UpdateCurr();
                    Winner(Winner1);
                    Stats(2,Players[0],Players[1]);
                    cout << Winner1->GetUser() << " is the League champion!" << endl;
                    End(Winner1);
                    gate1 = 1;
                }
                if (gate1!= 1)
                {
                    if(Players[0]->GetCurr() == 1 || Players[1]->GetCurr() == 1)
                    {
                        for(i=0;i<2;i++)
                        {
                            if(Players[i]->GetCurr() == 1)
                            {
                                Winner1 = Players[i];
                            }
                        }
                        Winner(Winner1);
                        Stats(2,Players[0],Players[1]);
                        cout << Winner1->GetUser() << " is the League champion!" << endl;
                        End(Winner1);
                    }
                }

            }

            break;
        }
        case 3://3 players
        {
            if(mode == 0)
            {
                //Base func
                Boardsizeprint(BoardSize);//write size to file
                Stats(3,Players[0],Players[1],Players[2]);//write stats
                Gamenum(games);//write game number
                Winner1 = Winner(Players[0], Players[1],BoardSize);//battle 1
                Winner1->UpdateCurr();//update stats
                for (i = 0; i < 2; i++) {//select loser
                    if (Players[i]->GetCurr() == 0) {
                        Loser1 = Players[i];
                    }
                }
                Winner(Winner1);//write winner to file
                games++;
                Stats(3,Players[0],Players[1],Players[2]);//write stats
                Gamenum(games);//write game number
                games++;
                NextBattle();
                Winner2 = Winner(Loser1, Players[2],BoardSize);//battle 2
                Winner2->UpdateCurr();//update stats
                Winner(Winner2);//write winner
                Stats(3,Players[0],Players[1],Players[2]);//write stats
                Gamenum(games);//write game number
                games++;
                NextBattle();
                Winner3 = Winner(Winner1,Winner2,BoardSize);//battle 3
                Winner3->UpdateCurr();//update stats
                Winner(Winner3);//write winner
                Stats(3,Players[0],Players[1],Players[2]);//write stats
                cout << Winner2->GetUser() << " is the League champion!" << endl;
                End(Winner2);//write end file
            }
            if(mode == 1)
            {
                if(gamenum == 0)
                {
                    Reset();
                    Boardsizeprint(BoardSize);//write size to file
                    Stats(3,Players[0],Players[1],Players[2]);//write stats
                    Gamenum(games);//write game number
                    Winner1 = Winner(Players[0], Players[1],BoardSize);//battle 1
                    Winner1->UpdateCurr();//update stats
                    for (i = 0; i < 2; i++) {//select loser
                        if (Players[i]->GetCurr() == 0) {
                            Loser1 = Players[i];
                        }
                    }
                    Winner(Winner1);//write winner to file
                    games++;
                    Stats(3,Players[0],Players[1],Players[2]);//write stats
                    Gamenum(games);//write game number
                    games++;
                    NextBattle();
                    Winner2 = Winner(Loser1, Players[2],BoardSize);//battle 2
                    Winner2->UpdateCurr();//update stats
                    Winner(Winner2);//write winner
                    Stats(3,Players[0],Players[1],Players[2]);//write stats
                    Gamenum(games);//write game number
                    games++;
                    NextBattle();
                    Winner3 = Winner(Winner1,Winner2,BoardSize);//battle 3
                    Winner3->UpdateCurr();//update stats
                    Winner(Winner3);//write winner
                    Stats(3,Players[0],Players[1],Players[2]);//write stats
                    cout << Winner2->GetUser() << " is the League champion!" << endl;
                    End(Winner2);//write end file
                }
                if(gamenum == 1 )
                {
                    for(i=0;i<3;i++)
                    {
                        sumwins +=Players[i]->GetCurr();
                    }
                    if(sumwins == 0)
                    {
                        Winner1 = Winner(Players[0], Players[1],BoardSize);//battle 1
                        Winner1->UpdateCurr();//update stats
                        for (i = 0; i < 2; i++) {//select loser
                            if (Players[i]->GetCurr() == 0) {
                                Loser1 = Players[i];
                            }
                        }
                        Winner(Winner1);//write winner to file
                        games++;
                        Stats(3,Players[0],Players[1],Players[2]);//write stats
                        Gamenum(games);//write game number
                        games++;
                        NextBattle();
                        Winner2 = Winner(Loser1, Players[2],BoardSize);//battle 2
                        Winner2->UpdateCurr();//update stats
                        Winner(Winner2);//write winner
                        Stats(3,Players[0],Players[1],Players[2]);//write stats
                        Gamenum(games);//write game number
                        games++;
                        NextBattle();
                        Winner3 = Winner(Winner1,Winner2,BoardSize);//battle 3
                        Winner3->UpdateCurr();//update stats
                        Winner(Winner3);//write winner
                        Stats(3,Players[0],Players[1],Players[2]);//write stats
                        cout << Winner2->GetUser() << " is the League champion!" << endl;
                        End(Winner2);//write end file
                        gate1 = 1;
                    }
                    if(sumwins == 1&&gate1 == 0)
                    {
                        for(i=0;i<3;i++)
                        {
                            if(Players[i]->GetCurr() == 1)
                            {
                                Winner1 = Players[i];
                                if(i == 0)
                                {
                                    Loser1 = Players[1];
                                }
                                if(i == 1)
                                {
                                    Loser1 = Players[0];
                                }
                            }

                        }
                        games = 2;
                        Gamenum(games);//write game number
                        games++;
                        NextBattle();
                        Winner2 = Winner(Loser1, Players[2],BoardSize);//battle 2
                        Winner2->UpdateCurr();//update stats
                        Winner(Winner2);//write winner
                        Stats(3,Players[0],Players[1],Players[2]);//write stats
                        Gamenum(games);//write game number
                        games++;
                        NextBattle();
                        Winner3 = Winner(Winner1,Winner2,BoardSize);//battle 3
                        Winner3->UpdateCurr();//update stats
                        Winner(Winner3);//write winner
                        Stats(3,Players[0],Players[1],Players[2]);//write stats
                        cout << Winner2->GetUser() << " is the League champion!" << endl;
                        End(Winner2);//write end file
                        gate1=1;
                    }

                }
                if(gamenum == 2&&gate1 == 0)
                {
                    if(sumwins == 1)
                    {
                        for(i=0;i<3;i++)
                        {
                            if(Players[i]->GetCurr() == 1)
                            {
                                Winner1 = Players[i];
                                if(i == 0)
                                {
                                    Loser1 = Players[1];
                                }
                                if(i == 1)
                                {
                                    Loser1 = Players[0];
                                }
                            }

                        }
                        NextBattle();
                        Winner2 = Winner(Loser1, Players[2],BoardSize);//battle 2
                        Winner2->UpdateCurr();//update stats
                        Winner(Winner2);//write winner
                        Stats(3,Players[0],Players[1],Players[2]);//write stats
                        Gamenum(games);//write game number
                        games++;
                        NextBattle();
                        Winner3 = Winner(Winner1,Winner2,BoardSize);//battle 3
                        Winner3->UpdateCurr();//update stats
                        Winner(Winner3);//write winner
                        Stats(3,Players[0],Players[1],Players[2]);//write stats
                        cout << Winner2->GetUser() << " is the League champion!" << endl;
                        End(Winner2);//write end file
                        gate1=1;
                    }
                    if(sumwins == 2&&gate1 == 0)
                    {
                        for(i=0;i<3;i++)
                        {
                            if(Players[i]->GetCurr() == 1)
                            {
                                Winner1 = Players[i];
                                break;
                            }
                        }
                        for(i=0;i<3;i++)
                        {
                            if(Players[i]->GetCurr() == 1&&strcmp(Players[i]->GetUser(),Winner1->GetUser()) != 0)
                            {
                                Winner2 = Players[i];
                                break;
                            }
                        }
                        for(i=0;i<3;i++)
                        {
                            if(Players[i]->GetCurr() == 0)
                            {
                                Loser1 = Players[i];
                                break;
                            }
                        }
                        NextBattle();
                        Winner3 = Winner(Winner1,Winner2,BoardSize);//battle 3
                        Winner3->UpdateCurr();//update stats
                        Winner(Winner3);//write winner
                        Stats(3,Players[0],Players[1],Players[2]);//write stats
                        cout << Winner2->GetUser() << " is the League champion!" << endl;
                        End(Winner2);//write end file
                    }
                }
            }
            break;
        }
        case 4: {
            if(mode == 0)
            {
                //Base
                Boardsizeprint(BoardSize);
                Stats(3,Players[0],Players[1],Players[2],Players[3]);
                Gamenum(games);
                games++;
                NextBattle();
                Winner1 = Winner(Players[0], Players[1],BoardSize);
                Winner1->UpdateCurr();
                Winner(Winner1);
                Stats(3,Players[0],Players[1],Players[2],Players[3]);
                for (i = 0; i < 2; i++) {
                    if (Players[i]->GetCurr() == 0) {
                        Loser1 = Players[i];
                    }
                }
                Gamenum(games);
                games++;
                NextBattle();
                Winner2 = Winner(Players[2], Players[3],BoardSize);
                Winner2->UpdateCurr();
                Winner(Winner2);
                Stats(3,Players[0],Players[1],Players[2],Players[3]);
                for (i = 2; i < 4; i++)
                {
                    if(Players[i]->GetCurr() == 0)
                    {
                        Loser2 = Players[i];
                    }
                }
                Gamenum(games);
                games++;
                NextBattle();
                Winner3 = Winner(Winner1,Winner2,BoardSize);
                Winner3->UpdateCurr();
                Winner(Winner3);
                Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                Gamenum(games);
                games++;
                NextBattle();
                Winner4 = Winner(Loser1,Loser2,BoardSize);
                Winner(Winner4);
                Winner4->UpdateCurr();
                Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                Gamenum(games);
                games++;
                NextBattle();
                Winner1 = Winner(Winner3,Winner4,BoardSize);
                Winner1->UpdateCurr();
                Winner(Winner1);
                Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                cout << Winner1->GetUser() << " is the League champion!" << endl;
                End(Winner1);
            }
            if(mode == 1)
            {
                for(i=0;i<4;i++)
                {
                    sumwins+=Players[i]->GetCurr();
                }
                if(sumwins == 0)
                {
                    Reset();
                    Boardsizeprint(BoardSize);
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);
                    Gamenum(games);
                    games++;
                    NextBattle();
                    Winner1 = Winner(Players[0], Players[1],BoardSize);
                    Winner1->UpdateCurr();
                    Winner(Winner1);
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);
                    for (i = 0; i < 2; i++) {
                        if (Players[i]->GetCurr() == 0) {
                            Loser1 = Players[i];
                        }
                    }
                    Gamenum(games);
                    games++;
                    NextBattle();
                    Winner2 = Winner(Players[2], Players[3],BoardSize);
                    Winner2->UpdateCurr();
                    Winner(Winner2);
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);
                    for (i = 2; i < 4; i++)
                    {
                        if(Players[i]->GetCurr() == 0)
                        {
                            Loser2 = Players[i];
                        }
                    }
                    Gamenum(games);
                    games++;
                    NextBattle();
                    Winner3 = Winner(Winner1,Winner2,BoardSize);
                    Winner3->UpdateCurr();
                    Winner(Winner3);
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                    Gamenum(games);
                    games++;
                    NextBattle();
                    Winner4 = Winner(Loser1,Loser2,BoardSize);
                    Winner(Winner4);
                    Winner4->UpdateCurr();
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                    Gamenum(games);
                    games++;
                    NextBattle();
                    Winner1 = Winner(Winner3,Winner4,BoardSize);
                    Winner1->UpdateCurr();
                    Winner(Winner1);
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                    cout << Winner1->GetUser() << " is the League champion!" << endl;
                    End(Winner1);
                    gate1=1;
                }
                if(sumwins == 1&&gate1==0)
                {
                    for(i=0;i<2;i++)
                    {
                        if(Players[i]->GetCurr() == 1)
                        {
                            Winner1 = Players[i];
                            break;
                        }
                        if(i == 0)
                        {
                            Loser1 = Players[1];
                        }
                        if(i == 1)
                        {
                            Loser1 = Players[0];
                        }
                    }
                    Gamenum(games);
                    games++;
                    NextBattle();
                    Winner2 = Winner(Players[2], Players[3],BoardSize);
                    Winner2->UpdateCurr();
                    Winner(Winner2);
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);
                    for (i = 2; i < 4; i++)
                    {
                        if(Players[i]->GetCurr() == 0)
                        {
                            Loser2 = Players[i];
                        }
                    }
                    Gamenum(games);
                    games++;
                    NextBattle();
                    Winner3 = Winner(Winner1,Winner2,BoardSize);
                    Winner3->UpdateCurr();
                    Winner(Winner3);
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                    Gamenum(games);
                    games++;
                    NextBattle();
                    Winner4 = Winner(Loser1,Loser2,BoardSize);
                    Winner(Winner4);
                    Winner4->UpdateCurr();
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                    Gamenum(games);
                    games++;
                    NextBattle();
                    Winner1 = Winner(Winner3,Winner4,BoardSize);
                    Winner1->UpdateCurr();
                    Winner(Winner1);
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                    cout << Winner1->GetUser() << " is the League champion!" << endl;
                    End(Winner1);
                    gate1=1;
                }
                if(sumwins == 2&&gate1==0)
                {
                    for(i=0;i<4;i++)
                    {
                        if(Players[i]->GetCurr() == 1)
                        {
                            Winner1 = Players[i];
                            break;
                        }
                    }
                    for(i=0;i<4;i++)
                    {
                        if(Players[i]->GetCurr() == 1&&strcmp(Players[i]->GetUser(),Winner1->GetUser()) != 0)
                        {
                            Winner2 = Players[i];
                            break;
                        }
                    }
                    for(i=0;i<4;i++)
                    {
                        if(Players[i]->GetCurr() == 0)
                        {
                            Loser1 = Players[i];
                            break;
                        }
                    }
                    for(i=0;i<4;i++)
                    {
                        if(Players[i]->GetCurr() == 0&&strcmp(Players[i]->GetUser(),Loser1->GetUser()) != 0)
                        {
                            Loser2 = Players[i];
                            break;
                        }
                    }
                    Gamenum(games);
                    games++;
                    NextBattle();
                    Winner3 = Winner(Winner1,Winner2,BoardSize);
                    Winner3->UpdateCurr();
                    Winner(Winner3);
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                    Gamenum(games);
                    games++;
                    NextBattle();
                    Winner4 = Winner(Loser1,Loser2,BoardSize);
                    Winner(Winner4);
                    Winner4->UpdateCurr();
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                    Gamenum(games);
                    games++;
                    NextBattle();
                    Winner1 = Winner(Winner3,Winner4,BoardSize);
                    Winner1->UpdateCurr();
                    Winner(Winner1);
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                    cout << Winner1->GetUser() << " is the League champion!" << endl;
                    End(Winner1);
                    gate1=1;
                }
                if(sumwins == 3&&gate1 == 0)
                {
                    for(i=0;i<4;i++)
                    {
                        if(Players[i]->GetCurr() == 2)
                        {
                            Winner3 = Players[i];
                            break;
                        }
                    }
                    for(i=0;i<4;i++)
                    {
                        if(Players[i]->GetCurr() == 0)
                        {
                            Loser1 = Players[i];
                            break;
                        }
                    }
                    for(i=0;i<4;i++)
                    {
                        if(Players[i]->GetCurr() == 0 && strcmp(Loser1->GetUser(),Players[i]->GetUser())!=0)
                        {
                            Loser2 = Players[i];
                            break;
                        }
                    }
                    NextBattle();
                    Winner4 = Winner(Loser1,Loser2,BoardSize);
                    Winner(Winner4);
                    Winner4->UpdateCurr();
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                    Gamenum(games);
                    games++;
                    NextBattle();
                    Winner1 = Winner(Winner3,Winner4,BoardSize);
                    Winner1->UpdateCurr();
                    Winner(Winner1);
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                    cout << Winner1->GetUser() << " is the League champion!" << endl;
                    End(Winner1);
                    gate1=1;
                }
                if(sumwins == 4&&gate1 ==0)
                {
                    for(i=0;i<4;i++)
                    {
                        if(Players[i]->GetCurr() == 2)
                        {
                            Winner3 = Players[i];
                            break;
                        }
                    }
                    for(i=0;i<4;i++)
                    {
                        if(Players[i]->GetCurr() == 1)
                        {
                            Winner4 = Players[i];
                            break;
                        }
                    }
                    NextBattle();
                    Winner1 = Winner(Winner3,Winner4,BoardSize);
                    Winner1->UpdateCurr();
                    Winner(Winner1);
                    Stats(3,Players[0],Players[1],Players[2],Players[3]);;
                    cout << Winner1->GetUser() << " is the League champion!" << endl;
                    End(Winner1);
                }
            }

            break;
        }
        default:
        {
            cout<<"Cannot return to this league."<<endl;
            break;
        }


    }
}

Symbol *League::Winner(Symbol *P1, Symbol *P2,int BoardSize) {
    Game G;
    int final = -1;
    cout<<P1->GetUser()<<" Vs "<<P2->GetUser()<<endl;
    final = G.GameRun(P1->GetUser(),P2->GetUser(),BoardSize);
    while(final == -1)
    {
        cout<<"Rematch!"<<endl;
        final = G.GameRun(P1->GetUser(),P2->GetUser(),BoardSize);
    }
    if(final == 0 )
    {
        return P1;
    }
    if(final == 1)
    {
        return P2;
    }
}

League::League() {
    fstream Le;
    Le.open("League.txt",ios::app);
    if(Le.is_open())
    {
        Le.close();
    }
}

bool League::ThereisaLeague() {
    fstream Le;
    Le.open("League.txt",ios::in);
    string Line;
    char end[4] = {"End"};
    int Linenum = 0;
    if(Le.is_open())
    {
        while(getline(Le,Line))
        {
            Linenum++;
        }
        Le.close();
    }
    if(Line == end)
    {
        Reset();
        return false;
    }
    if(Linenum == 0)
    {
        return false;
    }
    return true;
}

void League::Reset() {
    fstream Le;
    Le.open("League.txt",ios::out);
    if(Le.is_open())
    {
        Le.close();
    }

}

void League::Gamenum(int Gamenum) {
    fstream Le;
    Le.open("League.txt",ios::app);
    if(Le.is_open())
    {
        Le <<"Game "<<Gamenum<<endl;
        Le.close();
    }
}

void League::Stats(int Playernum, Symbol *p1, Symbol *p2, Symbol *p3, Symbol *p4) {
    fstream Le;
    Le.open("League.txt",ios::app);
    if(Le.is_open())
    {
        if( Playernum == 2)
        {
            Le<<p1->GetUser()<<" "<<p1->GetCurr()<<" "<<p2->GetUser()<<" "<<p2->GetCurr()<<endl;
        }
        if(Playernum == 3)
        {
            Le<<p1->GetUser()<<" "<<p1->GetCurr()<<" "<<p2->GetUser()<<" "<<p2->GetCurr()<<" ";
            Le<<p3->GetUser()<<" "<<p3->GetCurr()<<endl;
        }
        if(Playernum == 4)
        {
            Le<<p1->GetUser()<<" "<<p1->GetCurr()<<" "<<p2->GetUser()<<" "<<p2->GetCurr()<<" ";
            Le<<p3->GetUser()<<" "<<p3->GetCurr()<<" "<<p4->GetUser()<<" "<<p4->GetCurr()<<endl;
        }
        Le.close();
    }
}

void League::Winner(Symbol *winner) {
    fstream Le;
    Le.open("League.txt",ios::app);
    if(Le.is_open())
    {
        Le<<winner->GetUser()<<" win!"<<endl;
        Le.close();
    }
}

void League::End(Symbol *winner) {
    fstream Le;
    Le.open("League.txt",ios::app);
    if(Le.is_open())
    {
        Le<<winner->GetUser()<<" wins the tournament!"<<endl;
        Le<<"End";
        Le.close();
    }
}

char **League::Read(int *gamenum,int *playernum,int *Curr,int *Boardsize) {
int i,j,run = 0,Wins[4],k,r,e;
Leaderboard L;
string Line;
char c,Game[10],Stats[100],Win[50] ,**Names,Name[20],Winschar[4],BSize[3];
fstream Le;
for(i=0;i<4;i++)
{
    Wins[i] = -1;
}
Names = new char*[4];
Le.open("League.txt",ios::in);
run = -1;
if(Le.is_open())
{
    while(getline(Le,Line))
    {
        if(run == -1)
        {
            Line.copy(BSize,Line.length(),0);
            BSize[Line.length()] = '\0';
            run = 0;
            continue;
        }
        if(run == 0)
        {
            Line.copy(Stats,Line.length(),0);
            Stats[Line.length()] = '\0';
            run++;
            continue;
        }
        if(run == 1)
        {
            Line.copy(Game,Line.length(),0);
            Game[Line.length()] = '\0';
            run++;
            continue;
        }
        if(run == 2)
        {
            Line.copy(Win,Line.length(),0);
            Win[Line.length()] = '\0';
            run = 0;
            continue;
        }
    }
    Le.close();
    *Boardsize = L.chartoint(BSize);

   for(i=0;i<4;i++)
   {
       Names[i] = NULL;
   }
   c = Stats[0];
   i=0,run=0,j=0,k=0,r=0,e=0;
   while(c != '\0')
   {
       c = Stats[i];
       if(run == 0)
       {
           if(c == ' ')
           {
               run = 1;
               i++;
               Name[j] = '\0';
               j=0;
               Names[e] = new char[strlen(Name) + 1];
               strcpy(Names[e],Name);
               e++;
               Name[0] = '\0';
               continue;
           }
           Name[j] = c;
           j++;
           i++;
           continue;
       }
       if(run == 1)
       {
           if(c == ' ' || c == '\0')
           {
               run = 0;
               i++;
               Winschar[k] = '\0';
               Wins[r] = L.chartoint(Winschar);
               k=0,r++;
               Winschar[0] = '\0';
               continue;
           }
           Winschar[k] = c;
           k++;
           i++;
       }
   }
}
    c = Game[0];
    i=0,run=0,j=0,k=0,r=0,e=0;
    Name[0] = '\0';
    while(c != '\0')
    {
        c = Game[i];
        if(run == 0)
        {
            if(c == ' ')
            {
                i++;
                run = 1;
                continue;
            }
            Name[j] = c;
            j++;
            i++;
            continue;
        }
        if(run == 1)
        {
            Winschar[k] = c;
            k++;
            i++;
        }
    }
    *gamenum = L.chartoint(Winschar);
    for(i=0;i<4;i++)
    {
        if(Names[i] != NULL)
        {
            *playernum +=1;
        }
    }
    for(i=0;i<4;i++)
    {
        Curr[i] = Wins[i];
    }
    return Names;
}

void League::Boardsizeprint(int size) {
    fstream Le;
    Le.open("League.txt",ios::app);
    if(Le.is_open())
    {
        Le<<size<<endl;
        Le.close();
    }
}

void League::NextBattle() {
    cout<<"Get ready for the next battle!"<<endl;
}


