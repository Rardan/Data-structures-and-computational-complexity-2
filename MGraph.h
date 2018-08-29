#pragma once
class MGraph
{
	int n; //liczba wierzcho�k�w
	int m; //liczba kraw�dzi
	int **tab; //macierz
	int *weight; //wagi
	int e_count; //licznik dodanych kraw�dzi
public:
	MGraph(int = 0, int = 0);
	~MGraph();
	void addEdge(int, int, int = 0); //dodawanie kraw�dzi do macierzy w czasie wcztywania grafu
	void addEdgeNS(int, int, int = 0); //dodawanie kraw�dzi do macierzy w czasie wcztywania grafu
	int getSum(); //zwraca sum� wag drzewa
	void print(); //wypisanie macierzy incydencji
	void load(bool); //wczytuje struktur� z pliku
	void erase(); //usuwa struktur�
	MGraph* prim();
	MGraph* dijkstra(int, int);
};

