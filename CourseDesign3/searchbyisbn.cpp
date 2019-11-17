#include "searchbyisbn.h"

using namespace std;

SearchByISBN::SearchByISBN(QString ISBN)
{
    this->setISBN(ISBN);
}
SearchByISBN::SearchByISBN()
    :SearchBook()
{

}
int SearchByISBN::search(QString ISBN,Book * book)
{
    if(!selectByISBN(ISBN,book))
    {
        return 0;
    }
    else
        return 1;
}

int SearchByISBN::search(QString ISBN,Book * book[]){
    ISBN.insert(0,"%");
    ISBN.append("%");
    int i=searchByISBN(ISBN,book);
    return i;
}

void SearchByISBN::setISBN(QString ISBN)
{
    this->ISBN = ISBN;
}

QString SearchByISBN::getISBN()
{
    return ISBN;
}
