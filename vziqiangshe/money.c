#include "money.h"
int saveMoney(const Money money){
    if((fp2=fopen("money.ams","ab"))==NULL){
        if((fp2=fopen("money.ams","wb"))==NULL){
            return 0;
        }
    }
    fwrite(&money,sizeof(Money),1,fp2);
    fclose(fp2);
    return 1;
}


