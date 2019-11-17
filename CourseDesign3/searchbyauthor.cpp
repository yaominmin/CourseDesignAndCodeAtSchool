#include "searchbyauthor.h"

using namespace std;

SearchByAuthor::SearchByAuthor(QString author)
{
    this->setAuthor(author);
}
 int search(QString author,Book * book[],int& size);
 SearchByAuthor::SearchByAuthor()
     :SearchBook()
 {

 }
int SearchByAuthor::search(QString author,Book * book[],int& size)
{
    //模糊查找
    author.insert(0,"%");
    author.append("%");
    if(!selectByAuthor(author,book,size))
    {
        return 0;
    }
    else
        return 1;
}

void SearchByAuthor::setAuthor(QString author)
{
    this->author = author;
}

QString SearchByAuthor::getAuthor()
{
    return author;
}
