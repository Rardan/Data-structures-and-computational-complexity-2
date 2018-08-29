#pragma once

struct Node
{
	Node *next;
	int v;
	int weight;
};

class LGraph
{
	int n; //liczba wierzcho³ków
	int m; //liczba krawêdzi
	int e_count = 0; //licznik dodanych krawêdzi
	Node **node;
public:
	LGraph(int = 0, int = 0);
	~LGraph();
	void add_edge(int, int, int); //dodawanie krawêdzi w czasie wcztywania grafu
	void print(); //wypisanie listy s¹siedztwa
	int getSum(); //zwraca sumê wag drzewa
	void load(bool); //wczytuje strukturê z pliku
	void erase(); //usuwa strukturê
	LGraph* prim();
	LGraph* dijkstra(int, int);
	Node* getNodeList(int); //zwraca wskaŸnik na listê danego elementu
};

