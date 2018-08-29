#include "stdafx.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "MGraph.h"
#include "LGraph.h"

using namespace std;

Menu::Menu()
{
	MGraph m, *m1, mn, *m2;
	LGraph l, *l1, ln, *l2;
	int n;
	while (1)
	{
		cout << "Menu" << endl;
		cout << "--------------" << endl;
		cout << "1. Wczytaj dane z pliku" << endl;
		cout << "2. Wygeneruj graf losowo" << endl;
		cout << "3. Wyswietl graf listowo i macierzowo" << endl;
		cout << "4. Algoytm Prima" << endl;
		cout << "5. Algorytm Dijkstry" << endl;
		cout << "6. Autor" << endl;
		cout << "Wybor: ";
		cin >> n;

		switch (n)
		{
		case 1:
			system("cls");
			l.load(true);
			ln.load(false);
			m.load(true);
			mn.load(false);
			break;
		case 2:
			system("cls");
			int v, d;
			cout << "Podaj liczbe wierzcholkow: "; cin >> v;
			cout << "Podaj gestosc: "; cin >> d;
			generate(v, d);
			break;
		case 3:
			system("cls");
			cout << "Skierowany" << endl;
			l.print();
			cout << "Nieskierowany" << endl;
			ln.print();
			cout << "lista waga: " << l.getSum() << endl << endl;
			cout << "Skierowany" << endl;
			m.print();
			cout << "Nieskierowany" << endl;
			mn.print();
			cout << "macierz waga: " << m.getSum() << endl;
			break;
		case 4:
			system("cls");
			l1 = ln.prim();
			m1 = mn.prim();
			break;
		case 5:
			system("cls");
			int x, y;
			cout << "Podaj wierzcholek poczatkowy: "; cin >> x;
			cout << "Podaj wierzcholek koncowy: "; cin >> y;
			cout << "Macierzowo: " << endl;
			l2 = l.dijkstra(x, y);
			cout << "Listowo: " << endl;
			m2 = m.dijkstra(x, y);
			break;
		case 6:
			system("cls");
			cout << "Przemyslaw Skoneczny" << endl;
			cout << "Indeks: 234946" << endl;
			break;
		default:
			system("cls");
			cout << "Podano bledna wartosc!" << endl;
			break;
		}
	}
}


Menu::~Menu()
{
}

void Menu::generate(int v, int d)
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
			v1 = rand() % (v) + 0;
			v2 = v1;
			while (v1 == v2)
				v2 = rand() % (v)+0;

			m = rand() % (v) + 1;
			plik << v1 << " " << v2 << " " << m << endl;
		}
		int g = (200 * e) / (v*(v - 1));
		cout << "Wygenerowano graf dla: " << endl;
		cout << "liczby wierzcholkow: "<< v << endl;
		cout << "liczby krawedzi: " << e << endl;
		cout << "gestosci: " << g << endl;
	}
	plik.close();
}
