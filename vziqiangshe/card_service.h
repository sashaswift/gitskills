#ifndef CARD_SERVICE
#define CARD_SERVICE

#include "model.h"
listp cardlist;
listp head;
//listp card1
void initCardList();
 //int addCard(struct Card card);//������Ϣ����ṹ����
void releaseCardList();//�ͷſ���Ϣ����
 int getcard();//���ļ��л�ȡ����Ϣ�����浽������
 //listp querycard(char *num);
// listp dologon(const char*pName,const char*pPn);
 listp checkout(const char*pName,const char *pPn,listp cCard);
#endif // CARD
//#include "model.h"
//List ncard[10000];
//int ncount=0;
/*void addCard(List card);
listp querycard(char *num);*/
