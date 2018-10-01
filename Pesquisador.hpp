#ifndef PESQUISADOR_HPP_
#define PESQUISADOR_HPP_
#include <strings.h>
#include "Lista.hpp"
class Pesquisador {
 private:
    string palavra;

 public:
	Pesquisador(string palavra_) {
		palavra = palavra_;
	}
	
	void procurar_chave_primaria() {
        bool encontrouComando = false;
        ifstream chavesPrimarias("chavesPrimarias.dat");

        string nomeDoComandoAtual, conteudo;
        while(!chavesPrimarias.eof()) {
            chavesPrimarias >> nomeDoComandoAtual;
            if(strcasecmp(nomeDoComandoAtual.c_str(), palavra.c_str()) == 0) {
                getline(chavesPrimarias, conteudo, '\3');
                cout << conteudo << endl;
                encontrouComando = true;
                break;
            } else {
                chavesPrimarias.ignore(numeric_limits<streamsize>::max(), '\3');
            }
        }
        chavesPrimarias.close();
        if (!encontrouComando) {
            cout << "comando nao encontrado" << endl;
        }
    }

    void procurar_chave_secundaria() {
        Lista<string> resultados;
        Lista<string> termos;
        string temp;
        stringstream stream(palavra);
        while (stream >> temp) {
        	termos.adiciona(temp);
        }

        for(int i = 0; i < termos.retornaTamanho(); i++) {
            ifstream chavesSecundarias("chavesSecundarias.dat");
            string temp;
            while(!chavesSecundarias.eof()) {
                chavesSecundarias >> temp;
                if (strcasecmp(temp.c_str(),termos.retornaDado(i).c_str()) == 0) {
                    string linhaInteira;
                    
                    getline(chavesSecundarias, linhaInteira, '\n');
                    temp.clear();

                    stringstream line(linhaInteira);
                    Lista<string> comandosQueContemPalavra;

                    while(line >> temp) {
                        comandosQueContemPalavra.adiciona(temp);
                        temp.clear();
                    }

                    if (resultados.retornaTamanho() > 0) {
                        resultados.interseccao(&comandosQueContemPalavra);
                    } else {
                        swap(resultados, comandosQueContemPalavra);
                    }
                }
            }
        }

        if (resultados.retornaTamanho() > 0) {
            for(int i = 0; i < resultados.retornaTamanho(); i++) {
                cout << resultados.retornaDado(i) << ", ";  
            }
        } else {
            cout << "termos nao encontrados" << endl;
        }

    }

    
};
#endif
