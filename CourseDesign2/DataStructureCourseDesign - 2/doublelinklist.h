#ifndef DOUBLELINKLIST_H
#define DOUBLELINKLIST_H

#endif // DOUBLELINKLIST_H
#include <QString>

//Ŀǰʵ����˫����Ĳ��ң����ӣ�ɾ������

//˫������double linked list���洢��Ʊ�ͻ�Ա����Ϣ����̬�����ڴ�
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OK 1
#define INFEASIBLE -1
//#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

typedef struct DuLNode//˫�������溽����Ϣ
{
    QString num;         //����� QString��QT�е�һ���ַ����������ࡣ
    float price;         //Ʊ��
    QString start;       //��ʼ��
    QString arrive;      //Ŀ�ĵ�
    int count;           //��Ʊ��
    int min,sec;         //ʱ��
    //ElemType  data;
    struct DuLNode *prior;//ǰһ�����
    struct DuLNode *next; //��һ�����
} DulNode,*DuLinkList;

typedef struct Passenger
{
    QString name;//����
    QString id;//���֤��
    float money; //�ʲ�
    QString airnum;  //�����
    int sex;   //�Ա���1Ů0
    QString phone; //Ԥ���ֻ���
    struct Passenger *prior;
    struct Passenger *next;
}passenger,*PassengerNode;

DuLinkList GetElemP_DuL(DuLinkList va, int i);
//ListInsert_DuL�ĸ������������ҵ�i��Ԫ���ڱ��е�λ��
Status ListInsert_DuL(DuLinkList &L, int i, QString num, float price, QString start,
                      QString arrive,int count,int min, int sec);
//��˫����L�еĵ�i��Ԫ��֮ǰ����һ��������Ϣ
PassengerNode PassengerGetElemP_DuL(PassengerNode va, int i);
//PassengerListInsert_DuL�ĸ������������ҵ�i��Ԫ���ڱ��е�λ��
Status PassengerListInsert_DuL(PassengerNode &L, int i, QString name,QString id,float money,
                      QString airnum,int sex,QString phone);
//��˫����L�еĵ�i��Ԫ��֮ǰ����һ���˿ͻ�Ա����Ϣ
//DuLinkList GetElemP_DuL(DuLinkList va, int i) ;//ListDelete_DuL�ĸ������������ҵ�i��Ԫ���ڱ��е�λ��
Status ListDelete_DuL(DuLinkList &L, int i);//ɾ����˫����L�еĵ�i��Ԫ�صĺ�����Ϣ
Status PassengerListDelete_DuL(PassengerNode &L, int i);//ɾ����˫����L�еĵ�i��Ԫ�صĳ˿���Ϣ
