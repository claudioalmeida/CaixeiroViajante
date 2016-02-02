#include <iostream>
#include <list>
#include <iterator>
#include <Circuito.h>
#include <Individuo.h>
#include <Parametros.h>
#include <stdlib.h>
#include <time.h>
#include <tinyxml.h>
#include <string>
#include <time.h>

using namespace std;

int lerXML()
{
	TiXmlDocument doc;
	if(!doc.LoadFile(Parametros::ARQUIVO_DE_ENTRADA))
	{
	    cerr << doc.ErrorDesc() << endl;
	    return 0;
	}

	TiXmlElement* root = doc.FirstChildElement()->FirstChildElement( "graph" );
	if(root == NULL)
	{
	    cerr << "Failed to load file: No root element."
	         << endl;
	    doc.Clear();
	    return 0;
	}

	int i =-1, j;

	for(TiXmlElement* elem_i = root->FirstChildElement( "vertex" ); elem_i != NULL; elem_i = elem_i->NextSiblingElement())
	{
		i++;
		j = -1;
		for(TiXmlElement* elem_j = elem_i->FirstChildElement(); elem_j != NULL; elem_j = elem_j->NextSiblingElement())
		{
			j++;
			if (i==j)
			{
				Parametros::distancias[i][j] = 0;
				j++;
			}

			Parametros::distancias[i][j] = atof(elem_j->Attribute("cost"));
		}

	}
	j++;
	Parametros::distancias[i][j] = 0;

	doc.Clear();
	return 1;
}

struct less_than_key
{
    inline bool operator() (Individuo individuo1, Individuo individuo2)
    {
    	double fitnessIndividuo1 = individuo1.getFitness();
    	double fitnessIndividuo2 = individuo2.getFitness();
    	return (fitnessIndividuo1 < fitnessIndividuo2);
    }
};

int main(int argc, char *argv[]) {
	Individuo melhor_individuo;

	double melhor_fitness_atual, ultima_melhor_fitness;
	int numero_de_geracoes_desde_mudanca_de_fitness, segundo_individuo_crossover;

	srand(time(0));
	Parametros::SEMENTE_GERADOR_ALEATORIO = rand();
	lerXML();

	for (int i = 0; i < Parametros::NUMERO_DE_CIDADES; i++)
	{
		Parametros::cidades[i] = i;
	}

	vector<Individuo> individuo(Parametros::TAMANHO_DA_POPULACAO);

	for (int i = 0; i < Parametros::NUMERO_DE_CIDADES; i++)
	{
		individuo[i].sortearTrajeto();
	}

	//Individuo individuo[Parametros::TAMANHO_DA_POPULACAO];
	//std::sort(individuo, individuo + Parametros::TAMANHO_DA_POPULACAO, less_than_key());
	std::sort(individuo.begin(), individuo.begin() + Parametros::TAMANHO_DA_POPULACAO, less_than_key());

	melhor_fitness_atual = individuo[0].getFitness();
	ultima_melhor_fitness = individuo[0].getFitness();
	numero_de_geracoes_desde_mudanca_de_fitness = -1;

	clock_t tStart = clock();

	for (int i = 1; i < Parametros::NUMERO_DE_GERACOES; i++)
	{
		if ((melhor_fitness_atual - ultima_melhor_fitness) <= Parametros::LIMITE_DA_DIFERENCA_DE_FITNESS_PARA_CONSIDERAR_ESTAGNADO)
		{
			numero_de_geracoes_desde_mudanca_de_fitness++;
		}
		else
		{
			ultima_melhor_fitness = melhor_fitness_atual;
			numero_de_geracoes_desde_mudanca_de_fitness = 0;
			Parametros::PROBABILIDADE_DE_MUTACAO = Parametros::PROBABILIDADE_INICIAL_DE_MUTACAO;
			Parametros::PROBABILIDADE_DE_CROSSOVER = Parametros::PROBABILIDADE_INICIAL_DE_CROSSOVER;
		}

		if (numero_de_geracoes_desde_mudanca_de_fitness >= Parametros::LIMITE_DE_GERACOES_ESTAGNADAS)
		{
			Parametros::PROBABILIDADE_DE_MUTACAO *= 1.1;
			Parametros::PROBABILIDADE_DE_CROSSOVER *= 0.9;
		}

		for (int j = 0; j < Parametros::TAMANHO_DA_POPULACAO; j++)
		{
			double probabilidade_operacoes_geneticas = rand()%100;

			if (probabilidade_operacoes_geneticas <= Parametros::PROBABILIDADE_DE_MUTACAO)
			{
				individuo.push_back(individuo[j].mutacao());
			}

			if (probabilidade_operacoes_geneticas <= Parametros::PROBABILIDADE_DE_CROSSOVER)
			{
				segundo_individuo_crossover = rand() % Parametros::TAMANHO_DA_POPULACAO;
				individuo.push_back(individuo[j].crossover(individuo[segundo_individuo_crossover]));
			}
		}

		std::sort(individuo.begin(), individuo.end(), less_than_key());
		individuo.resize(Parametros::TAMANHO_DA_POPULACAO);
		ultima_melhor_fitness = individuo[0].getFitness();
		melhor_individuo.setForcedFitness(ultima_melhor_fitness);
		copy(individuo[0].trajeto, individuo[0].trajeto + Parametros::NUMERO_DE_CIDADES, melhor_individuo.trajeto);
	}

	printf("Tempo de execução: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

	melhor_individuo.imprimeTrajeto();
	cout << "\n";
	cout << melhor_individuo.getFitness();
	cout << "\n";



	return 0;
}
