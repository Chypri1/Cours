#
# Option compilation 
#

CCOBJ=gcc -c
CCLNK=gcc 

DEBUG=yes
# Valeurs possibles : apple , linux 
ARCH=linux

ifeq ($(DEBUG),yes)
	 CFLAGS=-Wall -g -D_DEBUG_
else
	 CFLAGS=-Wall 
endif


ifeq ($(ARCH),apple)

	ifeq ($(DEBUG),yes)
	      CFLAGS=-Wall  -g -D_DEBUG_ -D_APPLE_ 
	else
	      CFLAGS=-Wall  -D_APPLE_ 
	endif
endif

ifeq ($(ARCH),linux)
	ifeq ($(DEBUG),yes)
	      CFLAGS=-Wall -g -D_DEBUG_ -D_LINUX_
	else
	      CFLAGS=-Wall -D_LINUX_
	endif
endif

LIBS=-lcurses

#
# ------
#
fich_obj_peinture=peinture.o 



#
# Tests (executables+objets)
#

BIN= peinture

peinture : $(fich_obj_peinture) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_peinture) -o peinture $(LIBS)

peinture.o : peinture.c 
	$(CCOBJ) $(CFLAGS)  peinture.c -o peinture.o

#
# Modules (objets)
#

all : $(BIN)

clean :
	- rm *.o

tests :
