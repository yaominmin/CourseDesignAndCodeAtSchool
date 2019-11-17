#include "searchbypublisher.h"

using namespace std;

SearchByPublisher::SearchByPublisher(QString publisher)
{
    this->setPublisher(publisher);
}
SearchByPublisher::SearchByPublisher()
    :SearchBook()
{

}
int SearchByPublisher::search(QString publisher,Book * book[],int& size)
{
    publisher.insert(0,"%");
    publisher.append("%");
    if(!selectByPublisher(publisher,book,size))
    {
        return 0;
    }
    else
        return 1;
}

void SearchByPublisher::setPublisher(QString publisher)
{
    this->publisher = publisher;
}

QString SearchByPublisher::getPublisher()
{
    return publisher;
}
