#ifndef BOOK_H
#define BOOK_H
#include <QString>
class Book
{
private:
    QString author;
    QString bookName;
    QString publisher;
    QString ISBN;
    QString introduction;
    QString keyword;
    int collectionNum;
    int available;
public:
    QString getAuthor();
    QString getBookName();
    QString getPublisher();
    QString getISBN();
    QString getIntroduction();
    QString getKeyword();
    int getCollectionNum();
    int getAvailable();
    void setAuthor(QString Author);
    void setBookName(QString BookName);
    void setPublisher(QString Publisher);
    void setISBN(QString ISBN);
    void setIntroduction(QString Introduction);
    void setKeyword(QString Keyword);
    void setCollectionNum(int CollectionNum);
    void setAvailable(int Available);
    Book();
};

#endif // BOOK_H
