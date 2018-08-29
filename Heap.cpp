#include "stdafx.h"
#include "Heap.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <string>

// Przemys³aw Skoneczny 234946

using namespace std;

Heap::Heap()
{
	tab = new Edge [0];
	size = 0;
}


Heap::~Heap()
{
	delete[]tab;
	size = 0;
}
/*
void Heap::push(int v1, int v2, int w)
{
	int i, j;
	i = poz++;

	j = (i - 1) >> 1;

	while (i && (tab[j].weightE > w))
	{
		tab[i] = tab[j];
		i = j;
		j = (i - 1) >> 1;
	}
}
*/


void Heap::push(int v1, int v2, int liczba)
{
//	Edge e = Edge(v1, v2, liczba);
	Edge *tabb = new Edge[size + 1];

	for (int i = 0; i < size; i++)
		tabb[i] = tab[i];

	delete[]tab;
	tab = tabb;

	int i = size++;
	int j = (i - 1) / 2;

	while (i && tab[j].weightE > liczba)
	{
		tab[i] = tab[j];
		i = j;
		j = (i - 1) / 2;
	}
	tab[i].startV = v1;
	tab[i].endV = v2;
	tab[i].weightE = liczba;

}

void Heap::pop()
{
	if (size > 0)
	{
		int i, j, value, v1, v2;

		if (size--)
		{
			value = tab[size].weightE;
			v1 = tab[size].startV;
			v2 = tab[size].endV;


			i = 0;
			j = 1;

			while (j < size)
			{
				if (j + 1 < size && tab[j + 1].weightE < tab[j].weightE)
					j++;

				if (value <= tab[j].weightE)
					break;

				tab[i] = tab[j];
				i = j;
				j = 2 * j + 1;
			}

			tab[i].startV = v1;
			tab[i].endV = v2;
			tab[i].weightE = value;
		}

		Edge *tabb = new Edge[size];

		for (int i = 0; i < size; i++)
			tabb[i] = tab[i];

		delete[]tab;
		tab = tabb;
	}
}


Heap & Heap::operator=(const Heap & obj)
{
	size = obj.size;
	tab = new Edge[size];

	for (int i = 0; i < size; i++)
		tab[i] = obj.tab[i];

	return *this;
}

void Heap::clear()
{
	size = 0;
	delete[] tab;
	tab = NULL;
}

int Heap::getSize()
{
	return size;
}

Edge* Heap::getRoot()
{
	if (size <= 0)
		return nullptr;
	Edge *a = new Edge(tab[0].startV, tab[0].endV, tab[0].weightE);
	return a;
}

bool Heap::isEmpty()
{
	if (size > 0)
		return false;
	else return true;
}


