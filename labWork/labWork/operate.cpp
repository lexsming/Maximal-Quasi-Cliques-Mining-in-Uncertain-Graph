#include "operate.h"

operate::operate()
{
	memset(OPvertex, 0, sizeof OPvertex);
	min_deg_vertex.min_deg = maxn;
	SetCandX_size = SetX_size = 0;
}

operate::~operate()
{

}

void operate::vertex_remove_on_minSize(int min_size, double gamma, int vertex_num, int edge_num, PRE_VERTEX *pre_vertex, EDGE *pre_edge)
{
	int minDeg_num = (int)(gamma * (min_size - 1));
	if (1.0*gamma*(min_size - 1) - minDeg_num > 0)
		minDeg_num++;

	for (int i = 0; i < vertex_num; i++)
	{
		if (pre_vertex[i].is_removed == 0)
			vertex_judge_by_minSize(i, minDeg_num, pre_vertex, pre_edge);
	}
	return;
}

void operate::vertex_judge_by_minSize(int vertex_no, int minDeg_num, PRE_VERTEX *pre_vertex, EDGE *pre_edge)
{
	if (pre_vertex[vertex_no].degree >= minDeg_num)
		return;
	pre_vertex[vertex_no].is_removed = 1;
	int tem_edge_no = pre_vertex[vertex_no].first;
	while (tem_edge_no != -1)
	{
		int dis_vertex_no = pre_edge[tem_edge_no].to_vertex_no;
		double dis_vertex_pro = pre_edge[tem_edge_no].probability;
		if (pre_vertex[dis_vertex_no].is_removed == 0)
			pre_vertex[dis_vertex_no].degree--;
		if (pre_vertex[dis_vertex_no].degree < minDeg_num)
			vertex_judge_by_minSize(dis_vertex_no, minDeg_num, pre_vertex, pre_edge);
	}
	return;
}

void operate::find_UpperBound_in_set_X(double gamma)
{
	total_indeg_set_X = 0;
	min_deg_vertex.min_deg = maxn;
	//initialize the data

	int *all_in_setX, numX = 0;
	all_in_setX = new int[maxn];
	Printf_tree(SetX, all_in_setX, numX);
	for (int i = 0; i < numX; i++)
	{
		if (OPvertex[all_in_setX[i]].indeg_vertex_set_X + OPvertex[all_in_setX[i]].exdeg_vertex_set_CandX < min_deg_vertex.min_deg)
		{
			min_deg_vertex.min_deg = OPvertex[all_in_setX[i]].indeg_vertex_set_X + OPvertex[all_in_setX[i]].exdeg_vertex_set_CandX;
			min_deg_vertex.vertex_no = all_in_setX[i];
		}
		total_indeg_set_X += OPvertex[all_in_setX[i]].indeg_vertex_set_X;
	}

	upper_bound_Umin_X = (int)(1.0*min_deg_vertex.min_deg / gamma) + 1 - SetX_size;

	int *maxT_indeg_CandX = new int[upper_bound_Umin_X];

	int *all_in_CandX, numCandX = 0;
	all_in_CandX = new int[maxn];
	Printf_tree(SetCandX, all_in_CandX, numCandX);
	for (int i = 0; i < numCandX; i++)
	{
		if (i > upper_bound_Umin_X - 1)
		{
			int temp = OPvertex[all_in_CandX[i]].indeg_vertex_set_X;
			if (temp > maxT_indeg_CandX[0])
			{
				maxT_indeg_CandX[0] = temp;
				Min_heap_Adjust(maxT_indeg_CandX, 0, upper_bound_Umin_X - 1);
			}
		}
		else
		{
			int temp = OPvertex[all_in_CandX[i]].indeg_vertex_set_X;
			maxT_indeg_CandX[i] = temp;
			if (i == upper_bound_Umin_X - 1)
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
	
	int setX_size = SetX_size;
	int product = (int)(1.0*gamma*(setX_size + upper_bound_Umin_X - 1));
	if (product < 1.0*gamma*(setX_size + upper_bound_Umin_X - 1))
		product++;
	product *= setX_size;
	if (total_indeg_set_X + total_indeg_set_CandX >= product)
		upper_bound_UX = upper_bound_Umin_X;
	else
	{
		int i = 0;
		for (; i < upper_bound_Umin_X; i++)
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
		if (i == upper_bound_Umin_X)
			upper_bound_UX = 0;
	}

	delete[] all_in_setX;
	delete[] all_in_CandX;
	delete[] maxT_indeg_CandX;
}

void operate::find_LowerBound_in_set_X(double gamma, double alpha, int min_size, NOW_VERTEX *vertex, EDGE *edge)
{
	int min_indeg_in_set_X = maxn;
	total_indeg_set_X = 0;

	int *all_in_setX, numX = 0;
	all_in_setX = new int[maxn];
	Printf_tree(SetX, all_in_setX, numX);
	for (int i = 0; i < numX; i++)
	{
		if (OPvertex[all_in_setX[i]].indeg_vertex_set_X < min_indeg_in_set_X)
		{
			min_indeg_in_set_X = OPvertex[all_in_setX[i]].indeg_vertex_set_X;
		}
		total_indeg_set_X += OPvertex[all_in_setX[i]].indeg_vertex_set_X;
	}

	int size_X = SetX_size;
	for (int i = 0;; i++)
	{
		int product = (int)(1.0*gamma*(size_X + i - 1));
		if (product < 1.0*gamma*(size_X + i - 1))
			product++;
		if (min_indeg_in_set_X + i >= product)
		{
			Lower_bound_Lmin_X = i;
			break;
		}
	}

	int size_CandX = SetCandX_size;
	int *maxN_indeg_CandX = new int[size_CandX];
	int *all_in_CandX, numCandX = 0;
	all_in_CandX = new int[maxn];
	Printf_tree(SetCandX, all_in_CandX, numCandX);

	for (int i = 0; i < numCandX; i++)
		maxN_indeg_CandX[i] = OPvertex[all_in_CandX[i]].indeg_vertex_set_X;
	sort(maxN_indeg_CandX, maxN_indeg_CandX + size_CandX);//indeg in CandX increment

	int total_indeg_set_CandX = 0;
	for (int i = 0; i < Lower_bound_Lmin_X - 1; i++)
		total_indeg_set_CandX += maxN_indeg_CandX[size_CandX - 1 - i];
	int i;
	for (i = Lower_bound_Lmin_X - 1; i < size_CandX; i++)
	{
		total_indeg_set_CandX += maxN_indeg_CandX[size_CandX - 1 - i];
		int product = (int)(1.0*gamma*(size_X + i));
		if (product < 1.0*gamma*(size_X + i))
			product++;
		product *= size_X;
		if (total_indeg_set_X + total_indeg_set_CandX >= product)
		{
			Lower_bound_UX = i + 1;
			break;
		}
	}
	if (i == size_CandX)
		Lower_bound_UX = size_CandX + 1;

	int product = 1.0*gamma*(max(min_size, Lower_bound_UX) - 1);
	if (product < 1.0*gamma*(max(min_size, Lower_bound_UX) - 1))
		product++;
	for (int i = 0; i < numCandX; i++)
	{
		if (vertex[all_in_CandX[i]].degree == product)
		{
			int pos = vertex[all_in_CandX[i]].first;
			if (edge[pos].probability < alpha)
			{
				Delete_from_Set(all_in_CandX[i], SetCandX, vertex, edge, 2);
			}
		}
	}

	delete[] maxN_indeg_CandX;
	delete[] all_in_CandX;
	delete[] all_in_setX;
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

int operate::judge_isIn_VerterSetX_inDiameter2(int vertex_no, NOW_VERTEX *vertex, EDGE *edge)
{
	int pos = vertex[vertex_no].first;
	while (pos != -1)
	{
		if (OPvertex[edge[pos].to_vertex_no].vertex_position == 1)
		{
			return 1;
		}
		pos = edge[pos].next;
	}

	pos = vertex[vertex_no].first;
	while (pos != -1)
	{
		int vertex_now = edge[pos].to_vertex_no;
		int pos1 = vertex[vertex_now].first;
		while (pos1 != -1)
		{
			if (OPvertex[edge[pos1].to_vertex_no].vertex_position == 1)
				return 2;
			pos1 = edge[pos1].next;
		}
		pos = edge[pos].next;
	}
	return 0;/*
			 return 0: in diameter 2 have no vertex in X
			 return 1: in diameter 1 have vertex in X
			 return 2: in diameter 2 have vertex in X
			 */
}

AvlTree* operate::MakeEmpty(AvlTree* T)
{
	if (T != NULL)
	{
		MakeEmpty(T->left);
		MakeEmpty(T->right);
		free(T);
	}
	return NULL;
}

int operate::get_height(AvlTree* T)
{
	if (T == NULL)return -1;
	else return T->Height;
}

AvlTree* operate::left_left(AvlTree* k1)
{
	//if(height(k1->left)-height(k1->right)<2)return k1;
	AvlTree* k2 = k1->left;
	k1->left = k2->right;
	k2->right = k1;
	k1->Height = max(get_height(k1->left), get_height(k1->right)) + 1;
	k2->Height = max(get_height(k2->left), get_height(k2->right)) + 1;
	return k2;
}

AvlTree* operate::right_right(AvlTree* k1)
{
	//if(height(k1->right)-height(k1->left)<2)return k1;
	AvlTree* k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->Height = max(get_height(k1->left), get_height(k1->right)) + 1;
	k2->Height = max(get_height(k2->left), get_height(k2->right)) + 1;
	return k2;
}

AvlTree* operate::left_right(AvlTree* k1)
{
	k1->left = right_right(k1->left);
	return left_left(k1);
}

AvlTree* operate::right_left(AvlTree* k1)
{
	k1->right = left_left(k1->right);
	return right_right(k1);
}

void operate::Printf_tree(AvlTree* T, int *vertex_in_set, int &num)
{
	if (T->left != NULL)
		Printf_tree(T->left, vertex_in_set, num);
	//printf("%d ", T->vertex_no);
	vertex_in_set[num++] = T->vertex_no;
	if (T->right != NULL)
		Printf_tree(T->right, vertex_in_set, num);
}

void operate::put_diameter2_into_setCandX(int vertex_no, NOW_VERTEX * vertex, EDGE * edge)
{
	int pos = vertex[vertex_no].first;
	while (pos != -1)
	{
		if (OPvertex[edge[pos].to_vertex_no].vertex_position == 0)
		{
			Insert_into_Set(edge[pos].to_vertex_no, SetCandX, vertex, edge, 2);
		}
		if (OPvertex[edge[pos].to_vertex_no].vertex_position != 1)
		{
			int vertex_now = edge[pos].to_vertex_no;
			int pos1 = vertex[vertex_now].first;
			while (pos1 != -1)
			{
				if (OPvertex[edge[pos1].to_vertex_no].vertex_position == 0)
					Insert_into_Set(edge[pos1].to_vertex_no, SetCandX, vertex, edge, 2);
				pos1 = edge[pos1].next;
			}
		}
		pos = edge[pos].next;
	}
}

void operate::get_diameter2_out_setCandX(int vertex_no, NOW_VERTEX * vertex, EDGE * edge)
{
	int pos = vertex[vertex_no].first;
	while (pos != -1)
	{
		if (OPvertex[edge[pos].to_vertex_no].vertex_position == 1)
		{
			pos = edge[pos].next;
			continue;
		}
		int judge_ans = judge_isIn_VerterSetX_inDiameter2(edge[pos].to_vertex_no, vertex, edge);
		
		if (judge_ans == 1)
		{
			pos = edge[pos].next;
			continue;
		}
		else if (judge_ans == 2)
		{
			int vertex_now = edge[pos].to_vertex_no;
			int pos1 = vertex[vertex_now].first;
			while (pos1 != -1)
			{
				int judge_ans1 = judge_isIn_VerterSetX_inDiameter2(edge[pos1].to_vertex_no, vertex, edge);
				if (judge_ans1 == 1 || judge_ans1 == 2)
					continue;
				else Delete_from_Set(edge[pos1].to_vertex_no, SetCandX, vertex, edge, 2);
				pos1 = edge[pos1].next;
			}
		}
		else if (judge_ans == 0)
		{
			Delete_from_Set(edge[pos].to_vertex_no, SetCandX, vertex, edge, 2);
			int vertex_now = edge[pos].to_vertex_no;
			int pos1 = vertex[vertex_now].first;
			while (pos1 != -1)
			{
				int judge_ans1 = judge_isIn_VerterSetX_inDiameter2(edge[pos1].to_vertex_no, vertex, edge);
				if (judge_ans1 == 1 || judge_ans1 == 2)
					continue;
				else Delete_from_Set(edge[pos1].to_vertex_no, SetCandX, vertex, edge, 2);
				pos1 = edge[pos1].next;
			}
		}
		pos = edge[pos].next;
	}
}

AvlTree* operate::Insert_into_Set(int vertex_no, AvlTree* T, NOW_VERTEX *vertex, EDGE *edge, int kind)
{
	if (kind == 1)
		OPvertex[vertex_no].vertex_position = 1, SetX_size++;
	else if (kind == 2)
		OPvertex[vertex_no].vertex_position = 2, SetCandX_size++;

	int pos = vertex[vertex_no].first;
	while (pos != -1)
	{
		if (kind == 1)
			OPvertex[edge[pos].to_vertex_no].indeg_vertex_set_X++;
		else if (kind == 2)
			OPvertex[edge[pos].to_vertex_no].exdeg_vertex_set_CandX;
		pos = edge[pos].next;
	}

	if (T == NULL)
	{
		T = (AvlTree*)malloc(sizeof(struct AvlTree));
		T->vertex_no = vertex_no;
		T->Height = 0;

		T->left = NULL;
		T->right = NULL;
	}

	else if (vertex_no < T->vertex_no)
	{
		T->left = Insert_into_Set(vertex_no, T->left, vertex, edge, kind);
		if (get_height(T->left) - get_height(T->right) == 2)
		{
			if (vertex_no < T->left->vertex_no)
				T = left_left(T);
			else
				T = left_right(T);
		}
	}

	else
	{
		T->right = Insert_into_Set(vertex_no, T->right, vertex, edge, kind);
		if (get_height(T->right) - get_height(T->left) == 2)
		{
			if (vertex_no < T->right->vertex_no)
				T = right_left(T);
			else
				T = right_right(T);
		}
	}
	T->Height = max(get_height(T->left), get_height(T->right)) + 1;
	if (kind == 1)
		put_diameter2_into_setCandX(vertex_no, vertex, edge);
	return T;
}

AvlTree* operate::Delete_from_Set(int vertex_no, AvlTree* T, NOW_VERTEX *vertex, EDGE *edge, int kind)
{
	if (kind == 1)
		SetX_size--;
	else if (kind == 2)
		SetCandX_size--;

	OPvertex[vertex_no].vertex_position = 0;
	int pos = vertex[vertex_no].first;
	while (pos != -1)
	{
		if (kind == 1)
			OPvertex[edge[pos].to_vertex_no].indeg_vertex_set_X--;
		else if (kind == 2)
			OPvertex[edge[pos].to_vertex_no].exdeg_vertex_set_CandX--;
		pos = edge[pos].next;
	}

	if (T == NULL)
	{
		if (kind == 1)
			get_diameter2_out_setCandX(vertex_no, vertex, edge);
		return NULL;
	}
	else
	{
		if (T->vertex_no == vertex_no)
		{
			if (T->right == NULL)
			{
				AvlTree* tem = T;
				T = T->left;
				free(tem);
			}
			else
			{
				AvlTree* tem = T->right;
				while (tem->left != NULL)
				{
					tem = tem->left;
				}
				T->vertex_no = tem->vertex_no;
				T->right = Delete_from_Set(T->vertex_no, T->right, vertex, edge, kind);
				T->Height = max(get_height(T->left), get_height(T->right)) + 1;
			}
			return T;
		}
		else if (vertex_no > T->vertex_no)
		{
			T->right = Delete_from_Set(vertex_no, T->right, vertex, edge, kind);
		}
		else
		{
			T->left = Delete_from_Set(vertex_no, T->left, vertex, edge, kind);
		}

		T->Height = max(get_height(T->left), get_height(T->right)) + 1;
		if (T->left != NULL)
			T->left = balance(T->left);
		if (T->right != NULL)
			T->right = balance(T->right);
		if (T != NULL)
			T = balance(T);

		if (kind == 1)
			get_diameter2_out_setCandX(vertex_no, vertex, edge);
		return T;
	}
}

AvlTree* operate::balance(AvlTree* T)
{
	if (get_height(T->left) - get_height(T->right) == 2)
	{
		if (get_height(T->left->left)>get_height(T->left->right))
		{
			T = left_left(T);
		}
		else
		{
			T = left_right(T);
		}
	}
	else if (get_height(T->right) - get_height(T->left) == 2)
	{
		if (get_height(T->right) - get_height(T->left))
		{
			T = right_right(T);
		}
		else
		{
			T = right_left(T);
		}
	}
	else return T;
}
