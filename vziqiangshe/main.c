//#include <stdio.h>
#include "menu.h"
#include "model.h"
#include "tool.h"

int main(){
   int choice;
   int s;
   printf("��ӭ�������ɼƷѹ���ϵͳ!\n");
   printf("----------���ѡ��----------\n");
   printf("1,����Ա\n");
   printf("2,�û�\n");
   printf("��ѡ��������ݣ�");
   scanf("%d",&s);
   if(s==2){
   printf("��ӭ����Ʒ�ϵͳ!\n");
   do{
   printf("----------�˵�----------\n");
   printf("1,��ӿ�\n");
   printf("2,��ѯ��\n");
   printf("3,�ϻ�\n");
   printf("4,�»�\n");
   printf("5,��ֵ\n");
   printf("6,�˷�\n");
   printf("7,��ѯͳ��\n");
   printf("8,ע����\n");
   printf("0,�˳�\n");
   printf("��ѡ��˵����(0~8):");
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
	printf("�����������������\n");
	break;
   }
   }
   while(choice!=0);
  }
   if(s==1){
     int choice2;
     printf("��ӭ��������Ա����ϵͳ\n");
     printf("1,��ӹ���Ա\n");
     printf("2,����Ա��½\n");
     printf("��ѡ���ţ�1~2����");
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
