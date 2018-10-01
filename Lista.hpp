#ifndef LISTA_ENCADEDADA_HPP_
#define LISTA_ENCADEDADA_HPP_
#include <algorithm>
#include <strings.h>
#include <vector>
template <typename T>
class Lista {
	public:
		Lista() {}
		Lista<T>* interseccao(Lista<T> *outra){
			Lista<T> *interseccao = new Lista<T>();
			T procurado;

			for (int i = this->retornaTamanho()-1; i > 0; i--) {
				procurado = this->retornaDado(i);
				for (int j = outra->retornaTamanho()-1; j > 0; j--) {
					if (outra->retornaDado(j) == procurado) {
						interseccao->adiciona(procurado);
					}
				}
			}

			std::swap(this->l, interseccao->l);
			return interseccao;
		}
		
		void adiciona(T objeto) {
			l.push_back(objeto);
		}


		bool contem(T objeto) {
			return std::find(l.begin(), l.end(), objeto) != l.end();
		}


		T retornaDado(int posicao) {
			return l.at(posicao);
		}


		int retornaTamanho() {
			return l.size();
		}

	private:
		std::vector<T> l;

};
#endif
