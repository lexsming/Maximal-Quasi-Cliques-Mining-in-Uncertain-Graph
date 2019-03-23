#pragma once

#include <set>

#include "GRAPH.h"


struct SET_VERTEX {
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

struct AvlTree {
	int vertex_no;
	struct AvlTree *left;
	struct AvlTree *right;
	int Height;
};

class operate
{
public:
	AvlTree * SetX, *SetCandX;
	SET_VERTEX OPvertex[maxn];
	MIN_DEG min_deg_vertex;
	int upper_bound_Umin_X, upper_bound_UX, total_indeg_set_X;
	int Lower_bound_Lmin_X, Lower_bound_UX;
	int SetX_size, SetCandX_size;
	
	void vertex_remove_on_minSize(int min_size, double gamma, int vertex_num, int edge_num, PRE_VERTEX *pre_vertex, EDGE *pre_edge);
	void vertex_judge_by_minSize(int vertex_no, int minDeg_num, PRE_VERTEX *pre_vertex, EDGE *pre_edge);
	
	void find_UpperBound_in_set_X(double gamma);
	void find_LowerBound_in_set_X(double gamma, double alpha, int min_size, NOW_VERTEX *vertex, EDGE *edge);
	void Min_heap_Adjust(int *arr, int start, int end);
	void Min_heap_Sort(int *arr, int start, int end);

	AvlTree* Insert_into_Set(int vertex_no, AvlTree* T, NOW_VERTEX *vertex, EDGE *edge, int kind);// 1 set X, 2 set CandX
	AvlTree* Delete_from_Set(int vertex_no, AvlTree* T, NOW_VERTEX *vertex, EDGE *edge, int kind);

	AvlTree* left_left(AvlTree* k1);
	AvlTree* right_right(AvlTree* k1);
	AvlTree* left_right(AvlTree* k1);
	AvlTree* right_left(AvlTree* k1);
	AvlTree* balance(AvlTree* T);
	AvlTree* MakeEmpty(AvlTree* T);
	int get_height(AvlTree *T);
	void Printf_tree(AvlTree* T, int *vertex_in_set, int &num);
	int judge_isIn_VerterSetX_inDiameter2(int vertex_no, NOW_VERTEX *vertex, EDGE *edge);
	void put_diameter2_into_setCandX(int vertex_no, NOW_VERTEX *vertex, EDGE *edge);
	void get_diameter2_out_setCandX(int vertex_no, NOW_VERTEX *vertex, EDGE *edge);

	operate();
	~operate();
};