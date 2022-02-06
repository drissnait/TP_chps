#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>

#define epsilon       0.0001

float* matriceXvecteur(float** matrice, float* vecteur, int maxData){
	float * vecteurResultat = NULL;
	vecteurResultat=malloc(maxData*sizeof(vecteurResultat));
	for (int i =0; i < maxData;i++){
		for (int j=0; j <maxData;j++){
			vecteurResultat[i]+=matrice[i][j]*vecteur[j];
		}
	}
	return vecteurResultat;
}


int getMax(){
	const char* commentaire="#";

	int c;
	FILE *file;
	file = fopen("Wiki-Vote.txt", "r");
	
	char * valLigne;
	char * resStrSep;
	char * ligneActuel[2];
	int valeur1;
	int valeur2;
	int maxData=0;
	char* ligneSansCommentaire;
	
	const char* fichier = "Wiki-Vote.txt";
	struct stat sb;
	stat(fichier,&sb);
	
	char * data = malloc(sb.st_size);
	int indice;
	
	/*calculer le max pour la taille de notre matrice*/
	while(fscanf(file,"%[^\n] ",data) != EOF){ /*On parcourt tant qu'on est pas arrivé à la fin du fichier*/
		ligneSansCommentaire=strstr(data,commentaire);
		if(!ligneSansCommentaire){
			valLigne=data;
			int indice=0;
			while((resStrSep=strsep(&valLigne,"\t"))!=NULL){
				ligneActuel[indice]=resStrSep;
				indice++;
			}
			valeur1=atoi(ligneActuel[0]);
			valeur2=atoi(ligneActuel[1]);
			if (valeur1 > maxData || valeur2 > maxData){
				if(valeur1>valeur2){
					maxData=valeur1;
				}else{
					maxData=valeur2;
				}
			}
		}
	}
	return maxData;
}

float conditionArret(float *vecteur1, float* vecteur2, int maxData){
	float a =0;
	float b = 0;
	float ret=0;
	for (int i=0;i<maxData;i++){
		a+=vecteur1[i];
		b+=vecteur2[i];
	}
	ret=a-b;
	ret=ret*ret;
	return sqrt(ret);
}

void RemplirMatrice(int maxData){
	maxData=maxData+1;
	const char* commentaire="#";

	int c;
	FILE *file;
	file = fopen("Wiki-Vote.txt", "r");
	
	char * valLigne;
	char * resStrSep;
	char * ligneActuel[2];
	int valeur1;
	int valeur2;
	char* ligneSansCommentaire;
	float fin=1;
	float resultat1=0;
	float resultat2=0;
	float resultatFin=1;
	
	const char* fichier = "Wiki-Vote.txt";
	struct stat sb;
	stat(fichier,&sb);
	
	char * data = malloc(sb.st_size);
	int indice;
	float finIteration=1;
	
	float *nbrOccurence=malloc(maxData *sizeof(nbrOccurence));
	
	float *tabData=malloc(maxData *sizeof(tabData));
	int nbNoeuds=0;

	float *vecteurInitial=malloc(maxData *sizeof(vecteurInitial));
	
	for(int i =0;i<maxData;i++){
		vecteurInitial[i]=1.00/maxData;
	}

	/*printf("affichage vecteur initial : \n");
	for (int i=0; i < maxData; i ++){
		printf("vecteur[%d] : %f \n ", i, vecteurInitial[i]);
	}*/
	
	float **matriceProbabilite=NULL;
	matriceProbabilite=malloc(maxData*sizeof(*matriceProbabilite));
	for (int i=0; i<maxData;i++){
		matriceProbabilite[i]=malloc(maxData*sizeof(*(matriceProbabilite[i])));
	}
	if(*matriceProbabilite==NULL){
		fprintf(stderr,"malloc impossible\n");
		exit(1);
	}
	
	char ** matrice=NULL;
	matrice=malloc(maxData*sizeof(*matrice));
	for (int i=0; i<maxData;i++){
		matrice[i]=malloc(maxData*sizeof(*(matrice[i])));
	}
	if(*matrice==NULL){
		fprintf(stderr,"malloc impossible\n");
		exit(1);
	}
	/*On remplit la matrice de probabilite de 0 partout au debut*/
	for(int i=0;i<maxData;i++){
		for(int j=0;j<maxData;j++){
			matrice[i][j]='0';
		}
	}

	/*for (int i=0; i < maxData; i ++){
		for (int j=0; j < maxData; j ++){
			printf("matrice[%d][%d] : %c \n ", i, j, matrice[i][j]);
		}
	}*/

   
	
	while(fscanf(file,"%[^\n] ",data) != EOF){ /*On parcourt tant qu'on est pas arrivé à la fin du fichier*/
		ligneSansCommentaire=strstr(data,commentaire);
		if(!ligneSansCommentaire){
			valLigne=data;
			indice=0;
			while((resStrSep=strsep(&valLigne," \t")) != NULL){
				ligneActuel[indice]=resStrSep;
				indice++;
			}
			//printf("ligne actuelle %c: \n",ligneActuel[0]);
			valeur1=atoi(ligneActuel[0]);
			valeur2=atoi(ligneActuel[1]);
			tabData[valeur1]=1;
			tabData[valeur2]=1;
			matrice[valeur1][valeur2]='1';
			nbrOccurence[valeur1]+=1.0f; /*nbr Occurence contient le nbr de fleches sortantes de chaque arret*/
		}
	}
	/*Get number of nodes*/
	int indTabData=0;

	while (indTabData<maxData){
		if(tabData[indTabData]==1){
			nbNoeuds++;
		}
		indTabData++;
	}
	printf("nombre de noeuds : %d \n", nbNoeuds);
	/*for (int i=0; i < maxData; i ++){
		for (int j=0; j < maxData; j ++){
			if(matrice[i][j]=='1'){
				printf("matrice[%d][%d] : %c \n ", i, j, matrice[i][j]);
			}
		}
	}*/
	printf("\n\n --------------nommbreoccurences ---------------:\n\n");
	for (int i=0;i<maxData;i++){
		//printf("nbrOccurence[%d] : %f \n ", i, nbrOccurence[i]);
	}
	/*Tableau de prob*/
	/*for(int i=0; i<maxData;i++){
		if(nbrOccurence[i]!=0){
			nbrOccurence[i]=(float)1/nbrOccurence[i];
		}
	}*/
	
	/*for (int i=0;i<maxData;i++){
		printf("nbrOccurence[%d] : %f \n ", i, nbrOccurence[i]);
	}*/
	
	for (int i=0;i<maxData;i++){
		for(int j =0;j<maxData;j++){
			if(matrice[i][j]=='1'){
				matriceProbabilite[j][i]=(float)1/nbrOccurence[i];/*ou ji ????*/
			}
		}
	}

	for(int i=0; i<maxData;i++){
		if (tabData[i]==1){
			nbrOccurence[i]=(float)1/nbNoeuds;
		}
	}
	/*for (int i=0; i < maxData; i ++){
		for (int j=0; j < maxData; j ++){
			if (matriceProbabilite[i][j]!=0){
				printf("matrice Probabilite[%d][%d] : %f \n ", i, j, matriceProbabilite[i][j]);
			}
		}
	}*/
	
	float* vecteurResultat=NULL;
	vecteurResultat=malloc(maxData*sizeof(vecteurResultat));
	float* vecteurComparaison=NULL;
	vecteurComparaison=malloc(maxData*sizeof(vecteurResultat));
	for (int i =0; i<maxData;i++){
		vecteurResultat[i]=0.00;
	}
	for (int i =0; i<maxData;i++){
		vecteurComparaison[i]=0.00;
	}
	
	int num;
	FILE *fptr;

	fptr = fopen("data.dat","w");

	if(fptr == NULL)
	{
		printf("Erreur ouverture du fichier!");   
		exit(1);             
	}



	int iter=0;
	while(finIteration > epsilon){
		if (iter==0){
			vecteurResultat=matriceXvecteur(matriceProbabilite,nbrOccurence,maxData);
			/*printf("\n\nVecteur depart : \n");
			for (int i=0;i<maxData; i++){
				printf("vecteur[%d] : %f\n", i, nbrOccurence[i]);
			}
			printf("\n\n");

			for (int i=0;i<maxData; i++){
				for(int j=0; j < maxData; j ++){
					printf("  %f	", matriceProbabilite[i][j]);
				}
				printf("\n");
			}
			printf("\n\n");
			for (int i=0;i<maxData; i++){
				printf("vecteur[%d] : %f\n", i, vecteurResultat[i]);
			}*/
		}else{
			vecteurResultat=matriceXvecteur(matriceProbabilite,vecteurComparaison,maxData);
		}
		
		
		finIteration=conditionArret(vecteurResultat,vecteurComparaison,maxData);/*condition d'arret*/

		for (int i=0;i<maxData;i++){
			vecteurComparaison[i]=vecteurResultat[i];
		}
		fprintf(fptr,"%d;%f\n",iter,finIteration);
		printf("resultat = %f, iteration  = %d\n", finIteration, iter);
		iter++;
	}
	fclose(fptr);
	fclose(file);
	free(matrice);
	free(data);
}


int main(){
	int nb=getMax();
	printf("le maximum est : %d \n ", nb);
	RemplirMatrice(nb);
	
}
	

