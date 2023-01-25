//#include <stdio.h>
#include "menu.h"
#include "model.h"
#include "tool.h"

int main(){
   int choice;
   int s;
   printf("欢迎进入网吧计费管理系统!\n");
   printf("----------身份选择----------\n");
   printf("1,管理员\n");
   printf("2,用户\n");
   printf("请选择您的身份：");
   scanf("%d",&s);
   if(s==2){
   printf("欢迎进入计费系统!\n");
   do{
   printf("----------菜单----------\n");
   printf("1,添加卡\n");
   printf("2,查询卡\n");
   printf("3,上机\n");
   printf("4,下机\n");
   printf("5,充值\n");
   printf("6,退费\n");
   printf("7,查询统计\n");
   printf("8,注销卡\n");
   printf("0,退出\n");
   printf("请选择菜单编号(0~8):");
   scanf("%d",&choice);
   switch(choice){
    case 1:
    add();
    break;
    case 2:
    query();
    break;
    case 3:
    logon();
    break;
    case 4:
    settle();
    break;
    case 5:
    addmoney();
    break;
    case 6:
    refundmoney();
    break;
	case 7:
	rate();
	break;
    case 8:
    annul();
    break;
    case 0:
    exitApp();
    break;
	default:
	printf("输入错误，请重新输入\n");
	break;
   }
   }
   while(choice!=0);
  }
   if(s==1){
     int choice2;
     printf("欢迎来到管理员管理系统\n");
     printf("1,添加管理员\n");
     printf("2,管理员等陆\n");
     printf("请选择编号（1~2）：");
     scanf("%d",&choice2);
     switch(choice2){
     case 1:
        addManager();
        break;
     case 2:
        loginManager();
        break;
     }

   }
   return 0;
}
