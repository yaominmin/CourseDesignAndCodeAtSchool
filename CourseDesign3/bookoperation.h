#ifndef BOOKOPERATION_H
#define BOOKOPERATION_H
#include "book.h"
#include <qdatetime.h>
class BookOperation :public Book
{
public:
    BookOperation();
private:
    int bookListID;
    QString state;//ture代表归还,false代表为归还
    QDateTime returnDate;
public:
    QString getstate();
    QDateTime getreturnDate();
    void setstate(QString State);
    void setreturnDate(QDateTime ReturnDate);
    void borrowBook(QString ReaderID);
    void ReturnBook(QString ReaderID,QString ISBN);
    int getBookListID();
    void setBookListID(int bookListID);
};

#endif // BOOKOPERATION_H
