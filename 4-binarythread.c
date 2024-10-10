#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	int data;
	struct TreeNode* right, *left;
}TreeNode;

typedef struct ThreadNode {
	int data;
	struct ThreadNode* right, * left;
	int left_thread, right_thread;
} ThreadNode;

TreeNode* new_node(int key) {
	TreeNode* temp = NULL;

	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = key;
	temp->right = temp->left = NULL;

	return temp;
}

TreeNode* insert_node(TreeNode* node, int key) {
	if (node == NULL) return new_node(key);

	if (key < node->data) {
		node->left = insert_node(node->left, key);
	}
	else if (key > node->data) {
		node->right = insert_node(node->right, key);
	}
	return node;
}

TreeNode* GenerateBinaryTree(int inputData[]) {
	TreeNode* root = NULL;

	for (int i = 0; i < 15; i++) {
		root = insert_node(root, inputData[i]);
	}

	return root;
}

void BinaryTreeInOrder(TreeNode* root) {
	if (root != NULL) {
		BinaryTreeInOrder(root->left);
		printf("%d ", root->data);
		BinaryTreeInOrder(root->right);
	}
}

ThreadNode* find_successor(ThreadNode* p) {
	ThreadNode* q = p->right;

	if (p->right_thread == TRUE) {
		return q;
	}

	while (q->left != NULL && q->left_thread == FALSE) {
		q = q->left;
	}

	return q;
}

void ThreadTreeInOrder(ThreadNode* t) {
	ThreadNode* q;

	q = t;

	while (q->left) {
		q = q->left;
	}
	
	do {
		printf("%d ", q->data);
		q = find_successor(q);
	} while (q);
}

ThreadNode* new_tnode(int key) {
	ThreadNode* temp = (ThreadNode*)malloc(sizeof(ThreadNode));
	temp->data = key;
	temp->left = temp->right = NULL;
	temp->left_thread = temp->right_thread = TRUE;
	return temp;
}

ThreadNode* insert_tnode(ThreadNode* root, int key) {
	ThreadNode* temp = root;
	ThreadNode* parent = NULL;

	while (temp != NULL) {
		parent = temp;
		if (key < temp->data) {
			if (temp->left_thread == FALSE) {
				temp = temp->left;
			}
			else break;
		}
		else if (key > temp->data) {
			if (temp->right_thread == FALSE) {
				temp = temp->right;
			}
			else break;
		}
	}

	ThreadNode* new_node = new_tnode(key);
	if (parent == NULL) {
		root = new_node;
	}
	else if (key < parent->data) {
		new_node->left = parent->left;
		new_node->right = parent;
		parent->left_thread = FALSE;
		parent->left = new_node;
	}
	else {
		new_node->right = parent->right;
		new_node->left = parent;
		parent->right_thread = FALSE;
		parent->right = new_node;
	}

	return root;
}


ThreadNode* GenerateThreadTree(int inputData[]) {
	ThreadNode* root = NULL;
	

	for (int i = 0; i < 15; i++) {
		root = insert_tnode(root, inputData[i]);
	}

	return root;
}

int main() {
	int inputData[] = { 4,1,9,13,15,3,6,14,7,10,12,2,5,8,11 };

	TreeNode* root = GenerateBinaryTree(inputData);

	printf("Binary tree inorder: ");
	BinaryTreeInOrder(root);
	printf("\n");

	ThreadNode* troot = GenerateThreadTree(inputData);

	printf("Thread tree inorder: ");
	ThreadTreeInOrder(troot);
	printf("\n");

	free(root);
	free(troot);
	return 0;
}
