#ifndef LIBRARIAN_H
#define LIBRARIAN_H


#include <QDateTime>
#include "reader.h"
#include "bookoperation.h"
#include <QString>
using namespace std;

class Librarian :public User
{
public:
    //构造函数初始化基类和子类变量
    Librarian(QString userID, QString name, QString gender, QString password);
    Librarian();
    //设置初始化密码函数
    void setPassword(QString password);

    int findBookList(QString reader,BookOperation * bookList[],int &n);
    //返回密码
    QString getPassword();


    //修改密码函数，管理员用此修改密码,0表示修改成功，1表示前后密码不一致，2表示修改失败
    int changePassword(QString userID,QString password,QString passwordAgain);
    //修改管理员姓名，0表示修改成功，1表示姓名有误，2表示修改失败,3表示userID不存在。
    int changeName(QString userID,QString name);
    //修改管理员性别，0表示修改成功，1表示性别有误，2表示修改失败
    int changeGender(QString userID,QString gender);


    //创建读者 0表示创建成功 1表示userID有误，2表示name有误，3表示gender有误，4表示dept有误，
    //5表示type有误，6表示status有误，7表示创建失败
    int createReader(QString userID,QString name, QString gender,QString dept,QString type,QString status);

    //创建一个管理员 0表示创建成功 1表示userID有误，2表示name有误，3表示gender有误，4表示password有误
    //5表示创建失败
    int createLibrarian(QString userID, QString name, QString gender, QString password);

    //创建一本书 0表示创建成功 1表示ISBN号有误 2表示bookName有误 3表示author有误 4表示publisher
    //5表示introduction有误，6表示keyword有误，7表示available有误,8表示创建失败
    int createBook(QString ISBN,
                  QString bookname,QString author,QString publisher,
                  QString introduction, QString keyword,
                  int collectionnum,int available);
    //修改读者信息，0表示修改成功，1表示userID有误，2表示name有误，3表示gender有误，4表示dept有误，5表示type有误，6表示status有误，7表示修改失败
    int changeReaderInfo(QString userID,QString name,QString gender,QString dept,
                         QString type,QString status);
    //修改图书信息,0表示修改成功，1表示ISBN有误，2表示bookName有误，3表示author有误，4表示publisher有误，5表示status有误，6表示介绍有误,7表示馆藏数量有误，8表示可借数量有误，9表示修改失败
    int changeBookInfo(QString ISBN,QString bookName,QString author,QString publisher,
                       QString introduction,QString keyword,int collectionNum,int available);

    //删除读者
    int deleReaderInfo(QString userID);

    //删除管理员信息
    int deleLibrarianInfo(QString userID);

    //为读者续借//0 无此ID,1 无此借阅记录,2成功续借 3图书状态为已归还
    int continueBorrow(QString userID, QString bookID);

    //删除图书信息
    int deleBookInfo(QString ISBN);

    //借书//0 userID错误,1 借阅已满 ,2 无该图书,3 该图书库存为0,4 成功借阅
    int borrowBook(QString userID,QString bookID);
    //还书//0 无此ID,1 无此借阅记录, 2 成功还书
    int returnBook(QString userID,QString bookID);
    bool isRightUserID(QString userID);
    bool isRightName(QString name);
    bool isRightGender(QString gender);
    bool isRightPassword(QString password);

    //0表示状态错误 1表示正常状态 2表示锁定状态
    int recognizeStatus(QString status);

    //0表示类型错误  1表示计算机  2表示软件
    int recognizeDept(QString dept);

    //0表示类型错误  1表示学生类型 2表示老师类型
    int recognizeType(QString type);

    //返回0表示有错,返回1表示正确，传参1表示检测字符串长度是否是9，传参2表示检测字符串长度是否是13
    //传参3表示检测字符串长度是否小于等于50，传参4表示检测字符串长度是否小于等于1000
    int isRightLength(QString text,int n);

    //查找成功返回1，查找失败返回0，
    int selectReaderByID(QString userID,Reader *reader[]);
    int selectReaderByName(QString name,Reader *reader[]);

    //查找出读者借书的详细信息和书籍的详细信息,return i,表示搜索到的记录行数
    int searchRBL(QString userID,BookOperation *bookOperation[],Book *book[],Reader *reader[]);


private:
    QString password;
};
#endif // LIBRARIAN_H
