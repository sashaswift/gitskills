#include "billing_files.h"
#include "billing_service.h"
int saveBilling(Billing bill){
    if((fp1=fopen("billing.ams","ab"))==NULL){
        if((fp1=fopen("billing.ams","wb"))==NULL){
            return 0;
        }

    }

    fwrite(&bill,sizeof(Billing),1,fp1);
    fclose(fp1);
    return 1;
}
long getBillingCount(){
    long i=0;
    //char s[1000];
    /*Billing *bill;
    bill=malloc(sizeof(Billing));*/
    Billing bill;
    if((fp1=fopen("billing.ams","rb"))==NULL){
        return 0;
    }
    while(!feof(fp1)){
            //printf("get failed");
       if(fread(&bill,sizeof(Billing),1,fp1)){
           // printf("%s",bill.aCardName);
        i++;
       }
    }
    fclose(fp1);
    //printf("%ld\n",i);
    return i;
}
int readBilling(){
    IpBillingNode billlis1;
    Billing bill1;
    /*Billing *bill1;
    bill1=malloc(sizeof(Billing));*/
    initBillingList();
   if((fp1=fopen("billing.ams","rb"))==NULL){
       // printf("debug4");
    return 0;
   }
   while(!feof(fp1)){
    if(fread(&bill1,sizeof(Billing),1,fp1)){
        billlis1=malloc(sizeof(BillingNode));
           // billlis1->data=bill1;
            billlis1->data=bill1;
            billlis1->next=NULL;
            //printf("debug2");
        if(bHead==NULL){
           bHead=billlis1;
           billlist=billlis1;
        }
        else{
            billlist->next=billlis1;
            billlist=billlist->next;
        }
      }
       }
   //printf("debug1");
   fclose(fp1);
   return 1;
}
int updateBilling(Billing bill){
    Billing  bill2;
    long n=0;
    int t=0;
    if((fp1=fopen("billing.ams","rb+"))==NULL){
        return 0;
    }
    while(!feof(fp1)){
        if(fread(&bill2,sizeof(Billing),1,fp1)){
            if(strcmp(bill2.aCardName,bill.aCardName)==0){
                n=ftell(fp1)-sizeof(Billing);
                t=1;
            }
        }
    }
    if(t){
    fseek(fp1,n,SEEK_SET);
    fwrite(&bill,sizeof(Billing),1,fp1);
    fclose(fp1);
    return 1;
    }
    fclose(fp1);
    return 0;
}
/*int printBillingRecord(char*pNum,time_t startdate,time_t enddate){
    Billing bill;
    int result=0;
    if((fp1=fopen("billing.ams","rb"))==NULL){
        return 0;
    }
    while(!feof(fp1)){
        if(fread(&bill,sizeof(Billing),1,fp1)){
            if(strcmp(pNum,bill.aCardName)==0&&((bill.tStart>=startdate&&bill.tStart<=enddate)||(bill.tEnd>=startdate&&bill.tEnd<=enddate))&&bill.nDel==0){
                    printf("卡号\t\t消费金额\t\t上机时间\t\t\t下机时间\n");
                printf("%s\t\t%.2lf\t\t%s %s\n",bill.aCardName,bill.fAmount,ctime(&bill.tStart),ctime(&bill.tEnd));
                result=1;
            }
        }
    }
    return result;
}*/
