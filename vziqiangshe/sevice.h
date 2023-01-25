#ifndef SERVICE
#define SERVICE
#include "model.h"
//listp dologon(const char *pName,const char *pPn);
SettleInfo Set;
MoneyInfo Moneyinfo;
AnnulInfo annulinfo;
BillingS billingstandard;
PowerShell Power;
int dologon(const char *pName,const char *pPn);
int addCardInfo(struct Card card);
//listp queryCardInfo(char *num);
int queryCardInfo(char*num);
int doSettle(const char *pName,const char *pPn);
double getAmount(IpBillingNode pbill);
void releaseList();
//void releaseList2();
int doAddMoney(const char*pName,const char*pPn);
int doRefundMoney(const char*pName,const char*pPn);
int annulCard(const char*pName,const char*pPn);
int doAddManager(PowerShell powershell);
int doLoginManager(char *pName,char *pPn);
int doAddBillingStandard(BillingS Billingstandard);
int doChangeBillingStandard(BillingS bills);
IpBillingSNode doQueryBillingStandard(int ratetype);
int doChangeManager(char*pName);
int doDeleteManager(char*pName);
int doQueryBillingRecord(char*pNum,time_t startdate,time_t enddate);
double doSumAmount(time_t startdate,time_t enddate);
#endif // SERVICE
