#ifndef USER_H
#define USER_H

#include <QString>
#include "searchBook.h"
using namespace std;

class User
{
public:
    //构造函数初始化userID、name、gender
    User(QString userID,QString name,QString gender);
    User();
    //登录函数，验证id和密码
    //验证管理员登录,返回错误原因
    //如果验证成功，返回1；如果账号正确，密码错误，返回2 ；如果不存在这个账号，返回0
    int login(QString userID,QString password);
    void setName(QString name);
    void setGender(QString gender);
    void setUserID(QString userID);
    QString getName();
    QString getGender();
    QString getUserID();

private:
    QString userID;
    QString name;
    QString gender;
};
#endif // USER_H
