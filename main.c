/**
 * \mainpage Index du Projet Labyrinthe
 *
 * \section intro_sec Introduction
 *
 * Ce projet a pour but de réaliser un Labyrinthe en C, dans le style d'un "jeu de la vie" où des insectes évoluent.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Etape 1: Télécharger le projet
 * \subsection step2 Etape 2: Ouvrir un terminal
 * \subsection step3 Etape 3: Dans le terminal, se placer à la racine du projet
 * \subsection step4 Etape 4: Taper 'make'
 * \subsection step5 Etape 5: Taper './Vielab'
 *
 *
 * \file 			main.c
 * \author    Boisson Léo, Bussereau Keryann, Ciron Fabien
 * \version   1.0
 * \date      14 décembre 2015
 * \brief     Gère l'interface générale avec l'utilisateur
 * \details   Ce module à pour but de demander à l'utilisateur via un menu
 *            l'action qu'il souhaite effectuer, le lancement du programme
 *            ou la visualisation des règles du jeu.
 */

#include <stdio.h>
#include <stdlib.h>
#include "./header/struct_lab.h"
#include "./header/struct_ins.h"
#include "./header/main.h"

t_lab lab[X][Y];
t_fourmi fourmi[Z];


/**
 * \brief   Gère la vérification d'une victoire, une défaite ou aucun des deux.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \return  Un 0 si on a rien, un 1 si on a gagné et un 2 si on a perdu.
 */
int verifvictoire (t_lab lab[X][Y]) {
	int i, j;
	int victoire = 1;
	int defaite = 1;
	for(i=0;i<X;i++) {
	for(j=0;j<Y;j++) {
	  if(victoire && lab[i][j].decouvert==unseen && lab[i][j].etat!=mur){
		victoire=0;
	  }
	  if(defaite && lab[i][j].etat==insecte){
		defaite=0;
	  }
	  if(!defaite && !victoire)
		return 0;
	}
	}
	if(victoire)
	return 1;
	else if(defaite)
	return 2;
	else
	return 4;
}



/**
 * \brief   Affiche les règles du jeu.
 * \return  Un 0 si l'exécution a réussi.
 */
int regles() {
	printf("\n Les règles sont les suivantes :\n\n");
	printf("A chaque tour vous pouvez choisir de :\n");
	printf("- Placer soit 0 ou 1 insecte (géré aléatoirement)\n");
	printf("- Placer entre 1 et 3 de nourriture (géré aléatoirement)\n\n");
	printf("Vous gagnez si vous découvrez tout le labyrinthe.\n");
	printf("Vous perdez si tout vos insectes sont morts.\n");
	printf("Vous avez un certain nombre de tour de réserve de nourriture, il en va de même pour la durée de vie.\n");
	printf("Deux insectes sur des cases adjacentes se battent ou se reproduisent.\n");
	printf("Lorsqu'ils vont mourrir de faim, les insectes devienent vert.\n");
	printf("Ils deviennent rouge lorsqu'ils vont mourir de vieillesse\n");
	printf("Ils devienent noirs lorsqu'ils meurent au prochain tour.\n");
	return 0;
}




/**
 * \brief   Lance le jeux avec une génération du labyrinthe, puis un lancement.
 * \return  Un 0 si l'exécution a réussi, un 1 si elle a été stopée.
 */
int lancement() {
	int i, vic, res=5;
	int bouffe=10;
	int dureevie=30;
	int nb_ins;
	int posx;
	int posy;


	init_lab_rand(lab);							//Initialise le labyrinthe

	gene_ins_deb(bouffe, dureevie, lab, fourmi);//Génération des insectes de départ

	gene_nour(lab); 							//Génération de chaque case de nourriture

	decouvrir(lab);								//Cette fonction actualise la découverte du labyrinthe

	afficherstats(lab, fourmi);
	afficher_lab(lab, fourmi);					//Cette fonction affiche le labyrinthe


	vic=verifvictoire(lab);						//Cette fonction vérifie si on est en situation de victoire (labyrinthe découvert)

	while(vic==0){
		res=actionUser(lab, bouffe, dureevie, fourmi);
		if(res==0) return 1;
		nb_ins=nb_insecte();

		for(i=nb_ins-1; i>=0; i--) {					//Cette boucle gère le déplacement des insectes
			posx=fourmi[i].x;
			posy=fourmi[i].y;
			if(posx>=0 && posx<X && posy>=0 && posy<Y && lab[posx][posy].etat==insecte) {
				deplacement(lab, posx, posy, fourmi, bouffe, dureevie);
				decouvrir(lab);
			}
		}
		afficherstats(lab, fourmi);
		afficher_lab(lab, fourmi);
		vic=verifvictoire(lab);
	}

	if(vic==1)
	printf("Vous avez gagné\n");
	else if(vic==2)
	printf("Vous avez perdu\n");
	else
	printf("Erreur au niveau du lancement\n");
	return 0;
}



/**
 * \brief   Affiche le menu principal et lance soit le lancement soit les
 *          règles du jeu, sinon quitte.
 * \return  Un 0 si l'exécution a réussi.
 */
int main() {
	int choix;
	// Affichage du menu
	do {
	printf("\nMenu : \n");
	printf(" 1 - Voir les règles du jeu\n");
	printf(" 2 - Lancer la partie\n");
	printf(" 3 - Quitter\n");
	printf("Votre choix : ");
	scanf("%d", &choix);

	switch(choix) {
	  case 1 : regles() ; break;
	  case 2 : { 	lancement();
								//Réinitialisation des paramètres
								chang_nb_ins(0);
								break;
							}
	  case 3 : break;
	  default : printf("\nErreur de saisie\n\n"); break;

	}
	}
	while(choix!=3);
	printf("Au revoir !\n");
	return 0;
}
