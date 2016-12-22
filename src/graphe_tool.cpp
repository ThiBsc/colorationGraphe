#include "header/graphe_tool.h"

void creerGraphe(Graphe *g, int nbSommet){
	if (verbose)
		cout << "Création du graphe" << endl;
	for (int i=0; i<nbSommet; i++){
		g->push_back(new Sommet(i+1, 0));
	}
}

void afficheGraphe(Graphe g){
	vector<Sommet*>::iterator it;
	for(it=g.begin(); it<g.end(); it++){
		cout << **it << endl;
	}
}

int fillGrapheFromFile(char *filename, Graphe* g){
	if (verbose)
		cout << "Remplissage du graphe" << endl;
	/**
	c -> commentaire
	p col x y -> indique le nombre de sommet et le nombre d'arête
	e x y -> indique un arc
	*/
	FILE *in;
	const int lineSize = 60;
    char s[lineSize];

    in = fopen(filename, "r");
    if (in == NULL) {
    	printf("Error load ->[%s]", filename);
        return 0;
    }
    //fseek(conffile, 0, SEEK_SET);
    while (fgets(s, sizeof(s), in) != NULL) {
        if (s[0] != '\n' && s[0] != 'c') {
        	// p col -> n'arrive qu'une fois par fichier
            if (strstr(s, "p col") != NULL || strstr(s, "p edge") != NULL){
            	// p col 125 209
            	char *tok = strtok(s, " "); // tok = p
            	tok = strtok(NULL, " ");	// tok = col
            	tok = strtok(NULL, " ");	// tok = 125 (nombre sommet)
            	int nbSommet = atoi(tok);
            	tok = strtok(NULL, " ");	// tok = 209 (nombre arc)
            	// int nbArete = atoi(tok);
            	// on prepare la liste d'adjacence
            	creerGraphe(g, nbSommet);
            }
            // c'est une arête
            if (s[0] == 'e' && s[1] == ' ') {
            	// e 8 14
            	int a, b;
                char *tok = strtok(s, " "); // tok = e
                tok = strtok(NULL, " ");	// tok = 8
                a = atoi(tok);
                tok = strtok(NULL, " ");	// tok = 14
                b = atoi(tok);
                // ajout d'un arc
                (*g)[a-1]->addArc((*g)[b-1]);
                if (debug)
                	cout << "addArc(" << a << "," << b << ");" << endl;
            }
        }
    }
    fclose(in);
    return 1;
}

int colorGraphe(Graphe g){
	if (verbose)
		cout << "Coloration du graphe" << endl;
	int nombreChromatique = 0;
	// trier par degres croissant
	sort(g.begin(), g.end(), [](Sommet *s, Sommet *s2){
		return s->getDegres() > s2->getDegres();
	});
	vector<Sommet*> currents;
	// On parcourt tous les sommets
	for(Sommet *s : g){
		// Si il n'est pas colorié, on continue
		if (s->getCouleur() == 0){
			s->setCouleur(++nombreChromatique);
			// On vérifie l'adjacence à tous les sommets
			for(size_t i=0; i<g.size(); i++){
				// Si c'est le meme sommet, on ne fait rien
				if (s->getSommet() != g[i]->getSommet()){
					// Verification de l'adjacence
					if (!s->isAdjacent(g[i]) 
						&& !g[i]->isAdjacent(s)
						&& !sameColorAdjacent(g[i], currents)
						&& g[i]->getCouleur() == 0){
						g[i]->setCouleur(nombreChromatique);
						currents.push_back(g[i]);
					}
				}
			}
		}
		currents.clear();
		if (colorationStop(g)){
			break;
		}
	}
	return nombreChromatique;
}

bool colorationStop(Graphe g){
	bool stop = true;
	for (size_t i=0; i<g.size() && stop; i++) {
		if (g[i]->getCouleur()==0){
			stop = false;
		}
	}
	return stop;
}

bool sameColorAdjacent(Sommet *s, vector<Sommet*> v){
	bool colorAdj = false;
	for (size_t i=0; i<v.size() && !colorAdj; i++){
		if (s->isAdjacent(v[i]) || v[i]->isAdjacent(s)){
			colorAdj = true;
		}
	}
	return colorAdj;
}

void saveInFile(char *savefile, int k, Graphe g){
	if (verbose)
		cout << "Ecriture du fichier de sortie" << endl;
	ofstream file;
	file.open(savefile);
	file << k << "\n";
	for (Sommet *s : g){
		file << s->getCouleur() << " ";
	}
	file.close();
}