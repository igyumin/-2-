#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000

float compareCount = 0;
float searchCount = 0;

typedef struct Node { //Ʈ���� ����� ���� ����ü
	int data;
	struct Node* left, * right;
	int height;
}Node;

Node* creatNode(int key) { //���ο� ��带 ����� �Լ�
	Node* nptr = (Node*)malloc(sizeof(Node));
	nptr->data = key;
	nptr->right = (Node*)NULL;
	nptr->left = (Node*)NULL;
	nptr->height = 1;
	return nptr;
}

int getHeight(Node* nptr) { //����� ������ �����ϴ� �Լ�
	if (nptr == (Node*)NULL) {
		return 0;
	}
	else {
		return nptr->height;
	}
}

int getBalance(Node* nptr) { // ������ ����Ʈ���� ���� ����Ʈ���� ���� ���� ������
	return getHeight(nptr->left) - getHeight(nptr->right);
}

Node* rotateRight(Node* y) { //Ʈ���� ������ ���߱� ���� ���������� ����
	Node* x = y->left;
	Node* T3 = x->right;

	x->right = y;
	y->left = T3;

	y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
	x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

	return x;
}

Node* rotateLeft(Node* y) { //Ʈ���� ������ ���߱� ���� �������� ����
	Node* x = y->right;
	Node* T2 = x->left;

	x->left = y;
	y->right = T2;

	y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
	x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

	return x;
}

Node* insertNode(Node* root, int key) { //AVL Ʈ���� ��带 �߰��ϴ� �Լ�
	if (root == (Node*)NULL) {
		return creatNode(key);
	}

	if (root->data > key) {
		root->left = insertNode(root->left, key);
	}
	else if (root->data < key) {
		root->right = insertNode(root->right, key);
	}
	else {
		return root;
	}
	root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

	int balance = getBalance(root);

	if (balance >= 2) {
		if (getBalance(root->left) >= 0) {

			return rotateRight(root);
		}
		else {

			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
	}
	else if (balance <= -2) {
		if (getBalance(root->right) < 0) {
			return rotateLeft(root);
		}
		else {
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}
	}
	return root;
}

Node* getMinValueNode(Node* node) { //���� ���� ���� ��带 ����
	Node* current = node;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

Node* deleteNode(Node* root, int key) { //AVL Ʈ���� ��带 �����ϴ� �Լ�
	if (root == NULL) {
		return root;
	}
	if (key < root->data) {
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->data) {
		root->right = deleteNode(root->right, key);
	}
	else {
		if ((root->left == NULL) || (root->right == NULL)) {
			Node* temp = root->left ? root->left : root->right;
			if (temp == NULL) {
				root = NULL;
			}
			else {
				*root = *temp;
			}
			free(temp);
		}
		else {
			Node* temp = getMinValueNode(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right, temp->data);
		}
	}
	if (root == NULL) {
		return root;
	}

	root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

	int balance = getBalance(root);

	if (balance > 1 && getBalance(root->left) >= 0) {
		return rotateRight(root);
	}
	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	if (balance < -1 && getBalance(root->right) <= 0) {
		return rotateLeft(root);
	}
	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	return root;
}

Node* Search(Node* root, int key) { //AVLƮ���� ����Ʈ���� Ž���ϴ� �Լ�
	if (root == NULL || root->data == key) {
		compareCount++;
		return root;
	}
	if (key < root->data) {
		compareCount++;
		return Search(root->left, key);
	}
	else {
		compareCount++;
		return Search(root->right, key);
	}
}

void doAVLBatch(Node* root) {
	for (int i = 0; i < 2000; i++) {
		int A = rand() % 3;
		int B = rand() % 1000;
		switch (A) {
		case 0:
			root = insertNode(root, B);
			break;
		case 1:
			root = deleteNode(root, B);
			break;
		case 2:
			searchCount++;
			Search(root, B);
			break;
		}
	}
}

void freeTree(Node* root) { //��带 ������ȸ�ϸ� free��Ŵ
	if (root) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

Node* insertNode_Binary(Node* root, int key) { //����Ʈ���� ��带 �߰��ϴ� �Լ�
	if (root == NULL) {
		return creatNode(key);
	}
	if (key < root->data) {
		root->left = insertNode_Binary(root->left, key);
	}
	else if (key > root->data) {
		root->right = insertNode_Binary(root->right, key);
	}
	return root;
}

Node* deleteNode_Binary(Node* root, int key) { //����Ʈ���� ��带 �����ϴ� �Լ�
	if (root == NULL) {
		return root;
	}
	if (key < root->data) {
		root->left = deleteNode_Binary(root->left, key);
	}
	else if (key > root->data) {
		root->right = deleteNode_Binary(root->right, key);
	}
	else {
		if (root->left == NULL) {
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			Node* temp = root->left;
			free(root);
			return temp;
		}
		Node* temp = getMinValueNode(root->right);
		root->data = temp->data;
		root->right = deleteNode_Binary(root->right, temp->data);
	}
	return root;
}

void doBinaryBatch(Node* root) {
	for (int i = 0; i < 2000; i++) {
		int A = rand() % 3;
		int B = rand() % 1000;
		switch (A) {
		case 0:
			root = insertNode_Binary(root, B);
			break;
		case 1:
			root = deleteNode_Binary(root, B);
			break;
		case 2:
			searchCount++;
			Search(root, B);
			break;
		}
	}
}

int main(int argc, char* argv[]) {
	Node* root = NULL;
	srand(time(NULL));
	float allCount = 0.0;
	doAVLBatch(root);
	allCount = (float)compareCount / searchCount;
	printf("average AVL compare count: %.2f\n", allCount);
	freeTree(root);
	root = NULL;
	compareCount = searchCount = 0;
	doBinaryBatch(root);
	allCount = (float)compareCount / searchCount;
	printf("average Bin compare count: %.2f\n", allCount);
	freeTree(root);
	getchar();
	return 0;
}
