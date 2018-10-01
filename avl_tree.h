#ifndef AVL_TREE_H_
#define AVL_TREE_H_
#include <string>
#include <algorithm>
#include <list>
#include <stdexcept>
#include <vector>
#include "doubly_linked_list.h"
template<typename T, template<typename > class Container = doubly_linked_list>
class avl_tree {
	using size_type = std::size_t;
 private:
	struct no {
		no(const T& dado) :
				_altura(1), esquerda(nullptr), direita(nullptr), _dado(dado) {
		}

		size_type _altura;
		no* esquerda;
		no* direita;
		T _dado;
	};
	
	T& busca(no* root, const T& dado) {
		if (root != nullptr) {
			if (dado < root->_dado)
				return busca(root->esquerda, dado);
			if (root->_dado < dado)
				return busca(root->direita, dado);
			else {
				return root->_dado;
			}
		}
		throw std::range_error("");
	}
	
	int fator(no* root) const {
		return (root == nullptr) ?
				0 : altura(root->esquerda) - altura(root->direita);
	}
	
	size_type altura(no* root) const {
		return (root == nullptr) ? 0 : root->_altura;
	}
	
	no* insere(no* root, const T& dado) {
		if (root == nullptr)
			return root = new no(dado);
		else if (dado < root->_dado) {
			root->esquerda = insere(root->esquerda, dado);
			if (fator(root) == 2) {
				if (fator(root->esquerda) == -1)
					root->esquerda = rotateesquerda(root->esquerda);
				root = rotatedireita(root);
			}
		}
		else if (root->_dado < dado) {
			root->direita = insere(root->direita, dado);
			if (fator(root) == -2) {
				if (fator(root->direita) == 1)
					root->direita = rotatedireita(root->direita);
				root = rotateesquerda(root);
			}
		} else
			throw std::exception();

		root->_altura = std::max(altura(root->esquerda), altura(root->direita)) + 1;
		return root;
	}
	
	no* rotateesquerda(no* root) {
		no* aux;
		aux = root->direita;
		root->direita = aux->esquerda;
		aux->esquerda = root;
		root->_altura = std::max(altura(root->esquerda), altura(root->direita)) + 1;
		aux->_altura = std::max(altura(aux->esquerda), altura(aux->direita)) + 1;
		return aux;
	}
	
	no* rotatedireita(no* root) {
		no* aux;
		aux = root->esquerda;
		root->esquerda = aux->direita;
		aux->direita = root;
		root->_altura = std::max(altura(root->esquerda), altura(root->direita)) + 1;
		aux->_altura = std::max(altura(aux->esquerda), altura(aux->direita)) + 1;
		return aux;
	}
	no* remove(no* root, const T& dado) {
		if (root == nullptr)
			throw std::exception();

		else if (dado < root->_dado) {
			root->esquerda = remove(root->esquerda, dado);
			if (fator(root) == 2) {
				if (fator(root->esquerda) == -1)
					root = rotateesquerda(root->esquerda);
				root = rotatedireita(root);
			}
		} else if (root->_dado < dado) {
			root->direita = remove(root->direita, dado);

			if (fator(root) == -2) {
				if (fator(root->direita) == 1)
					root = rotatedireita(root->direita);
				root = rotateesquerda(root);
			}
		}

		else {
			if (root->esquerda == nullptr && root->direita == nullptr) {
				delete root;
				return nullptr;
			}
			if (root->esquerda == nullptr) {
				no* aux = root->direita;
				delete root;
				return aux;
			}
			if (root->direita == nullptr) {
				no* aux = root->esquerda;
				delete root;
				return aux;
			}
			no* aux = root->direita;
			while (aux->esquerda != nullptr)
				aux = aux->esquerda;
			std::swap(root->_dado, aux->_dado);
			root->direita = remove(root->direita, dado);
		}
		root->_altura = std::max(altura(root->esquerda), altura(root->direita)) + 1;
		return root;
	}
	
	void emOrdem(no* root, Container<T>& container) const {
		if (root != nullptr) {
			emOrdem(root->esquerda, container);
			container.push_back(root->_dado);
			emOrdem(root->direita, container);
		}
	}
	
	void preOrdem(no* root, Container<T>& container) const {
		if (root != nullptr) {
			container.push_back(root->_dado);
			preOrdem(root->esquerda, container);
			preOrdem(root->direita, container);
		}
	}
	
	void posOrdem(no* root, Container<T>& container) const {
		if (root != nullptr) {
			posOrdem(root->esquerda, container);
			posOrdem(root->direita, container);
			container.push_back(root->_dado);
		}
	}
	
	no* copiarArvore(no* other_root) {
		no* aux = new no(other_root->_dado);
		aux->esquerda = copiarArvore(other_root->esquerda);
		aux->direita = copiarArvore(other_root->direita);
		return aux;
	}
	
	void deletarArvore(no* root) {
		if (root != nullptr) {
			deletarArvore(root->esquerda);
			deletarArvore(root->direita);
			delete root;
		}
	}

	using self = avl_tree<T>;

public:
	avl_tree() :
			tamanho(0), _root(nullptr) {
	}
	
	avl_tree(const self& other) {
		_root = copiarArvore(other._root);
	}
	
	~avl_tree() {
		deletarArvore(_root);
	}
	
	T& busca(const T& dado) {
		return busca(_root, dado);
	}
	
	bool contem(const T& dado) {
		try {
			busca(_root, dado);
			return true;
		} catch (std::exception& e) {
			return false;
		}
	}
	
	size_type altura() const {
		return altura(_root);
	}
	
	size_type size() const {
		return tamanho;
	}
	
	void insere(const T& dado) {
		_root = insere(_root, dado);
		++tamanho;
	}
	
	void remove(const T& dado) {
		_root = remove(_root, dado);
		--tamanho;
	}
	
	Container<T> emOrdem() const {
		Container<T> container;
		emOrdem(_root, container);
		return container;
	}
	
	Container<T> preOrdem() const {
		Container<T> container;
		preOrdem(_root, container);
		return container;
	}
	
	Container<T> posOrdem() const {
		Container<T> container;
		posOrdem(_root, container);
		return container;
	}
	
	std::vector<T> breadth_first() const {
		Container<no*> nos;
		std::vector<T> dados;
		if (_root != nullptr) {
			nos.push_back(_root);
			
			for (auto no : nos) {
				if (no->esquerda != nullptr) {
					nos.push_back(no->esquerda);
				}
				if (no->direita != nullptr) {
					nos.push_back(no->direita);
				}
				dados.push_back(no->_dado);
			}
		}
		return dados;
	}
	
	private:
		size_type tamanho;
		no* _root;

};

#endif /* AVL_TREE_H_ */
