#include <doublelinklist.h>
#include <stdio.h>



DuLinkList GetElemP_DuL(DuLinkList va, int i) {
  // va为双向链表的头指针。
  // 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
  DuLinkList p;
  p = va->next;
  int j = 1;  // 初始化，p指向第一个结点，j为计数器
  while (p!=va && j<i) { //顺指针向后查找，直到p指向第i个元素或p为空
    p = p->next;
    ++j;
  }
  if (p==va && j<i) return NULL;  // 第i个元素不存在
  else return p;
} // GetElem_DUL

Status ListInsert_DuL(DuLinkList &L, int i, QString num, float price, QString start,
                      QString arrive, int count, int min, int sec) {
  // 在带头结点的双链循环线性表L的第i个元素之前插入这些航班信息，
  // i的合法值为1≤i≤表长+1。返回插入的状态，成功为OK；不成功为ERROR；
  DuLinkList p,s;
  if (!(p = GetElemP_DuL(L, i)))  // 在L中确定第i个元素的位置指针p
    return ERROR;                 // p=NULL, 即第i个元素不存在
  if (!(s = (DuLinkList)malloc(sizeof(DuLNode)))) //分配内存
    return ERROR;
  s->num = num;
  s->price = price;
  s->start = start;
  s->arrive = arrive;
  s->count = count;
  s->min = min;
  s->sec = sec;
  //数据赋值
  s->prior = p->prior;
  p->prior->next = s;
  s->next = p;
  p->prior = s;
  //修改指针
  return OK;
} // ListInsert_DuL

PassengerNode PassengerGetElemP_DuL(PassengerNode va, int i){
    // va为双向链表的头指针。
    // 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
    PassengerNode p;
    p = va->next;
    int j = 1;  // 初始化，p指向第一个结点，j为计数器
    while (p!=va && j<i) { //顺指针向后查找，直到p指向第i个元素或p为空
      p = p->next;
      ++j;
    }
    if (p==va && j<i) return NULL;  // 第i个元素不存在
    else return p;
}//PassengerGetElemP_DuL

Status PassengerListInsert_DuL(PassengerNode &L, int i, QString name, QString id, float money,
                               QString airnum, int sex, QString phone){
    // 在带头结点的双链循环线性表L的第i个元素之前插入这些乘客，会员信息，
    // i的合法值为1≤i≤表长+1。返回插入的状态，成功为OK；不成功为ERROR；
    PassengerNode p,s;
    if (!(p = PassengerGetElemP_DuL(L, i)))  // 在L中确定第i个元素的位置指针p
      return ERROR;                 // p=NULL, 即第i个元素不存在
    if (!(s = (PassengerNode)malloc(sizeof(Passenger)))) //分配内存
      return ERROR;
    s->name = name;
    s->id = id;
    s->money = money;
    s->airnum = airnum;
    s->sex = sex;
    s->phone = phone;
    //数据赋值
    s->prior = p->prior;
    p->prior->next = s;
    s->next = p;
    p->prior = s;
    //修改指针
    return OK;
}//PassengerListInsert_DuL

//DuLinkList GetElemP_DuL(DuLinkList va, int i) {
//  // va为带头结点的循环链表的头指针。
//  // 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
//  DuLinkList p;
//  p = va->next;
//  int j = 1;  // 初始化，p指向第一个结点，j为计数器
//  while (p!=va && j<i) {  //顺指针向后查找，直到p指向第i个元素或p为空
//    p = p->next;
//    ++j;
//  }
//  if (p==va || j<i) return NULL;  // 第i个元素不存在
//  else return p;
//} // GetElem_DUL

Status ListDelete_DuL(DuLinkList &L, int i) {
  // 删除带头结点的双链循环线性表L的第i个元素（航班信息），
  //i的合法值为1≤i≤表长，成功为OK；不成功为ERROR；
  DuLinkList p;
  if (!(p = GetElemP_DuL(L, i)))  // 在L中确定第i个元素的位置指针p
    return ERROR;                 // p=NULL, 即第i个元素不存在
  p->prior->next = p->next;
  p->next->prior = p->prior;
  free(p);
  return OK;
} // ListDelete_DuL

Status PassengerListDelete_DuL(PassengerNode &L, int i){
    // 删除带头结点的双链循环线性表L的第i个元素（乘客会员信息），
    //i的合法值为1≤i≤表长，成功为OK；不成功为ERROR；
    PassengerNode p;
    if (!(p = PassengerGetElemP_DuL(L, i)))  // 在L中确定第i个元素的位置指针p
      return ERROR;                 // p=NULL, 即第i个元素不存在
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return OK;
}
