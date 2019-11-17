#ifndef SEARCHBYISBN_H
#define SEARCHBYISBN_H
#include "searchBook.h"
#include "dboperation.h"

using namespace std;

class SearchByISBN:public SearchBook
{
public:
    //构造函数，初始化ISBN值
    SearchByISBN(QString ISBN);
    SearchByISBN();
    //搜索函数，用ISBN号来搜索书籍,精确搜索
    int search(QString ISBN,Book * book);
    //模糊搜索
    int search(QString ISBN,Book * book[]);

    //设置ISBN的值
    void setISBN(QString ISBN);
    QString getISBN();

private:
    QString ISBN;

};
#endif // SEARCHBYISBN_H
