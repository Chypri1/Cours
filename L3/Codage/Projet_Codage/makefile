include Makefile.compilation

LDFLAGS= -lm
OBJ_HAD=  obj/hadamard.o
OBJ_PSEUDO= obj/gen_pseudo_alea.o obj/gold.o obj/jpl.o obj/longueur_max.o
OBJ_HDBN_ARITH=obj/saisie.o obj/fonction_hdbn.o obj/fonction_binaire.o obj/decodage_binaire.o obj/fonction_arithmetique.o obj/decodage_arithmetique.o obj/decodage_hdbn.o
BIN= bin/hadamard bin/gen_pseudo_alea bin/hdbn_arith


#executables
bin/hadamard: $(OBJ_HAD)
	$(CCLNK)  $(CFLAGS)  $(OBJ_HAD) -o $@ $(LDFLAGS)

bin/gen_pseudo_alea: $(OBJ_PSEUDO)
	$(CCLNK) $(CFLAGS)  $(OBJ_PSEUDO) -o $@ $(LDFLAGS)

bin/hdbn_arith: $(OBJ_HDBN_ARITH)
	$(CCLNK) $(CFLAGS) $(OBJ_HDBN_ARITH) -o $@ $(LDFLAGS)

#objs
obj/hadamard.o: src/hadamard.c lib/hadamard.h
	$(CCOBJ) $(CFLAGS) -o $@ -c $<

obj/gen_pseudo_alea.o: src/gen_pseudo_alea.c lib/longueur_max.h lib/gold.h lib/jpl.h
	$(CCOBJ) $(CFLAGS) -o $@ -c $<

obj/longueur_max.o: src/longueur_max.c lib/longueur_max.h
	$(CCOBJ) $(CFLAGS) -o $@ -c $<

obj/gold.o: src/gold.c lib/gold.h
	$(CCOBJ) $(CFLAGS) -o $@ -c $<

obj/jpl.o: src/jpl.c lib/jpl.h
	$(CCOBJ) $(CFLAGS) -o $@ -c $<

obj/fonction_hdbn.o: src/codage_hdbn.c 
	$(CCOBJ) $(CFLAGS) -o $@ -c $< 

obj/decodage_hdbn.o: src/decodage_hdbn.c 
	$(CCOBJ) $(CFLAGS) -o $@ -c $<

obj/saisie.o: src/saisi_hdbn_Arith.c lib/codage_arithmetique.h lib/codage_binaire.h lib/codage_hdbn.h lib/decodage_arithmetique.h lib/decodage_binaire.h lib/decodage_binaire.h
	$(CCOBJ) $(CFLAGS) -o $@ -c $<

obj/fonction_binaire.o: src/codage_binaire.c 
	$(CCOBJ) $(CFLAGS) -o $@ -c $< 

obj/decodage_binaire.o: src/decodage_binaire.c 
	$(CCOBJ) $(CFLAGS) -o $@ -c $<

obj/fonction_arithmetique.o: src/codage_arithmetique.c 
	$(CCOBJ) $(CFLAGS) -o $@ -c $< 

obj/decodage_arithmetique.o: src/decodage_arithmetique.c 
	$(CCOBJ) $(CFLAGS) -o $@ -c $< 




all: $(BIN)

clean:
	- rm -rf obj/*.o
	- rm -rf bin/*


