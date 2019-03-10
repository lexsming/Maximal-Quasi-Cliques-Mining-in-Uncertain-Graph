#pragma once

#include <set>

#include "GRAPH.h"

struct VERTEX {
	int vertex_no;
	int indeg_vertex_set_X;
	int exdeg_vertex_set_CandX;
	int vertex_position;/* 0 no use
						   1 in vertex set X
						   2 in vertex set CandX
						*/
};

struct MIN_DEG {
	int vertex_no;
	int min_deg;
	//min_deg = indeg + exdeg;
};


class operate
{
public:
	set <int> vertex_set_X, vertex_set_CandX;
	VERTEX OPvertex[maxn];
	MIN_DEG min_deg_vertex;
	int upper_bound_Umin_X, upper_bound_UX, total_indeg_set_X;
	int Lower_bound_Lmin_X, Lower_bound_UX;

	void insert_into_vertex_set_X(int insert_vertex_no, GRAPH &ggraph);
	void insert_into_vertex_set_CandX(int insert_vertex_no, GRAPH &ggraph);
	void delete_from_vertex_set_X(int delete_vertex_no, GRAPH &ggraph);
	void delete_from_vertex_set_CandX(int delete_vertex_no, GRAPH &ggraph);
	void vertex_remove_on_minSize(int min_size, double gamma, GRAPH &ggraph);
	void vertex_judge_by_minSize(int vertex_no, int minDeg_num, GRAPH &ggraph);
	void find_UpperBound_in_set_X(double gamma);
	void find_LowerBound_in_set_X(double gamma);
	int judge_isIn_VerterSetX_inDiameter2(int vertex_no, GRAPH &ggraph);
	void Min_heap_Adjust(int *arr, int start, int end);
	void Min_heap_Sort(int *arr, int start, int end);

	operate();
	~operate();
};

