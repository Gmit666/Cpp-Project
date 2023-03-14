//
// Created by amitg on 29/01/2023.
//

#include "Users.h"

Users::Users() {
fstream UserFile;
if(!ThereisUsers())
{
    UserFile.open("Users.txt",ios::out);
    UserFile.close();
}
}

char* Users::Sign_up(int type) {
    char username[Size],password[Size],Type[Size];
    int size;
    cout<<"Enter Username:";
    cin>>username;
    cout<<"Enter password:";
    cin>>password;
    while(Check(username))
    {
        cout<<"Username is taken."<<endl;
        cout<<"Enter Username:";
        cin>>username;
    }
    switch(type) {
        case 1:
        {
            strcpy(Type,"Cat\0");
            break;
        }
        case 2:
        {
            strcpy(Type,"Dog\0");
            break;
        }
        case 3:
        {
            strcpy(Type,"Dolphin\0");
            break;
        }
        case 4:
        {
            strcpy(Type,"Shark\0");
            break;
        }
        case 5:
        {
            strcpy(Type,"Barracuda\0");
            break;
        }
        case 6:
        {
            strcpy(Type,"Ant\0");
            break;
        }
        case 7:
        {
            strcpy(Type,"Grasshopper\0");
            break;
        }
        case 8:
        {
            strcpy(Type,"Wasp\0");
            break;
        }
    }

    fstream UserFile;
    UserFile.open("Users.txt",ios::app);
    if(UserFile.is_open())
    {
        UserFile <<username<<" "<<password<<" "<<Type<<endl;
    }
    UserFile.close();
    char *u = NULL;
    size = strlen(username);
    u = new char[size + 1];
    strcpy(u,username);
    return u;
}

bool Users::Check(char *username)
{
    fstream UserFile;
    int i = 0,count = 0;
    //count -> 1 username match
    string Line;
    char c = 'c';
    UserFile.open("Users.txt",ios::in);
    if(UserFile.is_open())
    {
        while(getline(UserFile,Line))
        {
            i=0;
            c =Line[i];
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

            if(s1.compare(username) == 0)
            {
                UserFile.close();
                return true;
            }
        }
    }
    UserFile.close();
    return false;
}

bool Users::Login(char *Name) {
    fstream UserFile;
    char password[Size],c = 'c';
    string Line;
    int gate = 0,i = 0,count = 0;
    UserFile.open("Users.txt",ios::in);
    cout<<"Enter password:";
    cin>>password;

    if(UserFile.is_open())
    {
        while(getline(UserFile,Line))
        {
            i=0;
            c =Line[i];
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
            if(s1.compare(Name) != 0)
            {
                continue;
            }
            if(s1.compare(Name) == 0 && s2.compare(password) == 0)
            {
                cout<<"Login successful."<<endl;
                return true;
            }
            if(s1.compare(Name) == 0 && s2.compare(password) != 0)
            {
                cout<<"Password incorrect."<<endl;
                return false;
            }
        }

    }
    cout<<"Username doesn't exist."<<endl;
    return false;
}

char* Users::GetCred(int num, char *Username) {
    fstream UserFile;
    char c ,*tmp;
    string Line;
    int i,count,len;
    UserFile.open("Users.txt",ios::in);
    if(UserFile.is_open())
    {
        while(getline(UserFile,Line)) {
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
                if(num == 0)//password
                {
                    len = (int)s2.length() + 1;
                    tmp = new char[len];
                    s2.copy(tmp,len,0);
                    tmp[len-1] = '\0';
                    return tmp;
                }
                if(num == 1)//team
                {
                    len = (int)s3.length() + 1;
                    tmp = new char[len];
                    s3.copy(tmp,len,0);
                    tmp[len-1] = '\0';
                    return tmp;
                }
            }
        }
    }
    return NULL;
}

int Users::TypeOfUser(char *Name)
{
    Users x;
    char *Team;
    Team = x.GetCred(1,Name);
    if(strcmp(Team,"Cat") == 0)
    {
        return 1;
    }
    if(strcmp(Team,"Dog") == 0)
    {
        return 2;
    }
    if(strcmp(Team,"Dolphin") == 0)
    {
        return 3;
    }
    if(strcmp(Team,"Shark") == 0)
    {
        return 4;
    }
    if(strcmp(Team,"Barracuda") == 0)
    {
        return 5;
    }
    if(strcmp(Team,"Ant") == 0)
    {
        return 6;
    }
    if(strcmp(Team,"Grasshopper") == 0)
    {
        return 7;
    }
    if(strcmp(Team,"Wasp") == 0)
    {
        return 8;
    }
    return 0;
}

int Users::chooseTeam() {
    int team = 0,type = 0;
    while(team == 0)
    {
        cout<<"Choose team:"<<endl;
        cout<<"1.Mammal"<<endl<<"2.Fish"<<endl<<"3.Insect"<<endl;
        cin>>team;
    }
    switch(team)
    {
        case 1:
        {
            while(type == 0)
            {
                cout<<"1.Cat"<<endl<<"2.Dog"<<endl<<"3.Dolphin"<<endl;
                cin>>type;
            }
            if(type == 1)
                return 1;
            if(type == 2)
                return 2;
            if(type == 3)
                return 3;
            break;
        }
        case 2:
        {
            while(type == 0)
            {
                cout<<"1.Shark"<<endl<<"2.Barracuda"<<endl;
                cin>>type;
            }
            if(type == 1)
                return 4;
            if(type == 2)
                return 5;
            break;
        }
        case 3:
        {
            while(type == 0)
            {
                cout<<"1.Ant"<<endl<<"2.Grasshopper"<<endl<<"3.Wasp"<<endl;
                cin>>type;
            }
            if(type == 1)
                return 6;
            if(type == 2)
                return 7;
            if(type == 3)
                return 8;
            break;
        }
    }
    return 0;
}

bool Users::ThereisUsers() {

    fstream User;
    User.open("Users.txt", ios::in);
    if(User.is_open())
    {
        User.close();
        return true;
    }
    return false;
}

