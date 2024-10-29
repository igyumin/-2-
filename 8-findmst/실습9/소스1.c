#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0
#define MAX_VERTICES 100
#define INF 1000

typedef struct Edge {
	int start, end, weight;
} Edge;

typedef struct GraphType {
	int n;
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

typedef struct MinHeap {
	int size;
	Edge data[2 * MAX_VERTICES];
} MinHeap;

int parent[MAX_VERTICES + 1];

void set_init(int n) {
	for (int i = 1; i <= n; i++) {
		parent[i] = -1; //루트가 없는 상태
	}
}


int set_find(int curr) { //집합 루트 반환
	while (parent[curr] != -1) { //루트가 있으면 반복
		curr = parent[curr];
	}
	return curr;
}

void set_union(int a, int b){ //집합을 합치는 함수
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2)  //루트가 다르면 합친다
		parent[root1] = root2;
}

void graph_init(GraphType* g) { //그래프 초기화 
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

void insert_edge(GraphType* g, int start, int end, int w) { //엣지 삽입
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

void GenerateGraph(GraphType* g) { //그래프 생성
	insert_edge(g, 1, 6, 11);
	insert_edge(g, 1, 7, 12);
	insert_edge(g, 1, 2, 3);
	insert_edge(g, 2, 3, 5);
	insert_edge(g, 2, 4, 4);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 2, 6, 7);
	insert_edge(g, 2, 7, 8);
	insert_edge(g, 3, 7, 6);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 3, 8, 5);
	insert_edge(g, 4, 8, 14);
	insert_edge(g, 4, 5, 13);
	insert_edge(g, 4, 10, 16);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 5, 9, 18);
	insert_edge(g, 5, 10, 17);
	insert_edge(g, 7, 8, 13);
	insert_edge(g, 8, 10, 15);
	insert_edge(g, 9, 10, 10);
}

int compare(const void* a, const void* b) { //가중치 비교
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

void QuickKruskal(GraphType* g) {
	int edge_accepted = 0; //선택된 엣지 수
	int uset, vset;
	struct Edge e;

	set_init(g->n); //초기화
	qsort(g->edges, g->n, sizeof(struct Edge), compare); //정렬

	printf("Quick Based Kruskal\n");
	int i = 0;
	while (edge_accepted < (g->n - 1) && i < g->n) {
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) { //사이클이 형성되지 않았다면 추가
			printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset); //집합 합침
		}
		i++;
	}
}

void min_heapify(MinHeap* h, int idx) { //min heap을 유지하기 위해 힙 정렬을 수행함
	int smallest = idx; //현재가 가장 작은 것으로 가정
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < h->size && h->data[left].weight < h->data[smallest].weight)
		smallest = left; //왼쪽이 작으면 smallest에 왼쪽 자식을
	if (right < h->size && h->data[right].weight < h->data[smallest].weight)
		smallest = right; //오른쪽이 작으면 smallest에 오른쪽 자식을

	if (smallest != idx) { 
		Edge temp = h->data[idx];
		h->data[idx] = h->data[smallest];
		h->data[smallest] = temp;
		min_heapify(h, smallest);
	}
}

void insert_min_heap(MinHeap* h, Edge e) { //최소 힙에 엣지를 넣음
	h->data[h->size] = e;
	int i = h->size;
	h->size++;

	while (i > 0 && h->data[(i - 1) / 2].weight > h->data[i].weight) {
		Edge temp = h->data[i];
		h->data[i] = h->data[(i - 1) / 2];
		h->data[(i - 1) / 2] = temp; //루트노드와 교환
		i = (i - 1) / 2;
	}
}

Edge delete_min_heap(MinHeap* h) { //min값을 삭제, 반환
	Edge min = h->data[0];
	h->data[0] = h->data[h->size - 1]; //heap의 마지막을 최상단으로
	h->size--;
	min_heapify(h, 0); //heap 재정비
	return min;
}

void MinHeapKruskal(GraphType* g) {
	MinHeap h;
	h.size = 0;

	for (int i = 0; i < g->n; i++) { //모든 엣지를 min heap에 넣는다.
		insert_min_heap(&h, g->edges[i]);
	}

	set_init(g->n);

	printf("\nMinHeap Based Kruskal\n");
	int edge_accepted = 0;

	while (edge_accepted < (g->n - 1) && h.size > 0) { //heap에서 엣지를 꺼내서 트리에 넣는다.
		Edge e = delete_min_heap(&h); //min 가중치 간선 제거, 반환
		int uset = set_find(e.start);
		int vset = set_find(e.end);

		if (uset != vset) {
			printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
	}
	system("pause"); // 프로그램 실행 창이 빨리 종료되어서 넣음.
}


int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);
	//그래프를 생성하는 함수
	GenerateGraph(g);
	QuickKruskal(g); //quick 기반 kruskal
	MinHeapKruskal(g); //minheap 기반 kruskal
	free(g);

	return 0;
}