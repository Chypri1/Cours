# MAKEFILE pour TP sur les bibliotheques RPC par Files de Messages
#
#

#
# Object files
#

fich_obj_message = messages.o 
fich_obj_client = client.o commun.o messages.o appeler.o
fich_obj_serveur_RPC_int = serveur_RPC_int.o  commun.o messages.o bib_int_serveur.o
fich_obj_serveur_RPC_string = serveur_RPC_string.o  commun.o messages.o bib_string_serveur.o
fich_obj_serveur_RPC_tab = serveur_RPC_tab.o  commun.o messages.o bib_tab_serveur.o appeler.o

#
# Options for compilation
#

GCCOBJ = gcc -c 
GCCLNK = gcc 


# Option for debugger
opt = -g -Wall -D_DEBUG_
# opt = -O2 -Wall
#
#
#

#
#-------- Mains ---------------
#

BIN = client serveur_RPC_int serveur_RPC_string serveur_RPC_tab

client : $(fich_obj_client)
	$(GCCLNK) $(fich_obj_client) $(opt) -o client -I ./

client.o : client.c messages.h bib_int.h bib_string.h bib_tab.h
	$(GCCOBJ) $(opt) client.c -o client.o -I ./

serveur_RPC_int : $(fich_obj_serveur_RPC_int)
	$(GCCLNK) $(fich_obj_serveur_RPC_int) $(opt) -o serveur_RPC_int -I ./

serveur_RPC_int.o : serveur_RPC_int.c messages.h bib_int_serveur.h
	$(GCCOBJ) $(opt) serveur_RPC_int.c -o serveur_RPC_int.o -I ./

serveur_RPC_string : $(fich_obj_serveur_RPC_string)
	$(GCCLNK) $(fich_obj_serveur_RPC_string) $(opt) -o serveur_RPC_string -I ./

serveur_RPC_string.o : serveur_RPC_string.c messages.h bib_string_serveur.h
	$(GCCOBJ) $(opt) serveur_RPC_string.c -o serveur_RPC_string.o -I ./

serveur_RPC_tab : $(fich_obj_serveur_RPC_tab)
	$(GCCLNK) $(fich_obj_serveur_RPC_tab) $(opt) -o serveur_RPC_tab -I ./

serveur_RPC_tab.o : serveur_RPC_tab.c messages.h bib_tab_serveur.h
	$(GCCOBJ) $(opt) serveur_RPC_tab.c -o serveur_RPC_tab.o -I ./

#
# --- Tests ---
#

#
#-------- Modules -------------
#

commun.o : commun.c commun.h 
	$(GCCOBJ) $(opt) commun.c -o commun.o -I ./

messages.o : messages.c messages.h 
	$(GCCOBJ) $(opt) messages.c -o messages.o -I ./

appeler.o : appeler.c appeler.h 
	$(GCCOBJ) $(opt) appeler.c -o appeler.o -I ./


bib_int_serveur.o : bib_int_serveur.c bib_int_serveur.h
	$(GCCOBJ) $(opt) bib_int_serveur.c -o bib_int_serveur.o -I ./

bib_string_serveur.o : bib_string_serveur.c bib_string_serveur.h
	$(GCCOBJ) $(opt) bib_string_serveur.c -o bib_string_serveur.o -I ./

bib_tab_serveur.o : bib_tab_serveur.c bib_tab_serveur.h
	$(GCCOBJ) $(opt) bib_tab_serveur.c -o bib_tab_serveur.o -I ./

#
#-------- Headers -------------
#

messages.h : commun.h
	touch messages.h

bib_int_serveur.h : bib_int.h
	touch bib_int_serveur.h

bib_string_serveur.h : bib_string.h
	touch bib_string_serveur.h

bib_tab_serveur.h : bib_tab.h
	touch bib_tab_serveur.h

#
#-------- Clean objects -------
#

clean : 
	- rm *.o $(BIN) *~


#
#-------- All executables -------
#

all : $(BIN) 

#
#-------- All tests -------
#

#
#-------- Tags -------
#

tags :
	etags *.c 
