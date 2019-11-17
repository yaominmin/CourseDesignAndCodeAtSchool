#ifndef DBOPERATION_H
#define DBOPERATION_H

#include <QString>
#include <QDateTime>
#include"bookoperation.h"
#include"librarian.h"


    void dboperation();
    bool execSQLQuery(QString sql);
    //增加一行读者信息
    bool addReaderRow(QString userID, QString name, QString gender,QString dept,
                      QString type,QString status);
    //增加一行图书管理员的信息
    bool addLibrarianRow(QString userID, QString password,QString name, QString gender);
    //增加一行书籍信息
    bool addBookRow(QString ISBN,
                    QString bookname,QString author,QString publisher,
                    QString introduction, QString keyword,
                    int collectionnum,int available);
    //增加一行读者借书单信息
    bool addReaderBookListRow(QString userID,QString ISBN,QString state,QDateTime duetime);

    //删除表中的一行记录，只需传进来主键，即可删除对应的记录
    bool delReader(QString userID);
    bool delLibrarian(QString userID);
    bool delBook(QString ISBN);
    //读者借书单一旦生成就不会删除，只会更改借书单的状态，来表示书是否归还。
    //bool delReaderBookList();

    //更新读者信息
    bool updateReader(QString userID, QString name, QString gender,QString dept,
                      QString type,QString status);

    //可以更新图书管理员的密码
    bool updateLibPwd(QString userID, QString password);
    //可以更新图书管理员的姓名
    bool updateLibName(QString userID,QString name);
    //可以更新图书管理员的性别
    bool updateLibGender(QString userID,QString Gender);

    //更新书籍的可借数量
    bool updateBookAvailable(QString ISBN,int available);
    //更新书籍的馆藏数量
    bool updateBookCollectionnum(QString ISBN,int collectionnum);

    //更新读者借书单的状态,归还日期。
    //由于读者的userID和ISBN并不能唯一确定一个书单，所以我们只对未归还的书籍状态做修改
    bool updateReaderBookList(QString userID,QString ISBN,QString state,QDateTime duetime);

    //验证管理员登录,返回错误原因
    //如果验证成功，返回1；如果账号正确，密码错误，返回2 ；如果不存在这个账号，返回0
    int verifyLibLogin(QString userID, QString password);


    //精确查找，只传进一个指针，只查找一个读者。
    bool selectOneReaderID(QString userID,Reader *reader);
    //bool selectOneReaderName(QString name,Reader *reader);
    //检索读者、管理员，输入读者学工号、管理员，结果存到读者对象里。
    //Reader *reader[]指针数组，存储符合结果的对象指针
    //返回i为查找到的项目数量，0则为假
    bool selectReaderID(QString userID,Reader *reader[]);
    bool selectReaderName(QString name,Reader *reader[]);
    bool selectLib(QString userID,Librarian *lib);

    //验证管理员ID是否存在,1表示有这一个ID，0表示操作错误，2表示数据库不存在这个ID
    int selectLibID(QString userID);

    //验证读者ID是否存在,1表示有这一个ID，0表示操作错误，2表示数据库不存在这个ID
    int selectReaderID(QString userID);

    //在数据库中搜索作者为author的书，返回bool值，这四个函数功能相同。
    //Book *book[]指针数组，存储符合结果的对象指针
    //i统计查找到的对象的个数
    bool selectByAuthor(QString author,Book *book[],int &i);
    bool selectByBookName(QString bookName,Book *book[],int &i);
    bool selectByISBN(QString ISBN,Book *book);
    bool selectByPublisher(QString publisher,Book *book[],int &i);

    //返回查询结果的行数
    int searchByISBN(QString isbn,Book *book[]);

    //输入读者学工号，结果存到图书操作对象指针里。
    bool selectReaderBookList(QString userID, BookOperation *bookOperation[], int &i);

    //输入读者学工号，书籍的ISBN号，默认书籍状态是借出，返回书单的ID
    //不支持模糊查找
    int selectRBLID(QString userID,QString ISBN);

    //三表联合查询，查找出读者的详细信息和书籍的详细信息，返回i,表示搜索到的记录行数。
    int selectRBL(QString userID,BookOperation *bookOperation[],Book *book[],Reader *reader[]);

    //返回书单状态,不为空，则为书单状态，为空，则表示错误
    QString selectRBLState(int bookListID);

    //统计已经借阅的数量，返回SQL语句执行是否正确
    bool borrowNum(QString userID, int &i);



#endif
