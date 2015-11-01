#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#define size 4
#define FILENAME "highscore.txt"
#define LOGFILE "score_log.txt"

using namespace std;

string board[4][4]={{"","","",""},
                    {"","","",""},
                    {"","","",""},
                    {"","","",""}};
int score=0,run=1;
char buffer[33];

void print();
string fix(int,int);
void game_start();
void MOVE(int);
int shift_right();
int merge_right();
int shift_left();
int merge_left();
int shift_down();
int merge_down();
int shift_up();
int merge_up();
void RANDOM();
int random(int,int, int, int, int);
void empty_check();
void GAMEOVER();
void add_highscore(string);
void write_highscore(string);
int just_highscore();
string display_highscore();
void write_log(string);
void display_log();


int main()
{
    game_start();
    print();
    int control,keycode;

    while(run)
    {
        if((control = getch())!=224)
        {
            system("cls");
            MOVE(control);
            empty_check();
        }
        else
        {
            keycode = getch();
            system("cls");
            MOVE(keycode);
            empty_check();
        }
    }
}

void MOVE(int move)                                                         //IDENTIFYING & EXECUTING THE MOVES
{
    int shift_check;
    switch(move)
        {
            case 119:
            case 72:
                shift_check=shift_up();
                if(merge_up() || shift_check)
                    RANDOM();
                print();
                break;

            case 97:
            case 75:
                shift_check=shift_left();
                if(merge_left() || shift_check)
                    RANDOM();
                print();
                break;

            case 100:
            case 77:
                shift_check=shift_right();
                if(merge_right() || shift_check)
                    RANDOM();
                print();
                break;

            case 115:
            case 80:
                shift_check=shift_down();
                if(merge_down() || shift_check)
                    RANDOM();
                print();
                break;

            case 'o':
                print();
                cout<<"\n\nError: PROGRAM TERMINATED PREMATURELY BY THE USER.\n\n";
                run=0;
                break;

            case '8':
                display_log();
                break;

            case '9':
                cout<<display_highscore();
                break;

            case '0':
                GAMEOVER();
                break;

            default:
                print();
              break;

        }
}

void print()                                                                //PRINTING THE ARRAY
{
    char bar = 179;
    cout<<"\n\n\n";
    for (int R = 0; R < size; R++)
    {
        cout<<endl<<"                           _____________________"<<endl<<"                           "<<bar;
        for (int C = 0; C < size; C++)
            cout<<board[R][C]<<fix(R,C);
    }
    cout<<"\n                           _____________________";

    cout<<"\n\n                               SCORE :: "<<score;
}

int random(int amplifier, int a, int b, int c, int d)                       //RANDOM INTEGER OUT OF 4
{
    int arr[4]={a,b,c,d};
    time_t seconds;
    time(&seconds);
    srand((seconds*amplifier));
    int r=rand()%4;
return arr[r];
}

void game_start()                                                           //RANDOM POSITIONS OF 4 & 2
{
restart:
    int t1,t2,t3,t4,i=1;
    board[t1=random(i++,0,1,2,3)][t2=random(i++,0,1,2,3)]="2";
    board[t3=random(i++,0,1,2,3)][t4=random(i++,0,1,2,3)]="4";
    if(t1==t3 && t2==t4)
    {
        goto restart;
    }
 //   cout<<t1<<t2<<t3<<t4;

//     t1=1;t2=1;t3=1;t4=3;
//     board[t1][t2]='2';
//     board[t3][t4]='4';

}

int shift_right()
{
int shift_check=0;
int m;
    for(int i=0;i<4;i++)
    {
        for(int j=3,m=3;j>=0;j--)
        {
            if(atoi(board[i][j].c_str())!=0)
            {
                board[i][m--]=board[i][j];
                if((m+1)!=j)
                {
                    board[i][j]="";
                    shift_check=1;
                }
            }
        }
    }
return shift_check;
}

int shift_left()
{
int shift_check=0;
int m;
    for(int i=0;i<4;i++)
    {
        for(int j=0,m=0;j<4;j++)
        {
            if(atoi(board[i][j].c_str())!=0)
            {
                board[i][m++]=board[i][j];
                if((m-1)!=j)
                {
                    board[i][j]="";
                    shift_check=1;
                }
            }
        }
    }
return shift_check;
}

int shift_up()
{
int shift_check=0;
int m;
    for(int i=0;i<4;i++)
    {
        for(int j=0,m=0;j<4;j++)
        {
            if(atoi(board[j][i].c_str())!=0)
            {
                board[m++][i]=board[j][i];
                if((m-1)!=j)
                {
                    board[j][i]="";
                    shift_check=1;
                }
            }
        }
    }
return shift_check;
}

int shift_down()
{
int shift_check=0;
int m;
    for(int i=0;i<4;i++)
    {
        for(int j=3,m=3;j>=0;j--)
        {
            if(atoi(board[j][i].c_str())!=0)
            {
                board[m--][i]=board[j][i];
                if((m+1)!=j)
                {
                    board[j][i]="";
                    shift_check=1;
                }
            }
        }
    }
return shift_check;
}

int merge_right()
{
    int merge_check=0;
    int temp;
    for(int i=0;i<4;i++)
    {
        for(int j=3;j>=1;j--)
        {
            if(atoi(board[i][j].c_str())!=0 && atoi(board[i][j].c_str())==atoi(board[i][j-1].c_str()))
            {
                temp=atoi(board[i][j].c_str())+atoi(board[i][j-1].c_str());
                board[i][j]=string(itoa(temp,buffer,10));
                score=score+temp;

                board[i][j-1]="";
                j++;
                merge_check=1;
            }
        }
    }
shift_right();
return merge_check;
}

int merge_left()
{
    int merge_check=0;
    int temp;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(atoi(board[i][j].c_str())!=0 && atoi(board[i][j].c_str())==atoi(board[i][j+1].c_str()))
            {
                temp=atoi(board[i][j].c_str())+atoi(board[i][j+1].c_str());
                board[i][j]=string(itoa(temp,buffer,10));
                score=score+temp;

                board[i][j+1]="";
                j--;
                merge_check=1;
            }
        }
    }
shift_left();
return merge_check;
}

int merge_up()
{
    int merge_check=0;
    int temp;
    for(int j=0;j<3;j++)
    {
        for(int i=0;i<4;i++)
        {
            if(atoi(board[j][i].c_str())!=0 && atoi(board[j][i].c_str())==atoi(board[j+1][i].c_str()))
            {

                temp=atoi(board[j][i].c_str())+atoi(board[j+1][i].c_str());
                board[j][i]=string(itoa(temp,buffer,10));
                score=score+temp;

                board[j+1][i]="";
                j--;
                merge_check=1;
            }
        }
    }
shift_up();
return merge_check;
}

int merge_down()
{
    int merge_check=0;
    int temp;
    for(int j=3;j>0;j--)
    {
        for(int i=0;i<4;i++)
        {
            if(atoi(board[j][i].c_str())!=0 && atoi(board[j][i].c_str())==atoi(board[j-1][i].c_str()))
            {
                temp=atoi(board[j][i].c_str())+atoi(board[j-1][i].c_str());
                board[j][i]=string(itoa(temp,buffer,10));
                score=score+temp;

                board[j-1][i]="";
                j++;
                merge_check=1;
            }
        }
    }
shift_down();
return merge_check;
}

void RANDOM()                                                               //ALLOTS RANDOM 2 & 4 IN THE GRID
{
    int t1,t2,t3,i=1;
    again:
    if(board[t1=random(i++,0,1,2,3)][t2=random(i++,0,1,2,3)]=="")
    {
        t3=random(i++,0,1,0,1);
        if(t3)
        (board[t1][t2]="2");
        else
        (board[t1][t2]="4");
    }
    else
        goto again;
}

string fix(int i,int j)                                                     //FIXES THE ARRAY OUTPUT
{
    string tempi,tempf;
    char bar = 179;
    switch(board[i][j].length())
    {
        case 0:
            tempi="    ";
            tempf=tempi+bar;
            return tempf;
        case 1:
            tempi="   ";
            tempf=tempi+bar;
            return tempf;
        case 2:
            tempi="  ";
            tempf=tempi+bar;
            return tempf;
        case 3:
            tempi=" ";
            tempf=tempi+bar;
            return tempf;
        case 4:
            tempi="";
            tempf=tempi+bar;
            return tempf;
   }
   }

void empty_check()                                                          //CHECKS IF THE GRID IS EMPTY //INVOKES GAMEOVER();
{
    //EMPTY CHECK
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if((board[i][j])=="")
                return;
        }
    }


    //LEFT
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==board[i][j+1])
            return;
        }
    }

//    //RIGHT
//    for(int i=0;i<4;i++)
//    {
//        for(int j=3;j>0;j--)
//        {
//            if(board[i][j]==board[i][j-1])
//            return;
//        }
//    }

    //UP
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[j][i]==board[j+1][i])
            return;
        }
    }

//    //DOWN
//    for(int i=0;i<4;i++)
//    {
//        for(int j=3;j>0;j++)
//        {
//            if(board[j][i]==board[j-1][i])
//            return;
//        }
//    }
GAMEOVER();
}

void GAMEOVER()                                                             //ENDS THE GAME // ASKS NAME & DISPLAYS HIGHSCORE
{
string name;
        system("cls");
        print();
            cout<<"\n\n                                 GAMEOVER!!";
            cout<<"\n                           Enter your name:";
            cin>>name;
            write_log(name);

        if((just_highscore())<=score)
        {
            cout<<"\n                    Congrats! You've made the high score.";
            add_highscore(name);
        }

            cout<<"\n                     The highest score is by "<<display_highscore()<<"\n\n\n";
            run=0;
}

void write_highscore(string name)
{
    fstream myfile;
    myfile.open(FILENAME);
        if(myfile.is_open())
    {
        myfile<<name<<":  \n"<<flush;
        myfile <<score<<flush;
        myfile.close();
    }
    else
    cout<<"Unable to open file**";
}

void add_highscore(string name)
{
    fstream myfile;
    string line;
     myfile.open(FILENAME);
     if (myfile.is_open())
    {
        getline (myfile,line);
        int oldscore = atoi(line.c_str());

        if(score>oldscore)
            write_highscore(name);

        myfile.close();
    }

  else cout << "Unable to open file*";

}

string display_highscore()
{
    int output_score;
    string line;
    string final_score;
    fstream myfile;
    myfile.open(FILENAME);
     if (myfile.is_open())
    {
        while(!myfile.eof())
        {
            getline (myfile,line);
            final_score=final_score+line;
        }
        myfile.close();
    }
return final_score;
}

int just_highscore()
{
    int output_score;
    string line;
    fstream myfile;
    myfile.open(FILENAME);
     if (myfile.is_open())
    {
        while(!myfile.eof())
        {
            getline (myfile,line);
            output_score = atoi(line.c_str());
            if(output_score)
            {
                myfile.close();
                return output_score;
            }
        }
    }
}

void write_log(string name)
{
    fstream myfile;
    myfile.open(LOGFILE, ios::out | ios::app );
        if(myfile.is_open())
    {
        myfile<<name<<":  \n"<<flush;
        myfile <<score<<"\n"<<flush;
        myfile.close();
    }
    else
    cout<<"Unable to open file***";
}

void display_log()
{
    fstream myfile;
    myfile.open(LOGFILE, ios::in);
    if(myfile.is_open())
    {

        while(!myfile.eof())
        {
            string str;
            int data;
            getline(myfile,str); //read number
            cout<<str<<endl;
        }
        myfile.close();
    }
}
