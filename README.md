# Description
Le TP contient 2 dossiers : <br/>
 - TP_chps/src : 
   Contient le code source C, le fichier .h, le Makefile, le script gnuplot pour les courbes et les fichiers de données.
 - TP_chps/results :
   Contient les différents résultats de courbes
   
# Utilisation
Pour lancer le code il faut se déplacer dans le répertoire src et lancer la commande :<br/>
	```make```<br/>
Pour nettoyer, vous pouvez utiliser la commande :<br/>
	```make clean```<br/>
Si vous souhaitez faire une courbe du résultat de ||Xk - X(k-1)|| (on utilise la somme des vecteurs obtenus pour l'affichage en courbe), utilisez la commande :<br/>
	```gnuplot plot.gp > "plot.png" ```<br/>
La commande ci-dessous permet de stocker le résultat de la courbe dans l'image plot.png, ensuite il vous suffira juste de l'ouvrir comme toute autre image.<br/>

 - Le script gnuplot.gp utilise les données qui sont stockés dans le fichiers data.dat qui est remplis au fur et à mesure lors du lancement du programme C.<br/>
