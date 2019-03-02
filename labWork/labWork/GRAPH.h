#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#define maxn 1 << 10

using namespace std;

struct EDGE {
	int to_vertex_no;
	double probability;
};

class GRAPH
{
public:
	int vertex_num, edge_num;
	vector<struct EDGE> graph[maxn];
	bool is_vertex_removed[maxn];/*
								 0 not removed
								 1 have removed
								 */
	GRAPH();
	~GRAPH();
	void store_graph(string graph_file_address, GRAPH pre_graph);
};

