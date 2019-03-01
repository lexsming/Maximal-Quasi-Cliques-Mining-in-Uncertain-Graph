#include "operate.h"

operate::operate()
{
	memset(vertex_position, 0, sizeof vertex_position);
}


operate::~operate()
{
	vertex_set_X.clear();
	vertex_set_CandX.clear();
}

void operate::insert_into_vertex_set_X(int insert_vertex_no, GRAPH ggraph)
{
	if (vertex_position[insert_vertex_no] == 2)
	{
		vertex_set_CandX.erase(insert_vertex_no);
	}
	
	vertex_position[insert_vertex_no] = 1;
	vertex_set_X.insert(insert_vertex_no);

	for (int i = 0; i < ggraph.graph[insert_vertex_no].size(); i++)
	{
		if (vertex_position[ggraph.graph[insert_vertex_no][i].to_vertex_no] == 0)
		{
			insert_into_vertex_set_CandX(ggraph.graph[insert_vertex_no][i].to_vertex_no, ggraph);
		}
		if (vertex_position[ggraph.graph[insert_vertex_no][i].to_vertex_no] != 1)
		{
			int now_vertex_no = ggraph.graph[insert_vertex_no][i].to_vertex_no;
			for (int j = 0; j < ggraph.graph[now_vertex_no].size(); j++)
			{
				if (vertex_position[ggraph.graph[now_vertex_no][j].to_vertex_no] == 0)
				{
					insert_into_vertex_set_CandX(ggraph.graph[now_vertex_no][j].to_vertex_no, ggraph);
				}
			}
		}
	}
}

void operate::insert_into_vertex_set_CandX(int insert_vertex_no, GRAPH ggraph)
{
	vertex_position[insert_vertex_no] = 2;
	vertex_set_CandX.insert(insert_vertex_no);
}

void operate::delete_from_vertex_set_X(int delete_vertex_no, GRAPH ggraph)
{
	vertex_position[delete_vertex_no] = 0;
	for (int i = 0; i < ggraph.graph[delete_vertex_no].size(); i++)
	{
		if (vertex_position[ggraph.graph[delete_vertex_no][i].to_vertex_no] == 1)
			continue;
		int judge_ans = judge_isIn_VerterSetX_inDiameter2(ggraph.graph[delete_vertex_no][i].to_vertex_no, ggraph);
		if (judge_ans == 1)
		{
			continue;
		}
		else if (judge_ans == 2)
		{
			int now_vertex_no = ggraph.graph[delete_vertex_no][i].to_vertex_no;
			for (int j = 0; j < ggraph.graph[now_vertex_no].size(); j++)
			{
				int judge_ans1 = judge_isIn_VerterSetX_inDiameter2(ggraph.graph[now_vertex_no][j].to_vertex_no, ggraph);
				if (judge_ans1 == 1 || judge_ans1 == 2)
				{
					continue;
				}
				else delete_from_vertex_set_CandX(ggraph.graph[now_vertex_no][j].to_vertex_no, ggraph);
			}
		}
		else if (judge_ans == 0)
		{
			delete_from_vertex_set_CandX(ggraph.graph[delete_vertex_no][i].to_vertex_no, ggraph);
			int now_vertex_no = ggraph.graph[delete_vertex_no][i].to_vertex_no;
			for (int j = 0; j < ggraph.graph[now_vertex_no].size(); j++)
			{
				int judge_ans1 = judge_isIn_VerterSetX_inDiameter2(ggraph.graph[now_vertex_no][j].to_vertex_no, ggraph);
				if (judge_ans1 == 1 || judge_ans1 == 2)
				{
					continue;
				}
				else delete_from_vertex_set_CandX(ggraph.graph[now_vertex_no][j].to_vertex_no, ggraph);
			}
		}
	}
}

void operate::delete_from_vertex_set_CandX(int delete_vertex_no, GRAPH ggraph)
{
	vertex_position[delete_vertex_no] = 0;
	vertex_set_CandX.erase(delete_vertex_no);
}

int operate::judge_isIn_VerterSetX_inDiameter2(int vertex_no, GRAPH ggraph)
{
	for (int i = 0; i < ggraph.graph[vertex_no].size(); i++)
	{
		if (vertex_position[ggraph.graph[vertex_no][i].to_vertex_no] == 1)
		{
			return 1;
		}
	}
	for (int i = 0; i < ggraph.graph[vertex_no].size(); i++)
	{
		int now_vertex_no = ggraph.graph[vertex_no][i].to_vertex_no;
		for (int j = 0; j < ggraph.graph[now_vertex_no].size(); j++)
		{
			if (vertex_position[ggraph.graph[now_vertex_no][j].to_vertex_no] == 1)
				return 2;
		}
	}
	return 0;/*
			 return 0: in diameter 2 have no vertex in X
			 return 1: in diameter 1 have vertex in X
			 return 2: in diameter 2 have vertex in X
			 */
}
