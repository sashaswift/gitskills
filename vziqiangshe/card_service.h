#ifndef CARD_SERVICE
#define CARD_SERVICE

#include "model.h"
listp cardlist;
listp head;
//listp card1
void initCardList();
 //int addCard(struct Card card);//将卡信息储存结构体中
void releaseCardList();//释放卡信息链表
 int getcard();//从文件中获取卡信息并保存到链表中
 //listp querycard(char *num);
// listp dologon(const char*pName,const char*pPn);
 listp checkout(const char*pName,const char *pPn,listp cCard);
#endif // CARD
//#include "model.h"
//List ncard[10000];
//int ncount=0;
/*void addCard(List card);
listp querycard(char *num);*/
