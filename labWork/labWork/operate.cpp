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

	}
}

void operate::delete_from_vertex_set_CandX(int delete_vertex_no, GRAPH ggraph)
{

}
