#include <iostream>
#include "conio2.h"
#include "quiz.h"
using namespace std;

int main()
{
    int type,c;
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
    Admin::create_admin("uadmin","abc","Ayush");
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

        cin>>type;
        if(type==0)
            break;
        cin.ignore();
        if(type==1)
        {
            //admin options
            Admin adminObj;
            do
            {
                  c=adminObj.input();
                  if(c==0)
                  {
                    gotoxy(30,14);
                    textcolor(LIGHTRED);
                    cout<<"Login Cancelled";
                    gotoxy(1,20);
                    textcolor(WHITE);
                    cout<<"Press any key to continue";
                    getch();
                    break;
                  }
                   // checkUserExist();
                   c=adminObj.checkUserExists("admin");
                   if(c==1)
                   {
                       gotoxy(28,18);
                       textcolor(LIGHTGREEN);
                       cout<<"Login Accepted!";
                       gotoxy(28,20);
                       cout<<"Welcome "<<adminObj.getName();
                       gotoxy(28,22);
                       textcolor(WHITE);
                       cout<<"Press any key to continue";
                       getch();
                       while(1)
                       {
                           clrscr();
                           textcolor(LIGHTGREEN);
                           for(int i=1;i<=80;i++)
                            cout<<"*";
                           gotoxy(1,3);
                           for(int i=1;i<=80;i++)
                            cout<<"*";
                           textcolor(LIGHTRED);
                           gotoxy(32,2);
                           cout<<"QUIZ APPLICATION";
                           textcolor(LIGHTGREEN);
                           gotoxy(35,6);
                           cout<<"ADMIN MENU"<<endl;
                           textcolor(YELLOW);
                           for(int i=1;i<=80;i++)
                            cout<<"*";
                           gotoxy(32,8);
                           cout<<"1. Add Question";
                           gotoxy(32,9);
                           cout<<"2. Add Student";
                           gotoxy(32,10);
                           cout<<"3. Show Questions";
                           gotoxy(32,11);
                           cout<<"4. Show Students";
                           gotoxy(32,12);
                           cout<<"5. Remove Question";
                           gotoxy(32,13);
                           cout<<"6. Remove Student";
                           gotoxy(32,14);
                           cout<<"7. Exit";
                           gotoxy(32,16);
                           cout<<"Enter Choice:";
                           int choice;
                           textcolor(WHITE);
                           cin>>choice;
                           switch(choice)
                           {
                           case 1:
                                  clrscr();
                                  adminObj.addQuestion();
                                  break;
                           case 2:
                               clrscr();
                               adminObj.addStudent();
                               break;
                           case 3:
                                clrscr();
                                adminObj.viewQuestion();
                                break;
                           case 4:
                                 clrscr();
                                 adminObj.viewStudent();
                                 break;
                           case 5:
                                 clrscr();
                                 adminObj.removeQuestion();
                                 break;
                           case 6:
                                 clrscr();
                                 adminObj.removeStudent();
                           case 7:
                                clrscr();
                                break;
                           default:
                               textcolor(LIGHTRED);
                               gotoxy(32,18);
                               cout<<"Wrong choice. Try Again";
                               getch();
                               break;



                           }
                           if(choice==7)
                            break;








                       }

                   }
                   getch();

            }while(c==0);



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
