#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0
#define MAX_VERTICES 100
#define INF 1000

typedef struct GraphType {
	int n; //���� ����
	int weight[MAX_VERTICES][MAX_VERTICES]; //������ ����ġ
} GraphType;

int selected[MAX_VERTICES]; //MST�� ���ԵǾ����� ���� ����
int distance[MAX_VERTICES]; 

int get_min_vertex(int n) //���� ���� ����ġ�� ���� ���� ��ȯ
{
	int v, i;
	for (i = 0; i < n; i++)
		if (!selected[i]) { //���õ��� ���� ������ v�� ����
			v = i;
			break;
		}
	for (i = 0; i < n; i++) //���õ��� �ʰ� ���� ����ġ�� ���� ������ �ݺ����� ���� ã��
		if (!selected[i] && (distance[i] < distance[v])) v = i;
	return (v); //���� ���� ����ġ�� ���� ������ ��ȯ
}

void prim(GraphType* g, int s)
{
	int i, u, v;

	for (u = 0; u < g->n; u++)
		distance[u] = INF; //distance�� ��� INF�� �ʱ�ȭ
	distance[s] = 0; //���ۺκ��� �ٽ� 0���� ����
	for (i = 1; i < g->n; i++) {
		u = get_min_vertex(g->n); // ���� ���� ����ġ
		selected[u] = True; // MST�� ����
		if (distance[u] == INF) return; //���� �ȵ�.
		printf("���� %d �߰�\n", u);
		for (v = 1; v <= g->n; v++)
			if (g->weight[u][v] != INF) //����� ���� ����
				if (!selected[v] && g->weight[u][v] < distance[v])
					distance[v] = g->weight[u][v]; //�ּ� ����ġ ����
	}
}

void FindPrimMST(GraphType* g) {
	printf("Prim MST Algorithm\n");
	prim(g, 1); //������ 1���� �����ϹǷ� s = 1
	system("pause"); //���â�� ������ �ݰܼ� �߰��� �Ͻ����� ���
}

void graph_init(GraphType* g) { //����ġ �ʱ�ȭ
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			g->weight[i][j] = INF;
		}
	}
}

void GenerateGraph(GraphType* g) {
	g->n = 11;

	int weights[11][11] = {
	{INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}, //0
	{INF, 0, 3, INF, INF, INF, 11, 12, INF, INF, INF}, //1
	{INF, 3, 0, 5, 4, 1, 7, 8, INF, INF, INF}, //2
	{INF, INF, 5, 0, 2, INF, INF, 6, 5, INF, INF}, //3
	{INF, INF, 4, 2, 0, 13, INF, INF, 14, INF, 16}, //4
	{INF, INF, 1, INF, 4, 0, 9, INF, INF, 18, 17}, //5
	{INF, 11, 7, INF, INF, 9, 0, INF, INF, INF, INF}, //6
	{INF, 12, 8, 6, INF, INF, INF, 0, 13, INF, INF}, //7
	{INF, INF, INF, 5, 14, INF, INF, 13, 0, INF, 15}, //8
	{INF, INF, INF, INF, INF, 18, INF, INF, INF, 0, 10}, //9
	{INF, INF, INF, INF, 16, 17, INF, INF, 15, 10, 0}, //10
	};

	for (int i = 0; i < g->n; i++) {
		memcpy(g->weight[i], weights[i], g->n * sizeof(int)); //weights �迭�� g->weight�� ����
	}
}

int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	GenerateGraph(g);
	FindPrimMST(g);
	free(g);
	return 0;
}