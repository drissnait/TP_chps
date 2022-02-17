#include "pagerank.h"

/*
Fait le calcul à faire à chaque itération : A=(alpha *Matrice_transition * Vecteur )+((1-alpha)/N * Matrice_Gout *Vecteur)
entree : 
	-matrice : tableau 2D de float)
	-vecteur : tableau 1D de float)
	-maxData : entier représentant la taille de la matrice)
retour :
	-vecteurResultat : tableau 1d représentant le vecteur contenant le résultat du calcul
*/
float* calculIteration(float** matrice, float* vecteur, int maxData){
	float * vecteurResultat = NULL;
	float * vecteurCalcul = NULL;
	int coeff=(1-damping)/(float)maxData;
	vecteurResultat=malloc(maxData*sizeof(vecteurResultat));
	vecteurCalcul=malloc(maxData*sizeof(vecteurCalcul));
	/*alpha * Matrice*/
	for (int i=0;i<maxData;i++){
		for (int j=0;j<maxData;j++){
			matrice[i][j]=matrice[i][j]*damping;
		}
	}
	/*Matrice * vecteur*/
	for (int i =0; i < maxData;i++){
		for (int j=0; j <maxData;j++){
			vecteurResultat[i]+=matrice[i][j]*vecteur[j];
		}
	}

	/*Matrice gout*/
	float **matriceGout=NULL;
	matriceGout=malloc(maxData*sizeof(*matriceGout));
	for (int i=0; i<maxData;i++){
		matriceGout[i]=malloc(maxData*sizeof(*(matriceGout[i])));
		for (int j=0;j<maxData;j++){
			matriceGout[i][j]=1;
		}
	}

	/*coef * matrice gout*/
	for (int i=0;i<maxData;i++){
		for ( int j=0;j<maxData;j++){
			matriceGout[i][j]=matriceGout[i][j]*coeff;
		}
	}

	/* multiplié par le vecteur*/
	for (int i =0; i < maxData;i++){
		for (int j=0; j <maxData;j++){
			vecteurCalcul[i]+=matriceGout[i][j]*vecteur[j];
		}
	}

	/*somme des deux vecteurs*/
	for (int i=0;i<maxData;i++){
		vecteurResultat[i]=vecteurResultat[i]+vecteurCalcul[i];
	}


	return vecteurResultat;
}

/*
Fonction permettant d'avoir le noeud maximum dans notre graphe
retour :
	-maxData : entier représentant la valeur du plus grand noeud
*/
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

/*
La fonction permettant de retourner le résultat ||Xk - X(k-1)|| que l'on compare avec epsilon à chaque itération
entrée :
	-vecteur1 : tableau 1d de float
	-vecteur2 : tableau 1d de float
	-maxData : Taille des vecteurs
retour : 
	-ret : float contenant le résultat du calcul
*/
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

void pageRank(int maxData){
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
	
	while(fscanf(file,"%[^\n] ",data) != EOF){ /*On parcourt tant qu'on est pas arrivé à la fin du fichier*/
		ligneSansCommentaire=strstr(data,commentaire);
		if(!ligneSansCommentaire){
			valLigne=data;
			indice=0;
			while((resStrSep=strsep(&valLigne," \t")) != NULL){
				ligneActuel[indice]=resStrSep;
				indice++;
			}
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
	printf("		nombre de noeuds : %d \n", nbNoeuds);
	
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
		printf("Erreur ouverture du fichier d'écriture de données!");   
		exit(1);             
	}

	int iter=0;
	while( iter <= nb_iteration_max && finIteration > epsilon){
		if (iter==0){
			vecteurResultat=calculIteration(matriceProbabilite,nbrOccurence,maxData);
		}else{
			vecteurResultat=calculIteration(matriceProbabilite,vecteurComparaison,maxData);
		}
		
		finIteration=conditionArret(vecteurResultat,vecteurComparaison,maxData);/*condition d'arret*/

		for (int i=0;i<maxData;i++){
			vecteurComparaison[i]=vecteurResultat[i];
		}
		fprintf(fptr,"%d;%f\n",iter+1,finIteration);
		fflush(fptr);
		printf("		resultat = %f\n", finIteration);
		iter++;
	}
	fclose(fptr);
	fclose(file);
	free(matrice);
	free(data);
}

int main(){
	double time_spent = 0.0;
	clock_t begin = clock();
	int nb=getMax();
	pageRank(nb);
	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
}
	

