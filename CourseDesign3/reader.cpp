#include "reader.h"
#include <string>

using namespace std;
Reader::Reader()
    :User()
{

}
Reader::Reader(QString userID, QString name, QString gender,
               int maxBorrowNum,QString type,QString dept,QString status,QString borrowHistory)
        :User(userID,name,gender)
{
    this->setMaxNum(maxBorrowNum);
    this->setType(type);
    this->setDept(dept);
    this->setStatus(status);
}
void Reader::setMaxNum(int maxBorrowNum)
{
    this->maxBorrowNum = maxBorrowNum;
}

void Reader::setType(QString type)
{
    this->type = type;
}

void Reader::setDept(QString dept)
{
    this->dept = dept;
}

void Reader::setStatus(QString status)
{
    this->status = status;
}


int Reader::getMaxNum()
{
    return maxBorrowNum;
}

QString Reader::getType()
{
    return type;
}

QString Reader::getDept()
{
    return dept;
}

QString Reader::getStatus()
{
    return status;
}








