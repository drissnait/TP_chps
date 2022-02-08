#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>

#define epsilon       0.0001
#define damping       0.85
#define nb_iteration_max       150
#define NB_NOEUDS	  7115

float* matriceXvecteur(float** matrice, float* vecteur, int maxData);
int getMax();
float conditionArret(float *vecteur1, float* vecteur2, int maxData);
void pagerank(int maxData);