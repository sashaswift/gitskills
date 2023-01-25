#ifndef BILLING_FILES
#define BILLING_FILES
#include "model.h"
FILE *fp1;
int saveBilling(Billing bill);
int readBilling();
long getBillingCount ();
int updateBilling(Billing bill);
//int printBillingRecord(char*pNum,time_t startdate,time_t enddate);
#endif // BILLING_FILES
