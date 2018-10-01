#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <limits>
#include "Indexador.hpp"
#include "Pesquisador.hpp"

using namespace std;

bool does_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

int main (int argc, char **argv) {
	

	if (!does_file_exist("chavesPrimarias.dat") && !does_file_exist("chavesSecundarias.dat")) {		
	Indexador *index = new Indexador(argc, argv);
	index->indexar();
	}
	
	string escolhaString;
	bool sair = false;	
	int escolha = 0;
		
	do {
		while (escolha < 1 || escolha > 3) {
		cout << "\n1. procurar comando\n" << "2. procurar palavras\n" << "3. sair" << endl;
		getline(cin, escolhaString);
		
		stringstream myStream(escolhaString);
		if (myStream >> escolha)
			break;
		cout << "comando invalido" << endl;		
		}
		
		switch (escolha) {
			case 1: {
				string palavra = "";
				cout << "digite o nome do comando" << endl;
				getline(cin, palavra);
				Pesquisador *pesquisa = new Pesquisador(palavra);
				pesquisa -> procurar_chave_primaria();
				escolha = 0;
				break;
			}
			
			case 2: {
				string palavra = "";
				cout << "digite a(s) palavra(s)" << endl;
				getline(cin, palavra);
				Pesquisador *pesquisa = new Pesquisador(palavra);
				pesquisa -> procurar_chave_secundaria();
				escolha = 0;
				break;
			}
			
			case 3: {
				sair = true;
				break;
			}
		}
	} while (!sair);
}


