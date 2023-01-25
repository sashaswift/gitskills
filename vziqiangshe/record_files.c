#include "record_files.h"
#include "record_service.h"
int saveManager(PowerShell powershell){
      if((fp3=fopen("record.ams","ab"))==NULL){
        if((fp3=fopen("record.ams","wb"))==NULL){
            return 0;
        }
      }
      fwrite(&powershell,sizeof(PowerShell),1,fp3);
      fclose(fp3);
      return 1;
}
int readManager(){
    IpPowerShellNode pPower;
    PowerShell manager;
    initManager();
    if((fp3=fopen("record.ams","rb"))==NULL){
        return 0;
    }
    while(!feof(fp3)){
        if(fread(&manager,sizeof(PowerShell),1,fp3)){
             pPower=malloc(sizeof(PowerShellNode));
             pPower->date=manager;
             pPower->next=NULL;
             if(pHead==NULL){
                pHead=pPower;
                managerlist=pPower;
             }
             else{
                managerlist->next=pPower;
                managerlist=managerlist->next;
             }
        }
    }
    fclose(fp3);
    return 1;
}
int updateManager(PowerShell newManager){
    PowerShell originManager;
    long pos=0;
    if((fp3=fopen("record.ams","rb+"))==NULL){
        return 0;
    }
    while(!feof(fp3)){
        if(fread(&originManager,sizeof(PowerShell),1,fp3)){
            if(strcmp(originManager.name,newManager.name)==0){
                pos=ftell(fp3)-sizeof(PowerShell);
                //printf("%d\n",pos);
            }
        }
    }
    fseek(fp3,pos,SEEK_SET);
    fwrite(&newManager,sizeof(PowerShell),1,fp3);
    fclose(fp3);
    return 1;
}
