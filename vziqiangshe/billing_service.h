#ifndef BILLING_SERVICE
#define BILLING_SERVICE
#include "model.h"
IpBillingNode billlist;
IpBillingNode bHead;
int addBilling(Billing bill);
void releaseBillingList();
void initBillingList();
int getBilling();
IpBillingNode queryBilling(const char*pName);
#endif // BILLING_SERVICE

