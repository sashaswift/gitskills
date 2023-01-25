#ifndef MODEL
#define MODEL
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
struct Card{
    char num[20];//卡号
    char pn[9];//密码
    int status;//状态,0-未上机，1-正在上机，2-已注销
    double rest;//余额
    double already;//累计金额
    int times;//使用次数
    time_t last;//最后一次使用时间
    time_t start;//开卡时间
    time_t tEnd;//截至时间
    int del;//0-未删除，1-删除；
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
    char aCardName[20];//卡号
    time_t tStart;//上机时间
    time_t tEnd;//下机时间
    double fAmount;//消费金额
    int nStatus;//卡状态（0-未结算，1-已结算）
    int nDel;//删除标志（0-未删除，1-已删除）
};
typedef struct billing Billing;
typedef struct BillingNode{
    Billing data;
    struct BillingNode *next;
}BillingNode,*IpBillingNode;

struct billing_standard{
    time_t starttime;//开始时间
    //time_t endtime;//结束时间
    int unit;//最小计费单元（分钟）
    double charge;//每个计费单元的收费
    int ratetype;//收费类别，0-普通，1-包夜，2-包天
    double sum;//收费类别为包夜或包天是的总价
    int del;//0-未删除，1-已删除
};
typedef struct billing_standard BillingS;
int Ratetype;
typedef struct BillingSNode{
    BillingS data;
    struct BillingSNode *next;
}BillingSNode, *IpBillingSNode;
/*struct record{
    char cardName[20];//卡号
    time_t operationtime;//操作时间
    int operation;//操作类别（0-充值，1-退费）
    double money;//费用
    int del;//0-未删除，1-已删除
};
typedef struct record Record;*/
typedef struct PowerShell{
    char name[10];//用户名
    char pn[20];//密码
    int privilige;//权限等级
    int del;//0-未删除，1-已删除
}PowerShell;
typedef struct PowerShellNode{
    PowerShell date;
    struct PowerShellNode *next;
}PowerShellNode,*IpPowerShellNode;
char Name[10];
char Pn[20];
//上机信息结构体；
typedef struct LogonInfo
{
    char aCardName[18];//上机卡号；
    time_t tLogon;//上机时间；
    double fBalance;//上机时卡的余额；
}LogonInfo;
//下机信息结构体
typedef struct SettleInfo{
    char aCardName[20];//卡号
    time_t tStart;//上机时间
    time_t tEnd;//下机时间
    double fAmount;//消费
    double fBalance;//余额
}SettleInfo;
typedef struct Money{
    char aCardName[20];//卡号
    time_t tTime;//充值退费的时间
    int nStatus;//状态：0-充值
    double fMoney;//充值退费金额
    int nDel;//0-未删除，1-删除
}Money;
typedef struct MoneyInfo{
    char aCardName[20];//卡号
    double fMoney;//充值退费金额
    double fBalance;//余额
}MoneyInfo;
typedef struct AnnulInfo{
    char aCardName[20];//卡号；
    double fMoney;//退款金额；
}AnnulInfo;
#endif

