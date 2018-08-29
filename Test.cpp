#include "stdafx.h"
#include "Test.h"
#include "MGraph.h"
#include "LGraph.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <fstream>

using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}


Test::Test()
{
	prim_l();
	dijkstra_l();
	prim_m();
	dijkstra_m();
	system("cls");
	cout << "wykonalo sie!" << endl;
}


Test::~Test()
{
}

void Test::prim_l()
{
	fstream plik;
	plik.open("wyniki_prim_l.txt", ios::out);
	int x, y;
	double t = 0;

	for (int i = 0; i < 4; i++)
	{
		plik << "Prim_l " << pr[i] << "%" << endl;
		for (int j = 0; j < 5; j++)
		{
			t = 0;
			for (int k = 0; k < 100; k++)
			{
				x = rand() % (tab[j]) + 0;
				y = x;
				while (x == y)
					y = rand() % (tab[j]) + 0;

				generate(tab[j], pr[i]);
				LGraph l;
				l.load(false);
				StartCounter();
				l.prim();
				t += GetCounter();
			}
			t = t / 100.0;
			plik << t << endl;
		}
	}
	plik.close();
}

void Test::dijkstra_l()
{
	fstream plik;
	plik.open("wyniki_dijkstra_l.txt", ios::out);
	int x, y;
	double t = 0;

	for (int i = 0; i < 4; i++)
	{
		plik << "Dijkstra_l " << pr[i] << "%" << endl;
		for (int j = 0; j < 5; j++)
		{
			t = 0;
			for (int k = 0; k < 100; k++)
			{
				x = rand() % (tab[j]) + 0;
				y = x;
				while (x == y)
					y = rand() % (tab[j]) + 0;

				generate(tab[j], pr[i]);
				LGraph l;
				l.load(true);
				StartCounter();
				l.dijkstra(x, y);
				t += GetCounter();
			}
			t = t / 100.0;
			plik << t << endl;
		}
	}
	plik.close();
}

void Test::prim_m()
{
	fstream plik;
	plik.open("wyniki_prim_m.txt", ios::out);
	int x, y;
	double t = 0;

	for (int i = 0; i < 4; i++)
	{
		plik << "Prim_m " << pr[i] << "%" << endl;
		for (int j = 0; j < 5; j++)
		{
			t = 0;
			for (int k = 0; k < 100; k++)
			{
				x = rand() % (tab[j]) + 0;
				y = x;
				while (x == y)
					y = rand() % (tab[j]) + 0;

				generate(tab[j], pr[i]);
				MGraph m;
				m.load(false);
				StartCounter();
				m.prim();
				t += GetCounter();
			}
			t = t / 100.0;
			plik << t << endl;
		}
	}
	plik.close();
}

void Test::dijkstra_m()
{
	fstream plik;
	plik.open("wyniki_dijkstra_m.txt", ios::out);
	int x, y;
	double t = 0;

	for (int i = 0; i < 4; i++)
	{
		plik << "Dijkstra_m " << pr[i] << "%" << endl;
		for (int j = 0; j < 5; j++)
		{
			t = 0;
			for (int k = 0; k < 100; k++)
			{
				x = rand() % (tab[j]) + 0;
				y = x;
				while (x == y)
					y = rand() % (tab[j]) + 0;

				generate(tab[j], pr[i]);
				MGraph m;
				m.load(true);
				StartCounter();
				m.dijkstra(x, y);
				t += GetCounter();
			}
			t = t / 100.0;
			plik << t << endl;
		}
	}
	plik.close();
}

void Test::generate(int v, int d)
{
	system("cls");
	srand(time(NULL));
	fstream plik;
	plik.open("graf.txt", ios::out);
	int e = d * (v*(v - 1)) / 200;
	int v1, v2, m;
	if (!plik.good())
		cout << "Nie moza otworzyc pliku graf.txt!" << endl;
	else
	{
		plik << e << " " << v << endl;

		for (int i = 0; i < e; i++)
		{
			v1 = rand() % (v)+0;
			v2 = v1;
			while (v1 == v2)
				v2 = rand() % (v)+0;

			m = rand() % (v)+1;
			plik << v1 << " " << v2 << " " << m << endl;
		}
		int g = (200 * e) / (v*(v - 1));
		cout << "Wygenerowano graf dla: " << endl;
		cout << "liczby wierzcholkow: " << v << endl;
		cout << "liczby krawedzi: " << e << endl;
		cout << "gestosci: " << g << endl;
	}
	plik.close();
}

