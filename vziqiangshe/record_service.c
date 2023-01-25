#include "record_service.h"
#include "record_files.h"
void initManager(){
    pHead=NULL;
    managerlist=NULL;
}
/*void releaseManager(){
    free(pHead);
    free(managerlist);
}*/
int getManager(){
    if(readManager()){
            if(pHead!=NULL){
                return 1;
            }
    }
    return 0;
}
/*IpPowerShellNode queryManager(char*pName,char*pPn){
    managerlist=pHead;
    if(getManager()){
        while(managerlist!=NULL){
            if(strcmp(managerlist->date.name,pName)==0&&strcmp(managerlist->date.pn,pPn)==0&&managerlist->date.del==0){
            return managerlist;
        }
        managerlist=managerlist->next;
        }
    }
    return NULL;
}*/
IpPowerShellNode queryManager(char*pName){
   // managerlist=pHead;
    if(getManager()){
            managerlist=pHead;
        while(managerlist!=NULL){
            if(strcmp(managerlist->date.name,pName)==0&&managerlist->date.del==0){
            return managerlist;
        }
        managerlist=managerlist->next;
        }
    }
    return NULL;
}
