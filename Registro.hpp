#ifndef REGISTRO_HPP_
#define REGISTRO_HPP_
class Registro {
 public:

	char conteudo[150000];
	char comando[80];

	Registro() { }

	Registro(char _comando[80], char _conteudo[150000]){
		strcpy(comando, _comando);
		strcpy(conteudo, _conteudo);
	}

	char* retornarConteudo() {
		return conteudo;
	}

	char* retornarComando() {
		return comando;
	}
	
	void definirComando(char* novoNome) {
		strcpy(comando, novoNome);
	}
	
	void definirConteudo(char* novoConteudo) {
		strcpy(conteudo, novoConteudo);
	}
	
	bool operator<(const Registro& rhs) const {
		return comando < rhs.comando;
	}
};
#endif
