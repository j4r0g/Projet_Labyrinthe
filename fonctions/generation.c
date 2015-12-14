/**
 * \file 			generation.c
 * \author    Boisson Léo, Bussereau Keryann, Ciron Fabien
 * \version   1.0
 * \date      14 décembre 2015
 * \brief     Gère la génération des insectes et nourritures au début du programme
 * \details   Ce module à pour but de générer un insecte de façon aléatoire dans le labyrinthe
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../header/struct_lab.h"
#include "./../header/struct_ins.h"

/**
 * \brief   Génère aléatoirement de la nourriture dans une case
 * 					vide du labyrinthe et qui n'a pas besoin d'être dévouverte.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 */

void gene_nour(t_lab lab[X][Y]) {
	srand(time(NULL));
	int nombrex, nombrey;
	nombrex = rand()%X;
	nombrey = rand()%Y;
	while(lab[nombrex][nombrey].etat!=vide){
		nombrex = rand()%X;
		nombrey = rand()%Y;
	}
	lab[nombrex][nombrey].etat=food;
}
