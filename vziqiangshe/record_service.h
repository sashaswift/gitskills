#ifndef RECORD_SERVICE
#define RECORD_SERVICE
#include "model.h"
IpPowerShellNode pHead;
IpPowerShellNode managerlist;
void initManager();
//void releaseManager();
int getManager();
IpPowerShellNode queryManager(char *pName);
#endif // RECORD_SERVICE
