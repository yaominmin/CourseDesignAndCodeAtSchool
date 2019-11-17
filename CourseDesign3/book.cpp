#include "book.h"

Book::Book()
{

}
QString Book::getAuthor()
{
    return this->author;
}
QString Book::getBookName()
{
    return this->bookName;
}
QString Book::getPublisher()
{
    return this->publisher;
}
QString Book::getISBN()
{
    return this->ISBN;
}
QString Book::getIntroduction()
{
    return this->introduction;
}
QString Book::getKeyword()
{
    return this->keyword;
}
int Book::getCollectionNum()
{
    return this->collectionNum;
}
int Book::getAvailable()
{
    return this->available;
}
void Book::setAuthor(QString Author)
{
    this->author=Author;
}
void Book::setBookName(QString BookName)
{
    this->bookName=BookName;
}
void Book::setPublisher(QString Publisher)
{
    this->publisher=Publisher;
}
void Book::setISBN(QString ISBN)
{
    this->ISBN=ISBN;
}
void Book::setIntroduction(QString Introduction)
{
    this->introduction=Introduction;
}
void Book::setKeyword(QString Keyword)
{
    this->keyword=Keyword;
}
void Book::setCollectionNum(int CollectionNum)
{
    this->collectionNum=CollectionNum;
}
void Book::setAvailable(int Available)
{
    this->available=Available;
}
