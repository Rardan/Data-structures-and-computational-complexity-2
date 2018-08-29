#pragma once

struct Node
{
	Node *next;
	int v;
	int weight;
};

class LGraph
{
	int n; //liczba wierzcho�k�w
	int m; //liczba kraw�dzi
	int e_count = 0; //licznik dodanych kraw�dzi
	Node **node;
public:
	LGraph(int = 0, int = 0);
	~LGraph();
	void add_edge(int, int, int); //dodawanie kraw�dzi w czasie wcztywania grafu
	void print(); //wypisanie listy s�siedztwa
	int getSum(); //zwraca sum� wag drzewa
	void load(bool); //wczytuje struktur� z pliku
	void erase(); //usuwa struktur�
	LGraph* prim();
	LGraph* dijkstra(int, int);
	Node* getNodeList(int); //zwraca wska�nik na list� danego elementu
};

