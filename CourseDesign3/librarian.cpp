#include "librarian.h"
#include "dboperation.h"
using namespace std;
#include <QDebug>
Librarian::Librarian(QString userID, QString name, QString gender, QString password)
    :User(userID,name,gender)
{
    this->setPassword(password);

}
Librarian::Librarian()
    :User()
{

}
void Librarian::setPassword(QString password)
{
    this->password = password;
}

QString Librarian::getPassword()
{
    return password;
}

int Librarian::changePassword(QString userID,QString password,QString passwordAgain)
{
    if(password != passwordAgain)
        return 1;
    else
    {
        if(!updateLibPwd(userID,password) || password.size()<=0 || userID.size()<=0)
            return 2;
        else
            return 0;
    }
}

int Librarian::changeName(QString userID,QString name)
{

    if(!isRightLength(name,3))//检测name长度是否有误
        return 1;
    if(!updateLibName(userID,name))
        return 2;
    if(selectLibID(userID)!=1)
        return 3;
    else
        return 0;
}

int Librarian::changeGender(QString userID, QString gender)
{
    if(!isRightLength(gender,0))//检测性别是否有误
        return 1;
    if(!updateLibGender(userID,gender))
        return 2;
    else
        return 0;
}

int Librarian::createReader(QString userID,QString name, QString gender,QString dept,QString type,QString status="正常")
{
    if(!this->isRightLength(userID,1))
        return 1;
    if(!this->isRightLength(name,3))
        return 2;
    if(!this->isRightLength(gender,0))
        return 3;
    if(!this->recognizeDept(dept))
        return 4;
    if(!this->recognizeType(type))
        return 5;
    if(!this->recognizeStatus(status))
        return 6;
    if(!addReaderRow(userID,name,gender,dept,type,status))
        return 7;
    else
       return 0;
}

int Librarian::createLibrarian(QString userID, QString name, QString gender, QString password)

{
    if(!this->isRightLength(userID,1))
        return 1;
    if(!this->isRightLength(name,4))
        return 2;
    if(!this->isRightLength(gender,0))
        return 3;
    if(!this->isRightLength(password,4))
        return 4;
    if(!addLibrarianRow(userID,password,name,gender))
        return 5;
    else
        return 0;

}


int Librarian::createBook(QString ISBN,
              QString bookname,QString author,QString publisher,
              QString introduction, QString keyword,
              int collectionnum,int available)
{
    if(!this->isRightLength(ISBN,2))
        return 1;
    if(!this->isRightLength(bookname,3))
        return 2;
    if(!this->isRightLength(author,3))
        return 3;
    if(!this->isRightLength(publisher,3))
        return 4;
    if(!this->isRightLength(introduction,4))
        return 5;
    if(collectionnum<0)
        return 6;
    if(available>collectionnum)
        return 7;
    if(!addBookRow(ISBN,bookname,author,publisher,introduction,keyword,collectionnum,available))
        return 8;
    else
        return 0;
}

int Librarian::deleLibrarianInfo(QString userID)
{
    if(delLibrarian(userID))
        return 1;//成功，返回1
    else
        return 0;//失败，返回0
}

int Librarian::deleBookInfo(QString ISBN)
{
    if(delBook(ISBN))
        return 1;//成功，返回1
    else
        return 0;//失败，返回0
}
int Librarian::deleReaderInfo(QString userID)
{
    if(delReader(userID))
        return 1;//成功，返回1
    else
        return 0;//失败，返回0
}

int Librarian::continueBorrow(QString userID, QString bookID)
{
    QDateTime a=QDateTime::currentDateTime();
    a=a.addMonths(1);
    Reader * reader=new Reader();
    if(!selectOneReaderID(userID,reader))
        return 0;
    int c=selectRBLID(userID,bookID);
    qDebug()<<c;
    if(selectRBLState(c)=="归还")
        return 3;
    if(updateReaderBookList(userID,bookID,"续借",a))
    qDebug()<<"updateReaderBookList success";//bookID=isbn
    return 2;
}

//int Librarian::borrowBook(QString userID,QString bookID)
//{
//    BookOperation *b=new BookOperation();
//    BookOperation *p[100];
//    Reader * reader=new Reader();
//    if(!selectOneReaderID(userID,reader))
//    return 0;
//    int z;
//    if(reader->getType()=="教师")
//    {
//        z=10;
//    }
//    else
//    {
//        z=5;
//    }
//    for(int i=0;i<100;i++)
//        p[i]=new BookOperation();
//    int n;
//    borrowNum(userID,n);
//    //selectReaderBookList(userID,p,n);
//    if(n==z)
//        return 1;
//    Book * book=new Book();
//    if(!selectByISBN(bookID,book))
//        return 2;
//    if(book->getAvailable()==0)
//        return 3;
//    b->setISBN(bookID);
//    b->borrowBook(userID);
//    updateBookAvailable(bookID,book->getAvailable()-1);
//    return 4;
//}

//不存在该用户，返回0，借阅已满，返回1，库存为0，返回3，借阅成功，返回4
int Librarian::borrowBook(QString userID,QString bookID)
{
    BookOperation *b=new BookOperation();
    Reader * reader=new Reader();
    if(!selectOneReaderID(userID,reader))
        return 0;//不存在该用户，返回0，
    int z;//可借阅数量
    if(reader->getType()=="教师"){
        z=10;
    }else{
        z=5;
    }
    int n;
    borrowNum(userID,n);//n=已借阅数量
    if(n==z)
        return 1;//借阅已满，返回1
    Book * book=new Book();
    if(book->getAvailable()==0)
        return 3;//库存为0，返回3
    b->setISBN(bookID);
    b->borrowBook(userID);
    updateBookAvailable(bookID,book->getAvailable()-1);
    return 4;//借阅成功，返回4
}

//0 无此ID,1 无此借阅记录, 2 成功还书
int Librarian::returnBook(QString userID,QString bookID)
{
    Reader * reader=new Reader();
    if(!selectOneReaderID(userID,reader))
        return 0;
    if(!selectRBLID(userID,bookID))
        return 1;
    Book * book=new Book();
    selectByISBN(bookID,book);
    BookOperation *b=new BookOperation();
    b->ReturnBook(userID,bookID);
    updateBookAvailable(bookID,book->getAvailable()+1);
    return 2;
}

int Librarian::recognizeStatus(QString status)
{
    if(status=="正常")
        return 1;
    else if(status == "锁定")
        return 2;
    else
        return 0;
}

int Librarian::recognizeDept(QString dept)
{
    if(dept=="计算机")
        return 1;
    else if(dept == "软件")
        return 2;
    else if(dept=="计算机学院")
        return  3;
    else if(dept=="软件学院")
        return  4;
    else
        return 0;
}


int Librarian::recognizeType(QString type)
{
    if(type=="学生")
        return 1;
    else if(type == "教师")
        return 2;
    else
        return 0;
}

int Librarian::isRightLength(QString text,int n)//n为0到4从小到大
{
    switch(n)
    {
        case 0:
             if(text!="男"&&text!="女")
                 return 0;
        break;
        case 1:
             if(text.size()!=9)
                 return 0;
        break;
        case 2:
             if(text.size()!=13)
                 return 0;
        break;
        case 3:
             if(text.size()>50||text.size()<=0)
                 return 0;
        break;
        case 4:
             if(text.size()>1000||text.size()<=0)
                 return 0;
        break;

    };
    return 1;
}

int Librarian::findBookList(QString readerID,BookOperation * bookList[],int &n)
{

    selectReaderBookList(readerID,bookList,n);
    if(n==0)
        return 0;
    return 1;
}


int Librarian::changeReaderInfo(QString userID, QString name, QString gender, QString dept,
                                QString type, QString status)
{
    if(!isRightLength(userID,1))
        return 1;
    if(!isRightLength(name,3))
        return 2;
    if(!isRightLength(gender,0))
        return 3;
    if(!recognizeDept(dept))
        return 4;
    if(!recognizeStatus(status))
        return 5;
    if(!isRightLength(type,3))
        return 6;
    if(!updateReader(userID,name,gender,dept,type,status))
        return 7;
    else
        return 0;
}

int Librarian::changeBookInfo(QString ISBN, QString bookName, QString author, QString publisher,
                              QString introduction,QString keyword,int collectionNum,int available)
{
    if(!isRightLength(ISBN,2))
        return 1;
    if(!isRightLength(bookName,3))
        return 2;
    if(!isRightLength(author,3))
        return 3;
    if(!isRightLength(publisher,3))
        return 4;
    if(!isRightLength(introduction,4))
        return 5;
    if(!isRightLength(keyword,3))
        return 6;
    if(collectionNum<0)
        return 7;
    if(available>collectionNum)
        return 8;
    if(deleBookInfo(ISBN))
        qDebug()<<"success";
    else
        qDebug()<<"error";
    if(!addBookRow(ISBN,bookName,author,publisher,introduction,keyword,collectionNum,available))
        return 9;
    else
        return 0;
}
int Librarian::selectReaderByID(QString userID,Reader *reader[]){
    userID.insert(0,"%");
    userID.append("%");
    int i=selectReaderID(userID,reader);
    return i;
}
int Librarian::selectReaderByName(QString name, Reader *reader[]){
    name.insert(0,"%");
    name.append("%");
    int i=selectReaderName(name,reader);
    return i;
}

int Librarian::searchRBL(QString userID,BookOperation *bookOperation[],Book *book[],Reader *reader[]){
    userID.insert(0,"%");
    userID.append("%");
    int i = selectRBL(userID,bookOperation,book,reader);
    return i;
}
