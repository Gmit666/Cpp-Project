//
// Created by amitg on 30/01/2023.
//

#include "Game.h"
#include <conio.h>

int Game::GameRun(char* p1,char* p2,int size,int test) {
int BoardSize = 0,Gate = 0,PosX[2],PosY[2],S1 = 0,S2 = 0,i,j;
char**Board = NULL,c;
Leaderboard Log;
while(size < 3)
{
    cout<<"Enter board size:";
    cin>>size;
}
BoardSize = size;
while(BoardSize < 3)
{
    cout<<"Enter board size:";
    cin>>BoardSize;
}
if(BoardSize % 2 != 0)
{
    BoardSize+=1;
}
Board = Boardini(BoardSize);

if(test == 0)
{
    while(Gate != BoardSize*BoardSize*2)
    {
        print(Board,BoardSize);
        if(Gate != 0)
        {
            if(GameOver(Board,BoardSize,'X'))
            {
                break;
            }
        }
        cout<<p1<<"'s turn:"<<endl;
        cin>>PosX[0]>>PosX[1];
        Update(Board,PosX,BoardSize,'X');
        Flip(Board,PosX,BoardSize,'X');
        print(Board,BoardSize);
        if(GameOver(Board,BoardSize,'O'))
        {
            break;
        }
        cout<<p2<<"'s turn:"<<endl;
        cin>>PosY[0]>>PosY[1];
        Update(Board,PosY,BoardSize,'O');
        Flip(Board,PosY,BoardSize,'O');
        Gate +=1;
    }
}
if(test == 1)
{
    int break1 = 0;
    while(Gate != BoardSize*BoardSize*2)
    {
        if(Gate != 0)
        {
            if(GameOver(Board,BoardSize,'X'))
            {
                break;
            }
        }
        for(i=0;i<BoardSize;i++)
        {
            for(j=0;j<BoardSize;j++)
            {
                PosX[0] = i;
                PosX[1] = j;
                if(CheckifValid(Board,PosX,BoardSize,'X',0))
                {
                    break1 = 1;
                    break;
                }
            }
            if(break1 == 1)
            {
                break1 = 0;
                break;
            }
        }
        TestUpdate(Board,PosX,BoardSize,'X');
        Flip(Board,PosX,BoardSize,'X');
        if(GameOver(Board,BoardSize,'O'))
        {
            break;
        }
        for(i=0;i<BoardSize;i++)
        {
            for(j=0;j<BoardSize;j++)
            {
                PosY[0] = i;
                PosY[1] = j;
                if(CheckifValid(Board,PosY,BoardSize,'O',0))
                {
                    break1 = 1;
                    break;
                }
            }
            if(break1 == 1)
            {
                break1 = 0;
                break;
            }
        }
        TestUpdate(Board,PosY,BoardSize,'O');
        Flip(Board,PosY,BoardSize,'O');
        Gate +=1;
    }

}

    for(i=0;i<BoardSize;i++)//Scoring
    {
        for(j=0;j<BoardSize;j++)
        {
            c = Board[i][j];
            if(c == 'X')
            {
                S1++;
            }
            if(c == 'O')
            {
                S2++;
            }
        }
    }

if(S1 > S2)
{
    if(test == 0)
    {
        cout<<p1<<" won! "<<p1<<": "<<S1<<" "<<p2<<": "<<S2<<endl;
        Log.LeaderboardUpdate(p1,S1,1);
        Log.LeaderboardUpdate(p2,S2,0);
    }

    return 0;
}
if(S1 < S2)
{
    if(test == 0)
    {
        cout<<p2<<" won! "<<p2<<": "<<S2<<" "<<p1<<": "<<S1<<endl;
        Log.LeaderboardUpdate(p1,S1,0);
        Log.LeaderboardUpdate(p2,S2,1);

    }
    return 1;
}
if(S1 == S2)
{
    if(test == 0)
    {
        cout<<"Draw "<<p1<<": "<<S1<<" "<<p2<<": "<<S2<<endl;
        Log.LeaderboardUpdate(p1,S1,0);
        Log.LeaderboardUpdate(p2,S2,0);

    }
    return 2;
}


}

char ** Game::Boardini(int size) {
    int i =0,j=0;
    char **Board;
    Board = new char*[size];
    for(i=0;i<size;i++)
    {
        Board[i] = new char[size];
    }
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            Board[i][j] = '-';
        }
    }
    Board[(size-1)/2][(size-1)/2] = 'X';
    Board[(size-1)/2][(size-1)/2 + 1] = 'O';
    Board[(size-1)/2 + 1][(size-1)/2 + 1] = 'X';
    Board[(size-1)/2 + 1][(size-1)/2] = 'O';
return Board;
}

void Game::print(char **b, int size) {
int i=0,j=0;
cout<<"  ";
for(i=0;i<size;i++)
{
    cout<<" "<<i<<" ";
}
cout<<endl;

for(i=0;i<size;i++)
{
    cout<<i<<"|";
    for(j=0;j<size;j++)
    {
        cout<<" "<<b[i][j]<<" ";
    }
    cout<<"|"<<endl;
}

}



void Game::Update(char **Board,int Pos[],int size,char symbol) {

while(!CheckifValid(Board,Pos,size,symbol,1)) {
    cout<<"Not valid move,re-enter:"<<endl;
    cin>>Pos[0]>>Pos[1];
}
Board[Pos[0]][Pos[1]] = symbol;
}

bool const Game::CheckifValid(char **Board, int *Pos, int size,char symbol,int activate) {
    int count = 0,score = 0,i,j;
    int *scoreptr = &score;
    if(Pos[0] > (size - 1)||Pos[0] < 0 || Pos[1] >(size - 1)|| Pos[1] < 0)
    {
        return false;
    }
    if (Board[Pos[0]][Pos[1]] != '-') {
        if(activate == 1)
        {
            cout << "Position is taken." << endl;
        }
        return false;
    }
    if(!Horizontal(Board,Pos,size,symbol,0,scoreptr) && !Vertical(Board,Pos,size,symbol,0,scoreptr)&& !Diagonals(Board,Pos,size,symbol,0,scoreptr))
    {
        return false;
    }
    if(Pos[0] == 0 && Pos[1] == 0)// top left
    {
        if(Board[0][1] == '-')
        {
            count++;
        }
        if(Board[1][1] == '-')
        {
            count++;
        }
        if(Board[1][0] == '-')
        {
            count++;
        }
        if(count == 3)
        {
            return false;
        }
        return true;
    }
    if(Pos[0] == 0 && Pos[1] == (size - 1))//top right
    {
        if(Board[0][size - 2] == '-')
        {
            count++;
        }
        if(Board[1][size - 2] == '-')
        {
            count++;
        }
        if(Board[1][size - 1] == '-')
        {
            count++;
        }
        if(count == 3)
        {
            return false;
        }
        return true;
    }
    if(Pos[0] == (size - 1) && Pos[1] == 0)//bottom left
    {
        if(Board[size - 2][0] == '-')
        {
            count++;
        }
        if(Board[size - 2][1] == '-')
        {
            count++;
        }
        if(Board[size - 1][1] == '-')
        {
            count++;
        }
        if(count == 3)
        {
            return false;
        }
        return true;
    }
    if(Pos[0] == (size - 1) && Pos[1] == (size - 1))//bottom right
    {
        if(Board[size -1][size - 2] == '-')
        {
            count++;
        }
        if(Board[size - 2][size - 2] == '-')
        {
            count++;
        }
        if(Board[size - 2][size - 1] == '-')
        {
            count++;
        }
        if(count == 3)
        {
            return false;
        }
        return true;
    }
    if(Pos[0] == (size - 1))//bottom free
    {
        if (Board[Pos[0]-1][Pos[1]-1] == '-') {
            count++;
        }
        if (Board[Pos[0]-1][Pos[1]] == '-') {
            count++;
        }
        if (Board[Pos[0]-1][Pos[1]+1] == '-') {
            count++;
        }
        if (Board[Pos[0]][Pos[1]-1] == '-') {
            count++;
        }
        if (Board[Pos[0]][Pos[1]+1] == '-') {
            count++;
        }
        if(count == 5)
        {
            return false;
        }
        return true;
    }
    if(Pos[0] == 0)//top free
    {
        if (Board[Pos[0]][Pos[1]-1] == '-') {
            count++;
        }
        if (Board[Pos[0]][Pos[1]+1] == '-') {
            count++;
        }
        if (Board[Pos[0]+1][Pos[1]-1] == '-') {
            count++;
        }
        if (Board[Pos[0]+1][Pos[1]] == '-') {
            count++;
        }
        if (Board[Pos[0]+1][Pos[1]+1] == '-') {
            count++;
        }
        if(count == 5)
        {
            return false;
        }
        return true;
    }
    if(Pos[1] == 0 && size > 4)//left free
    {
        if (Board[Pos[0]-1][Pos[1]] == '-') {
            count++;
        }
        if (Board[Pos[0]+1][Pos[1]] == '-') {
            count++;
        }
        if (Board[Pos[0]-1][Pos[1]+1] == '-') {
            count++;
        }
        if (Board[Pos[0]][Pos[1]+1] == '-') {
            count++;
        }
        if (Board[Pos[0]+1][Pos[1]+1] == '-') {
            count++;
        }
        if(count == 5)
        {
            return false;
        }
        return true;
    }
    if(Pos[1] == (size-1) &&size > 4)//right free
    {
        if (Board[Pos[0]-1][Pos[1]] == '-') {
            count++;
        }
        if (Board[Pos[0]+1][Pos[1]] == '-') {
            count++;
        }
        if (Board[Pos[0]+1][Pos[1]-1] == '-') {
            count++;
        }
        if (Board[Pos[0]][Pos[1]-1] == '-') {
            count++;
        }
        if (Board[Pos[0]-1][Pos[1]-1] == '-') {
            count++;
        }
        if(count == 5)
        {
            return false;
        }
        return true;
    }
    if (Board[Pos[0]-1][Pos[1]-1] == '-') {
        count++;
    }
    if (Board[Pos[0]-1][Pos[1]] == '-') {
        count++;
    }
    if (Board[Pos[0]-1][Pos[1]+1] == '-') {
        count++;
    }
    if (Board[Pos[0]][Pos[1]-1] == '-') {
        count++;
    }
    if (Board[Pos[0]][Pos[1]+1] == '-') {
        count++;
    }
    if (Board[Pos[0]+1][Pos[1]-1] == '-') {
        count++;
    }
    if (Board[Pos[0]+1][Pos[1]] == '-') {
        count++;
    }
    if (Board[Pos[0]+1][Pos[1]+1] == '-') {
        count++;
    }
    if(count == 8)
    {
        return false;
    }
    return true;
}

void Game::Flip(char **Board, int *Pos, int size,char symbol) {
    int score = 0,*ptr = &score;
    Horizontal(Board,Pos,size,symbol,1,ptr);
    Vertical(Board,Pos,size,symbol,1,ptr);
    Diagonals(Board,Pos,size,symbol,1,ptr);
}

bool Game::Horizontal(char **Board, int *Pos, int size, char symbol,int flip,int *ptr) {
    int c = 0;
    if(Left(Board,Pos,size,symbol,flip,ptr) )
    {
        c++;
    }
    if(Right(Board,Pos,size,symbol,flip,ptr))
    {
        c++;
    }
    if(c!= 0)
    {
        return true;
    }
    return false;
}

bool Game::Left(char **Board, int *Pos, int size, char symbol, int flip, int *ptr) {
    int i,j,m,count = 0,gate = 0;
    char c;
    m= Pos[1];
    j=1;
    if(symbol == 'X')
    {
        for(i=0;i<size;i++)//Left
        {
            m--;
            if(m == -1)
            {
                break;
            }
            c = Board[Pos[0]][Pos[1] - j];
            j++;
            if(c == '-')
            {
                gate = 0;
                count = 0;
                break;
            }
            if(c == 'O')
            {
                count++;
                continue;
            }
            if(c == 'X')
            {
                gate = 1;
                break;
            }
        }
        if(count > 0 && gate == 1)
        {
            if(flip == 1)
            {
                for(i=0;i<count + 1;i++)
                {
                    Board[Pos[0]][Pos[1] - i] = 'X';
                }
            }
            *ptr+=count;
            return true;
        }
    }
    if(symbol == 'O')
    {
        for(i=0;i<size;i++)//Left
        {
            m--;
            if(m == -1)
            {
                break;
            }
            c = Board[Pos[0]][Pos[1] - j];
            j++;
            if(c == '-')
            {
                gate = 0;
                count = 0;
                break;
            }
            if(c == 'X')
            {
                count++;
                continue;
            }
            if(c == 'O')
            {
                gate = 1;
                break;
            }
        }
        if(count > 0 && gate == 1)
        {
            if(flip == 1)
            {
                for(i=0;i<count + 1;i++)
                {
                    Board[Pos[0]][Pos[1] - i] = 'O';
                }
            }
            *ptr+=count;
            return true;
        }
    }
    return false;
}

bool Game::Right(char **Board, int *Pos, int size, char symbol, int flip, int *ptr) {
    int i,j = 1,m,count = 0,gate = 0;
    char c;
    if(symbol == 'X') {
        m = Pos[1];
        for (i = 0; i < size; i++)//Right
        {
            m++;
            if (m == size) {
                break;
            }
            c = Board[Pos[0]][Pos[1] + j];
            j++;
            if (c == '-') {
                gate = 0;
                count = 0;
                break;
            }
            if (c == 'O') {
                count++;
                continue;
            }
            if (c == 'X') {
                gate = 1;
                break;
            }
        }
        if (count > 0 && gate == 1) {
            if (flip == 1) {
                for (i = 0; i < count + 1; i++) {
                    Board[Pos[0]][Pos[1] + i] = 'X';
                }
            }
            *ptr += count;
            return true;
        }
    }
    if(symbol == 'O') {
        m = Pos[1];
        for (i = 0; i < size; i++)//Right
        {
            m++;
            if (m == size) {
                break;
            }
            c = Board[Pos[0]][Pos[1] + j];
            j++;
            if (c == '-') {
                gate = 0;
                count = 0;
                break;
            }
            if (c == 'X') {
                count++;
                continue;
            }
            if (c == 'O') {
                gate = 1;
                break;
            }
        }
        if (count > 0 && gate == 1) {
            if (flip == 1) {
                for (i = 0; i < count + 1; i++) {
                    Board[Pos[0]][Pos[1] + i] = 'O';
                }
            }
            *ptr += count;
            return true;
        }
    }
    return false;
}

bool Game::Vertical(char **Board, int *Pos, int size, char symbol,int flip,int *ptr) {
    int c = 0;
    if(Down(Board,Pos,size,symbol,flip,ptr))
    {
        c++;
    }
    if(Up(Board,Pos,size,symbol,flip,ptr))
    {
        c++;
    }
    if(c!= 0)
    {
        return true;
    }
    return false;
}

bool Game::Up(char **Board, int *Pos, int size, char symbol, int flip, int *ptr) {
    int i=0,j=1,count = 0,gate = 0,m;
    char c;
    m=Pos[0];
    if(symbol == 'X')
    {
        for(i=0;i<size;i++) // up
        {
            m--;
            if(m == -1)
            {
                break;
            }
            if(Pos[0] == 0)
            {
                break;
            }
            c = Board[Pos[0] - j][Pos[1]];
            j++;
            if(c == '-')
            {
                gate = 0;
                count = 0;
                break;
            }
            if(c == 'O')
            {
                count++;
                continue;
            }
            if(c == 'X')
            {
                gate = 1;
                break;
            }

        }
        if(count > 0 && gate == 1)
        {
            if(flip == 1)
            {
                for(i=0;i<count + 1;i++)
                {
                    Board[Pos[0] - i][Pos[1]] = 'X';
                }
            }
            *ptr+=count;
            return true;
        }
    }
    if(symbol == 'O')
    {
        for(i=0;i<size;i++) // up
        {
            m--;
            if(m == -1)
            {
                break;
            }
            if(Pos[0] == 0)
            {
                break;
            }
            c = Board[Pos[0] - j][Pos[1]];
            j++;
            if(c == '-')
            {
                gate = 0;
                count = 0;
                break;
            }
            if(c == 'X')
            {
                count++;
                continue;
            }
            if(c == 'O')
            {
                gate = 1;
                break;
            }

        }
        if(count > 0 && gate == 1)
        {
            if(flip == 1)
            {
                for(i=0;i<count + 1;i++)
                {
                    Board[Pos[0] - i][Pos[1]] = 'O';
                }
            }
            *ptr+=count;
            return true;
        }
    }
    return false;
}
bool Game::Down(char **Board, int *Pos, int size, char symbol, int flip, int *ptr) {
    int i=0,j=1,count = 0,gate = 0,m;
    char c;
    if(symbol == 'X') {
        m = Pos[0];
        for (i = 0; i < size; i++)// down
        {
            m++;
            if (m == size) {
                break;
            }
            c = Board[Pos[0] + j][Pos[1]];
            j++;
            if (c == '-') {
                gate = 0;
                count = 0;
                break;
            }
            if (c == 'O') {
                count++;
                continue;
            }
            if (c == 'X') {
                gate = 1;
                break;
            }
        }
        if (count > 0 && gate == 1) {
            if (flip == 1) {
                for (i = 0; i < count + 1; i++) {
                    Board[Pos[0] + i][Pos[1]] = 'X';
                }
            }
            *ptr += count;
            return true;
        }
    }
    if(symbol == 'O') {
        m = Pos[0];
        for (i = 0; i < size; i++)// down
        {
            m++;
            if (m == size) {
                break;
            }
            c = Board[Pos[0] + j][Pos[1]];
            j++;
            if (c == '-') {
                gate = 0;
                count = 0;
                break;
            }
            if (c == 'X') {
                count++;
                continue;
            }
            if (c == 'O') {
                gate = 1;
                break;
            }
        }
        if (count > 0 && gate == 1) {
            if (flip == 1) {
                for (i = 0; i < count + 1; i++) {
                    Board[Pos[0] + i][Pos[1]] = 'O';
                }
            }
            *ptr += count;
            return true;
        }
    }
    return false;
}

bool Game::Diagonals(char **Board, int *Pos, int size, char symbol,int flip,int *ptr) {
    int c = 0;
    if(UpRight(Board,Pos,size,symbol,flip,ptr))
    {
        c++;
    }
    if(UpLeft(Board,Pos,size,symbol,flip,ptr))
    {
        c++;
    }
    if(DownRight(Board,Pos,size,symbol,flip,ptr))
    {
        c++;
    }
    if(DownLeft(Board,Pos,size,symbol,flip,ptr))
    {
        c++;
    }
    if(c != 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool Game::UpLeft(char **Board, int *Pos, int size, char symbol, int flip, int *ptr) {
    int i=0,j=1,count = 0,gate = 0,m,n;
    char c;
    m = Pos[0];
    n = Pos[1];
    if(symbol == 'X')
    {
        for(i=0;i<size;i++)
        {
            m--,n--;
            if(m == -1 || n == -1)
            {
                break;
            }
            c = Board[Pos[0] - j][Pos[1] - j];
            j++;
            if(c == '-')
            {
                gate = 0;
                count = 0;
                break;
            }
            if(c == 'O')
            {
                count++;
                continue;
            }
            if(c == 'X')
            {
                gate = 1;
                break;
            }

        }
        if(count > 0 && gate == 1)
        {
            if(flip == 1)
            {
                for(i=0;i<count + 1;i++)
                {
                    Board[Pos[0] - i][Pos[1] - i] = 'X';
                }
            }
            *ptr+=count;
            return true;
        }
    }
    if(symbol == 'O')
    {
        for(i=0;i<size;i++)
        {
            m--,n--;
            if(m == -1 || n == -1)
            {
                break;
            }
            c = Board[Pos[0] - j][Pos[1] - j];
            j++;
            if(c == '-')
            {
                gate = 0;
                count = 0;
                break;
            }
            if(c == 'X')
            {
                count++;
                continue;
            }
            if(c == 'O')
            {
                gate = 1;
                break;
            }

        }
        if(count > 0 && gate == 1)
        {
            if(flip == 1)
            {
                for(i=0;i<count + 1;i++)
                {
                    Board[Pos[0] - i][Pos[1] - i] = 'O';
                }
            }
            *ptr+=count;
            return true;
        }
    }
    return false;
}

bool Game::UpRight(char **Board, int *Pos, int size, char symbol, int flip, int *ptr) {
    int i=0,j=1,count = 0,gate = 0,m,n;
    char c;
    j=1;
    m = Pos[0];
    n = Pos[1];
    if(symbol == 'X')
    {
        for(i=0;i<size;i++)
        {
            m--,n++;
            if(m == -1 || n == size)
            {
                break;
            }
            c = Board[Pos[0] - j][Pos[1] + j];
            j++;
            if(c == '-')
            {
                gate = 0;
                count = 0;
                break;
            }
            if(c == 'O')
            {
                count++;
                continue;
            }
            if(c == 'X')
            {
                gate = 1;
                break;
            }
        }
        if(count > 0 && gate == 1)
        {
            if(flip == 1)
            {
                for(i=0;i<count + 1;i++)
                {
                    Board[Pos[0] - i][Pos[1] + i] = 'X';
                }
            }
            *ptr+=count;
            return true;
        }
    }
    if(symbol == 'O')
    {
        for(i=0;i<size;i++)
        {
            m--,n++;
            if(m == -1 || n == size)
            {
                break;
            }
            c = Board[Pos[0] - j][Pos[1] + j];
            j++;
            if(c == '-')
            {
                gate = 0;
                count = 0;
                break;
            }
            if(c == 'X')
            {
                count++;
                continue;
            }
            if(c == 'O')
            {
                gate = 1;
                break;
            }
        }
        if(count > 0 && gate == 1)
        {
            if(flip == 1)
            {
                for(i=0;i<count + 1;i++)
                {
                    Board[Pos[0] - i][Pos[1] + i] = 'O';
                }
            }
            *ptr+=count;
            return true;
        }
    }
    return false;
}

bool Game::DownLeft(char **Board, int *Pos, int size, char symbol, int flip, int *ptr) {
    int i=0,j=1,count = 0,gate = 0,m,n;
    char c;
    m = Pos[0];
    n = Pos[1];
    if(symbol == 'X')
    {
        for(i=0;i<size;i++)
        {
            m++,n--;
            if(m == size ||n == -1)
            {
                break;
            }
            c = Board[Pos[0] + j][Pos[1] - j];
            j++;
            if(c == '-')
            {
                gate = 0;
                count = 0;
                break;
            }
            if(c == 'O')
            {
                count++;
                continue;
            }
            if(c == 'X')
            {
                gate = 1;
                break;
            }
        }
        if(count > 0 && gate == 1)
        {
            if(flip == 1)
            {
                for(i=0;i<count + 1;i++)
                {
                    Board[Pos[0] + i][Pos[1] - i] = 'X';
                }
            }
            *ptr+=count;
            return true;
        }
    }
    if(symbol == 'O')
    {
        for(i=0;i<size;i++)
        {
            m++,n--;
            if(m == size ||n == -1)
            {
                break;
            }
            c = Board[Pos[0] + j][Pos[1] - j];
            j++;
            if(c == '-')
            {
                gate = 0;
                count = 0;
                break;
            }
            if(c == 'X')
            {
                count++;
                continue;
            }
            if(c == 'O')
            {
                gate = 1;
                break;
            }
        }
        if(count > 0 && gate == 1)
        {
            if(flip == 1)
            {
                for(i=0;i<count + 1;i++)
                {
                    Board[Pos[0] + i][Pos[1] - i] = 'O';
                }
            }
            *ptr+=count;
            return true;
        }
    }
    return false;
}

bool Game::DownRight(char **Board, int *Pos, int size, char symbol, int flip, int *ptr) {
    int i=0,j=1,count = 0,gate = 0,m,n;
    char c;
    m = Pos[0];
    n = Pos[1];
    if(symbol == 'X')
    {
        for(i=0;i<size;i++)
        {
            m++,n++;
            if(m == size || n == size)
            {
                break;
            }
            c = Board[Pos[0] + j][Pos[1] + j];
            j++;
            if(c == '-')
            {
                gate = 0;
                count = 0;
                break;
            }
            if(c == 'O')
            {
                count++;
                continue;
            }
            if(c == 'X')
            {
                gate = 1;
                break;
            }
        }
        if(count > 0 && gate == 1)
        {
            if(flip == 1)
            {
                for(i=0;i<count + 1;i++)
                {
                    Board[Pos[0] + i][Pos[1] + i] = 'X';
                }
            }
            *ptr+=count;
            return true;
        }
    }
    if(symbol == 'O')
    {
        for(i=0;i<size;i++)
        {
            m++,n++;
            if(m == size || n == size)
            {
                break;
            }
            c = Board[Pos[0] + j][Pos[1] + j];
            j++;
            if(c == '-')
            {
                gate = 0;
                count = 0;
                break;
            }
            if(c == 'X')
            {
                count++;
                continue;
            }
            if(c == 'O')
            {
                gate = 1;
                break;
            }
        }
        if(count > 0 && gate == 1)
        {
            if(flip == 1)
            {
                for(i=0;i<count + 1;i++)
                {
                    Board[Pos[0] + i][Pos[1] + i] = 'O';
                }
            }
            *ptr+=count;
            return true;
        }
    }
    return false;
}

int Game::GameRunCPU(char *p1,int size,int test) {
    int BoardSize = 0,Gate = 0,PosX[2],PosY[2],S1 = 0,S2 = 0,Postmp[2];
    int lvl = -1,*PosYptr,*Postmpptr,i,j,rank1 = -100,rank2 = 100,*prank1 = &rank1,*prank2 = &rank2;
    char c;
    char**Board = NULL;
    Leaderboard Log;
    PosYptr =&PosY[0];
    Postmpptr = &Postmp[0];
    while(size < 3)
    {
        cout<<"Enter board size:";
        cin>>size;
    }
    BoardSize = size;
    if(test == 0)
    {
        cout<<"Choose level(1 - 3)"<<endl;
        cin>>lvl;
        while(lvl < 1 || lvl > 3)
        {
            cout<<"Choose level(1 - 3)"<<endl;
            cin>>lvl;
        }
    }
    if(test == 1)
    {
        lvl = 1;
    }
    while(BoardSize < 3)
    {
        cout<<"Enter board size:";
        cin>>BoardSize;
    }
    if(BoardSize % 2 != 0)
    {
        BoardSize+=1;
    }
    Board = Boardini(BoardSize);
    if(test == 0)
    {
        while(Gate != BoardSize*BoardSize*2)
        {
            print(Board,BoardSize);
            if(Gate != 0)
            {
                if(GameOver(Board,BoardSize,'X'))
                {
                    break;
                }
            }
            cout<<p1<<"'s turn:"<<endl;
            cin>>PosX[0]>>PosX[1];
            Update(Board,PosX,BoardSize,'X');
            Flip(Board,PosX,BoardSize,'X');
            print(Board,BoardSize);
            if(GameOver(Board,BoardSize,'O'))
            {
                break;
            }
            cout<<"Cpu's turn:";
            MinMax(Board,lvl,'O',BoardSize,Postmpptr,PosYptr);//CPU
            Update(Board,PosY,BoardSize,'O');
            Flip(Board,PosY,BoardSize,'O');
            Gate +=1;
            cout<<PosY[0]<<" "<<PosY[1]<<endl;
        }
    }

    if(test == 1)
    {
        int break1 = 0;
        while(Gate != BoardSize*BoardSize*2)
        {
            if(Gate != 0)
            {
                if(GameOver(Board,BoardSize,'X'))
                {
                    break;
                }
            }
            for(i=0;i<BoardSize;i++)
            {
                for(j=0;j<BoardSize;j++)
                {
                    PosX[0] = i;
                    PosX[1] = j;
                    if(CheckifValid(Board,PosX,BoardSize,'X',0))
                    {
                        break1 = 1;
                        break;
                    }
                }
                if(break1 == 1)
                {
                    break1 = 0;
                    break;
                }
            }
            TestUpdate(Board,PosX,BoardSize,'X');
            Flip(Board,PosX,BoardSize,'X');
            if(GameOver(Board,BoardSize,'O'))
            {
                break;
            }
            MinMax(Board,lvl,'O',BoardSize,Postmpptr,PosYptr);
            TestUpdate(Board,PosY,BoardSize,'O');
            Flip(Board,PosY,BoardSize,'O');
            Gate +=1;
        }
    }
    for(i=0;i<BoardSize;i++)//Scoring
    {
        for(j=0;j<BoardSize;j++)
        {
            c = Board[i][j];
            if(c == 'X')
            {
                S1++;
            }
            if(c == 'O')
            {
                S2++;
            }
        }
    }
    if(S1 > S2)
    {
        if(test == 0)
        {
            cout<<p1<<" won! "<<p1<<": "<<S1<<" "<<"Cpu: "<<S2<<endl;
            Log.LeaderboardUpdate(p1,S1,1);
        }

        return 0;
    }
    if(S1 < S2)
    {
        if(test == 0)
        {
            cout<<"Cpu won! Cpu: "<<S2<<" "<<p1<<": "<<S1<<endl;
            Log.LeaderboardUpdate(p1,S1,0);
        }

        return 1;
    }
    if(S1 == S2)
    {
        if(test == 0)
        {
            cout<<"Draw! "<<p1<<": "<<S1<<" Cpu: "<<S2<<endl;
            Log.LeaderboardUpdate(p1,S1,0);
        }

        return 2;
    }
}

int Game::MinMax(char **Board,int lvl,char turn,int size,int *player,int*cpu) {

if(lvl == 0|| GameOver(Board,size,turn))
{
    return 0;
}
lvl--;
char nextplayer = 'X';
if(turn == 'X')
{
    nextplayer = 'O';
}

int i,j,Postmp[2],MaxMove[2],MinMove[2],move[2];
int maxscore = -100,minscore = 100,score;
int*m = &maxscore,*l = &minscore;
for(i=0;i<size;i++)
{
    for(j=0;j<size;j++)
    {
        Postmp[0] =i;
        Postmp[1] = j;
        if(Board[i][j] != '-'|| !CheckifValid(Board,Postmp,size,turn,0))
        {
            continue;
        }
        Board[i][j] = turn;
        move[0] = i;
        move[1] = j;
        MinMax(Board,lvl,nextplayer,size,player,cpu);
        score = BoardEval(Board,turn,move,size);
        if(maxscore < score)
        {
            maxscore = score;
            MaxMove[0] = i;
            MaxMove[1] = j;
        }
        if(minscore > score)
        {
            minscore = score;
            MinMove[0] = i;
            MinMove[1] = j;
        }
        Board[i][j] = '-';
    }
    if (turn == 'O')
    {
        Assign(MaxMove,cpu);
    }
    else
    {
        Assign(MinMove,player);
    }
}


}

void Game::Assign(int *from, int *to) {
to[0] = from[0];
to[1] = from[1];
}

int Game::BoardEval(char **Board, char turn, int *move,int size) {
int score = 0,*ptr = &score;

    if(Horizontal(Board,move,size,turn,0,ptr))
        score++;
    if(Vertical(Board,move,size,turn,0,ptr))
        score++;
    if(Diagonals(Board,move,size,turn,0,ptr))
        score++;
    return score;
}

bool Game::GameOver(char **Board, int size, char symbol) {
    int i,j,Postmp[2],score,*scoreptr = &score;
    int done = 0,free = 0,canteat = 0,notvalid = 0;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            if(Board[i][j] =='-')
            {
                free++;
            }

        }
    }
    if(free == 0)
    {
        cout<<"Game over."<<endl;
        return true;
    }
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            if(Board[i][j] == '-')
            {
                Postmp[0] = i;
                Postmp[1] = j;
                if(!Horizontal(Board,Postmp,size,symbol,0,scoreptr) && !Vertical(Board,Postmp,size,symbol,0,scoreptr) && !Diagonals(Board,Postmp,size,symbol,0,scoreptr))
                {
                    canteat++;
                }
                if(!CheckifValid(Board,Postmp,size,symbol,0))
                {
                    notvalid++;
                }
            }

        }
    }
    if(free == canteat)
    {
        return true;
    }
    if(free == notvalid)
    {
        return true;
    }
    return false;
}

bool Game::TestUpdate(char **Board, int *Pos, int size, char symbol) {
if(CheckifValid(Board,Pos,size,symbol,0))
{
    Board[Pos[0]][Pos[1]] = symbol;
    return true;
}
else
{
    return false;
}
}

