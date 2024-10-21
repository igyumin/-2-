#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

typedef struct Stack { //DFS�� ���� stack struct
	int item[MAX_VERTICES];
	int top;
}Stack;

typedef struct Queue { //BFS�� ���� queue struct
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

	push(stack, start);  //���� ������ ���ÿ� ����

	while (!isStackEmpty(stack)) {
		current = pop(stack);

		if (!visited[current]) {
			printf("%d ", current);  // �湮�� ������ ���
			visited[current] = 1;  // �湮��
			count++; // �湮 Ƚ�� ī��Ʈ

			if (current == end) { // ��ǥ ��忡 �����ϸ�
				printf("\nŽ�� ���� : %d\n", current);
				found = 1; // �ڿ� ������ found == 0�� �ɸ��� �ʱ� ���� 1�� set
				break; // Ž���� �����ϸ� ����
			}

			for (int i = 0; i < g->n; i++) { // �̿��� ������ ���ÿ� �߰�
				if (g->adj_mat[current][i] == 1 && !visited[i]) {
					push(stack, i);
				}
			}
		}
		else {
			printf("%d ", current);
		}
	}
	if (found == 0) { //Ž���� ���ߴٸ�
		printf("\nŽ�� ����\n");
	}
	printf("�湮�� ����� �� : %d\n", count);
	free(stack);
}

void BFS(GraphMatType* g, int start, int end) {
	int visited[MAX_VERTICES] = { 0 };
	int count = 0;
	int found = 0;
	int current;

	Queue* queue = (Queue*)malloc(sizeof(Queue));
	initQueue(queue);

	enqueue(queue, start);  // ���� ������ ť�� ����
	visited[start] = 1; 

	while (!isQueueEmpty(queue)) {
		current = dequeue(queue);
		printf("%d ", current);  // �湮�� ���� ���
		count++; // �湮 Ƚ�� ī��Ʈ

		if (current == end) { // ��ǥ ��忡 �����ϸ�
			printf("\nŽ�� ���� : %d\n", current);
			found = 1;
			break; // Ž���� �����ϸ� ����
		}

		for (int i = 0; i < g->n; i++) { // �̿��� �������� ť�� �߰�
			if (g->adj_mat[current][i] == 1 && !visited[i]) {
				enqueue(queue, i);
				visited[i] = 1; 
			}
		}
	}

	if (!found) {
		printf("\nŽ�� ����\n");
	}
	printf("�湮�� ����� �� : %d\n", count);
	free(queue); // �޸� ����
}

void print_interface(GraphMatType* g) {
	int choice, start, end;

	printf("----------------------\n");
	printf("1   : ���� �켱 Ž��  |\n");
	printf("2   : �ʺ� �켱 Ž��  |\n");
	printf("3   : ����            |\n");
	printf("----------------------\n");

	while (1) {
		printf("\n");
		printf("�޴� �Է�: ");
		scanf(" %d", &choice);

		switch (choice) {
		case 1:
			printf("���� ��ȣ�� Ž���� �� �Է�: ");
			scanf("%d %d", &start, &end);
			DFS(g, start, end);
			break;

			case 2:
				printf("���� ��ȣ�� Ž���� �� �Է�: ");
				scanf("%d %d", &start, &end);
				BFS(g, start, end);
				break;

			case 3:
				exit(1);
		}
	}
}


int main() {
	GraphMatType* g = generate_graph(); // �׷��� ����

	print_interface(g); // ���� �������̽� ���

	return 0;
}