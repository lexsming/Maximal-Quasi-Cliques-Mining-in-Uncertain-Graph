
#include "GRAPH.h"


GRAPH::GRAPH()
{
	now_vertex = new NOW_VERTEX[maxn];
	for (int i = 0; i < maxn; i++)
		now_vertex[i].first = -1;
}


GRAPH::~GRAPH()
{
}

void GRAPH::store_graph(string graph_file_address)
{
	FILE *in;
	in = fopen(graph_file_address.c_str(), "wb+");
	if (in == NULL)
	{
		printf("graph file address is null.\n");
		exit(1);
	}
	char c;
	int pos = 0;
	double num = 0;
	while ((c = getc(in)) != EOF)
	{
		if (c == '\n')
		{
			pos++;
			continue;
		}
		else if (c >= '0'&&c <= '9')
		{
			EDGE edgeTmp;
			num = num * 10 + (c - '0');
			while ((c == getc(in)) != ' ')
			{
				num = num * 10 + (c - '0');
			}
			edgeTmp.to_vertex_no = (int)num;
			do {
				c = getc(in);

			} while (c != ' '&&c != '\n');
		}
	}
}

void GRAPH::lessen_graph()
{
	int *tem, pos = 0, pos1 = 0;// pos:  the number of the vertex in now graph
								// pos1: the number of the edge in now graph
	tem = new int[vertex_num];
	for (int i = 0; i < vertex_num; i++)
	{
		tem[i] = -1;
		if (pre_vertex[i].is_removed == 0)
		{
			tem[i] = pos;
			pos++;
			pos1 += pre_vertex[i].degree;
		}
	}
	now_vertex = new NOW_VERTEX[pos];
	now_edge = new EDGE[pos1];

	for (int i = 0, j = 0; i < vertex_num; i++)
	{
		now_vertex[i].first = -1;
		if (pre_vertex[i].is_removed == 0)
		{
			now_vertex[j].degree = 0;
			now_vertex[j].pre_pos = i;
			j++;
		}
	}

	for (int i = 0, j = 0; i < vertex_num; i++)
	{
		if (pre_vertex[i].is_removed == 0)
		{
			int edge_no = pre_vertex[i].first;
			while (edge_no != -1)
			{
				if (pre_vertex[pre_edge[edge_num].to_vertex_no].is_removed == 0)
				{
					int now_from = pre_edge[edge_no].from_vertex_no;
					int now_to = pre_edge[edge_no].to_vertex_no;
					now_edge[j].next = now_vertex[now_from].first;
					now_edge[j].from_vertex_no = now_from;
					now_edge[j].to_vertex_no = now_to;
					now_edge[j].probability = pre_edge[edge_num].probability;
					
					now_vertex[now_from].first = j;
					now_vertex[now_from].degree++;
					j++;
				}
				edge_no = pre_edge[edge_num].next;
			}
		}
	}
	vertex_num = pos;
	edge_num = pos1 / 2;
	return;
}
