#ifndef MODEL
#define MODEL
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
struct Card{
    char num[20];//����
    char pn[9];//����
    int status;//״̬,0-δ�ϻ���1-�����ϻ���2-��ע��
    double rest;//���
    double already;//�ۼƽ��
    int times;//ʹ�ô���
    time_t last;//���һ��ʹ��ʱ��
    time_t start;//����ʱ��
    time_t tEnd;//����ʱ��
    int del;//0-δɾ����1-ɾ����
};

struct list123{
    struct Card t;
    struct list123 *next;
};
typedef struct list123 List;
typedef List *listp;

char num[20];
char pn[20];

struct billing{
    char aCardName[20];//����
    time_t tStart;//�ϻ�ʱ��
    time_t tEnd;//�»�ʱ��
    double fAmount;//���ѽ��
    int nStatus;//��״̬��0-δ���㣬1-�ѽ��㣩
    int nDel;//ɾ����־��0-δɾ����1-��ɾ����
};
typedef struct billing Billing;
typedef struct BillingNode{
    Billing data;
    struct BillingNode *next;
}BillingNode,*IpBillingNode;

struct billing_standard{
    time_t starttime;//��ʼʱ��
    //time_t endtime;//����ʱ��
    int unit;//��С�Ʒѵ�Ԫ�����ӣ�
    double charge;//ÿ���Ʒѵ�Ԫ���շ�
    int ratetype;//�շ����0-��ͨ��1-��ҹ��2-����
    double sum;//�շ����Ϊ��ҹ������ǵ��ܼ�
    int del;//0-δɾ����1-��ɾ��
};
typedef struct billing_standard BillingS;
int Ratetype;
typedef struct BillingSNode{
    BillingS data;
    struct BillingSNode *next;
}BillingSNode, *IpBillingSNode;
/*struct record{
    char cardName[20];//����
    time_t operationtime;//����ʱ��
    int operation;//�������0-��ֵ��1-�˷ѣ�
    double money;//����
    int del;//0-δɾ����1-��ɾ��
};
typedef struct record Record;*/
typedef struct PowerShell{
    char name[10];//�û���
    char pn[20];//����
    int privilige;//Ȩ�޵ȼ�
    int del;//0-δɾ����1-��ɾ��
}PowerShell;
typedef struct PowerShellNode{
    PowerShell date;
    struct PowerShellNode *next;
}PowerShellNode,*IpPowerShellNode;
char Name[10];
char Pn[20];
//�ϻ���Ϣ�ṹ�壻
typedef struct LogonInfo
{
    char aCardName[18];//�ϻ����ţ�
    time_t tLogon;//�ϻ�ʱ�䣻
    double fBalance;//�ϻ�ʱ������
}LogonInfo;
//�»���Ϣ�ṹ��
typedef struct SettleInfo{
    char aCardName[20];//����
    time_t tStart;//�ϻ�ʱ��
    time_t tEnd;//�»�ʱ��
    double fAmount;//����
    double fBalance;//���
}SettleInfo;
typedef struct Money{
    char aCardName[20];//����
    time_t tTime;//��ֵ�˷ѵ�ʱ��
    int nStatus;//״̬��0-��ֵ
    double fMoney;//��ֵ�˷ѽ��
    int nDel;//0-δɾ����1-ɾ��
}Money;
typedef struct MoneyInfo{
    char aCardName[20];//����
    double fMoney;//��ֵ�˷ѽ��
    double fBalance;//���
}MoneyInfo;
typedef struct AnnulInfo{
    char aCardName[20];//���ţ�
    double fMoney;//�˿��
}AnnulInfo;
#endif

