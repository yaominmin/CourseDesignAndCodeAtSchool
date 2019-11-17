#include "bookoperation.h"
#include<QObject>
#include "dboperation.h"
#include<QDebug>
BookOperation::BookOperation()
    :Book()
{

}
QString BookOperation::getstate()
{
    return this->state;
}
QDateTime BookOperation::getreturnDate()
{
    return this->returnDate;
}
void BookOperation::setstate(QString State)
{
    this->state=State;
}
void BookOperation::setreturnDate(QDateTime ReturnDate)
{
    this->returnDate=ReturnDate;
}
void BookOperation::borrowBook(QString ReaderID)
{
    QDateTime ReturnDate = QDateTime::currentDateTime();
    ReturnDate=ReturnDate.addMonths(1);
    addReaderBookListRow(ReaderID,this->getISBN(),"借出",ReturnDate);
}
int BookOperation::getBookListID()
{
    return this->bookListID;
}
void BookOperation::setBookListID(int bookListID)
{
    this->bookListID=bookListID;
}
void BookOperation::ReturnBook(QString ReaderID,QString ISBN)
{

    QDateTime p=QDateTime::currentDateTime();
    if(updateReaderBookList(ReaderID,ISBN,"归还",p))
        qDebug()<<"success";
    else
        qDebug()<<"fail";
}
