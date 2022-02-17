#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // for sleep()

#define epsilon       0.00000000001
#define damping       0.85
#define nb_iteration_max       100
#define NB_NOEUDS	  7115

float* calculIteration(float** matrice, float* vecteur, int maxData);
int getMax();
float conditionArret(float *vecteur1, float* vecteur2, int maxData);
void pagerank(int maxData);
