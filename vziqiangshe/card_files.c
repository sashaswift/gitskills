#include "card_files.h"
#include "card_service.h"
#include <ctype.h>
#include <stdlib.h>
int savecard(struct Card card){
     if((fp=fopen("card_service.txt","a"))==NULL){
        if((fp=fopen("card_service.txt","w"))==NULL){
           //printf("添加卡信息失败\n");
           return 0;
        }
        // fprintf(fp,"%s##%s##%d##%.2lf##%.2lf##%d##%lld##%lld##%lld##%d",card.num,card.pn,card.status,card.rest,card.already,card.times,card.last,card.start,card.tEnd,card.del);
    }
    else{
    fprintf(fp,"%s##%s##%d##%.2lf##%.2lf##%d##%lld##%lld##%lld##%d\n",card.num,card.pn,card.status,card.rest,card.already,card.times,card.last,card.start,card.tEnd,card.del);
    }
   // fwrite(card,sizeof(struct Card),1,fp);
    fclose(fp);
    return 1;
}
long getcardcount(){
    long i=0;
    char s[1000];
    //struct Card *cur;
    //cur=sizeof(struct Card);
    if((fp=fopen("card_service.txt","r"))==NULL){
        return 0;
    }
    while(!feof(fp)){
       if( fscanf(fp,"%s",s)!=0){
        i++;
        /*cardlist->t=malloc(sizeof(struct Card));
        cardlist=malloc(sizeof(List));
        cardlist=cardlist->next;
        head->t=malloc(sizeof(struct Card));
        head=malloc(sizeof(List));
        head=head->next;*/
       }//i=ftell(fp)-sizeof(struct Card);
    }
    fclose(fp);
    //printf("%ld\n",i);
    return i;
}
//struct Card parsecard(char *pubf){
//    struct Card card;
//    char *tokenP;
//    int n,i=0,j=-2;
//    tokenP=strtok(pubf,"##");
//    strcpy(card.num,tokenP);
//    tokenP=strtok(NULL,"##");
//    strcpy(card.pn,tokenP);
//    tokenP=strtok(NULL,"##");
//    card.status=tokenP[0]-'0';
//    tokenP=strtok(NULL,"##");
//    n=strlen(tokenP);
//    card.rest=0;
//    for(i=n-1;i>=0;i--){
//        if(isdigit(tokenP[i])){
//            card.rest+=(tokenP[i]-'0')*pow(10,j);
//            j++;
//        }
//    }
//    tokenP=strtok(NULL,"##");
//    card.already=0;
//    n=strlen(tokenP);
//    j=-2;
//    for(i=n-1;i>=0;i--){
//        if(isdigit(tokenP[i])){
//            card.already+=(tokenP[i]-'0')*pow(10,j);
//            j++;
//        }
//    }
//    tokenP=strtok(NULL,"##");
//    card.times=0;
//    n=strlen(tokenP);
//    for(i=n-1;i>=0;i--){
//        card.times+=(int)(tokenP[i]-'0')*pow(10,n-1-i);
//    }
//    tokenP=strtok(NULL,"##");
//    card.last=0;
//    n=strlen(tokenP);
//    for(i=n-1;i>=0;i--){
//        card.last+=(long long)(tokenP[i]-'0')*pow(10,n-1-i);
//    }
//    tokenP=strtok(NULL,"##");
//    card.start=0;
//    n=strlen(tokenP);
//    for(i=n-1;i>=0;i--){
//        card.start+=(long long)(tokenP[i]-'0')*pow(10,n-1-i);
//    }
//    tokenP=strtok(NULL,"##");
//    card.tEnd=0;
//    n=strlen(tokenP);
//    for(i=n-1;i>=0;i--){
//        card.tEnd+=(long long)(tokenP[i]-'0')*pow(10,n-1-i);
//    }
//    tokenP=strtok(NULL,"##");
//    card.del=tokenP[0]-'0';
//    return card;
//}
struct Card parsecard(char *pubf){
    struct Card card;
    char *tokenP;
    //int n,i=0,j=-2;
    tokenP=strtok(pubf,"##");
    strcpy(card.num,tokenP);
    tokenP=strtok(NULL,"##");
    strcpy(card.pn,tokenP);
    tokenP=strtok(NULL,"##");
    card.status=atoi(tokenP);
    tokenP=strtok(NULL,"##");
    //n=strlen(tokenP);
    card.rest=atof(tokenP);
    tokenP=strtok(NULL,"##");
    card.already=atof(tokenP);
    tokenP=strtok(NULL,"##");
    card.times=atoi(tokenP);
    tokenP=strtok(NULL,"##");
    card.last=atol(tokenP);
    tokenP=strtok(NULL,"##");
    card.start=atol(tokenP);
    tokenP=strtok(NULL,"##");
    card.tEnd=atol(tokenP);
    tokenP=strtok(NULL,"##");
    card.del=atoi(tokenP);
    return card;
}
int readcard(){
    listp card1;
    struct Card a;
    char s[1000];
    initCardList();
   if((fp=fopen("card_service.txt","r"))==NULL){
    return 0;
   }
   while(!feof(fp)){
      if((fscanf(fp,"%s",s))==0){
           // printf("false3");
          return 0;
          //printf("false");
      }

            else{
                if(feof(fp)){
                    break;
                }
        a=parsecard(s);
        card1=malloc(sizeof(List));
        card1->t=a;
        card1->next=NULL;
        //printf("%s",card1->t.num);
        //printf("du");
        if(head==NULL){
            head=card1;
            cardlist=card1;
           // printf("%s",head->t.num);
        }
        else{
            cardlist->next=card1;
            cardlist=cardlist->next;
            //printf("du");
            //printf("%s",cardlist->t.num);
        }
       }
   }
   fclose(fp);
  //printf("true");
   return 1;
}
int updateCard(const listp pCard,int index){
    int i=0;
    char s[1000];
    long pos=index;
    if((fp=fopen("card_service.txt","r+"))==NULL){
            exit(0);
            return 0;
  }
  while(!feof(fp)&&i<index-1){
    if(fscanf(fp,"%s",s)!=0){
        pos+=strlen(s)+1;
        i++;
        //printf("%s",s);
    }
    else{
            //printf("false3");
        return 0;
       // printf("false");
    }
  }
  fseek(fp,pos,SEEK_SET);//找到要更新信息位置
  fprintf(fp,"%s##%s##%d##%.2lf##%.2lf##%d##%lld##%lld##%lld##%d",pCard->t.num,pCard->t.pn,pCard->t.status,pCard->t.rest,pCard->t.already,pCard->t.times,pCard->t.last,pCard->t.start,pCard->t.tEnd,pCard->t.del);
  fclose(fp);
  return 1;
}
