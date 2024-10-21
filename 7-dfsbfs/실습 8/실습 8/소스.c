#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

typedef struct Stack { //DFS를 위한 stack struct
	int item[MAX_VERTICES];
	int top;
}Stack;

typedef struct Queue { //BFS를 위한 queue struct
	int data[MAX_VERTICES];
	int front;
	int rear;
} Queue;

void initStack(Stack* s) {
	s->top = -1;
}

int isStackEmpty(Stack* s) {
	return s->top == -1;
}

void push(Stack* s, int value) {
	s->item[++(s->top)] = value;
}

int pop(Stack* s) {
	return s->item[(s->top)--];
}

void initQueue(Queue* q) {
	q->front = -1;
	q->rear = -1;
}

int isQueueEmpty(Queue* q) {
	return q->front == -1;
}

void enqueue(Queue* q, int value) {
	if (q->rear == MAX_VERTICES - 1) {
		return;
	}
	if (q->front == -1) {
		q->front = 0; 
	}
	q->data[++q->rear] = value;
}

int dequeue(Queue* q) {
	int value = q->data[q->front++];
	if (q->front > q->rear) {
		q->front = q->rear = -1;
	}
	return value;
}

GraphMatType* create_mat_graph() {
	return (GraphMatType*)malloc(sizeof(GraphMatType));
}

void init_mat_graph(GraphMatType* g) {
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			g->adj_mat[i][j] = 0;
		}
	}
}

void insert_vertex_mat_graph(GraphMatType* g, int v) {
	if ((g->n) >= (MAX_VERTICES - 1)) {
		fprintf(stderr, "Over number of vertex\n");
		return;
	}
	(g->n)++;
}

void insert_edge_mat_graph(GraphMatType* g, int s, int e) {
	if (g->n <= s || g->n <= e) {
		fprintf(stderr, "vertex number error\n");
		return;
	}
	g->adj_mat[s][e] = 1;
	g->adj_mat[e][s] = 1;
}

GraphMatType* generate_graph() {
	GraphMatType* g = create_mat_graph();
	init_mat_graph(g);
	int i, j = 0;

	for (i = 0; i <= 10; i++) {
		insert_vertex_mat_graph(g, i);
	}

	insert_edge_mat_graph(g, 0, 2);
	insert_edge_mat_graph(g, 0, 5);
	insert_edge_mat_graph(g, 0, 4);
	insert_edge_mat_graph(g, 0, 6);
	insert_edge_mat_graph(g, 0, 9);

	insert_edge_mat_graph(g, 1, 4);
	insert_edge_mat_graph(g, 1, 7);
	insert_edge_mat_graph(g, 1, 5);
	insert_edge_mat_graph(g, 1, 10);

	insert_edge_mat_graph(g, 2, 4);
	insert_edge_mat_graph(g, 2, 3);

	insert_edge_mat_graph(g, 3, 4);
	insert_edge_mat_graph(g, 3, 5);

	insert_edge_mat_graph(g, 4, 7);

	insert_edge_mat_graph(g, 6, 7);
	insert_edge_mat_graph(g, 6, 8);

	insert_edge_mat_graph(g, 7, 10);

	insert_edge_mat_graph(g, 8, 9);
	insert_edge_mat_graph(g, 8, 10);

	return g;
}

void DFS(GraphMatType* g, int start, int end) {
	int visited[MAX_VERTICES] = { 0 };
	int count = 0;
	int found = 0;
	int current;

	Stack* stack = (Stack*)malloc(sizeof(Stack));
	initStack(stack);

	push(stack, start);  //시작 정점을 스택에 넣음

	while (!isStackEmpty(stack)) {
		current = pop(stack);

		if (!visited[current]) {
			printf("%d ", current);  // 방문한 정점을 출력
			visited[current] = 1;  // 방문함
			count++; // 방문 횟수 카운트

			if (current == end) { // 목표 노드에 도달하면
				printf("\n탐색 성공 : %d\n", current);
				found = 1; // 뒤에 나오는 found == 0에 걸리지 않기 위해 1로 set
				break; // 탐색에 성공하면 종료
			}

			for (int i = 0; i < g->n; i++) { // 이웃한 정점을 스택에 추가
				if (g->adj_mat[current][i] == 1 && !visited[i]) {
					push(stack, i);
				}
			}
		}
		else {
			printf("%d ", current);
		}
	}
	if (found == 0) { //탐색을 못했다면
		printf("\n탐색 실패\n");
	}
	printf("방문한 노드의 수 : %d\n", count);
	free(stack);
}

void BFS(GraphMatType* g, int start, int end) {
	int visited[MAX_VERTICES] = { 0 };
	int count = 0;
	int found = 0;
	int current;

	Queue* queue = (Queue*)malloc(sizeof(Queue));
	initQueue(queue);

	enqueue(queue, start);  // 시작 정점을 큐에 넣음
	visited[start] = 1; 

	while (!isQueueEmpty(queue)) {
		current = dequeue(queue);
		printf("%d ", current);  // 방문한 정점 출력
		count++; // 방문 횟수 카운트

		if (current == end) { // 목표 노드에 도달하면
			printf("\n탐색 성공 : %d\n", current);
			found = 1;
			break; // 탐색에 성공하면 종료
		}

		for (int i = 0; i < g->n; i++) { // 이웃한 정점들을 큐에 추가
			if (g->adj_mat[current][i] == 1 && !visited[i]) {
				enqueue(queue, i);
				visited[i] = 1; 
			}
		}
	}

	if (!found) {
		printf("\n탐색 실패\n");
	}
	printf("방문한 노드의 수 : %d\n", count);
	free(queue); // 메모리 해제
}

void print_interface(GraphMatType* g) {
	int choice, start, end;

	printf("----------------------\n");
	printf("1   : 깊이 우선 탐색  |\n");
	printf("2   : 너비 우선 탐색  |\n");
	printf("3   : 종료            |\n");
	printf("----------------------\n");

	while (1) {
		printf("\n");
		printf("메뉴 입력: ");
		scanf(" %d", &choice);

		switch (choice) {
		case 1:
			printf("시작 번호와 탐색할 값 입력: ");
			scanf("%d %d", &start, &end);
			DFS(g, start, end);
			break;

			case 2:
				printf("시작 번호와 탐색할 값 입력: ");
				scanf("%d %d", &start, &end);
				BFS(g, start, end);
				break;

			case 3:
				exit(1);
		}
	}
}


int main() {
	GraphMatType* g = generate_graph(); // 그래프 생성

	print_interface(g); // 유저 인터페이스 출력

	return 0;
}