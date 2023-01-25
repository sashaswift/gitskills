#include "rate_service.h"
#include "rate_files.h"
void initBillingSList(){
    Billingslist=NULL;
    Bhead=NULL;
}
/*void releaseBillingSList(){
    free(Billingslist);
    free(Bhead);
}*/
int getBillingS(){
    if(readBillingStandard()){
        if(Bhead!=NULL){
            return 1;
        }
    }
    return 0;
}
