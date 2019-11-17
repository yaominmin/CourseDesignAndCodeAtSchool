#include "dboperation.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QTextCodec>
#include <QTableWidget>
#include <QVariant>
#include <QObject>

void dboperation()
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
        //connect database
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("106.14.164.202");
    db.setPort(3306);
    db.setDatabaseName("course_design_3");
    db.setUserName("root");
    db.setPassword("ymm@170720231");
        //open database
    if (!db.open()) {
        QMessageBox::critical(nullptr, "Cannot open database",
                                  "Unable to establish a database connection.",
                                  QMessageBox::Cancel);
        }
        //Set Character-Set. char set must be utf-8
    db.exec("set NAMES 'UTF-8'");
}

bool execSQLQuery(QString sql){
    QSqlQuery sqlquery;
    if(sqlquery.exec(sql))
        return true;
    else
        return false;
}

    //增加一行读者信息
bool addReaderRow(QString userID, QString name, QString gender,QString dept,
                               QString type,QString status){
    QSqlQuery sqlquery;
    sqlquery.prepare("INSERT INTO READER VALUES(?,?,?,?,?,?)");
    sqlquery.addBindValue(userID);
    sqlquery.addBindValue(name);
    sqlquery.addBindValue(gender);
    sqlquery.addBindValue(dept);
    sqlquery.addBindValue(type);
    sqlquery.addBindValue(status);
    if(sqlquery.exec())
        return true;
    else
        return false;
}
//增加一行图书管理员的信息
bool addLibrarianRow(QString userID, QString password,
                                  QString name, QString gender){
    QSqlQuery sqlquery;
    sqlquery.prepare("INSERT INTO LIBRARIAN VALUES(?,?,?,?)");
    sqlquery.addBindValue(userID);
    sqlquery.addBindValue(password);
    sqlquery.addBindValue(name);
    sqlquery.addBindValue(gender);
    if(sqlquery.exec())
        return true;
    else
        return false;
}
//增加一行书籍信息
bool addBookRow(QString ISBN,
                             QString bookname, QString author, QString publisher,
                             QString introduction, QString keyword,
                             int collectionnum, int available){
    QSqlQuery sqlquery;
    sqlquery.prepare("INSERT INTO BOOK VALUES(:ISBN ,"
                     ":BOOKNAME,:AUTHOR,:PUBLISHER,"
                     ":INTRODUCTION,:KEYWORD,"
                     ":COLLECTIONNUM,:AVAILABLE)");
    sqlquery.bindValue(":ISBN",ISBN);
    sqlquery.bindValue(":BOOKNAME",bookname);
    sqlquery.bindValue(":AUTHOR",author);
    sqlquery.bindValue(":PUBLISHER",publisher);
    sqlquery.bindValue(":INTRODUCTION",introduction);
    sqlquery.bindValue(":KEYWORD",keyword);
    sqlquery.bindValue(":COLLECTIONNUM",collectionnum);
    sqlquery.bindValue(":AVAILABLE",available);
    if(sqlquery.exec())
        return true;
    else
        return false;
}

//增加一行读者借书单信息
bool addReaderBookListRow(QString userID,QString ISBN,
                                       QString state,QDateTime duetime){

    duetime.toString("yyyyMMddhhmmss");//转换成string类型才可以存到数据库里
    QSqlQuery sqlquery;
    sqlquery.prepare("INSERT INTO READERBOOKLIST(R_USERID,ISBN,RBL_STATE,RBL_DUETIME)"
                     "VALUES(:userID,:ISBN,:state,:duetime)");
    sqlquery.bindValue(":userID",userID);
    sqlquery.bindValue(":ISBN",ISBN);
    sqlquery.bindValue(":state",state);
    sqlquery.bindValue(":duetime",duetime);
    if(sqlquery.exec())
        return true;
    else
        return false;
}

//删除表中的一行记录，只需传进来主键，即可删除对应的记录
bool delReader(QString userID){
    QSqlQuery sqlquery;
    sqlquery.prepare("DELETE FROM READER WHERE R_USERID = :userID");
    sqlquery.bindValue(":userID",userID);
    if(sqlquery.exec())
        return true;
    else
        return false;
}
bool delLibrarian(QString userID){
    QSqlQuery sqlquery;
    sqlquery.prepare("DELETE FROM LIBRARIAN WHERE L_USERID = :userID");
    sqlquery.bindValue(":userID",userID);
    if(sqlquery.exec())
        return true;
    else
        return false;
}
bool delBook(QString ISBN){
    QSqlQuery sqlquery;
    sqlquery.prepare("DELETE FROM BOOK WHERE ISBN = :ISBN");
    sqlquery.bindValue(":ISBN",ISBN);
    if(sqlquery.exec())
        return true;
    else
        return false;
}
//读者借书单一旦生成就不会删除，只会更改借书单的状态，来表示书是否归还。
//bool delReaderBookList();

//不存在更新读者信息
//可以更新图书管理员的密码
bool updateLibPwd(QString userID, QString password){
    QSqlQuery sqlquery;
    sqlquery.prepare("UPDATE LIBRARIAN SET L_PASSWORD = :pwd WHERE L_USERID = :userid");
    sqlquery.bindValue(":pwd",password);
    sqlquery.bindValue(":userid",userID);
    if(sqlquery.exec())
        return true;
    else
        return false;
}

//可以更新图书管理员的姓名
bool updateLibName(QString userID,QString name){
    QSqlQuery sqlquery;
    sqlquery.prepare("UPDATE LIBRARIAN SET L_NAME = :name WHERE L_USERID = :userid");
    sqlquery.bindValue(":name",name);
    sqlquery.bindValue(":userid",userID);
    if(sqlquery.exec())
        return true;
    else
        return false;
}

//可以更新图书管理员的性别
bool updateLibGender(QString userID,QString Gender){
    QSqlQuery sqlquery;
    sqlquery.prepare("UPDATE LIBRARIAN SET L_GENDER = :gender WHERE L_USERID = :userid");
    sqlquery.bindValue(":gender",Gender);
    sqlquery.bindValue(":userid",userID);
    if(sqlquery.exec())
        return true;
    else
        return false;
}

//更新书籍的可借数量
bool updateBookAvailable(QString ISBN,int available){
    QSqlQuery sqlquery;
    sqlquery.prepare("UPDATE BOOK SET AVAILABLE = :available WHERE ISBN = :ISBN");
    sqlquery.bindValue(":available",available);
    sqlquery.bindValue(":ISBN",ISBN);
    if(sqlquery.exec())
        return true;
    else
        return false;
}

//更新书籍的馆藏数量
bool updateBookCollectionnum(QString ISBN,int collectionnum){
    QSqlQuery sqlquery;
    sqlquery.prepare("UPDATE BOOK SET COLLECTIONNUM = :collectionnum WHERE ISBN = :ISBN");
    sqlquery.bindValue(":collectionnum",collectionnum);
    sqlquery.bindValue(":ISBN",ISBN);
    if(sqlquery.exec())
        return true;
    else
        return false;
}

//更新读者借书单的状态,归还日期。
//由于读者的userID和ISBN并不能唯一确定一个书单，所以我们只对未归还的书籍状态做修改
bool updateReaderBookList(QString userID,QString ISBN,
                                       QString state,QDateTime duetime){
    duetime.toString("yyyyMMddhhmmss");//先转换成string，然后才可以传到MySQL数据库
    QSqlQuery sqlquery;
    sqlquery.prepare("UPDATE READERBOOKLIST SET RBL_STATE=:state, RBL_DUETIME=:duetime WHERE ISBN=:ISBN and R_USERID=:userID");
    sqlquery.bindValue(":state",state);
    sqlquery.bindValue(":duetime",duetime);
    sqlquery.bindValue(":ISBN",ISBN);
    sqlquery.bindValue(":userID",userID);
    if(sqlquery.exec())
        return true;
    else
        return false;
}

QString selectRBLState(int bookListID){
    QSqlQuery sqlquery;
    sqlquery.prepare("select RBL_STATE from READERBOOKLIST where RBL_ID=?");
    sqlquery.addBindValue(bookListID);
    if(sqlquery.exec()){
        sqlquery.next();
        return sqlquery.value(0).toString();
    }
    else
        return nullptr;
}

//验证管理员登录，
//如果验证成功，返回1；如果账号正确，密码错误，返回2 ；如果不存在这个账号，返回0
int verifyLibLogin(QString userID, QString password){
    QSqlQuery sqlquery;
    sqlquery.exec("SELECT L_USERID,L_PASSWORD FROM LIBRARIAN");
    int signal=0;
    while(sqlquery.next()){
        if(userID==sqlquery.value(0).toString() && password==sqlquery.value(1).toString()){
            signal++;
            return 1;//如果验证成功，返回1
        }
        else if(userID==sqlquery.value(0).toString() && password!=sqlquery.value(1).toString()){
            signal++;
            return 2;//如果账号正确，密码错误，返回2
        }
    }
    if(signal==0){
        return 0;//如果不存在这个账号，返回0
    }
    return 0;//不存在这个账号，返回0
}

bool selectOneReaderID(QString userID,Reader *reader){
    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT * FROM READER WHERE R_USERID=?");
    sqlquery.addBindValue(userID);
    if(!sqlquery.exec()){
        return false;
    }
    if(sqlquery.next()){
        QString id = sqlquery.value(0).toString();
        QString name = sqlquery.value(1).toString();
        QString gender = sqlquery.value(2).toString();
        QString dept = sqlquery.value(3).toString();
        QString type = sqlquery.value(4).toString();
        QString status = sqlquery.value(5).toString();

        reader->setUserID(id);
        reader->setName(name);
        reader->setGender(gender);
        reader->setDept(dept);
        reader->setType(type);
        reader->setStatus(status);
        return true;
    }
    else{
        return  false;
    }
}

bool selectReaderID(QString userID,Reader *reader[]){
    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT * FROM READER WHERE R_USERID LIKE ?");
    sqlquery.addBindValue(userID);
    if(!sqlquery.exec()){
        return false;
    }  
    int i=0;
    while(sqlquery.next()){
        QString id = sqlquery.value(0).toString();
        QString name = sqlquery.value(1).toString();
        QString gender = sqlquery.value(2).toString();
        QString dept = sqlquery.value(3).toString();
        QString type = sqlquery.value(4).toString();
        QString status = sqlquery.value(5).toString();

        reader[i]->setUserID(id);
        reader[i]->setName(name);
        reader[i]->setGender(gender);
        reader[i]->setDept(dept);
        reader[i]->setType(type);
        reader[i]->setStatus(status);
        i++;
    }
    return i;
}
bool selectReaderName(QString name,Reader *reader[]){
    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT * FROM READER WHERE R_NAME LIKE ?");
    sqlquery.addBindValue(name);
    if(!sqlquery.exec()){
        return false;
    }
    int i=0;
    while(sqlquery.next()){
        QString id = sqlquery.value(0).toString();
        QString name = sqlquery.value(1).toString();
        QString gender = sqlquery.value(2).toString();
        QString dept = sqlquery.value(3).toString();
        QString type = sqlquery.value(4).toString();
        QString status = sqlquery.value(5).toString();

        reader[i]->setUserID(id);
        reader[i]->setName(name);
        reader[i]->setGender(gender);
        reader[i]->setDept(dept);
        reader[i]->setType(type);
        reader[i]->setStatus(status);
        i++;
    }
    return i;
}

bool selectLib(QString userID,Librarian *lib){
    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT * FROM LIBRARIAN WHERE L_USERID=?");
    sqlquery.addBindValue(userID);
    if(!sqlquery.exec()){
        return false;
    }
    if(sqlquery.next()){
        QString id = sqlquery.value(0).toString();
        QString pwd = sqlquery.value(1).toString();
        QString name = sqlquery.value(2).toString();
        QString gender = sqlquery.value(3).toString();

        lib->setUserID(id);
        lib->setPassword(pwd);
        lib->setName(name);
        lib->setGender(gender);

        return true;
    }
    else
        return false;

}

int selectLibID(QString userID){
    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT * FROM LIBRARIAN WHERE L_USERID=?");
    sqlquery.addBindValue(userID);
    if(!sqlquery.exec()){
        return 0;//sql语句执行不成功
    }
    if(sqlquery.next()){
        if(sqlquery.value(0).toString() != nullptr)
            return 1;//有这一项
    }
    return 2;//不存在管理员ID
}

int selectReaderID(QString userID){
    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT * FROM READER WHERE L_USERID=?");
    sqlquery.addBindValue(userID);
    if(!sqlquery.exec()){
        return 0;//sql语句执行不成功
    }
    if(sqlquery.next()){
        if(sqlquery.value(0).toString() != nullptr)
            return 1;//有这一项
    }
    else
        return 2;//不存在读者ID
}


//三表联合查询，查找出读者的详细信息和书籍的详细信息

int selectRBL(QString userID, BookOperation *bookOperation[],Book *book[],Reader *reader[]){
    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT  READERBOOKLIST.R_USERID , R_NAME,  READERBOOKLIST.ISBN, BOOKNAME, AUTHOR, PUBLISHER, RBL_STATE, RBL_DUETIME FROM READERBOOKLIST,BOOK,READER WHERE READERBOOKLIST.R_USERID LIKE :userID AND READERBOOKLIST.R_USERID=READER.R_USERID AND READERBOOKLIST.ISBN=BOOK.ISBN");
    sqlquery.bindValue(":userID",userID);
    if(!sqlquery.exec()){
        return 0;
    }
    int i=0;
    //接收select的结果
    while (sqlquery.next()) {
        QString userID = sqlquery.value(0).toString();
        QString name = sqlquery.value(1).toString();
        QString isbn = sqlquery.value(2).toString();
        QString bookname = sqlquery.value(3).toString();
        QString author = sqlquery.value(4).toString();
        QString publisher = sqlquery.value(5).toString();
        QString state = sqlquery.value(6).toString();
        QDateTime dueTime = sqlquery.value(7).toDateTime();

        //将查找到的信息传给bookOperation对象
        reader[i]->setUserID(userID);
        reader[i]->setName(name);
        bookOperation[i]->setISBN(isbn);
        book[i]->setBookName(bookname);
        book[i]->setAuthor(author);
        book[i]->setPublisher(publisher);
        bookOperation[i]->setstate(state);
        bookOperation[i]->setreturnDate(dueTime);

        //i统计查找到的对象的个数
        i++;
    }
    return i;
}

bool selectByAuthor(QString author,Book *book[],int &i){
    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT * FROM BOOK WHERE AUTHOR LIKE ?");
    sqlquery.addBindValue(author);
    if(!sqlquery.exec()){
        return false;
    }
    //接收select的结果
    i=0;
    while (sqlquery.next()) { 
        QString ISBN = sqlquery.value(0).toString();
        QString BOOKNAME = sqlquery.value(1).toString();
        QString AUTHOR = sqlquery.value(2).toString();
        QString PUBLISHER = sqlquery.value(3).toString();
        QString INTRODUCTION = sqlquery.value(4).toString();
        QString KEYWORD = sqlquery.value(5).toString();
        int COLLECTIONNUM = sqlquery.value(6).toInt();
        int AVAILABLE = sqlquery.value(7).toInt();

        //将查找到的信息传给book对象
        book[i]->setISBN(ISBN);
        book[i]->setBookName(BOOKNAME) ;
        book[i]->setAuthor(AUTHOR);
        book[i]->setPublisher(PUBLISHER) ;
        book[i]->setIntroduction(INTRODUCTION);
        book[i]->setKeyword(KEYWORD);
        book[i]->setCollectionNum(COLLECTIONNUM);
        book[i]->setAvailable(AVAILABLE);
        //i统计查找到的对象的个数
        i++;
    }
    return true;
}

bool selectByBookName(QString bookName, Book *book[],int &i){
    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT * FROM BOOK WHERE BOOKNAME LIKE ?");
    sqlquery.addBindValue(bookName);
    if(!sqlquery.exec()){
        return false;
    }
    //接收select的结果
    i=0;
    while (sqlquery.next()) {
        QString ISBN = sqlquery.value(0).toString();
        QString BOOKNAME = sqlquery.value(1).toString();
        QString AUTHOR = sqlquery.value(2).toString();
        QString PUBLISHER = sqlquery.value(3).toString();
        QString INTRODUCTION = sqlquery.value(4).toString();
        QString KEYWORD = sqlquery.value(5).toString();
        int COLLECTIONNUM = sqlquery.value(6).toInt();
        int AVAILABLE = sqlquery.value(7).toInt();

        qDebug()<<ISBN<<BOOKNAME<<AUTHOR<<PUBLISHER<<INTRODUCTION<<KEYWORD;
        qDebug()<<COLLECTIONNUM<<AVAILABLE;

        //将查找到的信息传给book对象
        book[i]->setISBN(ISBN);
        book[i]->setBookName(BOOKNAME) ;
        book[i]->setAuthor(AUTHOR);
        book[i]->setPublisher(PUBLISHER) ;
        book[i]->setIntroduction(INTRODUCTION);
        book[i]->setKeyword(KEYWORD);
        book[i]->setCollectionNum(COLLECTIONNUM);
        book[i]->setAvailable(AVAILABLE);
        //i统计查找到的对象的个数
        i++;
    }
    return true;

}

bool selectByISBN(QString ISBN, Book *book){
    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT * FROM BOOK WHERE ISBN = ?");
    sqlquery.addBindValue(ISBN);
    if(!sqlquery.exec()){
        return false;
    }
    if(sqlquery.next()) {
        QString ISBN = sqlquery.value(0).toString();
        QString BOOKNAME = sqlquery.value(1).toString();
        QString AUTHOR = sqlquery.value(2).toString();
        QString PUBLISHER = sqlquery.value(3).toString();
        QString INTRODUCTION = sqlquery.value(4).toString();
        QString KEYWORD = sqlquery.value(5).toString();
        int COLLECTIONNUM = sqlquery.value(6).toInt();
        int AVAILABLE = sqlquery.value(7).toInt();

//        qDebug()<<ISBN<<BOOKNAME<<AUTHOR<<PUBLISHER<<INTRODUCTION<<KEYWORD;
//        qDebug()<<COLLECTIONNUM<<AVAILABLE;

        //将查找到的信息传给book对象
        book->setISBN(ISBN);
        book->setBookName(BOOKNAME) ;
        book->setAuthor(AUTHOR);
        book->setPublisher(PUBLISHER) ;
        book->setIntroduction(INTRODUCTION);
        book->setKeyword(KEYWORD);
        book->setCollectionNum(COLLECTIONNUM);
        book->setAvailable(AVAILABLE);
        //i统计查找到的对象的个数
        return true;
    }
    else
        return false;
}

int searchByISBN(QString isbn,Book *book[]){
    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT * FROM BOOK WHERE ISBN LIKE ?");
    sqlquery.addBindValue(isbn);
    if(!sqlquery.exec()){
        return 0;
    }
    int i=0;
    while(sqlquery.next()) {
        QString ISBN = sqlquery.value(0).toString();
        QString BOOKNAME = sqlquery.value(1).toString();
        QString AUTHOR = sqlquery.value(2).toString();
        QString PUBLISHER = sqlquery.value(3).toString();
        QString INTRODUCTION = sqlquery.value(4).toString();
        QString KEYWORD = sqlquery.value(5).toString();
        int COLLECTIONNUM = sqlquery.value(6).toInt();
        int AVAILABLE = sqlquery.value(7).toInt();

        //将查找到的信息传给book对象
        book[i]->setISBN(ISBN);
        book[i]->setBookName(BOOKNAME) ;
        book[i]->setAuthor(AUTHOR);
        book[i]->setPublisher(PUBLISHER) ;
        book[i]->setIntroduction(INTRODUCTION);
        book[i]->setKeyword(KEYWORD);
        book[i]->setCollectionNum(COLLECTIONNUM);
        book[i]->setAvailable(AVAILABLE);
        //i统计查找到的对象的个数
        i++;
    }
    return  i;//返回查询结果的行数
}

bool selectByPublisher(QString publisher, Book *book[], int &i){

    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT * FROM BOOK WHERE PUBLISHER LIKE ?");
    sqlquery.addBindValue(publisher);
    if(!sqlquery.exec()){
        return false;
    }
    //接收select的结果
    i=0;
    while (sqlquery.next()) {
        QString ISBN = sqlquery.value(0).toString();
        QString BOOKNAME = sqlquery.value(1).toString();
        QString AUTHOR = sqlquery.value(2).toString();
        QString PUBLISHER = sqlquery.value(3).toString();
        QString INTRODUCTION = sqlquery.value(4).toString();
        QString KEYWORD = sqlquery.value(5).toString();
        int COLLECTIONNUM = sqlquery.value(6).toInt();
        int AVAILABLE = sqlquery.value(7).toInt();

        qDebug()<<ISBN<<BOOKNAME<<AUTHOR<<PUBLISHER<<INTRODUCTION<<KEYWORD;
        qDebug()<<COLLECTIONNUM<<AVAILABLE;

        //将查找到的信息传给book对象
        book[i]->setISBN(ISBN);
        book[i]->setBookName(BOOKNAME) ;
        book[i]->setAuthor(AUTHOR);
        book[i]->setPublisher(PUBLISHER) ;
        book[i]->setIntroduction(INTRODUCTION);
        book[i]->setKeyword(KEYWORD);
        book[i]->setCollectionNum(COLLECTIONNUM);
        book[i]->setAvailable(AVAILABLE);
        //i统计查找到的对象的个数
        i++;
    }
    return true;
}
bool selectReaderBookList(QString userID,BookOperation *bookOperation[],int &i)
{
    QSqlQuery sqlquery;
    sqlquery.prepare("SELECT * FROM READERBOOKLIST WHERE R_USERID=?");
    sqlquery.addBindValue(userID);
    if(!sqlquery.exec()){
        return false;
    }
    //接收select的结果
    i=0;
    while (sqlquery.next()) {
        int bookListID = sqlquery.value(0).toInt();
        QString ISBN = sqlquery.value(2).toString();
        QString state = sqlquery.value(3).toString();
        QDateTime returnDate = sqlquery.value(4).toDateTime();

        //将查找到的信息传给bookOperation对象
        bookOperation[i]->setstate(state);
        bookOperation[i]->setreturnDate(returnDate);
        bookOperation[i]->setISBN(ISBN);
        bookOperation[i]->setBookListID(bookListID);
        //i统计查找到的对象的个数
        i++;
    }
    return true;
}

int selectRBLID(QString userID,QString ISBN){
    QSqlQuery sqlquery;
    QString str = QObject::tr("借出");//借出状态，可翻译
    QString str_2 = QObject::tr("续借");
    sqlquery.prepare("SELECT RBL_ID FROM READERBOOKLIST WHERE R_USERID = ? and ISBN=? "
                     "and RBL_ID in(select RBL_ID from READERBOOKLIST where RBL_STATE=? or RBL_STATE=?)");
    sqlquery.addBindValue(userID);
    sqlquery.addBindValue(ISBN);
    sqlquery.addBindValue(str);
    sqlquery.addBindValue(str_2);
    if(!sqlquery.exec()){
        return 0;
    }
    if(sqlquery.next()){
        int RBLID = sqlquery.value(0).toInt();
        return RBLID;
    }
    else {
        return 0;
    }

}

bool updateReader(QString userID, QString name, QString gender,QString dept,
                  QString type,QString status){
    if(!delReader(userID)){
        return false;
    }
    if(addReaderRow(userID,name,gender,dept,type,status)){
        return true;
    }else{
        return false;
    }
}


bool borrowNum(QString userID, int &i){
    QSqlQuery sqlquery;
    QString str = QObject::tr("借出");//借出状态，可翻译
    QString str_2 = QObject::tr("续借");
    sqlquery.prepare("SELECT * FROM READERBOOKLIST WHERE RBL_STATE=? or RBL_STATE=? "
                     "INTERSECT "
                     "SELECT * FROM READERBOOKLIST WHERE R_USERID=?");
    sqlquery.addBindValue(str);
    sqlquery.addBindValue(str_2);
    sqlquery.addBindValue(userID);
    if(!sqlquery.exec()){
        return false;
    }
    i=0;
    while(sqlquery.next()){
        i++;
    }
    return true;
}

