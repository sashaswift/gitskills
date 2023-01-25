#include "card_service.h"
#include "card_files.h"
#include "billing_service.h"
/*int addCard(struct Card card){
      if(savecard(card)){
        return 1;
      }
      return 0;
}*/
void initCardList(){
    cardlist=NULL;
    head=NULL;
}
int getcard(){
  /* long n;
   n=getcardcount();
   if(n){
   cardlist=malloc((sizeof(List))*n);
   head=malloc((sizeof(List))*n);
   }
   else{
    return 0;
   }*/
   if(readcard()==0){
    return 0;
   }
   //printf("debug");
   return 1;
}
/*listp querycard(char *num){
    listp cardlis;
    cardlis=head;
    //cardlist=head;
    //printf("%s",cardlis->t.num);
    if(getcard()!=0){
        while(cardlis!=NULL){
           if(strcmp(cardlis->t.num,num)==0&&(cardlist->t.del!=1)){
            return cardlis;
           }
           cardlis=cardlis->next;
        }
    }
    return NULL;
}*/
listp checkout(const char*pName,const char*pPn,listp cCard){
    if(strcmp(cCard->t.num,pName)==0&&strcmp(cCard->t.pn,pPn)==0){
            return cCard;
    }
    /*else{
        cCard=cCard->next;
        return cCard;
    }*/
    return NULL;
}
/*void releaseCardList(){
    free(cardlist);
    free(head);
}*/
/*listp dologon(const char*pName,const char*pPn){
    listp cardlis2,cardlis3;
    cardlis2=head;
    Billing bill;
    long n=1;
    //printf("debug2");
    if(getcard()!=0){
        while(cardlis2!=NULL){
            /*if(strcmp(cardlis2->t.num,pName)==0){
                if(strcmp(cardlis2->t.pn,pPn)==0&&cardlis2->t.status==0&&cardlis2->t.rest>0){
                    cardlis2->t.status=1;
                    cardlis2->t.last=time(NULL);
                 if(updateCard(cardlis2,n)){
                    return cardlis2;
                 }
                }
                return NULL;
            }
            cardlis2=cardlis2->next;
            n++;
        }*/
        //printf("debug4");
        /*cardlis3=checkout(pName,pPn,cardlis2);
        if(cardlis3!=NULL){
            if(cardlis3->t.status==0&&cardlis3->t.rest>0){
                    strcpy(bill.aCardName,cardlis3->t.num);
                    bill.tStart=time(NULL);
                    bill.tEnd=bill.tStart;
                    bill.fAmount=0;
                    bill.nStatus=0;
                    bill.nDel=0;
                    if(addBilling(bill)==0){
                        return NULL;
                    }
                cardlis3->t.status=1;
                cardlis3->t.last=time(NULL);
                if(updateCard(cardlis3,n)){
                    return cardlis3;
                }
            }
            else{
                return NULL;
            }
        }
        else{
        cardlis2=cardlis2->next;
        n++;
        }
    }
}
    //printf("debug5");
    return NULL;
}*/
/*listp checkout(const char*pName,const char*pPn,listp cCard){
    if(strcmp(cCard->t.num,pName)==0&&strcmp(cCard->t.pn,pPn)==0){
            return cCard;
    }
    /*else{
        cCard=cCard->next;
        return cCard;
    }
    return NULL;
}*/

