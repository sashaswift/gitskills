#include "card_service.h"
#include <stdio.h>
#include <time.h>
#include "menu.h"
#include "sevice.h"
#include "model.h"
#include "tool.h"
void add(){
    /*char num[20];
    char pn[20];*/
    struct Card new;
    struct tm* startTime;
    struct tm* endTime;
    //new=malloc(sizeof(struct Card));
    printf("----------��ӿ�---------\n");
    printf("�����뿨��(����Ϊ1~18):");
    scanf("%s",num);
    strcpy(new.num,num);
//       printf("����������(����Ϊ1~8):");
//       scanf("%s",pn);
    invisiblePn();
    strcpy(new.pn,pn);
    printf("�����뿪�����(RMB):");
    scanf("%lf",&(new.rest));
    new.already=new.rest;//����������ۼƽ�����
    new.last=new.start=new.tEnd=time(NULL);//����ʱ�䣬��һ��ʹ��ʱ����ͬ
    startTime=localtime(&new.start);
    endTime=localtime(&new.tEnd);
    endTime->tm_year=startTime->tm_year+1;
    new.tEnd=mktime(endTime);
    if(strlen(new.num)<=18&&strlen(new.num)>=1&&strlen(new.pn)>=1&&strlen(new.pn)<=8&&new.rest>0){
        printf("-----��ӿ�����Ϣ����-----\n");
        new.status=0;
        new.times=0;
        new.del=0;
        //new->next=NULL;
        if(addCardInfo(new)){
        printf("����\t\t����\t\t״̬\t\t�������\n");
        printf("%s\t\t%s\t\t%d\t\t%.2lf\n",new.num,new.pn,new.status,new.already);
        }
        else{
            printf("��ӿ���Ϣʧ�ܣ�\n");
        }
       }
       else{
        printf("�������\n");
       }
       //addcard(new);
       /*printf("����\t\t����\t\t״̬\t\t�������\n");
       printf("%s\t\t%s\t\t%d\t\t%.2lf\t\t",new.num,new.pn,new.status,new.already);*/
}
void query(){
    printf("----------��ѯ��----------\n");
    printf("�������ѯ�Ŀ���(����Ϊ1~18):");
    scanf("%s",num);
    printf("����\t\t״̬\t\t���\t\t�ۼ�ʹ��\t\tʹ�ô���\t\t�ϴ�ʹ��ʱ��\n");
   if(!queryCardInfo(num)){
     printf("û�иÿ���Ϣ��\n");
   }
}
/*void logon(){
    listp pCard=NULL;
    LogonInfo log;
    printf("----------�ϻ�----------\n");
    printf("�����뿨��(����Ϊ1~18):");
    scanf("%s",num);
    printf("����������(����Ϊ1~8):");
    scanf("%s",pn);
    switch(dologon(num,pn,pCard)){
        case 0:
        printf("�ϻ�ʧ�ܣ�\n");
        break;
        case 1:
        strcpy(log.aCardName,num);
        printf("denbug");
        printf("%s\n",pCard->t.num);
        log.fBalance=pCard->t.rest;
        log.tLogon=time(NULL);
        printf("----------�ϻ���Ϣ����----------\n");
        printf("����\t\t���\t\t�ϻ�ʱ��\n");
        printf("%s\t\t%.2lf\t\t%s\n",log.aCardName,log.fBalance,ctime(&log.tLogon));
        break;
        case 2:
            printf("�ÿ�����ʹ�û���ע����\n");
            break;
        case 3:
            printf("�����㣡\n");
            break;
    }
}*/
void exitApp(){
    //releaseList();
    printf("�˳��ɹ���\n");
}
/*void annul(){
    printf("----------ע����----------\n");
    printf("������ע������(����1~18):");
    scanf("%s",num);
    printf("����������(����Ϊ1~8):");
    scanf("%s",pn);

}*/
void logon(){
    //listp pCard=NULL;
    LogonInfo log;
    IpBillingSNode bills;
    printf("----------�ϻ�----------\n");
    printf("�����뿨��(����Ϊ1~18):");
    scanf("%s",num);
//    printf("����������(����Ϊ1~8):");
//    scanf("%s",pn);
     invisiblePn();
    switch(dologon(num,pn)){
        case 0:
        printf("�ϻ�ʧ�ܣ�\n");
        break;
        case 1:
        strcpy(log.aCardName,num);
        log.fBalance=cardlist->t.rest;
        log.tLogon=time(NULL);
        printf("----------�ϻ���Ϣ����----------\n");
        printf("����\t\t���\t\t�ϻ�ʱ��\n");
        printf("%s\t\t%.2lf\t\t",log.aCardName,log.fBalance);
        stringfortime(log.tLogon);
        printf("\n");
        do{
            printf("��ѡ���ϻ����ͣ�0-��ͨ��1-��ҹ��2-���죩��");
            scanf("%d",&Ratetype);
             if(Ratetype>2||Ratetype<0){
                printf("�ϻ����ʹ���\n");
             }
             else{
                bills=doQueryBillingStandard(Ratetype);
             billingstandard=bills->data;
             printf("�ϻ��ɹ���\n");
             }

        }
        while(Ratetype>2||Ratetype<0);
        break;
        case 2:
            printf("�ÿ�����ʹ�û���ע����\n");
            break;
        case 3:
            printf("�����㣡\n");
            break;
    }
}
void settle(){
    int nResult;
   // SettleInfo *pInfo;
    printf("----------�»�----------\n");
    printf("�����뿨�ţ�");
    scanf("%s",num);
//    printf("���������룺");
//    scanf("%s",pn);
    invisiblePn();
    nResult=doSettle(num,pn);
    switch(nResult){
    case 0:
        printf("�»�ʧ�ܣ�\n");
        break;
    case 1:
        printf("�»���Ϣ���£�\n");
        printf("����\t\t����\t\t���\t\t�ϻ�ʱ��\t\t\t\t�»�ʱ��\n");
        printf("%s\t\t%.2lf\t\t%.2lf\t\t",Set.aCardName,Set.fAmount,Set.fBalance);
        stringfortime(Set.tStart);
        printf("\t");
        stringfortime(Set.tEnd);
        printf("\n");
        break;
    }
}
void addmoney(){
    int nResult;
    double fMoney;
    printf("----------��ֵ----------\n");
    printf("�����뿨�ţ�");
    scanf("%s",num);
//    printf("���������룺");
//    scanf("%s",pn);
    invisiblePn();
    printf("�������ֵ��");
    scanf("%lf",&fMoney);
    Moneyinfo.fMoney=fMoney;
    nResult=doAddMoney(num,pn);
    switch(nResult){
    case 0:
        printf("��ֵʧ�ܣ�\n");
        break;
    case 1:
        printf("----------��ֵ��Ϣ����----------\n");
        printf("����\t\t��ֵ���\t\t���\n");
        printf("%s\t\t%.2lf\t\t%.2lf\n",Moneyinfo.aCardName,Moneyinfo.fMoney,Moneyinfo.fBalance);
        break;
    }
}
void refundmoney(){
     int nResult;
     double fMoney;
     printf("----------�˷�----------\n");
     printf("�����뿨�ţ�");
    scanf("%s",num);
//    printf("���������룺");
//    scanf("%s",pn);
     invisiblePn();
    nResult=doRefundMoney(num,pn);
     switch(nResult){
     case 0:
        printf("�˷�ʧ�ܣ�\n");
        break;
     case 1:
        printf("----------�˷���Ϣ����----------\n");
        printf("����\t\t�˷ѽ��\t\t���\n");
        printf("%s\t\t%.2lf\t\t%.2lf\n",Moneyinfo.aCardName,Moneyinfo.fMoney,Moneyinfo.fBalance);
        break;
     case 3:
        printf("�����㣡\n");
        break;
     }
}
void annul(){
    int nResult;
    double fMoney;
    printf("----------ע��----------\n");
     printf("�����뿨�ţ�");
    scanf("%s",num);
//    printf("���������룺");
//    scanf("%s",pn);
    invisiblePn();
    nResult=annulCard(num,pn);
    switch(nResult){
    case 0:
        printf("ע����ʧ�ܣ�");
        break;
    case 1:
        printf("----------ע������Ϣ����----------\n");
        printf("����\t\t�˿���\n");
        printf("%s\t\t%.2lf\n",annulinfo.aCardName,annulinfo.fMoney);
        break;
    case 2:
        printf("�ÿ�����ʹ�û���ע����\n");
        break;
    case 3:
        printf("���㣡\n");
        break;
    }
}
void addManager(){
    PowerShell powershell;
    printf("----------����Ա���----------\n");
    printf("�������û�����");
    scanf("%s",Name);
//    printf("���������룺");
//    scanf("%s",Pn);
    invisiblePnForManager();
    printf("������Ȩ�޵ȼ�(0~3)��");
    scanf("%d",&powershell.privilige);
    strcpy(powershell.name,Name);
    strcpy(powershell.pn,Pn);
    powershell.del=0;
    if(doAddManager(powershell)){
        printf("��ӳɹ�!\n");
    }
    else{
        printf("���ʧ�ܣ�\n");
    }

}
void loginManager(){
    int choice;
    printf("----------����Ա��¼----------\n");
    printf("�������û�����");
    scanf("%s",Name);
//    printf("���������룺");
//    scanf("%s",Pn);
    invisiblePnForManager();
    if(doLoginManager(Name,Pn)){
        printf("��¼�ɹ���\n");
        printf("----------�û���Ϣ----------\n");
        printf("�û���\t\t����Ա�ȼ�\n");
        printf("%s\t\t%d\n",Power.name,Power.privilige);
        switch(Power.privilige){
        case 1:
            PowerForManager1();
            break;
        case 2:
            PowerForManager2();
            break;
        case 3:
            PowerForManager3();
            break;
        case 4:
            PowerForManager4();
            break;
        }
    }
    else{
        printf("��¼ʧ�ܣ�\n");
    }
}
void PowerForManager1(){
    int Choice;
    do{
        printf("----------ϵͳ����----------\n");
        printf("1,��ѯ�Ʒѱ�׼\n");
        printf("0,�˳�\n");
        printf("��ѡ�������(0~1)��");
        scanf("%d",&Choice);
        switch(Choice){
        case 1:
           addBillingStandard();
           break;
        case 0:
            exitApp2();
            break;

        default:
            printf("û��Ȩ�ޣ�\n");
            break;
        }
    }
    while(Choice!=0);
}
void PowerForManager2(){
    int Choice;
    do{
        printf("----------ϵͳ����----------\n");
         printf("1,��ѯ�Ʒѱ�׼\n");
         printf("2,��ӼƷ�ϵͳ\n");
         printf("0,�˳�\n");
         scanf("%d",&Choice);
         switch(Choice){
         case 2:
            addBillingStandard();
            break;
         case 1:
            queryBillingStandard();
            break;
         case 0:
            exitApp2();
            break;
         default:
            printf("û��Ȩ�ޣ�\n");
            break;
         }
    }
    while(Choice!=0);
}
void PowerForManager3(){
    int Choice;
    do{
        printf("----------ϵͳ����----------\n");
         printf("1,��ѯ�Ʒѱ�׼\n");
         printf("2,��ӼƷ�ϵͳ\n");
         printf("3,���ļƷ�ϵͳ\n");
         printf("0,�˳�\n");
         printf("������ѡ������ţ�0~3����");
         scanf("%d",&Choice);
         switch(Choice){
         case 2:
            addBillingStandard();
            break;
         case 1:
            queryBillingStandard();
            break;
         case 3:
            changeBillingStandard();
            break;
         case 0:
            exitApp2();
            break;
         default:
            printf("û��Ȩ�ޣ�\n");
            break;
         }
    }
    while(Choice!=0);
}
void addBillingStandard(){
    BillingS billings;
    printf("----------��ӼƷѱ�׼----------\n");
    do{
        printf("������Ʒ����(0-��ͨ��1-��ҹ��2-����)��");
        scanf("%d",&billings.ratetype);
        if(billings.ratetype>2||billings.ratetype<0){
            printf("���������룡\n");
        }
    }
    while(billings.ratetype>2||billings.ratetype<0);
    switch(billings.ratetype){
    case 0:
        printf("��������С�Ʒѵ�Ԫ��");
        scanf("%d",&billings.unit);
        printf("������ÿ���Ʒѵ�Ԫ�շѣ�");
        scanf("%lf",&billings.charge);
        billings.sum=0;
        break;
    case 1:
        printf("�������ҹ��");
        scanf("%lf",&billings.sum);
        billings.charge=0;
        billings.unit=0;
        break;
    case 2:
        printf("����������");
        scanf("%lf",&billings.sum);
        billings.charge=0;
        billings.unit=0;
        break;
    }
    billings.starttime=time(0);
    billings.del=0;
    if(doAddBillingStandard(billings)){
        printf("��ӼƷѱ�׼�ɹ���\n");
    }
    else{
        printf("��ӼƷѱ�׼ʧ�ܣ�\n");
    }
}
void queryBillingStandard(){
   //int ratetype;
    IpBillingSNode billings;
    printf("----------��ѯ�Ʒѱ�׼-----------\n");
    printf("�������շ����0-��ͨ��1-��ҹ��2-���죩��");
    scanf("%d",&Ratetype);
    billings=doQueryBillingStandard(Ratetype);
    if(billings!=NULL){
        printf("----------�Ʒѱ�׼��Ϣ����----------\n");
        switch(Ratetype){
        case 0:
            printf("�շ����\t\t��С�Ʒѵ�Ԫ\t\tÿ���Ʒѵ�Ԫ���շ�\t��ʼʱ��\n");
            printf("��ͨ    \t\t%d\t\t\t%.2lf\t\t",billings->data.unit,billings->data.charge);
            stringfortime(billings->data.starttime);
            printf("\n");
            break;
        case 1:
             printf("�շ����\t\t�շѽ��\t\t��ʼʱ��\n");
             printf("��ҹ  \t\t%.2lf\t\t",billings->data.sum);
             stringfortime(billings->data.starttime);
             printf("\n");
             break;
        case 2:
            printf("�շ����\t\t�շѽ��\t\t��ʼʱ��\n");
            printf("����  \t\t%.2lf\t\t",billings->data.sum);
            stringfortime(billings->data.starttime);
             printf("\n");
            break;
        }
    }
    else{
        printf("��ѯʧ�ܣ�\n");
    }
}
void changeBillingStandard(){
   BillingS bills;
   printf("----------���ļƷѱ�׼----------\n");
   printf("������Ʒ����0-��ͨ��1-��ҹ��2-���죩��");
   scanf("%d",&bills.ratetype);
   bills.starttime=time(0);
   bills.del=0;
   switch(bills.ratetype){
   case 0:
       printf("��������С�Ʒѵ�Ԫ��");
       scanf("%d",&bills.unit);
       printf("������ÿ���Ʒѵ�Ԫ���շѣ�");
       scanf("%lf",&bills.charge);
       bills.sum=0;
       break;
   case 1:
       printf("��������İ�ҹ�շѽ�");
       scanf("%lf",&bills.sum);
       bills.charge=0;
       bills.unit=0;
       break;
   case 2:
       printf("��������İ����շѽ�");
       scanf("%lf",&bills.sum);
       bills.charge=0;
       bills.unit=0;
       break;
   }
   if(doChangeBillingStandard(bills)){
    printf("���ĳɹ���\n");
   }
   else{
     printf("����ʧ�ܣ�\n");
   }
}
void exitApp2(){
    //printf("�ѳɹ��˳���");
    //releaseList2();
    printf("�ѳɹ��˳���\n");
}
void PowerForManager4(){
    int Choice;
    do{
        printf("---------ϵͳ����----------\n");
        printf("1,��ѯ�Ʒѱ�׼\n");
         printf("2,��ӼƷ�ϵͳ\n");
         printf("3,���ļƷ�ϵͳ\n");
         printf("4,���ù���ԱȨ��\n");
         printf("5,ɾ������Ա\n");
         printf("0,�˳�\n");
         printf("������ѡ������ţ�0~5����");
         scanf("%d",&Choice);
         switch(Choice){
             case 2:
            addBillingStandard();
            break;
         case 1:
            queryBillingStandard();
            break;
         case 3:
            changeBillingStandard();
            break;
         case 0:
            exitApp2();
            break;
         case 4:
            changeManager();
            break;
         case 5:
            deleteMangager();
            break;
         default:
            printf("û��Ȩ�ޣ�\n");
            break;
         }
    }
    while(Choice!=0);

}
void changeManager(){
    //PowerShell newManager;
    printf("----------����ԱȨ�޹���----------\n");
    printf("���������Ա�˺�\n");
    scanf("%s",Name);
    if(doChangeManager(Name)){
        printf("���ĳɹ���\n");
    }
}
void deleteMangager(){
    printf("----------ɾ������Ա----------\n");
    printf("������ɾ������Ա�˺�\n");
    scanf("%s",Name);
    if(doDeleteManager(Name)){
        printf("ɾ���ɹ���\n");
    }
}
void rate(){
    int Choice;
     printf("----------��ѯͳ��----------\n");
     printf("1,���Ѽ�¼��ѯ\n");
     printf("2,ͳ����Ӫҵ��\n");
     printf("3,ͳ����Ӫҵ��\n");
     printf("��ѡ���ѯ��Ŀ��1~3����");
     scanf("%d",&Choice);
     switch(Choice){
     case 1:
        queryBillingRecord();
        break;
     case 2:
        AllOfincome();
        break;
     case 3:
        incomeOfMonth();
        break;
     default:
        printf("�������\n");
        break;
     }
}
void queryBillingRecord(){
      char startDate[12];
      char endDate[12];
      time_t startdate;
      time_t enddate;
      printf("----------���Ѽ�¼��ѯ----------\n");
      printf("�����뿨�ţ�");
      scanf("%s",num);
      printf("�����뿪ʼʱ�䣨��ʽΪ��-��-�գ���");
      scanf("%s",startDate);
      printf("���������ʱ�䣨��ʽΪ��-��-��): ");
      scanf("%s",endDate);
      printf("----------���Ѽ�¼����----------\n");
      startdate=stringToTime(startDate);
      enddate=stringToTime(endDate);

      if(doQueryBillingRecord(num,startdate,enddate)==FALSE){
        printf("�鲻���ÿ���¼��\n");
      }
}
void AllOfincome(){
     char startDate[12];
     char endDate[12];
     time_t startdate;
     time_t enddate;
     double sumAmount;
      printf("----------��Ӫҵ���ѯ----------\n");
      printf("�����뿪ʼʱ�䣨��ʽΪ��-��-�գ���");
      scanf("%s",startDate);
      printf("���������ʱ�䣨��ʽΪ��-��-��): ");
      scanf("%s",endDate);
      //printf("----------��Ӫҵ����Ϣ����----------\n");
      startdate=stringToTime(startDate);
      enddate=stringToTime(endDate);
       printf("----------��Ӫҵ����Ϣ����----------\n");
       sumAmount=doSumAmount(startdate,enddate);
       printf("�ö�ʱ�����Ӫҵ��Ϊ��%.2lf\n",sumAmount);
}
void incomeOfMonth(){
    char startDate[12];
     char endDate[12];
     char date[12];
     time_t startdate;
     time_t enddate;
     double amount;
    printf("----------��Ӫҵ���ѯ----------\n");
    printf("�������ѯ��ݣ�");
    scanf("%s",date);
    int i=1;
    for(i=1;i<=12;i++){
            strcpy(startDate,date);
        switch(i){
        case 1:
            strcpy(endDate,startDate);
            strcat(startDate,"-01-01");
            strcat(endDate,"-02-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("һ�·�Ӫҵ��Ϊ��%.2lf\n",amount);
            break;
        case 2:
            strcpy(endDate,startDate);
            strcat(startDate,"-02-01");
            strcat(endDate,"-03-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("���·�Ӫҵ��Ϊ��%.2lf\n",amount);
            break;
        case 3:
            strcpy(endDate,startDate);
            strcat(startDate,"-03-01");
            strcat(endDate,"-04-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("���·�Ӫҵ��Ϊ��%.2lf\n",amount);
            break;
        case 4:
            strcpy(endDate,startDate);
            strcat(startDate,"-04-01");
            strcat(endDate,"-05-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("���·�Ӫҵ��Ϊ��%.2lf\n",amount);
            break;
        case 5:
            strcpy(endDate,startDate);
            strcat(startDate,"-05-01");
            strcat(endDate,"-06-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("���·�Ӫҵ��Ϊ��%.2lf\n",amount);
            break;
        case 6:
            strcpy(endDate,startDate);
            strcat(startDate,"-06-01");
            strcat(endDate,"-07-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("���·�Ӫҵ��Ϊ��%.2lf\n",amount);
            break;
        case 7:
            strcpy(endDate,startDate);
            strcat(startDate,"-07-01");
            strcat(endDate,"-08-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("���·�Ӫҵ��Ϊ��%.2lf\n",amount);
            break;
        case 8:
            strcpy(endDate,startDate);
            strcat(startDate,"-08-01");
            strcat(endDate,"-09-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("���·�Ӫҵ��Ϊ��%.2lf\n",amount);
            break;
        case 9:
            strcpy(endDate,startDate);
            strcat(startDate,"-09-01");
            strcat(endDate,"-10-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("���·�Ӫҵ��Ϊ��%.2lf\n",amount);
            break;
        case 10:
            strcpy(endDate,startDate);
            strcat(startDate,"-10-01");
            strcat(endDate,"-11-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("ʮ�·�Ӫҵ��Ϊ��%.2lf\n",amount);
            break;
        case 11:
            strcpy(endDate,startDate);
            strcat(startDate,"-11-01");
            strcat(endDate,"-12-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("ʮһ�·�Ӫҵ��Ϊ��%.2lf\n",amount);
            break;
        case 12:
            strcpy(endDate,startDate);
            if(endDate[3]=='9'){
                endDate[3]='0';
                if(endDate[2]=='9'){
                    endDate[2]=='0';
                    if(endDate[1]=='9'){
                        endDate[1]=='0';
                        endDate[0]+=1;
                    }
                    else{
                        endDate[1]+=1;
                    }
                }
                else{
                    endDate[2]+=1;
                }
            }
            else{
                endDate[3]+=1;
            }
            strcat(startDate,"-12-01");
            strcat(endDate,"-01-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("ʮ���·�Ӫҵ��Ϊ��%.2lf\n",amount);
            break;
        }

    }

}
