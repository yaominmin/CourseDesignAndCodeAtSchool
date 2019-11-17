#ifndef SEARCHBYBOOKNAME_H
#define SEARCHBYBOOKNAME_H
#include "searchBook.h"
#include "dboperation.h"

using namespace std;

class SearchByBookName:public SearchBook
{
public:
    //构造函数，初始化bookName值
    SearchByBookName(QString bookName);
    SearchByBookName();
    //搜索函数，用bookName搜索图书
    int search(QString bookName,Book * book[],int& size);

    //设置bookName值
    void setBookName(QString bookName);
    QString getBookName();

private:
    QString bookName;

};
#endif // SEARCHBYBOOKNAME_H
