#include "searchbybookname.h"

using namespace std;

SearchByBookName::SearchByBookName(QString bookName)
{
    this->setBookName(bookName);
}
SearchByBookName::SearchByBookName()
    :SearchBook()
{

}
int SearchByBookName::search(QString bookName,Book * book[],int& size)
{
    bookName.insert(0,"%");
    bookName.append("%");
    if(!selectByBookName(bookName,book,size))
    {
        return 0;
    }
    else
        return 1;

}

void SearchByBookName::setBookName(QString bookName)
{
    this->bookName = bookName;
}

QString SearchByBookName::getBookName()
{
    return bookName;
}
