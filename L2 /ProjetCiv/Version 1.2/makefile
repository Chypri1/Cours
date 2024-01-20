# Option compilation
CCOBJ = gcc -c
CCLNK = gcc

# Valeurs possibles : yes , no
DEBUG = yes

# Valeurs possibles : apple , linux
ARCH = apple

ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -ansi -g -D_DEBUG_
else
	CFLAGS = -Wall -ansi
endif

ifeq ($(ARCH), apple)
	ifeq ($(DEBUG), yes)
		CFLAGS += -D_APPLE_
	else
		CFLAGS += -D_APPLE_
	endif
endif

ifeq ($(ARCH), linux)
	LIBMATH = -lm
	CFLAGS += -D_LINUX_
endif

# Options de compilation communes
CFLAGS += -I include -lSDL2main -lSDL2 -lSDL2_image

# Listes des fichiers source et des cibles
SRCS = src/admin_SDL.c src/arm_long.c src/arm_spec.c src/main.c src/menu.c src/plateau.c src/fonction_civilisation.c src/jeu.c src/bandeau_action.c src/mouvement_personnage.c src/batisseur.c src/colon.c src/guerrier.c src/ville.c
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))
TEST_SRCS = src/tests/test_click.c src/tests/test_plateau.c src/tests/test_jeu.c
TEST_OBJS = $(patsubst src/tests/%.c,obj/%.o,$(TEST_SRCS))

# Commandes
.PHONY: all clean

all: bin/prog bin/test_click bin/test_plateau

bin/prog: $(OBJS)
	$(CCLNK) $(CFLAGS) $^ -o $@

bin/test_click: $(OBJS) $(patsubst src/%.c,obj/%.o,$(filter-out src/plateau.c src/fonction_civilisation.c src/jeu.c,$(SRCS))) obj/test_click.o
	$(CCLNK) $(CFLAGS) $^ -o $@

bin/test_plateau: $(OBJS) $(patsubst src/%.c,obj/%.o,$(filter-out src/jeu.c,$(SRCS))) obj/test_plateau.o
	$(CCLNK) $(CFLAGS) $^ -o $@

# Génération des fichiers objets
obj/%.o: src/%.c
	$(CCOBJ) $(CFLAGS) $< -o $@

obj/tests/%.o: src/tests/%.c
	$(CCOBJ) $(CFLAGS) $< -o $@

clean:
	rm -rf obj/*.o bin/prog bin/test_click bin/test_plateau
