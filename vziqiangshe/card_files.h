#ifndef CARD_FILES
#define CARD_FILES
#include "card_service.h"
FILE *fp;
int savecard(struct Card card);
int readcard();
struct Card parsecard(char *pubf);
long getcardcount();
int updateCard(const listp pCard,int index);
#endif // CARD_FILES

