#ifndef GRAPHE_TOOL_H
#define GRAPHE_TOOL_H

#include <iostream>
#include <fstream>
#include "sommet.h"

typedef vector<Sommet*> Graphe;

// créer un graphe
void creerGraphe(Graphe *g, int nbSommet);
// affiche un graphe
void afficheGraphe(Graphe g);

// lire le fichier de graphe
/**
* If you want to modify a pointer to pointer
* you need to pass a pointer to pointer to pointer.
* src: http://stackoverflow.com/questions/4339201/c-how-to-pass-a-double-pointer-to-a-function
*/
int fillGrapheFromFile(char *filename, Graphe *g);

// coloration de graphe
int colorGraphe(Graphe g);
// dit si tous les sommets ont été coloré
bool colorationStop(Graphe g);
// dit avant d'ajouter si il est adjacent a un autre de meme couleur
bool sameColorAdjacent(Sommet *s, vector<Sommet*> v);
// sauvegarder dans un fichier la coloration
void saveInFile(char *savefile, int k, Graphe g);

#endif // GRAPHE_TOOL_H