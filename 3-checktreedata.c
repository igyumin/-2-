#include <stdio.h>
#include <stdlib.h>

typedef int value;

typedef struct TreeNode {
	value data;
	struct TreeNode* left, * right;
}TreeNode;

typedef TreeNode* element;

typedef struct QueueNode {
	element data;
	struct QueueNode* link;
} QueueNode;

typedef struct LinkedQueueType {
	QueueNode* rear, * front;
} LinkedQueueType;


void init(LinkedQueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(LinkedQueueType* q) {
	return (q->front == NULL);
}

void enqueue(LinkedQueueType* q, element data) {
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = data;
	temp->link = NULL;
	if (is_empty(q)) {
		q->front = temp;
		q->rear = temp;
	}
	else {
		q->rear->link = temp;
		q->rear = temp;
	}
}

element dequeue(LinkedQueueType* q) {
	QueueNode* temp = q->front;
	element data;
	if (is_empty(q)) {
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);
	}
	else {
		data = temp->data;
		q->front = q->front->link;
		if (q->front == NULL) {
			q->rear = NULL;
		}
		free(temp);
		return data;
	}
}

int queueSize(LinkedQueueType* q) {
	if (q->front == NULL) return;

	QueueNode* temp = q->front;
	int count = 0;

	while (temp != NULL) {
		count++;
		temp = temp->link;
	}

	return count;
}

void PlaceNode(TreeNode* node, value direction, value data) {
	element NewNode = (element)malloc(sizeof(TreeNode));
	NewNode->data = data;
	NewNode->left = NewNode->right = NULL;

	if (direction == 0) {
		node->left = NewNode;
	}
	else
		node->right = NewNode;
}

void GenerateLinkTree(element root) {
	PlaceNode(root, 0, 2);
	PlaceNode(root, 1, 9);
	PlaceNode(root->left, 0, 3);
	PlaceNode(root->left, 1, 5);
	PlaceNode(root->left->left, 0, 4);
	PlaceNode(root->left->left, 1, 6);
	PlaceNode(root->left->right, 0, 7);
	PlaceNode(root->left->right, 1, 8);
	PlaceNode(root->right, 0, 10);
	PlaceNode(root->right, 1, 13);
	PlaceNode(root->right->left, 0, 11);
	PlaceNode(root->right->left, 1, 12);
	PlaceNode(root->right->right, 0, 14);
	PlaceNode(root->right->right, 1, 15);
}

void GetSumOfNodes(TreeNode* root) {
	LinkedQueueType q;
	init(&q);
	TreeNode* ptr = root;
	int node_sum = 0;
	
	if (root == NULL) return;
	enqueue(&q, ptr);

	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		node_sum += ptr->data;
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}

	printf("Sum of nodes : %d\n", node_sum);
}

void GetNumberOfNodes(TreeNode* root) {
	LinkedQueueType q;
	TreeNode* ptr = root;
	init(&q);
	int count = 0;

	if (root == NULL) return;
	enqueue(&q, ptr);

	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		count++;
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}

	printf("Number of nodes : %d\n", count);
}

void GetHeightOfTree(TreeNode* root) {
	LinkedQueueType q;
	TreeNode* ptr = root;
	init(&q);
	int height = 0;
	
	if (ptr == NULL) return;
	enqueue(&q, ptr);

	while (!is_empty(&q)) {
		int levelSize = queueSize(&q); 
		for (int i = 0; i < levelSize; i++) {
			ptr = dequeue(&q);
			if (ptr->left) {
				enqueue(&q, ptr->left);
			}
			if (ptr->right) {
				enqueue(&q, ptr->right);
			}
		}
		height++;
	}

	printf("Height of Tree : %d\n", height); 
}


void GetNumberOfLeafNodes(TreeNode* root) {
	LinkedQueueType q;
	TreeNode* ptr = root;
	init(&q);
	int leafCount = 0;

	if (ptr == NULL) return;
	enqueue(&q, root);

	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		if (ptr->left == NULL && ptr->right == NULL) {
			leafCount++;
		}
		if (ptr->left) {
			enqueue(&q, ptr->left);
		}
		if (ptr->right) {
			enqueue(&q, ptr->right);
		}
	}

	printf("Number of leaf nodes : %d\n", leafCount);
}

int main() {
	element root = (element)malloc(sizeof(TreeNode));
	root->data = 1;

	GenerateLinkTree(root);

	GetSumOfNodes(root);
	GetNumberOfNodes(root);
	GetHeightOfTree(root);
	GetNumberOfLeafNodes(root);

	return 0;
}
