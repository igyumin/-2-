#include <stdio.h>
#include <stdlib.h>

typedef int value;

typedef struct TreeNode {
	value data;
	struct TreeNode* left, * right;
}TreeNode;

typedef TreeNode* element;

typedef struct StackNode {
	element data; 
	struct StackNode* link; 
} StackNode;

typedef struct LinkedStackType {
	StackNode* top;
} LinkedStackType;


void init(LinkedStackType* s){
	s->top = NULL;
}

value is_empty(LinkedStackType* s){
	return (s->top == NULL);
}

void push(LinkedStackType* s, element item){
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

element pop(LinkedStackType* s) {
	if (is_empty(s) == 1) {
		printf("Stack is empty");
		return NULL;
	}

	StackNode* temp = s->top;
	element data = temp->data;
	s->top = temp->link;
	free(temp);
	return data;
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

void LinkPreOrder(element root) {
	LinkedStackType s;
	init(&s);

	if (root != NULL) {
		push(&s, root);
		printf("push(%d) ", root->data);  
	}

	while (!is_empty(&s)) {
		element node = pop(&s);
		printf("pop(%d) ", node->data);   
		printf("visit(%d)\n", node->data); 

		
		if (node->right != NULL) {
			push(&s, node->right);
			printf("push(%d) ", node->right->data); 
		}

		if (node->left != NULL) {
			push(&s, node->left);
			printf("push(%d) ", node->left->data);  
		}
	}
}

void LinkInOrder(element root) {
	LinkedStackType s;
	init(&s);
	element node = root;

	while (node != NULL || !is_empty(&s)) {
		
		while (node != NULL) {
			push(&s, node);
			printf("push(%d) ", node->data);
			node = node->left;
		}

		node = pop(&s);
		printf("pop(%d) ", node->data);
		printf("visit(%d)\n", node->data);
		

		node = node->right;
	}
}

void LinkPostOrder(element root) {
	if (root == NULL) return;

	LinkedStackType s;
	init(&s);
	element node = root;
	element prev = NULL;

	while (node != NULL || !is_empty(&s)) {
		while (node != NULL) {
			push(&s, node);
			printf("push(%d) ", node->data);
			node = node->left;
		}

		node = pop(&s);
		printf("pop(%d) ", node->data);

		if (node->right != NULL && node->right != prev) {
			push(&s, node);
			printf("push(%d) ", node->data);
			node = node->right;
		}
		else {
			printf("visit(%d)\n", node->data);
			prev = node;
			node = NULL;
		}
	}
}


void LinkOrders(element root) {
	printf("전위 순회의 출력\n");
	LinkPreOrder(root);
	printf("\n중위 순회의 출력\n");
	LinkInOrder(root);
	printf("\n후위 순회의 출력\n");
	LinkPostOrder(root);
}

int main() {
	element root = (element)malloc(sizeof(TreeNode));
	root->data = 1;

	GenerateLinkTree(root);

	LinkOrders(root);

	return 0;
}
