#ifndef SOURCE_H
#define SOURCE_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
typedef enum{VRAI,FAUX}booleen;
typedef enum{POSITIF,NEGATIF}polarite;
typedef struct{
    char symbole;
    int cpt;
    double BI;
    double BS;
}hash;
#define N 50
#define TAILLE_MOT 5000
#endif
