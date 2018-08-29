#pragma once
#include "Edge.h"
// Przemys³aw Skoneczny 234946

class Heap
{
	Edge *tab;
	int size;
public:
	Heap();
	~Heap();
	void push(int, int, int); //dodaje element do kopca
	void pop(); //usuwa korzeñ z kopca
	Heap& operator=(const Heap &obj); //operator przypisania
	void clear();
	int getSize(); //zwraca rozmiar struktury
	Edge* getRoot();
	bool isEmpty();
};
