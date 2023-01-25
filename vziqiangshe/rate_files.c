#include "rate_files.h"
#include "rate_service.h"
int saveBillingStandard(BillingS Billingstandard){
    if((fp4=fopen("rate.ams","ab"))==NULL){
        if((fp4=fopen("rate.ams","wb"))==NULL){
            return 0;
        }
    }
    fwrite(&Billingstandard,sizeof(BillingS),1,fp4);
    fclose(fp4);
    return 1;
}
int readBillingStandard(){
    IpBillingSNode pBillingS;
    initBillingSList();
    BillingS billS;
    if((fp4=fopen("rate.ams","rb"))==NULL){
        return 0;
    }
    while(!feof(fp4)){
        if(fread(&billS,sizeof(BillingS),1,fp4)){
            //printf("bug");
            pBillingS=malloc(sizeof(BillingSNode));
            pBillingS->data=billS;
            pBillingS->next=NULL;
            if(Bhead==NULL){
                Bhead=pBillingS;
                Billingslist=pBillingS;
            }
            else{
                Billingslist->next=pBillingS;
                Billingslist=Billingslist->next;
            }
            //printf("ratetype=%d\n",Billingslist->data.ratetype);
        }
    }
    return 1;
}
int updateBillingStandard(BillingS bills){
    long pos=0;
    int t=0;
    BillingS bills1;
    if((fp4=fopen("rate.ams","rb+"))==NULL){
        return 0;
    }
    while(!feof(fp4)){
        if(fread(&bills1,sizeof(BillingS),1,fp4)){
            if(bills1.ratetype==bills.ratetype){
                pos=ftell(fp4)-sizeof(BillingS);
                t=1;
            }
        }
    }
    if(t){
        fseek(fp4,pos,SEEK_SET);
        fwrite(&bills,sizeof(BillingS),1,fp4);
        fclose(fp4);
        return 1;
    }
        fclose(fp4);
        return 0;

}
