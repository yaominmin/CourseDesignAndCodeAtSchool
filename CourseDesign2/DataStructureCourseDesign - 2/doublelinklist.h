#ifndef DOUBLELINKLIST_H
#define DOUBLELINKLIST_H

#endif // DOUBLELINKLIST_H
#include <QString>

//目前实现了双链表的查找，增加，删除功能

//双向链表（double linked list）存储机票和会员的信息。动态分配内存
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OK 1
#define INFEASIBLE -1
//#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

typedef struct DuLNode//双向链表储存航班信息
{
    QString num;         //航班号 QString是QT中的一个字符串操作的类。
    float price;         //票价
    QString start;       //起始地
    QString arrive;      //目的地
    int count;           //余票数
    int min,sec;         //时间
    //ElemType  data;
    struct DuLNode *prior;//前一个结点
    struct DuLNode *next; //后一个结点
} DulNode,*DuLinkList;

typedef struct Passenger
{
    QString name;//名字
    QString id;//身份证号
    float money; //资产
    QString airnum;  //航班号
    int sex;   //性别，男1女0
    QString phone; //预留手机号
    struct Passenger *prior;
    struct Passenger *next;
}passenger,*PassengerNode;

DuLinkList GetElemP_DuL(DuLinkList va, int i);
//ListInsert_DuL的辅助函数，查找第i个元素在表中的位置
Status ListInsert_DuL(DuLinkList &L, int i, QString num, float price, QString start,
                      QString arrive,int count,int min, int sec);
//在双链表L中的第i个元素之前插入一个航班信息
PassengerNode PassengerGetElemP_DuL(PassengerNode va, int i);
//PassengerListInsert_DuL的辅助函数，查找第i个元素在表中的位置
Status PassengerListInsert_DuL(PassengerNode &L, int i, QString name,QString id,float money,
                      QString airnum,int sex,QString phone);
//在双链表L中的第i个元素之前插入一个乘客会员的信息
//DuLinkList GetElemP_DuL(DuLinkList va, int i) ;//ListDelete_DuL的辅助函数，查找第i个元素在表中的位置
Status ListDelete_DuL(DuLinkList &L, int i);//删除在双链表L中的第i个元素的航班信息
Status PassengerListDelete_DuL(PassengerNode &L, int i);//删除在双链表L中的第i个元素的乘客信息
