#include "billing_service.h"
#include "billing_files.h"
int addBilling(Billing bill){
    if(saveBilling(bill)){
        return 1;
    }
        return 0;
}
/*void releaseBillingList(){
    free(billlist);
    free(bHead);
}*/
void initBillingList(){
    billlist=NULL;
    bHead=NULL;
}
int getBilling(){
     /*long n;
   n=getBillingCount();
   if(n){
   billlist=malloc((sizeof(BillingNode))*n);
   bHead=malloc((sizeof(BillingNode))*n);
   }
   else{
    return 0;
   }*/
   if(readBilling()==0){
    return 0;
   }
   return 1;
}
IpBillingNode queryBilling(const char*pName){
    IpBillingNode bill2;
    IpBillingNode bill3=NULL;
    //initBillingList();
    if(getBilling()!=0){
            bill2=bHead;
        while(bill2!=NULL){
            if(strcmp(pName,bill2->data.aCardName)==0){
                bill3=bill2;
            }
            bill2=bill2->next;
        }
        return bill3;
    }
    return NULL;
}
