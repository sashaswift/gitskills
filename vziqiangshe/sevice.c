#include "sevice.h"
#include "card_service.h"
#include "card_files.h"
#include "billing_service.h"
#include "billing_files.h"
#include "money.h"
#include "tool.h"
#include "record_files.h"
#include "record_service.h"
#include "rate_files.h"
#include "rate_service.h"
/*listp dologon(const char*pName,const char*pPn){
    listp cardlis2,cardlis3;
    cardlis2=head;
    Billing bill;
    long n=1;
    //printf("debug2");
    if(getcard()!=0){
        while(cardlis2!=NULL){

        //printf("debug4");
        cardlis3=checkout(pName,pPn,cardlis2);
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
int dologon(const char *pName,const char *pPn){
    listp cardlis2;
    //initCardList();
    //listp cardlis3;
    //cardlis2=head;
    Billing bill;
    long n=1;
    //initCardList();
    if(getcard()!=0){
            cardlis2=head;
            cardlist=NULL;
        while(cardlis2!=NULL){
       cardlist=checkout(pName,pPn,cardlis2);
        if(cardlist!=NULL){
            if(cardlist->t.status==0&&cardlist->t.rest>0){
                    strcpy(bill.aCardName,cardlist->t.num);
                    //strcpy(log.aCardName,cardlis3->t.num);
                    bill.tStart=time(0);
                    bill.tEnd=bill.tStart;
                    bill.fAmount=0;
                    bill.nStatus=0;
                    bill.nDel=0;
                    if(addBilling(bill)==0){
                        return FALSE;
                    }
                cardlist->t.status=1;
                cardlist->t.last=time(NULL);
                cardlist->t.times++;
                if(cardlist->t.last>cardlist->t.tEnd){
                    cardlist->t.status=3;
                    cardlist->t.del=1;
                    if(updateCard(cardlist,n)){
                        return OVERTIME;
                    }
                    return OVERTIME;
                }
                if(updateCard(cardlist,n)){
                    return TRUE;
                }
            }
            else if(cardlist->t.status!=0){
                return UNUSE;
            }
            else{
                return ENOUGHMONEY;
            }

        }
        else{
        cardlis2=cardlis2->next;
        n++;
        }
    }
}
   return FALSE;
}
int addCardInfo(struct Card card){
      if(savecard(card)){
        return 1;
      }
      return 0;
}
//listp queryCardInfo(char *num){
//    listp cardlis;
//    initCardList();
//    time_t now;
//    now=time(0);
//    long n=1;
//    //cardlis=head;
//    //printf("%s",head->t.pn);
//    //cardlist=head;
//    //printf("%s",cardlis->t.num);
//    //printf("%s",head->t.pn);
//    //printf("debug2");
//    if(getcard()!=0){
//            cardlis=head;
//            //printf("%s",cardlis->t.num);
//        while(cardlis!=NULL){
//           if(strcmp(cardlis->t.num,num)==0&&(cardlis->t.del==0)){
//               if(cardlis->t.tEnd<now){
//                cardlis->t.status=3;
//                cardlis->t.del=1;
//                if(updateCard(cardlis,n)){
//                    return NULL;
//                }
//                return NULL;
//               }
//            return cardlis;
//           }
//           cardlis=cardlis->next;
//           n++;
//        }
//        //printf("false");
//    }
//    return NULL;
//}
int queryCardInfo(char*num){
    listp cardlis;
    initCardList();
    time_t now;
    now=time(0);
    long n=1;
    int result=0;
    if(getcard()){
        cardlis=head;
        while(cardlis!=NULL){
                if(strstr(cardlis->t.num,num)!=NULL&&(cardlis->t.del==0)){
                     if(cardlis->t.tEnd<now){
                        // printf("debug");
                 cardlis->t.status=3;
                 cardlis->t.del=1;
                     }
                    else{
                        printf("%s\t\t%d\t\t%.2lf\t\t%.2lf\t\t%d\t\t",cardlis->t.num,cardlis->t.status,cardlis->t.rest,cardlis->t.already,cardlis->t.times);
                        stringfortime(cardlis->t.last);
                        printf("\n");
                    }
                    result++;
                }
                cardlis=cardlis->next;
                n++;
        }
    }
    return result;
}
int doSettle(const char*pName,const char*pPn){
    listp cardlis2;
    double amount;
    long n=1;
    IpBillingNode Bill;
    Billing bill;
    if(getcard()!=0){
            cardlis2=head;
            cardlist=NULL;
        while(cardlis2!=NULL){
       cardlist=checkout(pName,pPn,cardlis2);
        if(cardlist!=NULL){
            if(cardlist->t.status==1){
                   Bill=queryBilling(pName);
                   if(Bill!=NULL){
                    amount=getAmount(Bill);
                    if(amount<=cardlist->t.rest){
                         cardlist->t.status=0;
                         Bill->data.tEnd=cardlist->t.last=time(0);
                         cardlist->t.rest-=amount;
                         Bill->data.nStatus=1;
                         Bill->data.fAmount=amount;
                         bill=Bill->data;
                    if(cardlist->t.last>cardlist->t.tEnd){
                    cardlist->t.status=3;
                    cardlist->t.del=1;
                    if(updateCard(cardlist,n)){
                        return OVERTIME;
                    }
                    return OVERTIME;
                }
                         if(updateBilling(bill)==0){
                            return FALSE;
                         }
                         if(updateCard(cardlist,n)){
                                strcpy(Set.aCardName,pName);
                                Set.fAmount=amount;
                                Set.fBalance=cardlist->t.rest;
                                Set.tEnd=Bill->data.tEnd;
                                Set.tStart=Bill->data.tStart;
                            return TRUE;
                         }
                    }
                   }
                   return FALSE;
                }
                return FALSE;
            }
            else{
           cardlis2=cardlis2->next;
           n++;
            }
        }
    }
    return FALSE;
}
double getAmount(IpBillingNode pbill){
     /*IpBillingNode pbill2;
     pbill2=bHead;
     double getamount=0;
     while(pbill2!=NULL){
      if(pbill2->data.tStart==pbill->data.tStart&&strcpy(pbill2->data.aCardName,pbill->data.aCardName)==0){
            getamount+=pbill2->data.fAmount;
      }
        pbill2=pbill2->next;
     }*/
     double getamount=0;
     time_t now;
     now=time(0);
     if(billingstandard.ratetype==0){
     getamount=((now-(pbill->data.tStart))/(billingstandard.unit*60))*(billingstandard.charge);
     }
     else{
        getamount=billingstandard.sum;
     }
     return getamount;
}
/*void releaseList(){
    releaseBillingList();
    releaseCardList();
}*/

int doAddMoney(const char* pName,const char* pPn){
    listp cardlis;
    Money money;
    long n=1;
    if(getcard()!=0){
        cardlis=head;
        cardlist=NULL;
        while(cardlis!=NULL){
            cardlist=checkout(pName,pPn,cardlis);
            if(cardlist!=NULL){
                if(cardlist->t.del==0){
                    cardlist->t.rest+=Moneyinfo.fMoney;
                    cardlist->t.already+=Moneyinfo.fMoney;
                    cardlist->t.last=time(0);
                    strcpy(Moneyinfo.aCardName,pName);
                    Moneyinfo.fBalance=cardlist->t.rest;
                    strcpy(money.aCardName,pName);
                    money.fMoney=Moneyinfo.fMoney;
                    money.nDel=0;
                    money.nStatus=0;
                    money.tTime=cardlist->t.last;
                    if(cardlist->t.last>cardlist->t.tEnd){
                    cardlist->t.status=3;
                    cardlist->t.del=1;
                    if(updateCard(cardlist,n)){
                        return OVERTIME;
                    }
                    return OVERTIME;
                }
                    if(updateCard(cardlist,n)==0){
                        return FALSE;
                    }
                    if(saveMoney(money)){
                        return TRUE;
                    }
                }
                return FALSE;
            }
            else{
                cardlis=cardlis->next;
                n++;
            }
        }
    }
    return FALSE;
}
int doRefundMoney(const char* pName,const char* pPn){
    listp cardlis;
    Money money;
    long n=1;
    if(getcard()!=0){
        cardlis=head;
        cardlist=NULL;
        while(cardlis!=NULL){
            cardlist=checkout(pName,pn,cardlis);
            if(cardlist!=NULL){
                if(cardlist->t.del==0){
                    if(cardlist->t.rest>=0){
                        strcpy(money.aCardName,pName);
                        money.fMoney=cardlist->t.rest;
                        money.nDel=0;
                        money.nStatus=1;
                        cardlist->t.last=money.tTime=time(0);
                        cardlist->t.rest=0;
                        strcpy(Moneyinfo.aCardName,pName);
                        Moneyinfo.fBalance=0;
                        Moneyinfo.fMoney=money.fMoney;
                        if(cardlist->t.last>cardlist->t.tEnd){
                    cardlist->t.status=3;
                    cardlist->t.del=1;
                    if(updateCard(cardlist,n)){
                        return OVERTIME;
                    }
                    return OVERTIME;
                }
                        if(updateCard(cardlist,n)==0){
                            return FALSE;
                        }
                        if(saveMoney(money)){
                            return TRUE;
                        }
                    }
                    return ENOUGHMONEY;
                }
            }
            else{
                n++;
                cardlis=cardlis->next;
            }
        }
    }
    return FALSE;
}
int annulCard(const char*pName,const char*pPn){
    listp cardlis;
    long n=1;
    if(getcard()!=0){
        cardlis=head;
        cardlist=NULL;
        while(cardlis!=NULL){
            cardlist=checkout(pName,pPn,cardlis);
            if(cardlist!=NULL){
                if(cardlist->t.status==1||cardlist->t.status==2){
                    return UNUSE;
                }
                if(cardlist->t.rest<0){
                    return ENOUGHMONEY;
                }
                cardlist->t.rest=0;
                cardlist->t.status=2;
                cardlist->t.del=1;
                cardlist->t.last=time(0);
                if(cardlist->t.last>cardlist->t.tEnd){
                    cardlist->t.status=3;
                    cardlist->t.del=1;
                    if(updateCard(cardlist,n)){
                        return OVERTIME;
                    }
                    return OVERTIME;
                }
                if(updateCard(cardlist,n)){
                    annulinfo.fMoney=0;
                    strcpy(annulinfo.aCardName,pName);
                    return TRUE;
                }
                return FALSE;
            }
            else{
                cardlis=cardlis->next;
                n++;
            }
        }
    }
    return FALSE;
}
int doAddManager(PowerShell powershell){
    if(saveManager(powershell)){
        return TRUE;
    }
    return FALSE;
}
int doLoginManager(char*pName,char*pPn){
    IpPowerShellNode power=NULL;
    //PowerShell Power;
    power=queryManager(pName);
    if(power==NULL){
        return FALSE;
    }
    else if(strcmp(power->date.pn,pPn)==0){
        Power=power->date;
        return TRUE;
    }
    else {
        return FALSE;
    }
}
int doAddBillingStandard(BillingS Billingstandard){
    if(saveBillingStandard(Billingstandard)){
        return TRUE;
    }
    return FALSE;
}
IpBillingSNode doQueryBillingStandard(int ratetype){
     if(getBillingS()){
            Billingslist=Bhead;
        while(Billingslist!=NULL){
            if(Billingslist->data.ratetype==ratetype&&Billingslist->data.del==0){
                return Billingslist;
            }
            Billingslist=Billingslist->next;
        }
     }
     return NULL;
}
int doChangeBillingStandard(BillingS bills){
    if(updateBillingStandard(bills)){
        return TRUE;
    }
    return FALSE;
}
int doChangeManager(char*pName){
    IpPowerShellNode pPower;
    PowerShell newmanager;
    pPower=queryManager(pName);
    if(pPower!=NULL){
    newmanager=pPower->date;
    printf("请输入更改权限（0~4）：");
    scanf("%d",&newmanager.privilige);
    printf("%d",newmanager.privilige);
    if(updateManager(newmanager)){
        return TRUE;
    }
    }
    return FALSE;
}
int doDeleteManager(char*pName){
    IpPowerShellNode pPower;
    PowerShell newmanager;
    pPower=queryManager(pName);
    if(pPower!=NULL){
    newmanager=pPower->date;
    newmanager.del=1;
    if(updateManager(newmanager)){
        return TRUE;
    }
    }
    return FALSE;
}
int doQueryBillingRecord(char*pNum,time_t startdate,time_t enddate){
    IpBillingNode pbill;
    int result=0;
    if(getBilling()){
        pbill=bHead;
        while(pbill!=NULL){
            if(strcmp(pbill->data.aCardName,pNum)==0&&((pbill->data.tEnd>=startdate&&pbill->data.tEnd<=enddate)||(pbill->data.tStart>=startdate&&pbill->data.tStart<=enddate))&&pbill->data.nDel==0){
                printf("卡号\t\t消费金额\t\t上机时间\t\t\t下机时间\n");
                printf("%s\t\t%.2lf\t\t",pbill->data.aCardName,pbill->data.fAmount);
                stringfortime(pbill->data.tStart);
                printf("\t");
                stringfortime(pbill->data.tEnd);
                printf("\n");
                printf("----------------------------------------------\n");
                result=1;
            }
            pbill=pbill->next;
        }
        return result;
    }
    return FALSE;
}
double doSumAmount(time_t startdate,time_t enddate){
    double sumamount=0;
    IpBillingNode pbill;
    if(getBilling()){
        pbill=bHead;
        while(pbill!=NULL){
            if(((pbill->data.tEnd>=startdate&&pbill->data.tEnd<=enddate)||(pbill->data.tStart>=startdate&&pbill->data.tStart<=enddate))&&pbill->data.nDel==0){
                sumamount+=pbill->data.fAmount;
            }
            pbill=pbill->next;
        }
        //return sumamount;
    }
    return sumamount;
}
