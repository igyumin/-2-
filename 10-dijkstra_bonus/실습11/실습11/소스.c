/*#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	100	
#define INF	1000000	// 무한대 (연결이 없는 경우) 

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; // 시작정점으로부터의 최단경로 거리
int found[MAX_VERTICES];		// 방문한 정점 표시 

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void print_status(GraphType* g) {
	printf("Distance: ");
	for (int i = 1; i < g->n; i++) {
		if (distance[i] == INF) {
			printf(" * ");
		}
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf("Found: ");
	for (int i = 1; i < g->n; i++) {
		printf("%2d ", found[i]);
	}
	printf("\n\n");
}

void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	for (i = 0; i < g->n; i++) // 초기화 
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;    // 시작 정점 방문 표시
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
	}
}

int main(void)
{
	GraphType g = { 11,
		{{INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}, //0
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
	} };
	shortest_path(&g, 1);
	getchar();
	return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_ELEMENT 100
#define MAX_VERTICES 100

typedef struct {
    int number; 
    int weight; 
} element;

typedef struct DListNode { // 이중연결 노드 타입
    element vertex;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

typedef struct {
    int key;
    int start, end;
} heap_element;

typedef struct {
    heap_element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

typedef struct {
    int num_of_vertex;
    int num_of_edge;
    DListNode adj_list[MAX_VERTICES];
} GraphListType;

int dist[MAX_VERTICES], prev[MAX_VERTICES], found[MAX_VERTICES], found_order[MAX_VERTICES], found_count = 0;

void init_Dlist(DListNode* phead)
{
    phead->llink = phead;
    phead->rlink = phead;
}

void insert_Dlist(DListNode* before, element data)
{
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    newnode->vertex.number = data.number; // vertex
    newnode->vertex.weight = data.weight;
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

void delete_Dlist(DListNode* head, DListNode* removed)
{
    if (removed == head) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

DListNode* search_Dlist(DListNode* head, element data) {

    DListNode* node = head->rlink;
    do {
        if (node->vertex.number == data.number) return node;
        node = node->rlink;
    } while (node != head);
    return (DListNode*)NULL;
}

GraphListType* create_list_graph() {
    return (GraphListType*)malloc(sizeof(GraphListType));
}
void destroy_list_graph(GraphListType* g) {
    for (int i = 1; i < MAX_VERTICES; i++) {
        if (g->adj_list[i].vertex.number != -1) {
            DListNode* head, * next;
            head = &(g->adj_list[i]);
            next = head->rlink;
            while (next != head) {
                DListNode* temp = next;
                next = next->rlink;
                delete_Dlist(head, temp);
            }
        }
        g->adj_list[i].vertex.number = -1;
    }
    free(g);
}

void init_list_graph(GraphListType* g) {
    for (int i = 1; i < MAX_VERTICES; i++) {
        init_Dlist(&(g->adj_list[i]));
        g->adj_list[i].vertex.number = -1;
    }
    g->num_of_edge = g->num_of_vertex = 0;
}

void insert_vertex_list_graph(GraphListType* g, int v) {
    if (g->adj_list[v].vertex.number == -1) {
        g->adj_list[v].vertex.number = v;
        (g->num_of_vertex)++;
    }
    else {
        fprintf(stderr, "vertex %d already exist in graph\n", v);
    }
}

void insert_edge_list_graph(GraphListType* g, int s, int e, int w) {
    if (search_Dlist(&(g->adj_list[s]), (element) { e, w }) == NULL) {
        insert_Dlist(&(g->adj_list[s]), (element) { e, w });
        insert_Dlist(&(g->adj_list[e]), (element) { s, w });
        (g->num_of_edge)++;
    }
    else {
        fprintf(stderr, "edge (%d,%d) already exist in graph\n", s, e);
    }
}

HeapType* create_heap() {
    return (HeapType*)malloc(sizeof(HeapType));
}
void init_heap(HeapType* h) {
    h->heap_size = 0;
}

void insert_min_heap(HeapType* h, heap_element item) {

    int i = ++h->heap_size;

    while ((i > 1) && h->heap[i / 2].key > item.key) {
        h->heap[i] = h->heap[i / 2];
        i = i / 2;
    }
    h->heap[i] = item;
}

heap_element delete_min_heap(HeapType* h) {
    int parent, child;
    heap_element item, temp;

    item = h->heap[1];
    temp = h->heap[h->heap_size--];

    for (parent = 1, child = 2; child <= h->heap_size; parent = child, child *= 2) {
        if ((child < h->heap_size) &&
            (h->heap[child].key > h->heap[child + 1].key)) child++;
        if (temp.key <= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
    }

    h->heap[parent] = temp;
    return item;
}

GraphListType* dijkstra_sp(GraphListType* g, int start) {
    GraphListType* sp;
    HeapType* h;
    DListNode* nptr;

    h = create_heap(); //힙 생성
    init_heap(h); //초기화

    for (int i = 1; i <= g->num_of_vertex; i++) { //dist, prev, found 배열을 초기화.
        dist[i] = 100;
        prev[i] = -1;
        found[i] = 0;
    }
    dist[start] = 0; //처음 방문 지점의 dist를 0으로 설정.
    found[start] = 1; //처음 방문 지점에 방문함을 표시.
    found_order[found_count++] = start; //처음 방문 지점을 found_order의 0번지에 넣음

    printf("Distance: "); //처음 방문 지점에서의 distance 출력
    for (int i = 1; i <= g->num_of_vertex; i++) {
        if (dist[i] == 100) {
            printf(" * ");
        }
        else {
            printf("%2d ", dist[i]);
        }
    }
    printf("\nFound: "); //처음 방문 지점에서의 found 출력
    for (int i = 1; i <= g->num_of_vertex; i++) {
        printf("%2d ", found[i]);
    }
    printf("\n\n");

    nptr = g->adj_list[start].rlink;
    while (nptr != &(g->adj_list[start])) {
        dist[nptr->vertex.number] = nptr->vertex.weight;
        insert_min_heap(h, (heap_element) { nptr->vertex.weight, start, nptr->vertex.number });
        nptr = nptr->rlink;
    }

    sp = create_list_graph();
    init_list_graph(sp);
    insert_vertex_list_graph(sp, start);

    while (h->heap_size > 0) {
        heap_element min_edge = delete_min_heap(h);
        if (found[min_edge.end]) continue;
        found[min_edge.end] = 1;
        found_order[found_count++] = min_edge.end;
        prev[min_edge.end] = min_edge.start;
        insert_vertex_list_graph(sp, min_edge.end);
        insert_edge_list_graph(sp, min_edge.start, min_edge.end, min_edge.key);

        nptr = g->adj_list[min_edge.end].rlink;
        while (nptr != &(g->adj_list[min_edge.end])) {
            if (dist[nptr->vertex.number] > dist[min_edge.end] + nptr->vertex.weight) {
                dist[nptr->vertex.number] = dist[min_edge.end] + nptr->vertex.weight;
                insert_min_heap(h, (heap_element) { dist[nptr->vertex.number], min_edge.end, nptr->vertex.number });
            }
            nptr = nptr->rlink;
        }

        printf("Distance: ");
        for (int i = 1; i <= g->num_of_vertex; i++) {
            if (dist[i] == 100) {
                printf(" * ");
            }
            else {
                printf("%2d ", dist[i]);
            }
        }
        printf("\nFound: ");
        for (int i = 1; i <= g->num_of_vertex; i++) {
            printf("%2d ", found[i]);
        }
        printf("\n\n");
    }
    printf("Found Order: ");
    for (int i = 0; i < g->num_of_vertex; i++) {
        printf("%d ", found_order[i]);
    }
    printf("\n");
    return sp;
}

int main() {
    GraphListType* h;
    GraphListType* mst;

    h = create_list_graph(); //그래프 생성
    init_list_graph(h); //초기화

    for (int i = 1; i <= 10; i++) { //반복문으로 정점을 그래프에다 집어넣음
        insert_vertex_list_graph(h, i);
    }

    insert_edge_list_graph(h, 1, 6, 11); //엣지를 그래프에 집어넣음
    insert_edge_list_graph(h, 1, 7, 12);
    insert_edge_list_graph(h, 1, 2, 3);
    insert_edge_list_graph(h, 2, 3, 5);
    insert_edge_list_graph(h, 2, 4, 4);
    insert_edge_list_graph(h, 2, 5, 1);
    insert_edge_list_graph(h, 2, 6, 7);
    insert_edge_list_graph(h, 2, 7, 8);
    insert_edge_list_graph(h, 3, 4, 2);
    insert_edge_list_graph(h, 3, 7, 6);
    insert_edge_list_graph(h, 3, 8, 5);
    insert_edge_list_graph(h, 4, 5, 13);
    insert_edge_list_graph(h, 4, 8, 14);
    insert_edge_list_graph(h, 4, 10, 16);
    insert_edge_list_graph(h, 5, 6, 9);
    insert_edge_list_graph(h, 5, 9, 18);
    insert_edge_list_graph(h, 5, 10, 17);
    insert_edge_list_graph(h, 7, 8, 13);
    insert_edge_list_graph(h, 9, 10, 10);

    mst = dijkstra_sp(h, 1); //정점의 값은 1부터 시작함
    getchar(); //실행창이 빠르게 꺼져서 넣음

    destroy_list_graph(h);
    destroy_list_graph(mst);
}
