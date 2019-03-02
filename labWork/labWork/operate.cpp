#include "operate.h"

operate::operate()
{
	memset(OPvertex, 0, sizeof OPvertex);
}


operate::~operate()
{
	vertex_set_X.clear();
	vertex_set_CandX.clear();
}

void operate::insert_into_vertex_set_X(int insert_vertex_no, GRAPH &ggraph)
{
	if (OPvertex[insert_vertex_no].vertex_position == 2)
	{
		vertex_set_CandX.erase(insert_vertex_no);
		for (int i = 0; i < ggraph.graph[insert_vertex_no].size(); i++)
		{
			OPvertex[ggraph.graph[insert_vertex_no][i].to_vertex_no].exdeg_vertex_set_CandX--;
		}
	}
	
	OPvertex[insert_vertex_no].vertex_position = 1;
	vertex_set_X.insert(insert_vertex_no);

	for (int i = 0; i < ggraph.graph[insert_vertex_no].size(); i++)
	{
		OPvertex[ggraph.graph[insert_vertex_no][i].to_vertex_no].indeg_vertex_set_X++;

		if (OPvertex[ggraph.graph[insert_vertex_no][i].to_vertex_no].vertex_position == 0)
		{
			if (ggraph.is_vertex_removed[ggraph.graph[insert_vertex_no][i].to_vertex_no] == 0)
				insert_into_vertex_set_CandX(ggraph.graph[insert_vertex_no][i].to_vertex_no, ggraph);
		}
		if (OPvertex[ggraph.graph[insert_vertex_no][i].to_vertex_no].vertex_position != 1)
		{
			int now_vertex_no = ggraph.graph[insert_vertex_no][i].to_vertex_no;
			for (int j = 0; j < ggraph.graph[now_vertex_no].size(); j++)
			{
				if (OPvertex[ggraph.graph[now_vertex_no][j].to_vertex_no].vertex_position == 0)
				{
					if (ggraph.is_vertex_removed[ggraph.graph[now_vertex_no][j].to_vertex_no] == 0)
						insert_into_vertex_set_CandX(ggraph.graph[now_vertex_no][j].to_vertex_no, ggraph);
				}
			}
		}
	}
}

void operate::insert_into_vertex_set_CandX(int insert_vertex_no, GRAPH &ggraph)
{
	OPvertex[insert_vertex_no].vertex_position = 2;
	vertex_set_CandX.insert(insert_vertex_no);
	for (int i = 0; i < ggraph.graph[insert_vertex_no].size(); i++)
	{
		OPvertex[ggraph.graph[insert_vertex_no][i].to_vertex_no].exdeg_vertex_set_CandX++;
	}
}

void operate::delete_from_vertex_set_X(int delete_vertex_no, GRAPH &ggraph)
{
	OPvertex[delete_vertex_no].vertex_position = 0;
	for (int i = 0; i < ggraph.graph[delete_vertex_no].size(); i++)
	{
		OPvertex[ggraph.graph[delete_vertex_no][i].to_vertex_no].indeg_vertex_set_X--;

		if (OPvertex[ggraph.graph[delete_vertex_no][i].to_vertex_no].vertex_position == 1)
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

void operate::delete_from_vertex_set_CandX(int delete_vertex_no, GRAPH &ggraph)
{
	OPvertex[delete_vertex_no].vertex_position = 0;
	vertex_set_CandX.erase(delete_vertex_no);

	for (int i = 0; i < ggraph.graph[delete_vertex_no].size(); i++)
	{
		OPvertex[ggraph.graph[delete_vertex_no][i].to_vertex_no].exdeg_vertex_set_CandX--;
	}
}

void operate::vertex_remove_on_minSize(int min_size, double gamma, GRAPH &ggraph)
{
	int minDeg_num = (int)(gamma * (min_size - 1));
	if (1.0*gamma*(min_size - 1) - minDeg_num > 0)
		minDeg_num++;
	
	for (int i = 0; i < ggraph.vertex_num; i++)
	{
		if (ggraph.is_vertex_removed[i] == 0)
			vertex_judge_by_minSize(i, minDeg_num, ggraph);
	}
}

void operate::vertex_judge_by_minSize(int vertex_no, int minDeg_num, GRAPH &ggraph)
{
	if (ggraph.graph[vertex_no].size() >= minDeg_num)
		return;
	ggraph.is_vertex_removed[vertex_no] = 1;
	for (int i = 0; i < ggraph.graph[vertex_no].size(); i++)
	{
		int dis_vertex_no = ggraph.graph[vertex_no][i].to_vertex_no;
		double dis_vertex_pro = ggraph.graph[vertex_no][i].probability;
		for (int j = 0; j < ggraph.graph[dis_vertex_no].size(); j++)
		{
			if (ggraph.graph[dis_vertex_no][j].to_vertex_no == vertex_no)
			{
				ggraph.graph[dis_vertex_no].erase(ggraph.graph[dis_vertex_no].begin() + j);
				break;
			}
		}
		if (ggraph.graph[dis_vertex_no].size() < minDeg_num)
			vertex_judge_by_minSize(dis_vertex_no, minDeg_num, ggraph);
	}
	return;
}

int operate::judge_isIn_VerterSetX_inDiameter2(int vertex_no, GRAPH &ggraph)
{
	for (int i = 0; i < ggraph.graph[vertex_no].size(); i++)
	{
		if (OPvertex[ggraph.graph[vertex_no][i].to_vertex_no].vertex_position == 1)
		{
			return 1;
		}
	}
	for (int i = 0; i < ggraph.graph[vertex_no].size(); i++)
	{
		int now_vertex_no = ggraph.graph[vertex_no][i].to_vertex_no;
		for (int j = 0; j < ggraph.graph[now_vertex_no].size(); j++)
		{
			if (OPvertex[ggraph.graph[now_vertex_no][j].to_vertex_no].vertex_position == 1)
				return 2;
		}
	}
	return 0;/*
			 return 0: in diameter 2 have no vertex in X
			 return 1: in diameter 1 have vertex in X
			 return 2: in diameter 2 have vertex in X
			 */
}
