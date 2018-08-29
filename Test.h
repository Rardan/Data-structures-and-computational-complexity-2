#pragma once
class Test
{
	int tab[5] = { 25, 50, 75, 100, 125 };
	int pr[4] = { 25, 50, 75, 99 };
public:
	Test();
	~Test();
	void prim_l();
	void dijkstra_l();
	void prim_m();
	void dijkstra_m();
	void generate(int, int);
};

