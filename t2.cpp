// Trabalho 2 - Árvores binárias de busca
// Considere uma lista de carros, onde cada carro possui os seguintes campos: placa, marca e ano. Crie um programa com os seguintes requisitos:
// A lista deve ser ordenada fisicamente pela placa dos carros.
// Deve ser possivel incluir e excluir carros na lista.
// Deve ser mantida em memória uma árvore binária relativa à placa dos carros.
// Deve ser mantida em memória uma árvore binária cujo percurso seja equivalente à lista ordenada pelo marca.
// Deve ser mantida em memória uma árvore binária cujo percurso seja equivalente à lista ordenada pela ano.
// Deve ser possível buscar carros pela placa, usando a árvore binária auxiliar.
// Deve ser possivel listar os carros ordenadamente pela placa, percorrendo a lista.
// Deve ser possivel listar os carros ordenadamente pelo marca, através da árvore auxiliar.
// Deve ser possivel listar os carros ordenadamente pela ano, através da árvore auxiliar.


#include <iostream>
#include <list>

using namespace std;

template<typename comparador>
struct Arvore {
    comparador dado;
    Arvore<comparador>* esquerda = nullptr;
    Arvore<comparador>* direita = nullptr;

    void insere(comparador no) {
		if (vazio()) {
			dado = no;
			esquerda = new Arvore<comparador>;
			direita = new Arvore<comparador>;
		} else {
			if (no < dado)
				esquerda->insere(no);
			else
				direita->insere(no);
		}
	}

	// remove o elemento da arvore
	bool remove(comparador no) {
		if (vazio())
			return false;
		
		if (no == dado) {
			if (esquerda->vazio() && direita->vazio()) {
				dado = comparador();
				return true;
			} else if (esquerda->vazio()) {
				Arvore<comparador>* aux = direita;
				dado = aux->dado;
				esquerda = aux->esquerda;
				direita = aux->direita;
				aux->esquerda = nullptr;
				aux->direita = nullptr;
				delete aux;
				return true;
			} else if (direita->vazio()) {
				Arvore<comparador>* aux = esquerda;
				dado = aux->dado;
				esquerda = aux->esquerda;
				direita = aux->direita;
				aux->esquerda = nullptr;
				aux->direita = nullptr;
				delete aux;
				return true;
			} else {
				Arvore<comparador>* aux = esquerda;
				while (!aux->direita->vazio())
					aux = aux->direita;
				dado = aux->direita->dado;
				aux->direita->dado = comparador();
				return true;
			}
		} else if (no < dado)
			return esquerda->remove(no);
		else
			return direita->remove(no);
	}

	// busca um elemento na arvore
	comparador* busca(comparador no) {
		if (vazio())
			return nullptr;
		else if (no == dado)
			return &dado;
		else if (no < dado)
			return esquerda->busca(no);
		else
			return direita->busca(no);
	}

    // testa se a arvore esta vazia
	bool vazio() {
		if (dado == comparador())
			return true;
		else
			return false;
	}

	// recebe uma lista (vazia) onde insere os elementos da arvore
	// em ordem
	bool emOrdem(list<comparador>& saida) {
		if (esquerda != nullptr)
			esquerda->emOrdem(saida);
		saida.push_back(dado);
		if (direita != nullptr)
			direita->emOrdem(saida);

		return true;
	}

	// libera a memoria da arvore
	void destroi(void) {
		if (esquerda != nullptr) {
			esquerda->destroi();
			delete esquerda;
		}

		if (direita != nullptr) {
			direita->destroi();
			delete direita;
		}
	}
};

struct Carro {
	string placa;
	string marca;
	int ano;
};

struct ComparadorPlaca {
	Carro carro;

	void inicia(string placa, string marca, int ano){
		carro.placa = placa;
		carro.marca = marca;
		carro.ano = ano;
	}

	bool operator ==(const ComparadorPlaca& b) const{
		return this->carro.placa == b.carro.placa;
	}

	bool operator <(const ComparadorPlaca& b) const{
		return this->carro.placa < b.carro.placa;
	}

	bool operator >(const ComparadorPlaca& b) const{
		return this->carro.placa > b.carro.placa;
	}
};

struct ComparadorMarca {
	Carro carro;

	void inicia(string placa, string marca, int ano){
		carro.placa = placa;
		carro.marca = marca;
		carro.ano = ano;
	}

	bool operator ==(const ComparadorMarca& b) const{
		return this->carro.marca == b.carro.marca;
	}

	bool operator <(const ComparadorMarca& b) const{
		return this->carro.marca < b.carro.marca;
	}

	bool operator >(const ComparadorMarca& b) const{
		return this->carro.marca > b.carro.marca;
	}
};

struct ComparadorAno {
	Carro carro;

	void inicia(string placa, string marca, int ano){
		carro.placa = placa;
		carro.marca = marca;
		carro.ano = ano;
	}

	bool operator ==(const ComparadorAno& b) const{
		return this->carro.ano == b.carro.ano;
	}

	bool operator <(const ComparadorAno& b) const{
		return this->carro.ano < b.carro.ano;
	}

	bool operator >(const ComparadorAno& b) const{
		return this->carro.ano > b.carro.ano;
	}
};

void ordenar_carros_placa(list<Carro>& carros) {
	carros.sort([](Carro a, Carro b) {
		return a.placa < b.placa;
	});
}

int main() {
	list<Carro> carros;

	Arvore<ComparadorPlaca> arvorePlaca;
	Arvore<ComparadorMarca> arvoreMarca;
	Arvore<ComparadorAno> arvoreAno;

	while (true) {
		// ação que o usuário deseja fazer
		cout << "Escolha uma ação: " << endl;
		cout << "0 - Sair" << endl;
		cout << "1 - Incluir carro" << endl;
		cout << "2 - Excluir carro" << endl;
		cout << "3 - Buscar carro" << endl;
		cout << "4 - Listar carros ordenados pela placa" << endl;
		cout << "5 - Listar carros ordenados pela marca" << endl;
		cout << "6 - Listar carros ordenados pela ano" << endl;

		int acao;
		cin >> acao;

		if (acao == 0)
			break;

		switch(acao) {
			case 1: {
				Carro carro;
				cout << "Placa: ";
				cin >> carro.placa;
				cin.ignore();
				cout << "Marca: ";
				getline(cin, carro.marca);
				cout << "Ano: ";
				cin >> carro.ano;


				carros.push_back(carro);
				ordenar_carros_placa(carros);


				ComparadorPlaca comparadorPlaca;
				comparadorPlaca.inicia(carro.placa, carro.marca, carro.ano);
				arvorePlaca.insere(comparadorPlaca);

				ComparadorMarca comparadorMarca;
				comparadorMarca.inicia(carro.placa, carro.marca, carro.ano);
				arvoreMarca.insere(comparadorMarca);

				ComparadorAno comparadorAno;
				comparadorAno.inicia(carro.placa, carro.marca, carro.ano);
				arvoreAno.insere(comparadorAno);

				cout << "Carro incluído com sucesso!" << endl;
			}
			break;

			case 2: {
				string placa;
				cout << "Placa: ";
				cin >> placa;

				ComparadorPlaca comparadorPlaca;
				comparadorPlaca.inicia(placa, "", 0);
				arvorePlaca.remove(comparadorPlaca);

				ComparadorMarca comparadorMarca;
				comparadorMarca.inicia(placa, "", 0);
				arvoreMarca.remove(comparadorMarca);

				ComparadorAno comparadorAno;
				comparadorAno.inicia(placa, "", 0);
				arvoreAno.remove(comparadorAno);

				carros.remove_if([placa](Carro carro) {
					return carro.placa == placa;
				});

				cout << "Carro removido com sucesso!" << endl;
			}
			break;

			case 3: {
				string placa;
				cout << "Placa: ";
				cin >> placa;

				ComparadorPlaca comparadorPlaca;
				comparadorPlaca.inicia(placa, "", 0);
				ComparadorPlaca* carro = arvorePlaca.busca(comparadorPlaca);

				if (carro != nullptr)
					cout << "Carro encontrado: " << carro->carro.placa << " " << carro->carro.marca << " " << carro->carro.ano << endl;
				else
					cout << "Carro não encontrado" << endl;
			}
			break;

			case 4: {
				if (carros.size() == 0)
					cout << "Nenhum carro cadastrado" << endl;
				else {
					for (Carro carro : carros)
						cout << carro.placa << " " << carro.marca << " " << carro.ano << endl;
				}
			}
			break;

			case 5: {
				list<ComparadorMarca> carrosMarca;
				arvoreMarca.emOrdem(carrosMarca);

				if (carrosMarca.size() == 0)
					cout << "Nenhum carro cadastrado" << endl;
				else {
					for (ComparadorMarca carro : carrosMarca) {
						if (!(carro.carro.ano == 0))
							cout << carro.carro.placa << " " << carro.carro.marca << " " << carro.carro.ano << endl;
					}
				}
			}
			break;

			case 6: {
				list<ComparadorAno> carrosAno;
				arvoreAno.emOrdem(carrosAno);

				if (carrosAno.size() == 0)
					cout << "Nenhum carro cadastrado" << endl;
				else {
					for (ComparadorAno carro : carrosAno) {
						if (!(carro.carro.ano == 0))
							cout << carro.carro.placa << " " << carro.carro.marca << " " << carro.carro.ano << endl;
					}
				}
			}
			break;
		}
	}

	arvorePlaca.destroi();
	arvoreMarca.destroi();
	arvoreAno.destroi();
	carros.clear();

    return 0;
}