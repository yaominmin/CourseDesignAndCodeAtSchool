#ifndef SEARCHBYPUBLISHER_H
#define SEARCHBYPUBLISHER_H
#include "searchBook.h"
#include "dboperation.h"

using namespace std;

class SearchByPublisher:public SearchBook
{
public:
    //构造函数，初始化publisher值
    SearchByPublisher(QString publisher);
    SearchByPublisher();
    //搜索函数，用publisher搜索书籍
    int search(QString publisher,Book * book[],int& size);

    //设置publisher值
    void setPublisher(QString publisher);
    QString getPublisher();

private:
    QString publisher;

};
#endif // SEARCHBYPUBLISHER_H
