#include "operate.h"

operate::operate()
{
	memset(OPvertex, 0, sizeof OPvertex);
	min_deg_vertex.min_deg = maxn;
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
		OPvertex[insert_vertex_no].indeg_vertex_set_X = 0;
		OPvertex[insert_vertex_no].exdeg_vertex_set_CandX = 0;
		for (int i = 0; i < ggraph.graph[insert_vertex_no].size(); i++)
		{
			if (OPvertex[ggraph.graph[insert_vertex_no][i].to_vertex_no].vertex_position != 0)
				OPvertex[ggraph.graph[insert_vertex_no][i].to_vertex_no].exdeg_vertex_set_CandX--;
		}
	}
	
	OPvertex[insert_vertex_no].vertex_position = 1;
	vertex_set_X.insert(insert_vertex_no);

	for (int i = 0; i < ggraph.graph[insert_vertex_no].size(); i++)
	{
		if (OPvertex[ggraph.graph[insert_vertex_no][i].to_vertex_no].vertex_position != 0)
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

		if (OPvertex[ggraph.graph[insert_vertex_no][i].to_vertex_no].vertex_position == 1)
		{
			OPvertex[insert_vertex_no].indeg_vertex_set_X++;
		}
		else if(OPvertex[ggraph.graph[insert_vertex_no][i].to_vertex_no].vertex_position == 2)
			OPvertex[insert_vertex_no].exdeg_vertex_set_CandX++;
	}


}

void operate::insert_into_vertex_set_CandX(int insert_vertex_no, GRAPH &ggraph)
{
	OPvertex[insert_vertex_no].vertex_position = 2;
	vertex_set_CandX.insert(insert_vertex_no);
	for (int i = 0; i < ggraph.graph[insert_vertex_no].size(); i++)
	{
		if (ggraph.graph[insert_vertex_no][i].to_vertex_no)
			OPvertex[ggraph.graph[insert_vertex_no][i].to_vertex_no].exdeg_vertex_set_CandX++;

		if (OPvertex[ggraph.graph[insert_vertex_no][i].to_vertex_no].vertex_position == 1)
		{
			OPvertex[insert_vertex_no].indeg_vertex_set_X++;
		}
		else if (OPvertex[ggraph.graph[insert_vertex_no][i].to_vertex_no].vertex_position == 2)
			OPvertex[insert_vertex_no].exdeg_vertex_set_CandX++;
	}
}

void operate::delete_from_vertex_set_X(int delete_vertex_no, GRAPH &ggraph)
{
	OPvertex[delete_vertex_no].vertex_position = 0;
	OPvertex[delete_vertex_no].indeg_vertex_set_X = 0;
	OPvertex[delete_vertex_no].exdeg_vertex_set_CandX = 0;
	vertex_set_X.erase(delete_vertex_no);

	for (int i = 0; i < ggraph.graph[delete_vertex_no].size(); i++)
	{
		if (OPvertex[ggraph.graph[delete_vertex_no][i].to_vertex_no].vertex_position != 0)
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
	OPvertex[delete_vertex_no].indeg_vertex_set_X = 0;
	OPvertex[delete_vertex_no].exdeg_vertex_set_CandX = 0;
	vertex_set_CandX.erase(delete_vertex_no);

	for (int i = 0; i < ggraph.graph[delete_vertex_no].size(); i++)
	{
		if (OPvertex[ggraph.graph[delete_vertex_no][i].to_vertex_no].vertex_position != 0)
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

void operate::find_minDeg_in_set_X(double gamma)
{
	set <int>::iterator it;
	total_indeg_set_X = 0;
	for (it = vertex_set_X.begin(); it != vertex_set_X.end(); it++)
	{
		if (OPvertex[*it].indeg_vertex_set_X + OPvertex[*it].exdeg_vertex_set_CandX < min_deg_vertex.min_deg)
		{
			min_deg_vertex.min_deg = OPvertex[*it].indeg_vertex_set_X + OPvertex[*it].exdeg_vertex_set_CandX;
			min_deg_vertex.vertex_no = *it;
		}
		total_indeg_set_X += OPvertex[*it].indeg_vertex_set_X;
	}
	upper_bound_Umin_X = (int)(1.0*min_deg_vertex.min_deg / gamma) + 1 - vertex_set_X.size();

	int *maxT_indeg_CandX = new int[upper_bound_Umin_X];

	int num = 0;
	for (it = vertex_set_CandX.begin(); it != vertex_set_CandX.end(); it++, num++)
	{
		if (num > upper_bound_Umin_X - 1)
		{
			int temp = OPvertex[*it].indeg_vertex_set_X;
			if (temp > maxT_indeg_CandX[0]) 
			{
				maxT_indeg_CandX[0] = temp;
				Min_heap_Adjust(maxT_indeg_CandX, 0, upper_bound_Umin_X - 1);
			}
		}
		else 
		{
			int temp = OPvertex[*it].indeg_vertex_set_X;
			maxT_indeg_CandX[num] = temp;
			if (num == upper_bound_Umin_X - 1)//bulid Min_heap
			{
				for (int j = (upper_bound_Umin_X - 1 - 1) / 2; j >= 0; j--)
					Min_heap_Adjust(maxT_indeg_CandX, j, upper_bound_Umin_X - 1);
			}
		}
	}
	Min_heap_Sort(maxT_indeg_CandX, 0, upper_bound_Umin_X - 1);
	int total_indeg_set_CandX = 0;
	for (int i = 0; i < upper_bound_Umin_X; i++)
		total_indeg_set_CandX += maxT_indeg_CandX[i];
	
	int setX_size = vertex_set_X.size();
	int product = (int)(1.0*gamma*(setX_size + upper_bound_Umin_X - 1));
	if (product < 1.0*gamma*(setX_size + upper_bound_Umin_X - 1))
		product++;
	product *= setX_size;
	if (total_indeg_set_X + total_indeg_set_CandX >= product)
		upper_bound_UX = upper_bound_Umin_X;
	else
	{
		for (int i = 0; i < upper_bound_Umin_X; i++)
		{
			total_indeg_set_CandX -= maxT_indeg_CandX[upper_bound_Umin_X - 1 - i];
			product = (int)(1.0*gamma*(setX_size + upper_bound_Umin_X - 1 - i - 1));
			if (product < 1.0*gamma*(setX_size + upper_bound_Umin_X - 1 - i - 1))
				product++;
			product *= setX_size;
			if (total_indeg_set_X + total_indeg_set_CandX >= product)
			{
				upper_bound_UX = upper_bound_Umin_X - i - 1;
				break;
			}
		}
	}

	delete[] maxT_indeg_CandX;
}

void operate::Min_heap_Adjust(int *arr, int start, int end)
{
	int i = start * 2 + 1;
	while (i <= end) 
	{
		if (i + 1 <= end && arr[i] > arr[i + 1])
			i++;
		if (arr[start] > arr[i]) 
		{
			swap(arr[start], arr[i]);
			start = i;
			i = 2 * start + 1;
		}
		else break;
	}
}

void operate::Min_heap_Sort(int *arr, int start, int end)
{
	for (int i = (end - 1) / 2; i >= 0; i--)
		Min_heap_Adjust(arr, i, end);
	for (int i = end; i - 1 >= 0; i--) 
	{
		swap(arr[i], arr[0]);
		Min_heap_Adjust(arr, 0, i - 1);
	}
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


