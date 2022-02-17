# Description
Le TP contient 2 dossiers : <br/>
 - **TP_chps/src** : 
   Contient le code source C, le fichier .h, le Makefile, le script gnuplot pour les courbes et les fichiers de données.
 - **TP_chps/results** :
   Contient les différents résultats de courbes
   
# Utilisation
Pour lancer le code il faut se déplacer dans le répertoire **TP_chps/src** et lancer la commande :<br/>
	```make```<br/>
Pour nettoyer, vous pouvez utiliser la commande :<br/>
	```make clean```<br/>
Si vous souhaitez faire une courbe du résultat de ||Xk - X(k-1)|| (on utilise la somme des vecteurs obtenus pour l'affichage en courbe), utilisez la commande :<br/>
	```gnuplot plot.gp > "plot.png" ```<br/>
La commande ci-dessous permet de stocker le résultat de la courbe dans l'image plot.png, ensuite il vous suffira juste de l'ouvrir comme toute autre image.<br/>

Le script gnuplot.gp utilise les données qui sont stockés dans le fichiers data.dat qui est remplis au fur et à mesure lors du lancement du programme C.<br/>
 
Les résultats dans **TP_chps/results** sont : 
  - courbeExecutionDamping.png : courbe que l'on a généré précédement en effectuant plusieurs tests avec différentes valeurs de damping pour obtenir le temps d'éxecution à chaque test
  - histogrammeEpsilonExecution.png  : histogramme que l'on a généré précédement en effectuant plusieurs tests avec différentes valeurs d'epsilon pour obtenir le temps d'éxecution à chaque test
  - resultatParIteration.png : résultats de la somme du vecteur de ||Xk - X(k-1)|| à chaque itération (c'est la même courbe que l'on génére avec la commande " *gnuplot plot.gp > "plot.png"* " dans le répertoire TP_chps/src
