#ifndef SEARCHBYAUTHOR_H
#define SEARCHBYAUTHOR_H
#include "searchBook.h"
#include "dboperation.h"

using namespace std;

class SearchByAuthor:public SearchBook
{
public:
    //构造函数，初始化author变量
    SearchByAuthor(QString author);
    SearchByAuthor();
    //搜索函数，用author搜索书籍
    int search(QString author,Book * book[],int& size);

    //设置author值
    void setAuthor(QString author);
    QString getAuthor();

private:
    QString author;

};
#endif // SEARCHBYAUTHOR_H
