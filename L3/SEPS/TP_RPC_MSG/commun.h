#ifndef _COMMUN_H_
#define _COMMUN_H_

#include <stdio.h>
#include <unistd.h>

typedef enum cr_s {
		   OK ,
		   ERR_NUM_FONC,
		   ERR_NUM_BIB ,
		   ERR_BIB_STRING_TR ,
		   ERR_BIB_TAB_NB ,
		   ERR_MSGSND ,
		   ERR_MSGRCV } cr_t ;

extern void print_cr( const cr_t cr );

#endif
