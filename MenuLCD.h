#ifndef __MENULCD_H_
#define __MENULCD_H_

#include "stdio.h"

typedef struct menuItem
{
	int id;
	char *name;
	char select;
	struct menuItem *up;
	struct menuItem *right;
	struct menuItem *left;
	struct menuItem *down;
} menuItem;


extern menuItem m[6];
extern menuItem m1[3];
extern menuItem m2[3];
extern menuItem m3[3];
extern menuItem m4[3];
extern menuItem m5[3];
extern menuItem m6[3];


void InitMenu();

#endif
