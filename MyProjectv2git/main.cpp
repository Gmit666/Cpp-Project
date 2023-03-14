#include <iostream>
#include "Users.h"
#include "Symbol.h"
#include "Game.h"
#include "Leaderboard.h"
#include "League.h"
#include "TestMode.h"
using namespace std;
#define Size 10
#define General_Size 10
#define Name_Size 20
#include <string.h>


void Home();
Symbol *Whatami(int type,char *Names);
int NameExists(Symbol **General,char **Names,int size);
void FreeAll(Symbol **General,char **Names);

int main() {
    Symbol *General[General_Size];
    Users U;
    League L;
    Game G;
    Leaderboard Lead;
    TestMode T;
    int choice = 0,type,k = 0, i,j,PNum = 0,Lchoose = 0;
    int gamenum = 0,playernum = 0,*gamenumptr = &gamenum,*playernumptr = &playernum;
    int gate1 = 0,Currentwins[4],*Currwin = &Currentwins[0],ResumeBoardSize = 0,*Resumeptr = & ResumeBoardSize;
    char *name,username[Name_Size],*Names[General_Size],**Names2;
    for(i=0;i<4;i++)
    {
        Currentwins[i] = -1;
    }
    for(i=0;i<General_Size;i++)
    {
        General[i] = NULL;
        Names[i] = NULL;
    }
    i=0;

    while(choice != 6)
    {
        Home();
        cin>>choice;
        switch(choice)
        {
            case 1://New User
            {
                type = U.chooseTeam();
                name = U.Sign_up(type);
                Names[i] = name;
                General[k] = Whatami(type,Names[i]);
                i++;
                k++;
                FreeAll(General,Names);
                PNum = 0;
                break;
            }

            case 2://Play vs cpu
            {
                cout<<"Username:";
                cin>>username;
                i=0;
                while(Names[i] != NULL)
                {
                    i++;
                }
                if(Names[i] == NULL)
                {
                    Names[i] = new char[strlen(username) + 1];
                    strcpy(Names[i],username);
                }
                if(U.Login(Names[i])) {
                    type = U.TypeOfUser(Names[i]);
                    for(k=0;k<Size;k++)
                    {
                        if(General[k] == NULL)
                        {
                            General[k] = Whatami(type,Names[i]);
                            break;
                        }
                    }
                }
                G.GameRunCPU(Names[i]);
                FreeAll(General,Names);
                PNum = 0;
                break;
            }
            case 3://League
            {
                if(L.ThereisaLeague())
                {
                    cout<<"There is an active league, what would you like to do:"<<endl;
                    while(Lchoose < 1 || Lchoose > 2)
                    {
                        cout<<"1.Resume active league"<<endl;
                        cout<<"2.Create new league"<<endl;
                        cin>>Lchoose;
                    }
                }
                else
                {
                    Lchoose = 2;
                }
                if(Lchoose == 1)
                {
                    Names2 = L.Read(gamenumptr,playernumptr,Currwin,Resumeptr);
                    for(i=0;i<General_Size;i++)
                    {
                        if(General[i] == NULL)
                        {
                            for(j=0;j<playernum;j++)
                            {
                                type = U.TypeOfUser(Names2[j]);
                                General[i + j] = Whatami(type,Names2[j]);
                                PNum++;
                            }
                            break;
                        }
                    }
                    for(j=0;j<playernum;j++)
                    {
                        while(General[i]->GetCurr() != Currentwins[j])
                        {
                            General[i]->UpdateCurr();
                        }
                        i++;
                    }
                    L.LeagueChoose(General,playernum,ResumeBoardSize,gamenum,1);
                    FreeAll(General,Names);
                    Names2 = NULL;
                    break;
                }
                if(Lchoose == 2)
                {
                    FreeAll(General,Names);
                    gate1 = 0;
                    while(gate1 != 2)
                    {
                        cout<<"1.Add player to league"<<endl;
                        cout<<"2.Start league"<<endl;
                        cout<<"3.Return to menu"<<endl;
                        cin>>gate1;
                        if(gate1 == 1)
                        {
                            cout<<"Username:";
                            cin>>username;
                            i=0;
                            while(Names[i] != NULL)
                            {
                                i++;
                            }
                            if(Names[i] == NULL)
                            {
                                Names[i] = new char[strlen(username) + 1];
                                strcpy(Names[i],username);
                            }
                            if(U.Login(Names[i])) {
                                type = U.TypeOfUser(Names[i]);
                                for(k=0;k<Size;k++)
                                {
                                    if(General[k] == NULL)
                                    {
                                        General[k] = Whatami(type,Names[i]);
                                        break;
                                    }
                                }
                                PNum++;
                                if(PNum == 4)
                                {
                                    break;
                                }
                            }
                            else
                            {
                                delete Names[i];
                                Names[i] = NULL;
                            }
                        }
                        if(gate1 == 2)
                        {
                            break;
                        }
                        if(gate1 == 3)
                        {
                            break;
                        }
                    }
                    if(gate1 == 3)
                    {
                        break;
                    }
                    if(PNum < 2)
                    {
                        cout<<"Not enough players to start a league."<<endl;
                        break;
                    }
                    cout<<"New League has begun!"<<endl;
                    L.Reset();
                    L.LeagueChoose(General,PNum,0);
                }
                FreeAll(General,Names);
                PNum = 0;
                break;
            }
            case 4://Leaderboard print
            {
                cout<<"Name - Wins - Score"<<endl;
                Lead.LeadPrint();
                cout<<endl;
                break;
            }
            case 5:
            {
                if(T.TestAll())
                {
                    cout<<"All is working as intended!"<<endl;
                    cout<<endl;
                }
                else
                {
                    cout<<"Test Failed!"<<endl;
                }

                break;
            }
            case 6:
            {
                cout<<"Program has ended."<<endl;
                break;
            }
        }
    }
    FreeAll(General,Names);
    return 0;
}

void Home()
{
    cout<<"1.Sign-up"<<endl;
    cout<<"2.Play vs Cpu"<<endl;//login needed
    cout<<"3.League"<<endl;
    cout<<"4.Leaderboard"<<endl;
    cout<<"5.Test Mode"<<endl;
    cout<<"6.Quit"<<endl;
}

Symbol *Whatami(int type,char *Names)
{
    int i =0;
    Symbol *Ptr = NULL;

    switch(type)
    {
        case 1:
        {
            Ptr = new Cat(Names);
            return Ptr;
        }
        case 2:
        {
            Ptr = new Dog(Names);
            return Ptr;
        }
        case 3:
        {
            Ptr = new Dolphin(Names);
            return Ptr;
        }
        case 4:
        {
            Ptr = new Shark(Names);
            return Ptr;
        }
        case 5:
        {
            Ptr = new Barracuda(Names);
            return Ptr;
        }
        case 6:
        {
            Ptr = new Ant(Names);
            return Ptr;
        }
        case 7:
        {
            Ptr = new Grasshopper(Names);
            return Ptr;
        }
        case 8:
        {
            Ptr = new Wasp(Names);
            return Ptr;
        }
    }
    return NULL;
}

int NameExists(Symbol **General,char **Names,int size)
{
    int i,j;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            if(Names[j] != NULL && General[i] != NULL)
            {
                if(strcmp(Names[j],General[i]->GetUser()) == 0)
                {
                    return j;
                }
            }
        }
    }

    return -1;
}

void FreeAll(Symbol **General,char **Names)
{
    int i;
    for(i=0;i<General_Size;i++)
    {
        if(General[i] != NULL)
        {
            delete General[i];
            General[i] = NULL;
        }
        if(Names[i] != NULL)
        {
            Names[i] = NULL;
        }
    }
}