// TAD que implementa a população (solução) do Caixeiro Viajante
#include <Parametros.h>
#include <algorithm>
using namespace std;

typedef struct cidade_improved_gx {
	int cidade;
	double distancia;
	list<int>::iterator iterador;
} Cidade_Improved_GX;

struct less_than_distance
{
    inline bool operator() (Cidade_Improved_GX cidade1, Cidade_Improved_GX cidade2)
    {
    	double distanciaCidade1 = cidade1.distancia;
    	double distanciaCidade2 = cidade2.distancia;
    	return (distanciaCidade1 < distanciaCidade2);
    }
};

class Individuo {
private:
	double fitness;

public:
	int trajeto[Parametros::NUMERO_DE_CIDADES];
	Individuo() {
			sortearTrajeto();
		}

	Individuo(int cidades[Parametros::NUMERO_DE_CIDADES]) {
		sortearTrajeto(cidades);
	}

	// Sortear Trajeto

	void sortearTrajeto()
	{
		copy(Parametros::cidades, Parametros::cidades + Parametros::NUMERO_DE_CIDADES, trajeto);
		random_shuffle(trajeto, trajeto + Parametros::NUMERO_DE_CIDADES);
		setFitness();
	}

	// Sortear Trajeto

	void sortearTrajeto(int cidades[Parametros::NUMERO_DE_CIDADES])
	{
		copy(cidades, cidades + Parametros::NUMERO_DE_CIDADES, trajeto);
		random_shuffle(trajeto, trajeto + Parametros::NUMERO_DE_CIDADES);
		setFitness();
	}


	// Imprimir Circuito
	void imprimeTrajeto() {
		for (int i = 0; i < Parametros::NUMERO_DE_CIDADES; i ++) {
			cout << trajeto[i] << ' ';
		}
	}

	void setFitness()
	{
		fitness = 0.0;

		for (int i = 0; i < Parametros::NUMERO_DE_CIDADES - 1; i ++)
		{
			fitness += Parametros::distancias[trajeto[i]][trajeto[i+1]];
		}

		fitness += Parametros::distancias[trajeto[Parametros::NUMERO_DE_CIDADES - 1]][trajeto[0]];
	}

	void setForcedFitness(double new_fitness)
	{
			fitness = new_fitness;
	}

	double getFitness() {
		return fitness;
	}

	Individuo mutacao()
	{
		Individuo individuo_mutado;
		copy(trajeto, trajeto + Parametros::NUMERO_DE_CIDADES, individuo_mutado.trajeto);
		int i = rand()%Parametros::NUMERO_DE_CIDADES;
		int j = rand()%Parametros::NUMERO_DE_CIDADES;
		int aux = individuo_mutado.trajeto[i];
		individuo_mutado.trajeto[i] = individuo_mutado.trajeto[j];
		individuo_mutado.trajeto[j] = aux;
		individuo_mutado.setFitness();

		return individuo_mutado;
	}

	Individuo crossover(Individuo individuo)
	{
		Individuo individuo_crossover;

		Cidade_Improved_GX cidade_atual_individuo1, cidade_anterior_individuo1, cidade_posterior_individuo1, cidade_atual_individuo2, cidade_anterior_individuo2, cidade_posterior_individuo2;
		list<int> lista_duplamente_encadeada_individuo1(trajeto, trajeto + Parametros::NUMERO_DE_CIDADES), lista_duplamente_encadeada_individuo2(individuo.trajeto, individuo.trajeto + Parametros::NUMERO_DE_CIDADES);

		cidade_atual_individuo1.cidade = rand()%Parametros::NUMERO_DE_CIDADES;
		cidade_atual_individuo2.cidade = cidade_atual_individuo1.cidade;
		individuo_crossover.setForcedFitness(0.0);

		for (int i=0; i < Parametros::NUMERO_DE_CIDADES; i++)
		{
			if (i == 121)
			{
				int a = 0;
			}


			individuo_crossover.trajeto[i] = cidade_atual_individuo1.cidade;
			if (i != 0)
			{
				individuo_crossover.setForcedFitness(individuo_crossover.getFitness() + cidade_atual_individuo1.distancia);

				if (i == (Parametros::NUMERO_DE_CIDADES - 1))
				{
					individuo_crossover.setForcedFitness(individuo_crossover.getFitness() + Parametros::distancias[individuo_crossover.trajeto[i]][individuo_crossover.trajeto[0]]);
				}
			}

			cidade_atual_individuo1.iterador = std::find(lista_duplamente_encadeada_individuo1.begin(), lista_duplamente_encadeada_individuo1.end(), cidade_atual_individuo1.cidade);
			cidade_atual_individuo2.iterador = std::find(lista_duplamente_encadeada_individuo2.begin(), lista_duplamente_encadeada_individuo2.end(), cidade_atual_individuo2.cidade);

			cidade_anterior_individuo1.iterador = cidade_atual_individuo1.iterador;
			if (cidade_anterior_individuo1.iterador == lista_duplamente_encadeada_individuo1.begin())
			{
				cidade_anterior_individuo1.iterador = lista_duplamente_encadeada_individuo1.end();
			}
			advance(cidade_anterior_individuo1.iterador,-1);
			cidade_anterior_individuo1.cidade = *cidade_anterior_individuo1.iterador;
			cidade_anterior_individuo1.distancia = Parametros::distancias[cidade_atual_individuo1.cidade][cidade_anterior_individuo1.cidade];
			cidade_anterior_individuo2.iterador = cidade_atual_individuo2.iterador;
			if (cidade_anterior_individuo2.iterador == lista_duplamente_encadeada_individuo2.begin())
			{
				cidade_anterior_individuo2.iterador = lista_duplamente_encadeada_individuo2.end();
			}
			advance(cidade_anterior_individuo2.iterador,-1);
			cidade_anterior_individuo2.cidade = *cidade_anterior_individuo2.iterador;
			cidade_anterior_individuo2.distancia = Parametros::distancias[cidade_atual_individuo2.cidade][cidade_anterior_individuo2.cidade];

			cidade_posterior_individuo1.iterador = cidade_atual_individuo1.iterador;
			advance(cidade_posterior_individuo1.iterador,1);
			if (cidade_posterior_individuo1.iterador == lista_duplamente_encadeada_individuo1.end())
			{
				cidade_posterior_individuo1.iterador = lista_duplamente_encadeada_individuo1.begin();
			}
			cidade_posterior_individuo1.cidade = *cidade_posterior_individuo1.iterador;
			cidade_posterior_individuo1.distancia = Parametros::distancias[cidade_atual_individuo1.cidade][cidade_posterior_individuo1.cidade];
			cidade_posterior_individuo2.iterador = cidade_atual_individuo2.iterador;
			advance(cidade_posterior_individuo2.iterador,1);
			if (cidade_posterior_individuo2.iterador == lista_duplamente_encadeada_individuo2.end())
			{
				cidade_posterior_individuo2.iterador = lista_duplamente_encadeada_individuo2.begin();
			}

			cidade_posterior_individuo2.cidade = *cidade_posterior_individuo2.iterador;
			cidade_posterior_individuo2.distancia = Parametros::distancias[cidade_atual_individuo2.cidade][cidade_posterior_individuo2.cidade];

			lista_duplamente_encadeada_individuo1.erase(cidade_atual_individuo1.iterador);
			lista_duplamente_encadeada_individuo2.erase(cidade_atual_individuo2.iterador);

			Cidade_Improved_GX cidades[4] = {cidade_anterior_individuo1, cidade_posterior_individuo1, cidade_anterior_individuo2, cidade_posterior_individuo2};
			std::sort(cidades, cidades + 4, less_than_distance());

			cidade_atual_individuo1.cidade = cidades[0].cidade;
			cidade_atual_individuo1.distancia = cidades[0].distancia;
			cidade_atual_individuo2.cidade = cidades[0].cidade;
		}

		return individuo_crossover;
	}
};
