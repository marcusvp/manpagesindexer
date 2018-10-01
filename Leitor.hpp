#ifndef LEITOR_HPP_
#define LEITOR_HPP_
#include <iostream>

class Leitor {
 private:
 	string arquivo;

 public:
 	Leitor(string archive) {
 		arquivo = archive;
 	}
    
    Registro ler_arquivo() {
        
        ifstream arquivoLido(arquivo.c_str());
        if (arquivoLido.is_open()) {

            int pos_barra = arquivo.find_last_of("/") + 1;
            int pos_ponto = arquivo.find_last_of(".");
            int quantidadeDeCaracteres = pos_ponto - pos_barra;
            string nomeDoComando = arquivo.substr(pos_barra, quantidadeDeCaracteres);

            char conteudo[200000];
            std::stringstream buffer;
            buffer << arquivoLido.rdbuf(); 
            strcpy(conteudo, buffer.str().c_str());
              
            char comando[80];
            strcpy(comando, nomeDoComando.c_str());

            Registro mr(comando, conteudo);
            arquivoLido.close();
            return mr;
        } else {
            cout << "arquivo nao lido" << endl;
        }
    }

};
#endif
