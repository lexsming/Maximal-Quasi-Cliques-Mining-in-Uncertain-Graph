#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <set>

#include "operate.h"
#include "GRAPH.h"

using namespace std;

double alpha, gamma;
string graph_file_address;
int min_size;

int main()
{
	operate s;
	GRAPH a;

	s.SetX = NULL;
	getchar();
	s.SetX = s.Insert_into_SetX(1, s.SetX, a.now_vertex, a.now_edge);
	s.SetX = s.Insert_into_SetX(2, s.SetX, a.now_vertex, a.now_edge);
	//Printf_tree(T);
	s.SetX = s.Insert_into_SetX(3, s.SetX, a.now_vertex, a.now_edge);
	//Printf_tree(T);
	s.SetX = s.Insert_into_SetX(6, s.SetX, a.now_vertex, a.now_edge);
	s.SetX = s.Insert_into_SetX(5, s.SetX, a.now_vertex, a.now_edge);
	s.SetX = s.Insert_into_SetX(8, s.SetX, a.now_vertex, a.now_edge);
	s.SetX = s.Insert_into_SetX(7, s.SetX, a.now_vertex, a.now_edge);
	s.SetX = s.Insert_into_SetX(9, s.SetX, a.now_vertex, a.now_edge);
	s.SetX = s.Insert_into_SetX(4, s.SetX, a.now_vertex, a.now_edge);
	s.Printf_tree(s.SetX);
	s.SetX = s.Delete_from_SetX(5, s.SetX, a.now_vertex, a.now_edge);
	printf("\n");
	s.Printf_tree(s.SetX);
	printf("\n");
	s.SetX = s.Delete_from_SetX(2, s.SetX, a.now_vertex, a.now_edge);
	s.Printf_tree(s.SetX);
	getchar();

	system("pause");
	return 0;
}