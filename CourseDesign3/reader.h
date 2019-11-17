#ifndef READER_H
#define READER_H


#include "user.h"
#include <QString>
using namespace std;

class Reader:public User
{
public:
    //构造函数，初始化一系列基类子类私有变量
    Reader(QString userID, QString name, QString gender,
           int maxBorrowNum,QString type,QString dept,QString status,QString borrowHistory);
    void setMaxNum(int maxBorrowNum);
    void setType(QString type);
    void setDept(QString dept);
    void setStatus(QString status);
    void setBorrowHistory(QString borrowHistory);
    int getMaxNum();
    QString getType();
    QString getDept();
    QString getStatus();

    Reader();
private:
    int maxBorrowNum;
    QString type;
    QString dept;
    QString status;
};
#endif // READER_H
