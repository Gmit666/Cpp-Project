//
// Created by amitg on 05/02/2023.
//

#include "Leaderboard.h"

Leaderboard::Leaderboard() {
    fstream Leaderboard;
    fstream Update;
    fstream Sort;
    if(!ThereisALeaderboard())
    {
        Leaderboard.open("Leaderboard.txt", ios::out);
        if(Leaderboard.is_open())
        {
            Leaderboard.close();
        }
    }
    if(!TheisALeaderboardUpdate())
    {
        Update.open("LeaderboardUpdate.txt",ios::out);
        if(Update.is_open())
        {
            Update.close();
        }

    }
    if(!TheisSort())
    {
        Sort.open("LeaderboardUpdate.txt",ios::out);
        if(Sort.is_open())
        {
            Sort.close();
        }

    }
}

void Leaderboard::todayDate() {
    fstream History;
    time_t now = time(0);
    char *dt =::ctime(&now);
    History.open("Leaderboard.txt",ios::app);
    if(History.is_open())
    {
        History << dt<<endl;
    }
    History.close();
}

void Leaderboard::LeaderboardUpdate(char *user, int score,int win) {
    fstream Lead,Update;
    int i,count,NotFound = 0;
    char c = 'c';
    string Line;
    Lead.open("Leaderboard.txt",ios::in);
    if(Lead.is_open())
    {
        while(getline(Lead,Line))//find username and stats
        {
            i=0;
            c = Line[i];
            string s1,s2,s3;
            count = 0;
            while(c!='\0')
            {
                c=Line[i];
                if(c == ' ')
                {
                    count++;
                    i++;
                    continue;
                }
                if(count == 0)
                {
                    s1.push_back(c);
                    i++;
                    continue;
                }
                if(count == 1)
                {
                    s2.push_back(c);
                    i++;
                    continue;
                }
                if(count == 2)
                {
                    if (c == '\0') {
                        continue;
                    }
                    s3.push_back(c);
                    i++;
                    continue;
                }
            }
            if(s1 == user)//if username is found
            {
                NotFound = 1;
                int num1,num2;
                char St1[20],St2[20];
                s2.copy(St1,s2.length());
                St1[s2.length()] = '\0';
                s3.copy(St2,s3.length());
                St2[s3.length()] = '\0';
                num1 = chartoint(St1);
                num2 = chartoint(St2);
                num1+=win;
                num2+=score;
                Lead.close();
                Lead.open("Leaderboard.txt",ios::in);
                Update.open("LeaderboardUpdate.txt",ios::out);
                if(Lead.is_open() && Update.is_open())//copy to update without him
                {
                    while(getline(Lead,Line)) {
                        i = 0;
                        c = Line[i];
                        string l1, s2, s3;
                        count = 0;
                        while (c != '\0') {
                            c = Line[i];
                            if (c == ' ') {
                                count++;
                                i++;
                                continue;
                            }
                            if (count == 0) {
                                l1.push_back(c);
                                i++;
                                continue;
                            }
                            if (count == 1) {
                                s2.push_back(c);
                                i++;
                                continue;
                            }
                            if (count == 2) {
                                if (c == '\0') {
                                    continue;
                                }
                                s3.push_back(c);
                                i++;
                                continue;
                            }
                        }
                        if(l1 == user)
                        {
                            continue;
                        }
                        else
                        {
                            Update<<Line<<endl;
                        }

                    }
                    Lead.close();
                    Update.close();
                    Update.open("LeaderboardUpdate.txt",ios::app);
                    if(Update.is_open())//insert his updated stats into update
                    {
                        Update<<s1<<" "<<num1<<" "<<num2<<endl;
                    }
                    Update.close();
                    Update.open("LeaderboardUpdate.txt",ios::in);
                    Lead.open("Leaderboard.txt",ios::out);
                    if(Lead.is_open() && Update.is_open())//copy stats to leaderboard.txt
                    {
                        while(getline(Update,Line))
                        {
                            Lead << Line <<endl;
                        }
                    }
                    Update.close();
                    Lead.close();
                }

            }
        }
        if(Lead.is_open())
        {
            Lead.close();
        }
        if(NotFound == 0)//if username is new to the leaderboard
        {
            Lead.open("Leaderboard.txt",ios::app);
            if(Lead.is_open())
            {
                Lead<<user<<" "<<win<<" "<<score<<endl;
            }
            Lead.close();
        }
    }
LeaderboardSort();
}

int Leaderboard::chartoint(char *str) {
    int i=0,num=0,power = 0,j = 0;
    char c;
    while(str[i] != '\0')
    {
        if(i == 0)
        {
            power = 1;
            i++;
            continue;
        }
        power*=10;
        i++;
    }
    i=0;
    while(str[i] != '\0')
    {
        c = str[i];
        for(j=0;j<=9;j++)
        {
            if(c == '0' + j)
            {
                break;
            }
        }
        j*=power;
        power /=10;
        num+= j;
        i++;

    }

    return num;
}

char *Leaderboard::inttochar(int num) {
    int i,j,size = 0,num2 = num,power = 1,num3;
    char *Num = NULL,c;
    while(num2 != 0)
    {
        size++;
        num2 /= 10;
    }
    Num = new char[size+1];
    for(i=0;i<size-1;i++)
    {
        power*=10;
    }
    for(i=0;i<size;i++)
    {
        num3 = num/power;
        if(num3 > 9 )
        {
            num3%= 10;
        }
        power/=10;
        c = '0' +num3;
        Num[i] = c;
    }
    Num[size] = '\0';
    return Num;
}

void Leaderboard::LeaderboardSort()
{
    fstream Sort,Lead;
    string Line;
    int i,count,j = 0,Sorted = 0,*Num,size = 0,max;
    char c;
    Lead.open("Leaderboard.txt",ios::in);
    if(Lead.is_open())
    {
        while(getline(Lead,Line))//get size
        {
            size++;
        }
    }
    Lead.close();
    Num = new int[size];
    char NumHolder[3];//Holds up to 999 wins
    Lead.open("Leaderboard.txt",ios::in);
    while(getline(Lead,Line))//get all the Win numbers
    {
        i = 0;
        c = Line[i];
        string s1, s2, s3;
        count = 0;
        while (c != '\0') {
            c = Line[i];
            if (c == ' ') {
                count++;
                i++;
                continue;
            }
            if (count == 0) {
                s1.push_back(c);
                i++;
                continue;
            }
            if (count == 1) {
                s2.push_back(c);
                i++;
                continue;
            }
            if (count == 2) {
                if (c == '\0') {
                    continue;
                }
                s3.push_back(c);
                i++;
                continue;
            }
        }
        s2.copy(NumHolder,s2.size(),0);
        NumHolder[s2.size()] = '\0';
        Num[j] = chartoint(NumHolder);
        j++;
        NumHolder[0] = '\0';
    }
    Lead.close();
    Lead.open("Leaderboard.txt",ios::in);
    Sort.open("Sort.txt",ios::out);
    max = GetMax(Num,size);

    while(getline(Lead,Line))//Find max and print to new file
    {
        i = 0;
        c = Line[i];
        string s1, s2, s3;
        count = 0;
        while (c != '\0') {
            c = Line[i];
            if (c == ' ') {
                count++;
                i++;
                continue;
            }
            if (count == 0) {
                s1.push_back(c);
                i++;
                continue;
            }
            if (count == 1) {
                s2.push_back(c);
                i++;
                continue;
            }
            if (count == 2) {
                if (c == '\0') {
                    continue;
                }
                s3.push_back(c);
                i++;
                continue;
            }
        }
        s2.copy(NumHolder,s2.length(),0);
        NumHolder[s2.size()] = '\0';
        if(chartoint(NumHolder) == max)
        {
            Sort << Line <<endl;
            for(j=0;j<size;j++)
            {
                if (Num[j] == max)
                {
                    Num[j] = -1;
                }
            }
            break;
        }
    }
    Lead.close();
    Sort.close();
    int k = 0;
    Sort.open("Sort.txt",ios::app);
    for(j=0;j<size-1;j++)
    {
        Lead.open("Leaderboard.txt",ios::in);
        max = GetMax(Num,size);
        for(k=0;k<size;k++)
        {
            if(Num[k] == max)
            {
                Num[k] = -1;
            }
        }
        if(Lead.is_open())
        {
            while(getline(Lead,Line))
            {
                i = 0;
                c = Line[i];
                string s1, s2, s3;
                count = 0;
                while (c != '\0')
                {
                    c = Line[i];
                    if (c == ' ') {
                        count++;
                        i++;
                        continue;
                    }
                    if (count == 0) {
                        s1.push_back(c);
                        i++;
                        continue;
                    }
                    if (count == 1) {
                        s2.push_back(c);
                        i++;
                        continue;
                    }
                    if (count == 2) {
                        if (c == '\0') {
                            continue;
                        }
                        s3.push_back(c);
                        i++;
                        continue;
                    }
                }
                s2.copy(NumHolder,s2.length(),0);
                NumHolder[s2.size()] = '\0';
                if(chartoint(NumHolder) == max)
                {
                    Sort << Line << endl;
                }
            }
        }
        Lead.close();
    }
    Sort.close();
    Lead.open("Leaderboard.txt",ios::out);
    Sort.open("Sort.txt",ios::in);
    if(Sort.is_open()&&Lead.is_open())
    {
        while(getline(Sort,Line))
        {
            Lead << Line <<endl;
        }
    }
    Sort.close();
    Lead.close();
}

int Leaderboard::GetMax(int *arr,int size)
{
    int i,j,max;
    max = arr[0];
    for(i=0;i<size;i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

void Leaderboard::LeadPrint() {
fstream Lead;
Lead.open("Leaderboard.txt",ios::in);
string Line;
if(Lead.is_open())
{
    while(getline(Lead,Line))
    {
        cout << Line <<endl;
    }
}
Lead.close();
}

int Leaderboard::GetStats(int num, char *Username) {
    fstream Lead;
    Lead.open("Leaderboard.txt",ios::in);
    string Line;
    int count,i;
    char c;
    if(Lead.is_open())
    {
        while(getline(Lead,Line)) {
            i = 0;
            c = Line[i];
            string s1, s2, s3;
            count = 0;
            while (c != '\0') {
                c = Line[i];
                if (c == ' ') {
                    count++;
                    i++;
                    continue;
                }
                if (count == 0) {
                    s1.push_back(c);
                    i++;
                    continue;
                }
                if (count == 1) {
                    s2.push_back(c);
                    i++;
                    continue;
                }
                if (count == 2) {
                    if (c == '\0') {
                        continue;
                    }
                    s3.push_back(c);
                    i++;
                    continue;
                }
            }
            if(s1 == Username)
            {
                char Holder[5];
                int final;
                if(num == 0)
                {
                    s2.copy(Holder,s2.length(),0);
                    Holder[s2.length()] = '\0';
                    final = chartoint(Holder);
                    Lead.close();
                    return final;
                }
                if (num == 1)
                {
                    s3.copy(Holder,s3.length(),0);
                    Holder[s3.length()] = '\0';
                    final = chartoint(Holder);
                    Lead.close();
                    return final;
                }

            }
        }
    }
    Lead.close();
    return 0;
}

bool Leaderboard::ThereisALeaderboard() {
    fstream Leaderboard;
    Leaderboard.open("Leaderboard.txt", ios::in);
    if(Leaderboard.is_open())
    {
        Leaderboard.close();
        return true;
    }
    return false;
}

bool Leaderboard::TheisALeaderboardUpdate() {
    fstream Leaderboard;
    Leaderboard.open("LeaderboardUpdate.txt", ios::in);
    if(Leaderboard.is_open())
    {
        Leaderboard.close();
        return true;
    }
    return false;
}

bool Leaderboard::TheisSort() {
    fstream Leaderboard;
    Leaderboard.open("Sort.txt", ios::in);
    if(Leaderboard.is_open())
    {
        Leaderboard.close();
        return true;
    }
    return false;
}
