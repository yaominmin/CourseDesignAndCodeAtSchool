#include <doublelinklist.h>
#include <stdio.h>



DuLinkList GetElemP_DuL(DuLinkList va, int i) {
  // vaΪ˫�������ͷָ�롣
  // ����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
  DuLinkList p;
  p = va->next;
  int j = 1;  // ��ʼ����pָ���һ����㣬jΪ������
  while (p!=va && j<i) { //˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪ��
    p = p->next;
    ++j;
  }
  if (p==va && j<i) return NULL;  // ��i��Ԫ�ز�����
  else return p;
} // GetElem_DUL

Status ListInsert_DuL(DuLinkList &L, int i, QString num, float price, QString start,
                      QString arrive, int count, int min, int sec) {
  // �ڴ�ͷ����˫��ѭ�����Ա�L�ĵ�i��Ԫ��֮ǰ������Щ������Ϣ��
  // i�ĺϷ�ֵΪ1��i�ܱ�+1�����ز����״̬���ɹ�ΪOK�����ɹ�ΪERROR��
  DuLinkList p,s;
  if (!(p = GetElemP_DuL(L, i)))  // ��L��ȷ����i��Ԫ�ص�λ��ָ��p
    return ERROR;                 // p=NULL, ����i��Ԫ�ز�����
  if (!(s = (DuLinkList)malloc(sizeof(DuLNode)))) //�����ڴ�
    return ERROR;
  s->num = num;
  s->price = price;
  s->start = start;
  s->arrive = arrive;
  s->count = count;
  s->min = min;
  s->sec = sec;
  //���ݸ�ֵ
  s->prior = p->prior;
  p->prior->next = s;
  s->next = p;
  p->prior = s;
  //�޸�ָ��
  return OK;
} // ListInsert_DuL

PassengerNode PassengerGetElemP_DuL(PassengerNode va, int i){
    // vaΪ˫�������ͷָ�롣
    // ����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
    PassengerNode p;
    p = va->next;
    int j = 1;  // ��ʼ����pָ���һ����㣬jΪ������
    while (p!=va && j<i) { //˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪ��
      p = p->next;
      ++j;
    }
    if (p==va && j<i) return NULL;  // ��i��Ԫ�ز�����
    else return p;
}//PassengerGetElemP_DuL

Status PassengerListInsert_DuL(PassengerNode &L, int i, QString name, QString id, float money,
                               QString airnum, int sex, QString phone){
    // �ڴ�ͷ����˫��ѭ�����Ա�L�ĵ�i��Ԫ��֮ǰ������Щ�˿ͣ���Ա��Ϣ��
    // i�ĺϷ�ֵΪ1��i�ܱ�+1�����ز����״̬���ɹ�ΪOK�����ɹ�ΪERROR��
    PassengerNode p,s;
    if (!(p = PassengerGetElemP_DuL(L, i)))  // ��L��ȷ����i��Ԫ�ص�λ��ָ��p
      return ERROR;                 // p=NULL, ����i��Ԫ�ز�����
    if (!(s = (PassengerNode)malloc(sizeof(Passenger)))) //�����ڴ�
      return ERROR;
    s->name = name;
    s->id = id;
    s->money = money;
    s->airnum = airnum;
    s->sex = sex;
    s->phone = phone;
    //���ݸ�ֵ
    s->prior = p->prior;
    p->prior->next = s;
    s->next = p;
    p->prior = s;
    //�޸�ָ��
    return OK;
}//PassengerListInsert_DuL

//DuLinkList GetElemP_DuL(DuLinkList va, int i) {
//  // vaΪ��ͷ����ѭ�������ͷָ�롣
//  // ����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
//  DuLinkList p;
//  p = va->next;
//  int j = 1;  // ��ʼ����pָ���һ����㣬jΪ������
//  while (p!=va && j<i) {  //˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪ��
//    p = p->next;
//    ++j;
//  }
//  if (p==va || j<i) return NULL;  // ��i��Ԫ�ز�����
//  else return p;
//} // GetElem_DUL

Status ListDelete_DuL(DuLinkList &L, int i) {
  // ɾ����ͷ����˫��ѭ�����Ա�L�ĵ�i��Ԫ�أ�������Ϣ����
  //i�ĺϷ�ֵΪ1��i�ܱ����ɹ�ΪOK�����ɹ�ΪERROR��
  DuLinkList p;
  if (!(p = GetElemP_DuL(L, i)))  // ��L��ȷ����i��Ԫ�ص�λ��ָ��p
    return ERROR;                 // p=NULL, ����i��Ԫ�ز�����
  p->prior->next = p->next;
  p->next->prior = p->prior;
  free(p);
  return OK;
} // ListDelete_DuL

Status PassengerListDelete_DuL(PassengerNode &L, int i){
    // ɾ����ͷ����˫��ѭ�����Ա�L�ĵ�i��Ԫ�أ��˿ͻ�Ա��Ϣ����
    //i�ĺϷ�ֵΪ1��i�ܱ����ɹ�ΪOK�����ɹ�ΪERROR��
    PassengerNode p;
    if (!(p = PassengerGetElemP_DuL(L, i)))  // ��L��ȷ����i��Ԫ�ص�λ��ָ��p
      return ERROR;                 // p=NULL, ����i��Ԫ�ز�����
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return OK;
}
