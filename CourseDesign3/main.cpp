#include "first.h"
#include <QApplication>
#include "dboperation.h"
#include "librarian.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dboperation();
    First q;
    q.show();


//    BookOperation *bookOperation[100];
//    for(int i=0;i<100;i++)
//    {
//        bookOperation[i]=new BookOperation();
//    }
//    Book *book[100];
//    for(int i=0;i<100;i++)
//    {
//        book[i]=new Book();
//    }
//    Reader *reader[100];
//    for(int i=0;i<100;i++)
//    {
//        reader[i]=new Reader();
//    }
//    QString userID ="170720231";
//    Librarian *lib = new Librarian();
//    lib->searchRBL(userID,bookOperation,book,reader);
    //qDebug()<<row;

//    int row =selectRBL(userID,bookOperation,book,reader);
//    qDebug()<<row;




//    dboperation();



    return a.exec();
}
