#include "stdafx.h"
#include "MGraph.h"
#include "Heap.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

MGraph::MGraph(int x, int y)
{
	n = x;
	m = y;
	e_count = 0;
	tab = new int *[n];
	weight = new int[m];

	for (int i = 0; i < n; i++)
		tab[i] = new int[m];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			tab[i][j] = 0;

	for (int i = 0; i < m; i++)
	{
		weight[i] = 0;
	}
}


MGraph::~MGraph()
{
	erase();
}

void MGraph::addEdge(int v1, int v2, int w)
{
	if (e_count < m)
	{
		tab[v1][e_count] = 1;
		tab[v2][e_count] = -1;
		weight[e_count] = w;
		e_count++;
	}
}

void MGraph::addEdgeNS(int v1, int v2, int w)
{
	if (e_count < m)
	{
		tab[v1][e_count] = 1;
		tab[v2][e_count] = 1;
		weight[e_count] = w;
		e_count++;
	}
}

int MGraph::getSum()
{
	int c = 0;
	for (int i = 0; i < m; i++)
		c += weight[i];
	return c;
}

void MGraph::print()
{
	cout << "Macierz incydencji" << endl;
	cout << "    ";
	for (int i = 0; i < m; i++)
		cout << setw(4) << i;
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << setw(4) << i;
		for (int j = 0; j < m; j++)
			cout << setw(4) << tab[i][j];
		cout << endl;
	}
	cout << setw(4) << "w";
	for (int i = 0; i<m; i++)
		cout << setw(4) << weight[i];
	cout << endl;
}

void MGraph::load(bool s)
{
	fstream plik;
	plik.open("graf.txt", ios::in);

	if (!plik.good())
		cout << "Blad otwarcia pliku!" << endl;
	else
	{
		erase();

		int v1, v2, w;
		plik >> m >> n;

		tab = new int *[n];
		weight = new int[m];

		for (int i = 0; i < n; i++)
			tab[i] = new int[m];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				tab[i][j] = 0;

		while (!plik.eof())
		{
			plik >> v1 >> v2 >> w;
			if (s == true)
				addEdge(v1, v2, w);
			else
				addEdgeNS(v1, v2, w);

		}
		if (s == true)
			cout << "Wczytano graf skierowany do macierzy!" << endl;
		else cout << "Wczytano graf nieskierowany do macierzy!" << endl;
	}
	plik.close();
}

void MGraph::erase()
{
	for (int i = 0; i < n; i++)
		delete[] tab[i];

	delete[] tab;
	delete[] weight;
	n = 0;
	m = 0;
	e_count = 0;
}

MGraph* MGraph::prim()
{
	MGraph *mst = new MGraph(n, n-1);
	Heap heap;
	Edge* edg = new Edge();

	bool* visited = new bool[n];
	
	visited[0] = true;
	for (int i = 1; i < n; i++)
		visited[i] = false;


	int v1 = 0;
	for (int i = 0; i < n - 1; i++) //iterowanie po wierzcho³kach
	{
		for (int e = 0; e < m; e++) //szukanie krawêdzi
		{
			if (tab[v1][e] == 1) //pocz¹tek krawêdzi
			{
				for (int v2 = 0; v2 < n; v2++)
				{
					if (v1 != v2 && (tab[v2][e] == 1)) //koniec krawêdzi
					{
						if (!visited[v2])
						{
							heap.push(v1, v2, weight[e]);
						}
					}
				}
			}
		}


		do
		{
			edg = heap.getRoot(); //pobranie krawêdzi z kolejki
			heap.pop();
			if (edg == nullptr)
				break;
		} while (visited[edg->endV]); //sprawdzenie czy krawêdŸ prowadzi poza drzewo

		if (edg == nullptr)
			break;

		mst->addEdgeNS(edg->startV, edg->endV, edg->weightE);
		visited[edg->endV] = true;
		v1 = edg->endV;

	}

	delete[] visited;

	mst->print();

	cout << "Suma wag drzewa rozpinajacego: " << mst->getSum() << endl;

	return mst;
}

MGraph * MGraph::dijkstra(int start, int end)
{
	Heap heap;
	MGraph dij = MGraph(n, m);
	Edge edg;
	int* d = new int[n]; //tablica kosztów dojœcia
	int* p = new int[n]; //tablica poprzedników na œcie¿ce
	bool* q = new bool[n]; // zbiór q
	for (int i = 0; i < n; i++)
	{
		d[i] = INT32_MAX;
		p[i] = -1;
		q[i] = false;
	}

	if (start > n - 1 || end > n - 1)
	{
		cout << "Nie ma takiego wierzcholka!" << endl;
		return nullptr;
	}

	d[start] = 0;
	
	for (int i = 0; i < n; i++)
	{
		int j, v1;
		for (j = 0; q[j]; j++);
		for (v1 = j++; j < n; j++)
			if (!q[j] && (d[j] < d[v1]))
				v1 = j;
		
		q[v1] = true;

		for (int e = 0; e < m; e++)
		{
			if (tab[v1][e] == 1)
			{
				for (int v2 = 0; v2 < n; v2++)
				{
					if (tab[v2][e] == -1 && v2 != start)
					{
						int cost = d[v1] + weight[e];
						if (cost < d[v2])
						{
							d[v2] = cost;
							p[v2] = v1;
						}
					}
				}
			}
		}

	}

	if (start == end)
	{
		cout << "Sciezka pusta - koszt 0" << endl;
	}
	else if (d[end] == INT32_MAX)
	{
		cout << "Najkrotsza sciezka z " << start << " do " << end << " nie istnieje!" << endl;
	}
	else
	{
		cout << "Sciezka z wierzcholka " << start << " do " << end << ": " << endl;
		int v = end;
		while (v != -1)
		{
			cout << v << " <- ";
			v = p[v];
		}
		cout << endl;
		cout << "Koszt: " << d[end] << endl;
	}

	delete[] d;
	delete[] p;

	return nullptr;
}
