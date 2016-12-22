#ifndef SOMMET_H
#define SOMMET_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

extern int debug, verbose;

class Sommet
{

public:
	Sommet();
	Sommet(int sommet, int couleur);
	virtual ~Sommet();

	void addArc(Sommet *s);
	void setSommet(int s);
	void setCouleur(int c);
	bool removeArc(Sommet *s);
	bool isAdjacent(Sommet *s);
	int getSommet();
	int getCouleur();
	int getDegres();

	friend bool operator<(const Sommet& s, const Sommet& s2){
		return s.arcs.size() < s2.arcs.size();
	}

	friend bool operator>(const Sommet& s, const Sommet& s2){
		return s.arcs.size() > s2.arcs.size();
	}

	friend ostream& operator<<(ostream& out, Sommet& s){
		out << "(" << s.sommet << "[" << s.couleur << "], (";
		for (auto a : s.arcs){
			out << a->sommet << "[" << a->couleur << "] ";
		}
		out << "));";
		return out;
	}

private:

protected:	
	int sommet;
	int couleur;
	vector<Sommet*> arcs;
};

#endif // SOMMET_H
