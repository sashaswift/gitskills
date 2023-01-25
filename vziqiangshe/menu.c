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
    printf("----------添加卡---------\n");
    printf("请输入卡号(长度为1~18):");
    scanf("%s",num);
    strcpy(new.num,num);
//       printf("请输入密码(长度为1~8):");
//       scanf("%s",pn);
    invisiblePn();
    strcpy(new.pn,pn);
    printf("请输入开卡金额(RMB):");
    scanf("%lf",&(new.rest));
    new.already=new.rest;//开卡余额与累计金额相等
    new.last=new.start=new.tEnd=time(NULL);//开卡时间，上一次使用时间相同
    startTime=localtime(&new.start);
    endTime=localtime(&new.tEnd);
    endTime->tm_year=startTime->tm_year+1;
    new.tEnd=mktime(endTime);
    if(strlen(new.num)<=18&&strlen(new.num)>=1&&strlen(new.pn)>=1&&strlen(new.pn)<=8&&new.rest>0){
        printf("-----添加卡的信息如下-----\n");
        new.status=0;
        new.times=0;
        new.del=0;
        //new->next=NULL;
        if(addCardInfo(new)){
        printf("卡号\t\t密码\t\t状态\t\t开卡金额\n");
        printf("%s\t\t%s\t\t%d\t\t%.2lf\n",new.num,new.pn,new.status,new.already);
        }
        else{
            printf("添加卡信息失败！\n");
        }
       }
       else{
        printf("输入错误！\n");
       }
       //addcard(new);
       /*printf("卡号\t\t密码\t\t状态\t\t开卡金额\n");
       printf("%s\t\t%s\t\t%d\t\t%.2lf\t\t",new.num,new.pn,new.status,new.already);*/
}
void query(){
    printf("----------查询卡----------\n");
    printf("请输入查询的卡号(长度为1~18):");
    scanf("%s",num);
    printf("卡号\t\t状态\t\t余额\t\t累计使用\t\t使用次数\t\t上次使用时间\n");
   if(!queryCardInfo(num)){
     printf("没有该卡信息！\n");
   }
}
/*void logon(){
    listp pCard=NULL;
    LogonInfo log;
    printf("----------上机----------\n");
    printf("请输入卡号(长度为1~18):");
    scanf("%s",num);
    printf("请输入密码(长度为1~8):");
    scanf("%s",pn);
    switch(dologon(num,pn,pCard)){
        case 0:
        printf("上机失败！\n");
        break;
        case 1:
        strcpy(log.aCardName,num);
        printf("denbug");
        printf("%s\n",pCard->t.num);
        log.fBalance=pCard->t.rest;
        log.tLogon=time(NULL);
        printf("----------上机信息如下----------\n");
        printf("卡号\t\t余额\t\t上机时间\n");
        printf("%s\t\t%.2lf\t\t%s\n",log.aCardName,log.fBalance,ctime(&log.tLogon));
        break;
        case 2:
            printf("该卡正在使用或已注销！\n");
            break;
        case 3:
            printf("卡余额不足！\n");
            break;
    }
}*/
void exitApp(){
    //releaseList();
    printf("退出成功！\n");
}
/*void annul(){
    printf("----------注销卡----------\n");
    printf("请输入注销卡号(长度1~18):");
    scanf("%s",num);
    printf("请输入密码(长度为1~8):");
    scanf("%s",pn);

}*/
void logon(){
    //listp pCard=NULL;
    LogonInfo log;
    IpBillingSNode bills;
    printf("----------上机----------\n");
    printf("请输入卡号(长度为1~18):");
    scanf("%s",num);
//    printf("请输入密码(长度为1~8):");
//    scanf("%s",pn);
     invisiblePn();
    switch(dologon(num,pn)){
        case 0:
        printf("上机失败！\n");
        break;
        case 1:
        strcpy(log.aCardName,num);
        log.fBalance=cardlist->t.rest;
        log.tLogon=time(NULL);
        printf("----------上机信息如下----------\n");
        printf("卡号\t\t余额\t\t上机时间\n");
        printf("%s\t\t%.2lf\t\t",log.aCardName,log.fBalance);
        stringfortime(log.tLogon);
        printf("\n");
        do{
            printf("请选择上机类型（0-普通，1-包夜，2-包天）：");
            scanf("%d",&Ratetype);
             if(Ratetype>2||Ratetype<0){
                printf("上机类型错误！\n");
             }
             else{
                bills=doQueryBillingStandard(Ratetype);
             billingstandard=bills->data;
             printf("上机成功！\n");
             }

        }
        while(Ratetype>2||Ratetype<0);
        break;
        case 2:
            printf("该卡正在使用或已注销！\n");
            break;
        case 3:
            printf("卡余额不足！\n");
            break;
    }
}
void settle(){
    int nResult;
   // SettleInfo *pInfo;
    printf("----------下机----------\n");
    printf("请输入卡号：");
    scanf("%s",num);
//    printf("请输入密码：");
//    scanf("%s",pn);
    invisiblePn();
    nResult=doSettle(num,pn);
    switch(nResult){
    case 0:
        printf("下机失败！\n");
        break;
    case 1:
        printf("下机信息如下：\n");
        printf("卡号\t\t消费\t\t余额\t\t上机时间\t\t\t\t下机时间\n");
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
    printf("----------充值----------\n");
    printf("请输入卡号：");
    scanf("%s",num);
//    printf("请输入密码：");
//    scanf("%s",pn);
    invisiblePn();
    printf("请输入充值金额：");
    scanf("%lf",&fMoney);
    Moneyinfo.fMoney=fMoney;
    nResult=doAddMoney(num,pn);
    switch(nResult){
    case 0:
        printf("充值失败！\n");
        break;
    case 1:
        printf("----------充值信息如下----------\n");
        printf("卡号\t\t充值金额\t\t余额\n");
        printf("%s\t\t%.2lf\t\t%.2lf\n",Moneyinfo.aCardName,Moneyinfo.fMoney,Moneyinfo.fBalance);
        break;
    }
}
void refundmoney(){
     int nResult;
     double fMoney;
     printf("----------退费----------\n");
     printf("请输入卡号：");
    scanf("%s",num);
//    printf("请输入密码：");
//    scanf("%s",pn);
     invisiblePn();
    nResult=doRefundMoney(num,pn);
     switch(nResult){
     case 0:
        printf("退费失败！\n");
        break;
     case 1:
        printf("----------退费信息如下----------\n");
        printf("卡号\t\t退费金额\t\t余额\n");
        printf("%s\t\t%.2lf\t\t%.2lf\n",Moneyinfo.aCardName,Moneyinfo.fMoney,Moneyinfo.fBalance);
        break;
     case 3:
        printf("卡余额不足！\n");
        break;
     }
}
void annul(){
    int nResult;
    double fMoney;
    printf("----------注销----------\n");
     printf("请输入卡号：");
    scanf("%s",num);
//    printf("请输入密码：");
//    scanf("%s",pn);
    invisiblePn();
    nResult=annulCard(num,pn);
    switch(nResult){
    case 0:
        printf("注销卡失败！");
        break;
    case 1:
        printf("----------注销卡信息如下----------\n");
        printf("卡号\t\t退款金额\n");
        printf("%s\t\t%.2lf\n",annulinfo.aCardName,annulinfo.fMoney);
        break;
    case 2:
        printf("该卡正在使用或已注销！\n");
        break;
    case 3:
        printf("余额不足！\n");
        break;
    }
}
void addManager(){
    PowerShell powershell;
    printf("----------管理员添加----------\n");
    printf("请输入用户名：");
    scanf("%s",Name);
//    printf("请输入密码：");
//    scanf("%s",Pn);
    invisiblePnForManager();
    printf("请输入权限等级(0~3)：");
    scanf("%d",&powershell.privilige);
    strcpy(powershell.name,Name);
    strcpy(powershell.pn,Pn);
    powershell.del=0;
    if(doAddManager(powershell)){
        printf("添加成功!\n");
    }
    else{
        printf("添加失败！\n");
    }

}
void loginManager(){
    int choice;
    printf("----------管理员登录----------\n");
    printf("请输入用户名：");
    scanf("%s",Name);
//    printf("请输入密码：");
//    scanf("%s",Pn);
    invisiblePnForManager();
    if(doLoginManager(Name,Pn)){
        printf("登录成功！\n");
        printf("----------用户信息----------\n");
        printf("用户名\t\t管理员等级\n");
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
        printf("登录失败！\n");
    }
}
void PowerForManager1(){
    int Choice;
    do{
        printf("----------系统管理----------\n");
        printf("1,查询计费标准\n");
        printf("0,退出\n");
        printf("请选择管理编号(0~1)：");
        scanf("%d",&Choice);
        switch(Choice){
        case 1:
           addBillingStandard();
           break;
        case 0:
            exitApp2();
            break;

        default:
            printf("没有权限！\n");
            break;
        }
    }
    while(Choice!=0);
}
void PowerForManager2(){
    int Choice;
    do{
        printf("----------系统管理----------\n");
         printf("1,查询计费标准\n");
         printf("2,添加计费系统\n");
         printf("0,退出\n");
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
            printf("没有权限！\n");
            break;
         }
    }
    while(Choice!=0);
}
void PowerForManager3(){
    int Choice;
    do{
        printf("----------系统管理----------\n");
         printf("1,查询计费标准\n");
         printf("2,添加计费系统\n");
         printf("3,更改计费系统\n");
         printf("0,退出\n");
         printf("请输入选择功能序号（0~3）：");
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
            printf("没有权限！\n");
            break;
         }
    }
    while(Choice!=0);
}
void addBillingStandard(){
    BillingS billings;
    printf("----------添加计费标准----------\n");
    do{
        printf("请输入计费类别(0-普通，1-包夜，2-包天)：");
        scanf("%d",&billings.ratetype);
        if(billings.ratetype>2||billings.ratetype<0){
            printf("请重新输入！\n");
        }
    }
    while(billings.ratetype>2||billings.ratetype<0);
    switch(billings.ratetype){
    case 0:
        printf("请输入最小计费单元：");
        scanf("%d",&billings.unit);
        printf("请输入每个计费单元收费：");
        scanf("%lf",&billings.charge);
        billings.sum=0;
        break;
    case 1:
        printf("请输入包夜金额：");
        scanf("%lf",&billings.sum);
        billings.charge=0;
        billings.unit=0;
        break;
    case 2:
        printf("请输入包天金额：");
        scanf("%lf",&billings.sum);
        billings.charge=0;
        billings.unit=0;
        break;
    }
    billings.starttime=time(0);
    billings.del=0;
    if(doAddBillingStandard(billings)){
        printf("添加计费标准成功！\n");
    }
    else{
        printf("添加计费标准失败！\n");
    }
}
void queryBillingStandard(){
   //int ratetype;
    IpBillingSNode billings;
    printf("----------查询计费标准-----------\n");
    printf("请输入收费类别（0-普通，1-包夜，2-包天）：");
    scanf("%d",&Ratetype);
    billings=doQueryBillingStandard(Ratetype);
    if(billings!=NULL){
        printf("----------计费标准信息如下----------\n");
        switch(Ratetype){
        case 0:
            printf("收费类别\t\t最小计费单元\t\t每个计费单元的收费\t开始时间\n");
            printf("普通    \t\t%d\t\t\t%.2lf\t\t",billings->data.unit,billings->data.charge);
            stringfortime(billings->data.starttime);
            printf("\n");
            break;
        case 1:
             printf("收费类别\t\t收费金额\t\t开始时间\n");
             printf("包夜  \t\t%.2lf\t\t",billings->data.sum);
             stringfortime(billings->data.starttime);
             printf("\n");
             break;
        case 2:
            printf("收费类别\t\t收费金额\t\t开始时间\n");
            printf("包天  \t\t%.2lf\t\t",billings->data.sum);
            stringfortime(billings->data.starttime);
             printf("\n");
            break;
        }
    }
    else{
        printf("查询失败！\n");
    }
}
void changeBillingStandard(){
   BillingS bills;
   printf("----------更改计费标准----------\n");
   printf("请输入计费类别（0-普通，1-包夜，2-包天）：");
   scanf("%d",&bills.ratetype);
   bills.starttime=time(0);
   bills.del=0;
   switch(bills.ratetype){
   case 0:
       printf("请输入最小计费单元：");
       scanf("%d",&bills.unit);
       printf("请输入每个计费单元的收费：");
       scanf("%lf",&bills.charge);
       bills.sum=0;
       break;
   case 1:
       printf("请输入更改包夜收费金额：");
       scanf("%lf",&bills.sum);
       bills.charge=0;
       bills.unit=0;
       break;
   case 2:
       printf("请输入更改包天收费金额：");
       scanf("%lf",&bills.sum);
       bills.charge=0;
       bills.unit=0;
       break;
   }
   if(doChangeBillingStandard(bills)){
    printf("更改成功！\n");
   }
   else{
     printf("更改失败！\n");
   }
}
void exitApp2(){
    //printf("已成功退出！");
    //releaseList2();
    printf("已成功退出！\n");
}
void PowerForManager4(){
    int Choice;
    do{
        printf("---------系统管理----------\n");
        printf("1,查询计费标准\n");
         printf("2,添加计费系统\n");
         printf("3,更改计费系统\n");
         printf("4,设置管理员权限\n");
         printf("5,删除管理员\n");
         printf("0,退出\n");
         printf("请输入选择功能序号（0~5）：");
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
            printf("没有权限！\n");
            break;
         }
    }
    while(Choice!=0);

}
void changeManager(){
    //PowerShell newManager;
    printf("----------管理员权限管理----------\n");
    printf("请输入管理员账号\n");
    scanf("%s",Name);
    if(doChangeManager(Name)){
        printf("更改成功！\n");
    }
}
void deleteMangager(){
    printf("----------删除管理员----------\n");
    printf("请输入删除管理员账号\n");
    scanf("%s",Name);
    if(doDeleteManager(Name)){
        printf("删除成功！\n");
    }
}
void rate(){
    int Choice;
     printf("----------查询统计----------\n");
     printf("1,消费记录查询\n");
     printf("2,统计总营业额\n");
     printf("3,统计月营业额\n");
     printf("请选择查询项目（1~3）：");
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
        printf("输入错误！\n");
        break;
     }
}
void queryBillingRecord(){
      char startDate[12];
      char endDate[12];
      time_t startdate;
      time_t enddate;
      printf("----------消费记录查询----------\n");
      printf("请输入卡号：");
      scanf("%s",num);
      printf("请输入开始时间（格式为年-月-日）：");
      scanf("%s",startDate);
      printf("请输入结束时间（格式为年-月-日): ");
      scanf("%s",endDate);
      printf("----------消费记录如下----------\n");
      startdate=stringToTime(startDate);
      enddate=stringToTime(endDate);

      if(doQueryBillingRecord(num,startdate,enddate)==FALSE){
        printf("查不到该卡记录！\n");
      }
}
void AllOfincome(){
     char startDate[12];
     char endDate[12];
     time_t startdate;
     time_t enddate;
     double sumAmount;
      printf("----------总营业额查询----------\n");
      printf("请输入开始时间（格式为年-月-日）：");
      scanf("%s",startDate);
      printf("请输入结束时间（格式为年-月-日): ");
      scanf("%s",endDate);
      //printf("----------总营业额信息如下----------\n");
      startdate=stringToTime(startDate);
      enddate=stringToTime(endDate);
       printf("----------总营业额信息如下----------\n");
       sumAmount=doSumAmount(startdate,enddate);
       printf("该段时间的总营业额为：%.2lf\n",sumAmount);
}
void incomeOfMonth(){
    char startDate[12];
     char endDate[12];
     char date[12];
     time_t startdate;
     time_t enddate;
     double amount;
    printf("----------月营业额查询----------\n");
    printf("请输入查询年份：");
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
            printf("一月份营业额为：%.2lf\n",amount);
            break;
        case 2:
            strcpy(endDate,startDate);
            strcat(startDate,"-02-01");
            strcat(endDate,"-03-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("二月份营业额为：%.2lf\n",amount);
            break;
        case 3:
            strcpy(endDate,startDate);
            strcat(startDate,"-03-01");
            strcat(endDate,"-04-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("三月份营业额为：%.2lf\n",amount);
            break;
        case 4:
            strcpy(endDate,startDate);
            strcat(startDate,"-04-01");
            strcat(endDate,"-05-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("四月份营业额为：%.2lf\n",amount);
            break;
        case 5:
            strcpy(endDate,startDate);
            strcat(startDate,"-05-01");
            strcat(endDate,"-06-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("五月份营业额为：%.2lf\n",amount);
            break;
        case 6:
            strcpy(endDate,startDate);
            strcat(startDate,"-06-01");
            strcat(endDate,"-07-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("六月份营业额为：%.2lf\n",amount);
            break;
        case 7:
            strcpy(endDate,startDate);
            strcat(startDate,"-07-01");
            strcat(endDate,"-08-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("七月份营业额为：%.2lf\n",amount);
            break;
        case 8:
            strcpy(endDate,startDate);
            strcat(startDate,"-08-01");
            strcat(endDate,"-09-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("八月份营业额为：%.2lf\n",amount);
            break;
        case 9:
            strcpy(endDate,startDate);
            strcat(startDate,"-09-01");
            strcat(endDate,"-10-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("九月份营业额为：%.2lf\n",amount);
            break;
        case 10:
            strcpy(endDate,startDate);
            strcat(startDate,"-10-01");
            strcat(endDate,"-11-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("十月份营业额为：%.2lf\n",amount);
            break;
        case 11:
            strcpy(endDate,startDate);
            strcat(startDate,"-11-01");
            strcat(endDate,"-12-01");
            startdate=stringToTime(startDate);
            enddate=stringToTime(endDate);
            amount=doSumAmount(startdate,enddate);
            printf("十一月份营业额为：%.2lf\n",amount);
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
            printf("十二月份营业额为：%.2lf\n",amount);
            break;
        }

    }

}
