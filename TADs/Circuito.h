// TAD que implementa as cidades do Caixeiro Viajante
#include <algorithm>
#include <vector>
using namespace std;

class Circuito {
private:
	list<int> cidades;
	int numero_cidades;

public:
	// Construtor
	Circuito(int i = 0) {
		numero_cidades = i;

		for (int j = 0; j < i; j++) {
			cidades.push_back(j);
		}
	}
	;

	// Retornar tamanho do Indivíduo
	int getNumeroCircuito() {
		return numero_cidades;
	}
	;

	// Imprimir Circuito
	void imprimeCircuito() {
		for (list<int>::iterator it = cidades.begin(); it != cidades.end();
				it++) {
			cout << *it << ' ';
		}
	}
	;

	list<int> permutaCircuito() {
		vector<int> myVector(cidades.size());
		copy(cidades.begin(), cidades.end(), myVector.begin());
		srand(time(0));
		random_shuffle(myVector.begin(), myVector.end());
		list<int> myListShuffled(myVector.begin(), myVector.end());
		return myListShuffled;
	}
};
