#pragma once

#include <set>

#include "GRAPH.h"


class operate
{
public:
	set <int> vertex_set_X, vertex_set_CandX;
	int vertex_position[maxn];/* 0 no use
							     1 in vertex set X
								 2 in vertex set CandX
							  */

	void insert_into_vertex_set_X(int insert_vertex_no, GRAPH ggraph);
	void insert_into_vertex_set_CandX(int insert_vertex_no, GRAPH ggraph);
	void delete_from_vertex_set_X(int delete_vertex_no, GRAPH ggraph);
	void delete_from_vertex_set_CandX(int delete_vertex_no, GRAPH ggraph);
	operate();
	~operate();
};

