#ifndef INDEXADOR_HPP_
#define INDEXADOR_HPP_
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream> 
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>
#include <strings.h>
#include <vector>
#include <cstdlib>
#include <list>
#include <limits>
#include <string>
#include "Registro.hpp"
#include "Palavra.hpp"
#include "Leitor.hpp"
#include "avl_tree.h"
#include "Lista.hpp"

using namespace std;
class Indexador {
 private:
        avl_tree<Registro> indicesPrimarios; 
        avl_tree<Palavra> indicesSecundarios;

        int argc;
        char **argv;

 public:
    Indexador(int _argc, char **_argv) {
        argc = _argc;
        argv = _argv;
    }

    void indexar() {
        gerarIndex();
        gerarPrimarias();
        gerarSecundarias();
    }

    void gerarIndex() {
        for(int i = 1; i < argc; i++) {

            Leitor *read = new Leitor(argv[i]);
            Registro mr = read->ler_arquivo();

            indicesPrimarios.insere(mr);

            string temp, comando = mr.retornarComando();
            stringstream stream(mr.retornarConteudo());
            while(stream >> temp) {

                transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
                if(temp.size() > 2) {
                    try{
                        indicesSecundarios.busca(temp).adicionarComandosQueContem(comando);
                    } catch (std::range_error& e) {
                        Palavra p(temp);
                        p.adicionarComandosQueContem(comando);
                        indicesSecundarios.insere(p);
                    }
                }

                temp.clear();
            }
            cout << comando << " indexado." << endl;
        }
    }
    void gerarPrimarias() {
        ofstream arquivoSaida("chavesPrimarias.dat");  

        if (arquivoSaida.is_open()) {
            vector<Registro> registrosEmOrdem = indicesPrimarios.breadth_first();
            
            for(int i = 0; i < registrosEmOrdem.size(); i++) {
                arquivoSaida << registrosEmOrdem.at(i).retornarComando(); 
                arquivoSaida << " ";
                arquivoSaida << registrosEmOrdem.at(i).retornarConteudo();
                arquivoSaida << "\3";
            }
            vector<Registro>().swap(registrosEmOrdem);
            arquivoSaida.close();
        }
    }
    void gerarSecundarias(){
        
        ofstream chavesSecundarias("chavesSecundarias.dat");
        
        if (chavesSecundarias.is_open()) {            
            vector<Palavra> palavrasEmOrdem = indicesSecundarios.breadth_first();
            
            for(int i = 0; i < palavrasEmOrdem.size(); i++) {                
                chavesSecundarias << palavrasEmOrdem.at(i).retornarPalavra();
                Lista<string> comandos = palavrasEmOrdem.at(i).retornarComandosQueContem();
                
                for(int j = 0; j < comandos.retornaTamanho(); j++) {
                    chavesSecundarias << ' ' << comandos.retornaDado(j);
                }
                chavesSecundarias << endl;
            }
            vector<Palavra>().swap(palavrasEmOrdem);
            chavesSecundarias.close();

        }
    }
};
#endif
