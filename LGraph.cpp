#include "stdafx.h"
#include "LGraph.h"
#include "Heap.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

LGraph::LGraph(int x, int y)
{
	n = x;
	m = y;

	node = new Node *[n];
	
	for (int i = 0; i < n; i++)
		node[i] = NULL;
}


LGraph::~LGraph()
{
	erase();
}

void LGraph::add_edge(int v1, int v2, int w)
{
	if (e_count < m)
	{
		Node *a = new Node;
		a->v = v2;
		a->weight = w;
		a->next = node[v1];
		node[v1] = a;
		e_count++;
	}
}

void LGraph::print()
{
	cout << "lista sasiedztwa" << endl;
	Node *a;
	for (int i = 0; i < n; i++)
	{
		cout << i << ": ";
		a = node[i];
		
		while (a)
		{
			cout << setw(3) << a->v << "( "<< a->weight << " )";
			a = a->next;
		}
		cout << endl;
	}
}

int LGraph::getSum()
{
	int s = 0;
	Node *a = node[0];
	for (int i = 0; i < n; i++)
	{
		a = node[i];
		while (a)
		{
			s += a->weight;
			a = a->next;
		}
	}
		
	return s;
}

void LGraph::load(bool s)
{
	fstream plik;
	plik.open("graf.txt", ios::in);

	if (!plik.good())
		cout << "Blad otwarcia pliku!" << endl;
	else
	{
		erase();
;
		int v1, v2, w;
		plik >> m >> n;

		node = new Node *[n];

		for (int i = 0; i < n; i++)
			node[i] = NULL;

		for(int i = 0; i < m; i++)
		{
			plik >> v1 >> v2 >> w;
			add_edge(v1, v2, w);

			if (s == false)
			{
				Node *b = new Node;
				b->v = v1;
				b->weight = w;
				b->next = node[v2];
				node[v2] = b;
			}

		}
		if(s == true)
			cout << "Wczytano graf skierowany do listy sasiedztwa!" << endl;
		else cout << "Wczytano graf nieskierowany do listy sasiedztwa!" << endl;
	}
	plik.close();
}

void LGraph::erase()
{
	Node *a, *b;
	for (int i = 0; i < n; i++)
	{
		a = node[i];
		while (a)
		{
			b = a;
			a = a->next;
			delete b;
		}
	}
	delete[] node;
	e_count = 0;
}

LGraph* LGraph::prim()
{
	LGraph* mst = new LGraph(n, n-1);
	Heap heap;
	Edge* edg = nullptr;
	Node* nd = nullptr;
	bool* visited = new bool[n];

	visited[0] = true;
	for (int i = 1; i < n; i++)
		visited[i] = false;
	int v1 = 0;

	for (int i = 0; i < n; i++)
	{
		for (nd = getNodeList(v1); nd; nd = nd->next)
		{
			if (!visited[nd->v])
			{
				heap.push(v1, nd->v, nd->weight);
			}
		}

		do
		{
			edg = heap.getRoot();
			heap.pop();
			if (edg == nullptr)
				break;
		} while (visited[edg->endV]);

		if (edg == nullptr)
			break;

		mst->add_edge(edg->startV, edg->endV, edg->weightE);
		visited[edg->endV] = true;
		v1 = edg->endV;
	}

	mst->print();
	cout << "Suma wag drzewa rozpinajacego: " << mst->getSum() << endl;
	delete[] visited;
	return mst;
}

LGraph * LGraph::dijkstra(int start, int end)
{
	Heap heap;
	LGraph dij = LGraph(n, m);
	Edge edg;
	Node* nd = nullptr;
	int* d = new int[n]; //tablica kosztów dojœcia
	int* p = new int[n]; //tablica poprzedników na œcie¿ce
	bool* q = new bool[n];
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

		for(nd = getNodeList(v1); nd; nd = nd->next)
			if (!q[nd->v] && (d[nd->v] > d[v1] + nd->weight))
			{
				d[nd->v] = d[v1] + nd->weight;
				p[nd->v] = v1;
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

Node * LGraph::getNodeList(int v)
{
	Node* nd = node[v];
	return nd;
}
