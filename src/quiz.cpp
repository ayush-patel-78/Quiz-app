#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include "quiz.h"
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
