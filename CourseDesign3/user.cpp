#include <iostream>
#include <QString>
#include "user.h"
#include "dboperation.h"

using namespace std;

User::User(QString userID, QString name, QString gender)
{
    this->setUserID(userID);
    this->setName(name);
    this->setGender(gender);
}
User::User()
{

}
int User::login(QString userID,QString password)
{
    if(verifyLibLogin(userID,password)==1)
        return 1;//success
    if(verifyLibLogin(userID,password)==2)
        return 2;//password wrong
    if(verifyLibLogin(userID,password)==0)
        return 0;//userID not exist
    else
        return 3;//unknown error
}


void User::setGender(QString gender)
{
    this->gender = gender;
}

void User::setName(QString name)
{
    this->name = name;
}

void User::setUserID(QString userID)
{
    this->userID = userID;
}

QString User::getGender()
{
    return gender;
}

QString User::getName()
{
    return name;
}

QString User::getUserID()
{
    return userID;
}





