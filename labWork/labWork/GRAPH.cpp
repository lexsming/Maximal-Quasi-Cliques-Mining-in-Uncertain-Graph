
#include "GRAPH.h"


GRAPH::GRAPH()
{
	memset(is_vertex_removed, 0, sizeof is_vertex_removed);
}


GRAPH::~GRAPH()
{
}

void GRAPH::store_graph(string graph_file_address, GRAPH pre_graph)
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
