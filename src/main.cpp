#include <getopt.h>
#include <unistd.h>
#include "header/graphe_tool.h"

int help=0, debug=0, verbose=0;
const char *progname = "gcoloration";

void print_help(){
	printf("usage: %s [-OPTION...]\n"
		"\t--help\t\t Show help\n"
		"\t-f exemple.col\t Specify the graphe file to open\n"
		"\t-o exemple.txt\t Specify where to save file\n"
		"\t--debug, -d\t Debug mode\n"
		"\t--verbose, -v\t Verbose mode\n"
		"Ex: gcoloration -f graphe.col -o out.txt\n", progname);
    	exit(0);
}

int main(int argc, char *argv[])
{
	int idxopt, opt;
	char *grapheFile = NULL;
	char *saveFile = NULL;
	struct option t_opt[] =
	{
		{"help",	no_argument,		&help,		1},
		{"debug",	no_argument,		&debug,		2},
		{"verbose",	no_argument,		&verbose,	3},
        {0,         0,              NULL,		0}
	};

	// OPTION LONGUE (-- de la structure) et les courtes dans la chaine (c:)
	while ((opt = getopt_long(argc, argv, "dvf:o:", t_opt, &idxopt )) != -1) {
		switch (opt){
			case 'f':
				grapheFile = new char[strlen(optarg)+1];
				strcpy(grapheFile, optarg);
				break;
			case 'o':
				saveFile = new char[strlen(optarg)+1];
				strcpy(saveFile, optarg);
				break;
			case 'd':
				debug = 1;
				break;
			case 'v':
				verbose = 1;
				break;
			default:
				break;
		}
    }
	if (help || grapheFile==NULL){
		print_help();
	}
	else{
		cout << "Read graphe file..." << grapheFile << endl;
		Graphe graphe;
		fillGrapheFromFile(grapheFile, &graphe);
		int k = colorGraphe(graphe);
		if (debug)
			afficheGraphe(graphe);
		if (saveFile != NULL){
			cout << "Save file..." << saveFile << endl;
			saveInFile(saveFile, k, graphe);
		}

		// libération mémoire
		delete [] grapheFile;
		if (saveFile){
			delete [] saveFile;
		}
		for (Sommet *s : graphe){
			delete s;
		}
		graphe.clear();

		cout << "\nk-coloration -> " << k << endl;
	}
	return 0;
}