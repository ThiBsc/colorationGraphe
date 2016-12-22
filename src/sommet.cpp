#include "header/sommet.h"

Sommet::Sommet(){
	sommet = 0;
	couleur = 0;
}

Sommet::Sommet(int sommet, int couleur){
	this->sommet = sommet;
	this->couleur = couleur;
}

Sommet::~Sommet(){
	arcs.clear();
}

void Sommet::addArc(Sommet *s){
	arcs.push_back(s);
}

void Sommet::setSommet(int s){
	sommet = s;
}

void Sommet::setCouleur(int c){
	couleur = c;
}

bool Sommet::removeArc(Sommet *s){
	bool erase = false;
	/*auto it = arcs.begin();
	while (it != arcs.end() && !erase){
		if (it == s){
			arcs.erase(it);
			erase = true;
		}
		it++;
	}*/
	return erase;
}

bool Sommet::isAdjacent(Sommet *s){
	if (find(arcs.begin(), arcs.end(), s) != arcs.end())
		return true;
	return false;
}

int Sommet::getSommet(){
	return sommet;
}

int Sommet::getCouleur(){
	return couleur;
}

int Sommet::getDegres(){
	return arcs.size();
}
