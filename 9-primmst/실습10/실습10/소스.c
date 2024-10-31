#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0
#define MAX_VERTICES 100
#define INF 1000

typedef struct GraphType {
	int n; //정점 개수
	int weight[MAX_VERTICES][MAX_VERTICES]; //간선의 가중치
} GraphType;

int selected[MAX_VERTICES]; //MST에 포함되었는지 여부 저장
int distance[MAX_VERTICES]; 

int get_min_vertex(int n) //가장 작은 가중치를 가진 정점 반환
{
	int v, i;
	for (i = 0; i < n; i++)
		if (!selected[i]) { //선택되지 않은 정점을 v에 대입
			v = i;
			break;
		}
	for (i = 0; i < n; i++) //선택되지 않고 가장 가중치가 작은 정점을 반복문을 통해 찾음
		if (!selected[i] && (distance[i] < distance[v])) v = i;
	return (v); //가장 작은 가중치를 가진 정점을 반환
}

void prim(GraphType* g, int s)
{
	int i, u, v;

	for (u = 0; u < g->n; u++)
		distance[u] = INF; //distance를 모두 INF로 초기화
	distance[s] = 0; //시작부분은 다시 0으로 설정
	for (i = 1; i < g->n; i++) {
		u = get_min_vertex(g->n); // 가장 작은 가중치
		selected[u] = True; // MST에 포함
		if (distance[u] == INF) return; //연결 안됨.
		printf("정점 %d 추가\n", u);
		for (v = 1; v <= g->n; v++)
			if (g->weight[u][v] != INF) //연결된 간선 존재
				if (!selected[v] && g->weight[u][v] < distance[v])
					distance[v] = g->weight[u][v]; //최소 가중치 갱신
	}
}

void FindPrimMST(GraphType* g) {
	printf("Prim MST Algorithm\n");
	prim(g, 1); //정점이 1부터 시작하므로 s = 1
	system("pause"); //결과창이 빠르게 닫겨서 추가한 일시정지 기능
}

void graph_init(GraphType* g) { //가중치 초기화
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
		memcpy(g->weight[i], weights[i], g->n * sizeof(int)); //weights 배열을 g->weight에 복사
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