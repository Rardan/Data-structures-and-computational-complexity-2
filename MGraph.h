#pragma once
class MGraph
{
	int n; //liczba wierzcho³ków
	int m; //liczba krawêdzi
	int **tab; //macierz
	int *weight; //wagi
	int e_count; //licznik dodanych krawêdzi
public:
	MGraph(int = 0, int = 0);
	~MGraph();
	void addEdge(int, int, int = 0); //dodawanie krawêdzi do macierzy w czasie wcztywania grafu
	void addEdgeNS(int, int, int = 0); //dodawanie krawêdzi do macierzy w czasie wcztywania grafu
	int getSum(); //zwraca sumê wag drzewa
	void print(); //wypisanie macierzy incydencji
	void load(bool); //wczytuje strukturê z pliku
	void erase(); //usuwa strukturê
	MGraph* prim();
	MGraph* dijkstra(int, int);
};

