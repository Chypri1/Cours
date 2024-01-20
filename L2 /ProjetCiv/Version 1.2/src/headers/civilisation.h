#ifndef _CIVILISATION_H_
#define _CIVILISATION_H_


/*stats de civilization globale*/
typedef struct civilization_s{
  int civilization;
  int sciences_globale;
  int culture_globale;
  int nb_ferme;
  int nb_biblio;
  int bonus_sciences;
  int bonus_culture;
}civilization_t;

#endif
