#ifndef PALAVRA_HPP_
#define PALAVRA_HPP_
#include <string>
#include <algorithm>
#include "Lista.hpp"

using namespace std;
class Palavra {
private:

	std::string palavra;
	Lista<string> comandosQueContem;

public:

	Palavra(std::string _palavra) {
		palavra = _palavra;
	}

	void adicionarComandosQueContem(std::string comando) {
		if (!comandosQueContem.contem(comando)) {
			comandosQueContem.adiciona(comando);
		}
	}

	Lista<string> retornarComandosQueContem() {
		return comandosQueContem;
	}

	std::string retornarPalavra() {
		return palavra;
	}
	
	bool operator<(const Palavra& rhs) const {
		return palavra < rhs.palavra;
	}

	bool operator==(const Palavra& rhs) const {
		return palavra == rhs.palavra;
	}

};
#endif
