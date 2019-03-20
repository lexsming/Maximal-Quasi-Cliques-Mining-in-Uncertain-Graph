#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#define maxn 1 << 10

using namespace std;

struct EDGE {
	int from_vertex_no;
	int to_vertex_no;
	double probability;
	int next;
};

struct PRE_VERTEX {
	bool is_removed;/* 0 not removed , 1 have removed */
	int degree;
	int first;
};

struct NOW_VERTEX {
	int degree;
	int first;
	int pre_pos;
};

class GRAPH
{
public:
	int vertex_num, edge_num;
	PRE_VERTEX *pre_vertex;
	NOW_VERTEX *now_vertex;
	EDGE *pre_edge, *now_edge;

	GRAPH();
	~GRAPH();
	void store_graph(string graph_file_address);
	void lessen_graph();
};

