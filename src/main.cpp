#include <iostream>
#include "conio2.h"
#include "quiz.h"
using namespace std;

int main()
{
    textcolor(LIGHTGREEN);
    for(int i=1;i<=80;i++)
        cout<<"*";
    textcolor(LIGHTRED);
    gotoxy(32,2);
    cout<<"QUIZ APPLICATION";
    gotoxy(1,3);
    textcolor(LIGHTGREEN);
    for(int i=1;i<=80;i++)
        cout<<"*";

    gotoxy(20,10);
    textcolor(YELLOW);
    cout<<"WELCOME TO TECH TEST - QUIZ APPLICATION";
    gotoxy(20,14);
    textcolor(LIGHTGREEN);
    cout<<"TEST YOUR SKILLS! IMPROVE YOUR KNOWLEDGE !";
    gotoxy(1,20);
    textcolor(WHITE);
    cout<<"Press any key to continue";
    getch();
    Admin::create_admin("uadmin","abc","Sachin");
    do
    {
        clrscr();
        textcolor(LIGHTGREEN);
        for(int i=1;i<=80;i++)
          cout<<"*";
        textcolor(LIGHTRED);
        gotoxy(32,2);
        cout<<"QUIZ APPLICATION";
        gotoxy(1,3);
        textcolor(LIGHTGREEN);
        for(int i=1;i<=80;i++)
          cout<<"*";
        gotoxy(58,4);
        textcolor(WHITE);
        cout<<"Press 0 to exist/Go Back";
        gotoxy(1,8);
        textcolor(YELLOW);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(1,17);
        textcolor(YELLOW);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(32,10);
        cout<<"1. ADMIN";
        gotoxy(32,12);
        cout<<"2. STUDENT";
        gotoxy(32,14);
        textcolor(WHITE);
        cout<<"Select your role:";
        int type;
        cin>>type;
        if(type==0)
            break;
        if(type==1)
        {
            //admin options
            Admin adminObj;
        }
        else if(type==2)
        {
            //student options
        }
        else
        {
            gotoxy(32,14);
            cout<<"\t\t\t\t\t\t\t\t\t";
            gotoxy(32,14);
            textcolor(LIGHTRED);
            cout<<"Invalid User Type";
            getch();

        }


        getch();

    }while(1);


    return 0;
}
