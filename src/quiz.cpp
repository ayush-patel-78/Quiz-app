#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "quiz.h"
# include "conio2.h"
#include <time.h>

using namespace std;



void Admin::create_admin(string userid,string password,string username)
{
    fstream fobj("Admin.bin",ios::in|ios::binary);
    if(fobj.fail())
    {
        fobj.open("Admin.bin",ios::out|ios::binary);
        Admin adminObj;
        adminObj.setUserDetails(userid,password,username);
        fobj.write((char *)&adminObj,sizeof(Admin));
        cout<<"File created";
    }
    else
        cout<<"File already present";
    fobj.close();

}

void User::setUserDetails(string userid,string pwd,string username)
{
    strcpy(this->userid,userid.c_str());
    strcpy(this->pwd,pwd.c_str());
    strcpy(this->uname,username.c_str());
}
int User::input()
{
    clrscr();
    textcolor(LIGHTGREEN);
    gotoxy(1,1);
    for(int i=1;i<=80;i++)
        cout<<"*";
    gotoxy(1,3);
    for(int i=1;i<=80;i++)
        cout<<"*";
    gotoxy(58,4);
    textcolor(WHITE);
    cout<<"Press 0 to exit/go back";
    gotoxy(32,2);
    textcolor(LIGHTRED);
    cout<<"QUIZ APPLICATION";
    gotoxy(1,8);
    textcolor(YELLOW);
    for(int i=1;i<=80;i++)
    {
        cout<<"*";
    }
    gotoxy(1,17);
    textcolor(YELLOW);
    for(int i=1;i<=80;i++)
    {
        cout<<"*";
    }
    gotoxy(28,11);
    cout<<"Enter userid:";
    textcolor(WHITE);
    cin.getline(userid,20);
    if(strcmp(userid,"0")==0)
        return 0;
    gotoxy(28,12);
    textcolor(YELLOW);
    cout<<"Enter password:";
    textcolor(WHITE);


    char ch;
    int i=0;
    while(true)
    {
        ch=getch();
        if(ch==13)
            break;
        if(ch==8)
        {
            if(i==0)
                continue;
            cout<<"\b \b";
            i--;
           continue;
        }
        cout<<ch;
        delay(200);
        cout<<"\b*";
        pwd[i]=ch;
        i++;
    }
    pwd[i]='\0';
    if(strcmp(pwd,"0")==0)
        return 0;
    return 1;
}
int User::checkUserExists(string usertype)
{
    if(strcmp(userid,"")==0 || strcmp(pwd,"")==0)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        cout<<"BOTH THE FIELDS ARE MANDATORY";
        getch();
        //gotoxy(28,20);
        //cout<<"\t\t\t\t\t\t\t\t\t\t";
        //gotoxy(41,10);
        //cout<<"\t\t\t\t\t\t\t\t\t\t\t";
        //gotoxy(42,12);
        //cout<<"\t\t\t\t\t\tt\t\t\t\t\t";
        return 0;

    }
    ifstream fin;
    User *uptr;
    if(usertype=="admin")
    {
        fin.open("Admin.bin",ios::in|ios::binary);
        uptr=new Admin;
    }
    else if(usertype=="student")
    {
        fin.open("Student.bin",ios::in|ios::binary);
        uptr=new Student;
    }
    else
    {
        gotoxy(28,20);
    textcolor(LIGHTRED);
    cout<<"WRONG USERTYPE PASSED!";
    getch();
    return 0;
    }
    bool useridfound=0;
    bool pwdfound=0;
    while(1)
    {
        fin.read((char*)uptr,sizeof(*uptr));
        if(fin.eof())
            break;
        if(strcmp(userid,uptr->userid)==0)
        {
            if(strcmp(pwd,uptr->pwd)==0)
            {
                useridfound=pwdfound=1;
                break;
            }
            useridfound=1;
        }
    }
    bool result=0;
    if(useridfound==0)
    {
        gotoxy(28,18);
        textcolor(LIGHTRED);
        cout<<"No such User exists!";
        getch();
    }
    else if(pwdfound==0)
    {
         gotoxy(28,18);
        textcolor(LIGHTRED);
        cout<<"Invalid password!";
        getch();
    }
    else
    {
        result=1;
        strcpy(uname,uptr->uname);
    }

    fin.close();
    return result;
}
string User::getName()
{
    string USERNAME(uname);
    return USERNAME;
}
string User::getUserID()
{
    string USERID;
    USERID=userid;
    return USERID;
}
void Admin::addQuestion()
{
    Question quesObj;
    quesObj.add();
    clrscr();
}
void Question::add()
{
    fstream fobj("Question.bin",ios::app|ios::binary|ios::in);
    if(!fobj)
    {
        gotoxy(32,18);
        textcolor(LIGHTRED);
        cout<<"Sorry! file cannot be opened";
        getch();
        return;
    }
    fobj.seekg(0,ios::end);
    if(fobj.tellg()==0)
    {
        quesid=1;
    }
    else
    {
        fobj.seekg(-1*sizeof(*this),ios::end);
        fobj.read((char*)this,sizeof(*this));
        cout<<"Last Question Id is "<<quesid;
        quesid++;
        cout<<"New Question Id is "<<quesid;
        getch();


    }
    char uchoice;
    do
    {
        clrscr();
        textcolor(WHITE);
        gotoxy(58,4);
        cout<<"Press 0 to exit/go back";
        textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(1,3);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APP";
        textcolor(WHITE);
        gotoxy(25,5);
        cout<<"***** ADD QUESTION DETAILS *****";
        gotoxy(1,8);
        textcolor(YELLOW);
        string str;
        cout<<"Enter Question:";
        cin.ignore();
        textcolor(WHITE);
        getline(cin,str,'*');
        if(strcmp(str.c_str(),"0")==0)
        {
            gotoxy(1,24);
            textcolor(LIGHTRED);
            //gotoxy(5,20);
            cout<<"Closing add question"<<endl;
            getch();
            fobj.close();
            return;
        }
        strncpy(ques,str.c_str(),499);
        //gotoxy(1,11);
        textcolor(LIGHTGREEN);
        cout<<endl<<"Carries marks:";
        textcolor(YELLOW);
        cin>>tot_marks;
        // gotoxy(1,13);
        textcolor(LIGHTGREEN);
        cout<<endl<<"Options"<<endl<<endl;
       // gotoxy(1,15);
        textcolor(YELLOW);
        cout<<"(a) ";
        textcolor(WHITE);
        cin.ignore();
        getline(cin,str);
        strncpy(op1,str.c_str(),99);
        //strcpy(op1,str.c_str());
        //gotoxy(1,16);
        textcolor(YELLOW);
        cout<<"(b) ";
        textcolor(WHITE);
        //cin.ignore();
        getline(cin,str);
        strncpy(op2,str.c_str(),99);
        //strcpy(op2,str.c_str());


        //gotoxy(1,17);
        textcolor(YELLOW);
        cout<<"(c) ";
        textcolor(WHITE);
         //cin.ignore();
        getline(cin,str);
        strncpy(op3,str.c_str(),99);
        //strcpy(op3,str.c_str());
        //gotoxy(1,18);
        textcolor(YELLOW);
        cout<<"(d) ";
        textcolor(WHITE);
         //cin.ignore();
        getline(cin,str);
        strncpy(op4,str.c_str(),99);
        //strcpy(op4,str.c_str());
        bool valid=false;
        do
        {
           textcolor(YELLOW);
           gotoxy(1,19);
           cout<<"Enter correct ans(a/b/c/d):  \b";
           //cout<<"\t\b\b\b\b\b";
           textcolor(WHITE);
           cin>>ans;

           if(ans>='a'&&ans<='d')
            {
                valid=true;
             /* textcolor(LIGHTRED);
              gotoxy(25,22);
              cout<<"Invalid option entered! please try again.";
              getch();*/
            }
           else
           {
              gotoxy(24,22);
              textcolor(LIGHTRED);
              cout<<"Invalid option entered! please try again.";
              getch();
              valid=false;

           }
           /*gotoxy(25,22);
           cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
           getch();*/
        }while(valid==false);

        fobj.write((char *)this,sizeof(*this));
        quesid++;

        gotoxy(24,22);
        cout<<"\t\t\t\t\t\t\t";
        gotoxy(34,22);
        textcolor(LIGHTGREEN);
        cout<<"Question added successfully!";
        getch();
        gotoxy(1,24);
        textcolor(LIGHTMAGENTA);
        cout<<endl<<"Do you want to add more questions(Y/N): ";
        textcolor(WHITE);
        cin>>uchoice;



    }while(uchoice=='Y'||uchoice=='y');
    fobj.close();

}
void Admin::viewQuestion()
{
    Question quesObj;
    quesObj.viewQuestion();
    clrscr();
}
void Question::viewQuestion()
{
    ifstream fin("Question.bin",ios::in|ios::binary);
    if(!fin)
    {
        gotoxy(1,10);
        textcolor(LIGHTRED);
        cout<<"No Questions have been added yet!";
        getch();
        return;
    }
    fin.seekg(0,ios::end);
    if(fin.tellg()==0)
    {
        gotoxy(1,10);
        textcolor(LIGHTRED);
        cout<<"No Questions present in the file!";
        getch();
        return;
    }
    clrscr();
    fin.seekg(0);
    while(1)
    {
         textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(1,3);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APP";
        textcolor(WHITE);
        gotoxy(25,5);
        cout<<"***** SHOW QUESTION DETAILS *****";
        gotoxy(1,7);
        textcolor(LIGHTGREEN);
        for(int i=1;i<=80;i++)
            cout<<"*";
        fin.read((char*)this,sizeof(*this));
        if(fin.eof())
        {
            cout<<endl;
            textcolor(LIGHTRED);
            gotoxy(35,10);
            cout<<"NO MORE QUESTIONS PRESENT!";
            getch();
            break;
        }
        else
        {
            show();
            getch();
            clrscr();
        }
    }
    fin.close();
}
void Question::show()
{
    cout<<endl;
    textcolor(YELLOW);
    cout<<"Q."<<quesid<<"  ";
    cout<<ques<<endl;
    cout<<"Carries Marks: "<<tot_marks<<endl;
    cout<<"a.  "<<op1<<endl;
    cout<<"b.  "<<op2<<endl;
    cout<<"c.  "<<op3<<endl;
    cout<<"d.  "<<op4<<endl;

    textcolor(LIGHTGREEN);

    cout<<endl<<"Correct Option "<<ans;
}

void Admin::removeQuestion()
{
    Question quesObj;
    quesObj.Remove();
    clrscr();

}
void Question::Remove()
{
    clrscr();
    textcolor(WHITE);
    gotoxy(58,4);
    cout<<"Press 0 to exit";
    textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(1,3);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APP";
        textcolor(WHITE);
        gotoxy(25,5);
        cout<<"***** REMOVE QUESTION DETAILS *****";

        ifstream fin("Question.bin",ios::in|ios::binary);
        if(!fin)
        {
         gotoxy(35,10);
         textcolor(LIGHTRED);
         cout<<"Sorry file cannot be opened!";
         getch();
         return;
        }
        fin.seekg(0,ios::end);
        if(fin.tellg()==0)
        {
            gotoxy(35,10);
         textcolor(LIGHTRED);
         cout<<"No Question Available for deletion!";
         getch();
         fin.close();
         return;
        }
        getch();
        gotoxy(1,8);
        textcolor(YELLOW);
        cout<<"Enter Question ID:";
        bool found=false,valid;
        int id;
        ofstream fout("temp.bin",ios::out|ios::binary|ios::trunc);
        if(!fout)
        {
           gotoxy(35,10);
         textcolor(LIGHTRED);
         cout<<"Sorry! removal not possible!";
         getch();
         fin.close();
         return;
        }
        fin.seekg(0);
        do{
            valid=true;
            cin>>id;
            if(id==0)
            {
                fin.close();
                fout.close();
                remove("temp.bin");
                return;
            }
            if(id<0)
            {
                valid=false;
                 gotoxy(1,24);
                 textcolor(LIGHTRED);
                 cout<<"\t\t\t\t\t\t\t\t\rInvalid Question ID";
                 getch();
                 gotoxy(19,8);
                 cout<<"\t\t\t\t\t\t\t";
                 gotoxy(19,8);
                 textcolor(WHITE);


            }
            else
            {
                while(true)
                {
                  fin.read((char*)this,sizeof(*this));
                  if(fin.eof())
                        break;
                  if(this->quesid==id)
                  {
                      found=true;
                      continue;
                  }
                  else{
                    fout.write((char*)this,sizeof(*this));
                  }
                }
                fout.close();
                fin.close();
                if(found)
                {
                    textcolor(WHITE);
                    gotoxy(1,24);
                    cout<<"\t\t\t\t\t\t\t\t\t\t\rQuestion removed Successfully!";
                    getch();
                    remove("Question.bin");
                    rename("temp.bin","Question.bin");
                }
                else
                {
                     textcolor(LIGHTRED);
                    gotoxy(1,24);
                    cout<<"\t\t\t\t\t\t\t\t\t\t\rQuestion ID not found!";
                    getch();
                    remove("temp.bin");
                    getch();
                }
            }
        }while(valid==false);
}
void Admin::addStudent()
{
    Student studObj;
    studObj.add();
    clrscr();
}
void Student::add()
{
    char uchoice;
    int id;
    char stuid[10];
    string str;
    fstream fobj("Student.bin",ios::app|ios::in|ios::binary);
    fobj.seekg(0,ios::end);
    if(fobj.tellg()==0)
        id=1;
    else
    {
        fobj.seekg(-1*sizeof(*this),ios::end);
        fobj.read((char*)this,sizeof(*this));
        char *pos=strchr(userid,'-');
        if(pos!=NULL)
        {
           id=atoi(pos+1);
           id++;
        }
    }
    cout<<"Next id is:"<<id;
    getch();
    fobj.seekg(0,ios::end);
    do{
        clrscr();
        textcolor(WHITE);
        gotoxy(58,4);
        cout<<"Press 0 to Exit/Go back";
        gotoxy(37,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APP";
        textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i=1;i<=80;i++)
            cout<<"~";
        gotoxy(1,3);
        for(int i=1;i<=80;i++)
            cout<<"~";
        textcolor(WHITE);
        gotoxy(25,5);
        cout<<"***** ADD STUDENT DETAILS *****";
        gotoxy(1,8);
        textcolor(YELLOW);
        cout<<"Enter student name:";
        cin.ignore();
        textcolor(WHITE);
        getline(cin,str);
        strncpy(uname,str.c_str(),19);
        if(strcmp(uname,"0")==0)
        {
            gotoxy(1,24);
            textcolor(LIGHTRED);
            cout<<"Cancelling Add Student..."<<endl;
            getch();
            fobj.close();
            return;
        }
        textcolor(YELLOW);
        cout<<"Enter student Password:";

        textcolor(WHITE);
        getline(cin,str);
        strncpy(pwd,str.c_str(),19);
        if(strcmp(pwd,"0")==0)
        {
            gotoxy(1,24);
            textcolor(LIGHTRED);
            cout<<"Cancelling Add Student..."<<endl;
            getch();
            fobj.close();
            return;
        }
        sprintf(stuid,"STU-%d",id);
        strcpy(userid,stuid);
        fobj.write((char*)this,sizeof(*this));
        gotoxy(30,15);
        textcolor(LIGHTGREEN);
        cout<<"STUDENT ADDED SUCCESSFULLY!";
        cout<<endl<<"STUDENT ID IS :"<<userid;
        getch();
        gotoxy(1,20);
        textcolor(MAGENTA);
        cout<<"Do you want to add more student (Y/N) ?";
        cin>>uchoice;
        id++;
    }while(uchoice=='Y'||uchoice=='y');
}

void Admin::viewStudent()
{
    Student studObj;
    studObj.showStudentDetails();
    clrscr();
}
void Student::showStudentDetails()
{

    clrscr();
    ifstream fin("Student.bin",ios::in|ios::binary);
    if(!fin)
    {
        gotoxy(1,10);
        textcolor(LIGHTRED);
        cout<<"No Students have been added yet!";
        getch();
        return;
    }
    fin.seekg(0,ios::end);
    if(fin.tellg()==0)
    {
        gotoxy(1,10);
        textcolor(LIGHTRED);
        cout<<"No Student present in the file!";
        getch();
        return;
    }
    clrscr();
    fin.seekg(0);
    while(1)
    {
         textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(1,3);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APP";
        textcolor(WHITE);
        gotoxy(25,5);
        cout<<"***** SHOW STUDENT DETAILS *****";
        gotoxy(1,7);
        textcolor(LIGHTGREEN);
        for(int i=1;i<=80;i++)
            cout<<"*";
        fin.read((char*)this,sizeof(*this));
        if(fin.eof())
        {
            cout<<endl;
            textcolor(LIGHTRED);
            gotoxy(35,10);
            cout<<"NO MORE STUDENTS PRESENT!";
            getch();
            break;
        }
        else
        {
            show();
            getch();
            clrscr();
        }
    }
    fin.close();
}
void User::show()
{
    cout<<endl;
    textcolor(YELLOW);
    cout<<"User ID:";
    textcolor(LIGHTGREEN);
    cout<<userid<<endl;

     textcolor(YELLOW);
    cout<<"User Name:";
    textcolor(LIGHTGREEN);
    cout<<uname<<endl;

     textcolor(YELLOW);
    cout<<"User password:";
    textcolor(LIGHTGREEN);
    cout<<pwd<<endl;
}
void Admin::removeStudent()
{
    Student studObj;
    studObj.Remove();
    clrscr();

}
void Student::Remove()
{
    clrscr();
    textcolor(WHITE);
    gotoxy(58,4);
    cout<<"Press 0 to exit";
    textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(1,3);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APP";
        textcolor(WHITE);
        gotoxy(25,5);
        cout<<"***** REMOVE STUDENT DETAILS *****";

        ifstream fin("Student.bin",ios::in|ios::binary);
        if(!fin)
        {
         gotoxy(35,10);
         textcolor(LIGHTRED);
         cout<<"Sorry file cannot be opened!";
         getch();
         return;
        }
        fin.seekg(0,ios::end);
        if(fin.tellg()==0)
        {
            gotoxy(35,10);
         textcolor(LIGHTRED);
         cout<<"No Student Available for deletion!";
         getch();
         fin.close();
         return;
        }

        gotoxy(1,8);
        textcolor(YELLOW);
        cout<<"Enter Student ID:";
        bool found=false,valid;
        char id[10];
        ofstream fout("temp.bin",ios::out|ios::binary|ios::trunc);
        if(!fout)
        {
           gotoxy(35,10);
         textcolor(LIGHTRED);
         cout<<"Sorry! removal not possible!";
         getch();
         fin.close();
         return;
        }
        fin.seekg(0);
        do{
            valid=true;
            cin>>id;


                while(true)
                {
                  fin.read((char*)this,sizeof(*this));
                  if(fin.eof())
                        break;
                  if(strcmp(this->userid,id)==0)
                  {
                      found=true;
                      continue;
                  }
                  else{
                    fout.write((char*)this,sizeof(*this));
                  }
                }
                fout.close();
                fin.close();
                if(found)
                {
                    textcolor(WHITE);
                    gotoxy(1,24);
                    cout<<"\t\t\t\t\t\t\t\t\t\t\rStudent removed Successfully!";
                    getch();
                    remove("Student.bin");
                    rename("temp.bin","Student.bin");
                }
                else
                {
                     textcolor(LIGHTRED);
                    gotoxy(1,24);
                    cout<<"\t\t\t\t\t\t\t\t\t\t\rStudent ID not found!";
                    getch();
                    remove("temp.bin");
                    getch();
                }

        }while(valid==false);
}
void Student::quiz()
{
    Question quesObj;
    quesObj.startQuiz(userid);
}
void Question::startQuiz(string id)
{
    ifstream fin("Question.bin",ios::in|ios::binary);
    if(fin.fail())
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        cout<<"No Questions have Been Added yet!";
        getch();
        return;
    }
    vector <Question> vecQues;
    while(1)
    {
       fin.read((char*)this,sizeof(*this));

       if(fin.eof())
            break;
       vecQues.push_back(*this);
    }
    fin.close();
    vector <int> vecRand;
    srand((unsigned int)time(NULL));
    int randno;
    while(1)
    {
        randno=rand()%vecQues.size();

        if(ispresent(vecRand,randno)==true)
        {
            continue;
        }
        vecRand.push_back(randno);
        if(vecRand.size()==vecQues.size())
            break;

    }
    int count=0;
    User userObj;
    int local_marks=0;
    int local_tot_marks=0;
    string name=userObj.getName(id);
    for(int i=0;i<vecQues.size();i++)
    {
        int index=vecRand.at(i);
        *this=vecQues.at(index);
        clrscr();
        gotoxy(37,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APP";
        textcolor(YELLOW);
        gotoxy(1,3);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(50,5);
        cout<<name;
        gotoxy(10,5);
        cout<<"TOTAL QUESTION: "<<vecQues.size()<<endl;
        gotoxy(1,6);
        textcolor(YELLOW);
        for(int j=1;j<=80;j++)
            cout<<"*";
        textcolor(GREEN);
        gotoxy(1,8);
        count++;
        cout<<count<<")";
        gotoxy(4,8);
        cout<<this->ques<<endl<<endl;
        textcolor(LIGHTGRAY);
        cout<<"a."<<this->op1<<endl<<endl;
        cout<<"b."<<this->op2<<endl<<endl;
        cout<<"c."<<this->op3<<endl<<endl;
        cout<<"d."<<this->op4<<endl<<endl;
        bool valid;
        char uans;

        do
        {
            textcolor(YELLOW);
            cout<<"Enter your option(a/b/c/d):  \b";
            cin>>uans;
            if(uans>='a'&&uans<='d')
                valid=true;
            else
            {
                valid=false;
                gotoxy(24,22);
                textcolor(LIGHTRED);
                cout<<"Invalid option entered. Try again";
                getch();
                gotoxy(24,22);
                cout<<"\t\t\t\t\t\t\t\t\t\t\t";
                gotoxy(1,18);

            }
        }while(valid==false);
        local_tot_marks+=this->tot_marks;
        if(uans==this->ans)
            local_marks+=this->tot_marks;

    }
    clrscr();
    gotoxy(37,2);
    textcolor(LIGHTRED);
    cout<<"QUIZ APP";
    textcolor(YELLOW);
    gotoxy(1,4);
    for(int i=1;i<=80;i++)
        cout<<"*";
    gotoxy(32,10);
    textcolor(LIGHTRED);
    cout<<"** TEST FINISHED **";
    gotoxy(22,12);
    cout<<"Press any key to go back to main menu";
    getch();
    StudentPerformance sp;
    sp.setMarksDetails(id,local_marks,local_tot_marks);


}

bool ispresent(vector<int>& v,int value)
{
    for(int i=0;i<v.size();i++)
    {
       if(v.at(i)==value)
       {
           return true;
       }
    }
    return false;
}
void StudentPerformance::setMarksDetails(string id,int marks, int tot_marks)
{
    strcpy(studid,id.c_str());
    this->marks=marks;
    this->tot_marks=tot_marks;
    saveMarksDetails();

}
void StudentPerformance::saveMarksDetails()
{
    ofstream fout("Performance.bin",ios::app|ios::binary);
    if(!fout)
    {
        gotoxy(1,26);
        textcolor(LIGHTRED);
        cout<<"Error in creating/opening file";
        getch();
        return;
    }
    fout.write((char *)this,sizeof(*this));
    fout.close();

}

void Student::viewPerformance()
{
    StudentPerformance sp;
    sp.show();
    sp.viewDetails(userid);

}
void StudentPerformance::viewDetails(string id)
{
    Student s;
    string name;
    name=s.getName(id);
    gotoxy(7,8);
    cout<<name;
    int row=0;
    ifstream fin("Performance.bin",ios::in|ios::binary);
    while(1)
    {
        fin.read((char *)this,sizeof(StudentPerformance));
        if(fin.eof())
        {
            gotoxy(1,row+13);
            textcolor(YELLOW);
            for(int i=1;i<=80;i++)
                cout<<"-";
            gotoxy(30,row+15);
            textcolor(LIGHTRED);
            cout<<"NO MORE RECORDS";
            break;
        }
        int result=strcmp(this->studid,id.c_str());
        if(result==0)
        {
            row++;
            textcolor(YELLOW);
            gotoxy(1,row+10);
            cout<<row;
            gotoxy(25,row+10);
            cout<<this->marks;
            gotoxy(55,row+10);
            cout<<this->tot_marks;
        }

    }
    fin.close();
    getch();


}
void StudentPerformance::show()
{
    clrscr();
    textcolor(WHITE);

    textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(1,3);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APP";
        textcolor(YELLOW);
        gotoxy(25,5);
        cout<<"***** VIEW REPORT CARD *****";
        gotoxy(1,6);
        for(int i=1;i<=80;i++)
            cout<<"-";
        gotoxy(1,8);
        cout<<"NAME :";
        gotoxy(1,10);
        textcolor(LIGHTGREEN);
        cout<<"S.NO";
        gotoxy(25,10);
        cout<<"MARKS OBTAINED";
        gotoxy(55,10);
        cout<<"TOTAL MARKS";





}

string User::getName(string id)
{
    ifstream fin("Student.bin",ios::in|ios::binary);
    while(1)
    {
        fin.read((char *)this,sizeof(User));
        if(fin.eof())
        {
            cout<<"NO match of record found";
            break;
        }
        int result=strcmp(this->getUserID().c_str(),id.c_str());
        if(result==0)
        {
            return this->uname;
        }

    }
    fin.close();
    return NULL;
}

void Admin::editQuestion()
{
    Question quesObj;
    quesObj.edit();
    clrscr();
}
void Question::edit()
{
    clrscr();
    textcolor(LIGHTGREEN);
    gotoxy(1,1);
    for(int i=1;i<=80;i++)
            cout<<"*";
    gotoxy(1,3);
    for(int i=1;i<=80;i++)
            cout<<"*";
    gotoxy(32,2);
    textcolor(LIGHTRED);
    cout<<"QUIZ APP";
    textcolor(WHITE);
    gotoxy(25,5);
    cout<<"***** EDIT QUESTION *****";
    gotoxy(30,7);
    textcolor(YELLOW);
    cout<<"1. Select Question by slide view  ";
    gotoxy(30,8);
    cout<<"2. Select Question by ID";
    gotoxy(30,9);
    cout<<"3. EXIT";
    gotoxy(32,11);
    cout<<"Enter your choice :";

    int choice;
    gotoxy(53,11);
    cin>>choice;
    switch(choice)
    {
        case 1:
              editBySlideView();
              break;
        case 2:
              editByQuestionID();
              break;
        case 3:
              break;
        default:
              gotoxy(30,15);
              textcolor(LIGHTGREEN);
              cout<<"WRONG CHOICE !!!";
              getch();

    }
    return ;



}
void Question::editBySlideView()
{
    fstream fin("Question.bin",ios::out|ios::in|ios::binary);
    if(!fin)
    {
        clrscr();
        gotoxy(1,10);
        textcolor(LIGHTRED);
        cout<<"No Questions have been added yet!";
        getch();
        return;
    }
    fin.seekg(0,ios::end);
    if(fin.tellg()==0)
    {
        clrscr();
        gotoxy(1,10);
        textcolor(LIGHTRED);
        cout<<"No Questions present in the file!";
        getch();
        return;
    }
    clrscr();
    fin.seekg(0);
    while(1)
    {   clrscr();
        textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(1,3);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APP";
        textcolor(WHITE);
        gotoxy(25,5);
        cout<<"***** EDIT QUESTION  *****";
        gotoxy(1,7);
        textcolor(LIGHTGREEN);
        for(int i=1;i<=80;i++)
            cout<<"*";

        fin.read((char*)this,sizeof(*this));
        if(fin.eof())
        {
            cout<<endl;
            textcolor(LIGHTRED);
            gotoxy(35,10);
            cout<<"NO MORE QUESTIONS PRESENT!";
            getch();
            break;
        }
        else
        {
            show();
            cout<<endl<<endl;
            char editing;
            textcolor(YELLOW);
            gotoxy(1,25);
            cout<<"Do You want to edit ?(Y/N):";

            gotoxy(30,25);
            cin>>editing;
            if(editing=='Y'||editing=='y')
            {


                clrscr();
                textcolor(WHITE);
                gotoxy(58,4);
                cout<<"Press 0 to exit/go back";

                textcolor(LIGHTGREEN);
                gotoxy(1,1);
                for(int i=1;i<=80;i++)
                    cout<<"*";
                gotoxy(1,3);
                for(int i=1;i<=80;i++)
                    cout<<"*";
                gotoxy(32,2);
                textcolor(LIGHTRED);
                cout<<"QUIZ APP";
                textcolor(WHITE);
                gotoxy(25,5);
                cout<<"***** EDIT QUESTION DETAILS *****";
                gotoxy(1,8);
                textcolor(YELLOW);
                string str;
                cout<<"Enter Question:";
                cin.ignore();
                textcolor(WHITE);
                getline(cin,str,'*');
                if(strcmp(str.c_str(),"0")==0)
               {
                    gotoxy(1,24);
                    textcolor(LIGHTRED);
                    //gotoxy(5,20);
                    cout<<"Closing edit question"<<endl;
                    getch();
                    fin.close();
                    return;
               }
                strncpy(this->ques,str.c_str(),499);
                //gotoxy(1,11);
                textcolor(LIGHTGREEN);
                cout<<endl<<"Carries marks:";
                textcolor(YELLOW);
                cin>>this->tot_marks;
                // gotoxy(1,13);
                textcolor(LIGHTGREEN);
                cout<<endl<<"Options"<<endl<<endl;
                //       gotoxy(1,15);
                textcolor(YELLOW);
                cout<<"(a) ";
                textcolor(WHITE);
                cin.ignore();
                getline(cin,str);
                strncpy(this->op1,str.c_str(),99);
                //strcpy(op1,str.c_str());
                //gotoxy(1,16);
                textcolor(YELLOW);
                cout<<"(b) ";
                textcolor(WHITE);
                //cin.ignore();
                getline(cin,str);
                strncpy(this->op2,str.c_str(),99);
                //strcpy(op2,str.c_str());


                //gotoxy(1,17);
                textcolor(YELLOW);
                cout<<"(c) ";
                textcolor(WHITE);
                 //cin.ignore();
                getline(cin,str);
                strncpy(this->op3,str.c_str(),99);
                //strcpy(op3,str.c_str());
                //gotoxy(1,18);
                textcolor(YELLOW);
                cout<<"(d) ";
                textcolor(WHITE);
                 //cin.ignore();
                getline(cin,str);
                strncpy(this->op4,str.c_str(),99);
                //strcpy(op4,str.c_str());
                bool valid=false;
                do
                {
                   textcolor(YELLOW);
                   gotoxy(1,19);
                   cout<<"Enter correct ans(a/b/c/d):  \b";
                   //cout<<"\t\b\b\b\b\b";
                   textcolor(WHITE);
                   cin>>this->ans;

                   if(this->ans>='a'&&this->ans<='d')
                    {
                        valid=true;
                     /* textcolor(LIGHTRED);
                      gotoxy(25,22);
                      cout<<"Invalid option entered! please try again.";
                      getch();*/
                    }
                    else
                   {
                    gotoxy(24,22);
                    textcolor(LIGHTRED);
                    cout<<"Invalid option entered! please try again.";
                    getch();
                    valid=false;

                  }
                 /*gotoxy(25,22);
                  cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
                   getch();*/
                    }while(valid==false);
                    fin.seekg(-1*sizeof(*this),ios::cur);

                    fin.write((char *)this,sizeof(*this));


                    gotoxy(24,22);
                    cout<<"\t\t\t\t\t\t\t";
                    gotoxy(34,22);
                    textcolor(LIGHTGREEN);
                    cout<<"Question edited successfully!";
                    getch();
                    clrscr();


              }


        }
    }
    fin.close();
}




//SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEWSLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW
//SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEWSLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW
//SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEWSLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW
//SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEWSLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW
//SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEWSLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW
//SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEWSLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW
//SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEWSLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW
//SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEWSLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW
//SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEWSLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW
//SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEWSLIDE VIEW SLIDE VIEW SLIDE VIEW SLIDE VIEW


void Question::editByQuestionID()
{
    clrscr();
    textcolor(WHITE);
    gotoxy(58,4);
    cout<<"Press 0 to exit";
    textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(1,3);
        for(int i=1;i<=80;i++)
            cout<<"*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APP";
        textcolor(WHITE);
        gotoxy(25,5);
        cout<<"***** EDIT QUESTION DETAILS *****";

        fstream fin("Question.bin",ios::out|ios::in|ios::binary);
        if(!fin)
        {
         gotoxy(35,10);
         textcolor(LIGHTRED);
         cout<<"Sorry file cannot be opened!";
         getch();
         return;
        }
        fin.seekg(0,ios::end);
        if(fin.tellg()==0)
        {
            gotoxy(35,10);
         textcolor(LIGHTRED);
         cout<<"No Question Available for Editing!";
         getch();
         fin.close();
         return;
        }
        getch();
        gotoxy(1,8);
        textcolor(YELLOW);
        cout<<"Enter Question ID:";
        bool found=false,valid;
        int id;
        //ofstream fout("temp.bin",ios::out|ios::binary|ios::trunc);
        //if(!fout)
        //{
           //gotoxy(35,10);
         //textcolor(LIGHTRED);
         //cout<<"Sorry! Editing not possible!";
         //getch();
         //fin.close();
         //return;
        //}
        fin.seekg(0);
        do{
            valid=true;
            cin>>id;
            if(id==0)
            {
                fin.close();
                //fout.close();
                //remove("temp.bin");
                return;
            }
            if(id<0)
            {
                valid=false;
                 gotoxy(1,24);
                 textcolor(LIGHTRED);
                 cout<<"\t\t\t\t\t\t\t\t\rInvalid Question ID";
                 getch();
                 gotoxy(19,8);
                 cout<<"\t\t\t\t\t\t\t";
                 gotoxy(19,8);
                 textcolor(WHITE);


            }
            else
            {
                while(true)
                {
                  fin.read((char*)this,sizeof(*this));
                  if(fin.eof())
                        break;
                  if(this->quesid==id)
                  {
                      found=true;
                        clrscr();
                        textcolor(WHITE);
                        gotoxy(58,4);
                        cout<<"Press 0 to exit/go back";

                        textcolor(LIGHTGREEN);
                        gotoxy(1,1);
                        for(int i=1;i<=80;i++)
                            cout<<"*";
                        gotoxy(1,3);
                        for(int i=1;i<=80;i++)
                            cout<<"*";
                        gotoxy(32,2);
                        textcolor(LIGHTRED);
                        cout<<"QUIZ APP";
                        textcolor(WHITE);
                        gotoxy(25,5);
                        cout<<"***** EDIT QUESTION DETAILS *****";
                        gotoxy(1,8);
                        textcolor(YELLOW);
                        string str;
                        cout<<"Enter Question:";
                        cin.ignore();
                        textcolor(WHITE);
                         getline(cin,str,'*');
                         if(strcmp(str.c_str(),"0")==0)
                        {
                             gotoxy(1,24);
                             textcolor(LIGHTRED);
                             //gotoxy(5,20);
                             cout<<"Closing edit question"<<endl;
                             getch();
                             fin.close();
                             return;
                        }
                         strncpy(this->ques,str.c_str(),499);
                        //gotoxy(1,11);
                        textcolor(LIGHTGREEN);
                        cout<<endl<<"Carries marks:";
                        textcolor(YELLOW);
                        cin>>this->tot_marks;
                        // gotoxy(1,13);
                        textcolor(LIGHTGREEN);
                        cout<<endl<<"Options"<<endl<<endl;
                        //       gotoxy(1,15);
                        textcolor(YELLOW);
                        cout<<"(a) ";
                        textcolor(WHITE);
                        cin.ignore();
                        getline(cin,str);
                        strncpy(this->op1,str.c_str(),99);
                        //strcpy(op1,str.c_str());
                        //gotoxy(1,16);
                        textcolor(YELLOW);
                        cout<<"(b) ";
                        textcolor(WHITE);
                        //cin.ignore();
                        getline(cin,str);
                        strncpy(this->op2,str.c_str(),99);
                        //strcpy(op2,str.c_str());


                         //gotoxy(1,17);
                         textcolor(YELLOW);
                         cout<<"(c) ";
                         textcolor(WHITE);
                          //cin.ignore();
                         getline(cin,str);
                         strncpy(this->op3,str.c_str(),99);
                                 //strcpy(op3,str.c_str());
                                 //gotoxy(1,18);
                                 textcolor(YELLOW);
                        cout<<"(d) ";
                        textcolor(WHITE);
                         //cin.ignore();
                        getline(cin,str);
                        strncpy(this->op4,str.c_str(),99);
                        //strcpy(op4,str.c_str());
                        bool valid=false;
                        do
                        {
                           textcolor(YELLOW);
                           gotoxy(1,19);
                           cout<<"Enter correct ans(a/b/c/d):  \b";
                           //cout<<"\t\b\b\b\b\b";
                           textcolor(WHITE);
                           cin>>this->ans;

                           if(this->ans>='a'&&this->ans<='d')
                           {
                               valid=true;
                            /* textcolor(LIGHTRED);
                             gotoxy(25,22);
                           cout<<"Invalid option entered! please try again.";
                           getch();*/
                          }
                         else
                         {
                            gotoxy(24,22);
                            textcolor(LIGHTRED);
                            cout<<"Invalid option entered! please try again.";
                            getch();
                            valid=false;

                        }
                        /*gotoxy(25,22);
                        cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
                         getch();*/
                          }while(valid==false);
                          fin.seekg(-1*sizeof(*this),ios::cur);

                          fin.write((char *)this,sizeof(*this));


                          gotoxy(24,22);
                         cout<<"\t\t\t\t\t\t\t";
                         gotoxy(34,22);
                         textcolor(LIGHTGREEN);
                         cout<<"Question edited successfully!";
                         getch();


                      continue;
                  }
                  else{
                    //fout.write((char*)this,sizeof(*this));
                  }
                }
                //fout.close();
                fin.close();

            }
        }while(valid==false);
}

