#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

int count = 0;

typedef struct element {
	int key;
} element;

typedef struct TreeNode {
	int heap_size;
	element heap[];
} TreeNode;

void init(TreeNode* root) {
	root->heap_size = 0;
}

void InsertMaxHeapTree(TreeNode* root, element data) { //�־��� �迭�� ����Ʈ���� �����ϴ� �Լ� - ������ ����
	int i, n;
	n = i = ++(root->heap_size); //���ο� ��尡 �߰��Ǳ⿡ ����� �ø�

	while ((i != 1) && (data.key > root->heap[i / 2].key)) { //���� �߰��� ����� Ű�� �θ��� Ű���� ũ��
		root->heap[i] = root->heap[i / 2]; //�ڽ��� ���� �θ� ����ִ´�.
		i /= 2;
		
	}
	root->heap[i] = data; //�θ��ڸ��� ���ο� ��带 �߰�
}

TreeNode* generateMaxHeapTree(element inputData[], int size) { //�־��� �迭�� ����Ʈ���� �����ϴ� �Լ� 
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode*)); //�����Ҵ�

	init(root); //�Ҵ��� ��带 �ʱ�ȭ

	for (int i = 0; i < size; i++) {
		InsertMaxHeapTree(root, inputData[i]); //�־��� �迭�� �ݺ����� ����Ͽ� ����Ʈ���� ����
	}

	return root;
}

void InsertHeapTree(TreeNode* root, element data) { //�����Լ�
	int i, n;
	(root->heap_size) = n = i = ++(root->heap_size); //���߿� ������ ���� heap_size�� �� ĭ �÷��ش�.

	root->heap[i].key = data.key; //�� ĭ �ø� ������ �ڸ��� ��忡 ���ο� ����� Ű���� �־��ش�.
	for (int j = 1; j <= n; j++) { //���
		printf("%d ", root->heap[j].key);
	}
	printf("\n");

	while ((i != 1) && (data.key > root->heap[i / 2].key)) { //���ο� ����� Ű ���� �θ��� Ű ������ ũ��
		root->heap[i] = root->heap[i / 2]; //�ڽ��ڸ��� �θ� ����
		i /= 2;
		root->heap[i] = data; //�θ��ڸ��� �ڽ��� ����

		for (int j = 1; j <= n; j++) { //�̵��ϴ� ���� ���
			printf("%d ", root->heap[j].key);
		}
		printf("\n");

		count++; //�̵�Ƚ�� ���
	}

}

void DeleteHeapTree(TreeNode* root) {
	int parent, child, n;
	element temp;

	parent = 1;
	child = 2;

	root->heap[1].key = root->heap[root->heap_size].key; // �� ������ ����� Ű ���� ù ��°��忡 ����

	n = --(root->heap_size); //heap_size�� �� ĭ �ٿ��� �� ��������带 ���ܽ�Ŵ

	for (int j = 1; j <= n; j++) { //���
		printf("%d ", root->heap[j].key);
	}
	printf("\n");

	count++; //�̵�Ƚ��

	while (child <= root->heap_size) {
		if ((child < root->heap_size) && (root->heap[child].key) < root->heap[child + 1].key) { //���� �ڽ��� ������ �ڽĺ��� ���� ��
			child++; //������ �ڽ����� ����
		}

		if (root->heap[parent].key >= root->heap[child].key) { //���� �θ� ��尡 �ڽĳ�庸�� ũ�ų� ���� ������ �ݺ��� Ż��
			break;
		}

		temp = root->heap[parent]; // temp�� �θ��带 �ְ� �θ��忡 �ڽĳ�带 ����, �ڽĳ�忡 �θ��� ����
		root->heap[parent] = root->heap[child];
		root->heap[child] = temp;

		parent = child; //�ݺ����� �� ���� ���� ����
		child *= 2; 

			for (int j = 1; j <= n; j++) { //���
				printf("%d ", root->heap[j].key);
			}
			printf("\n");

			count++; //�̵�Ƚ��

	}
}

void PrintHeapTree(TreeNode* root) { //����Ʈ���� ��������Ʈ������ �̿��Ͽ� ���. ù ��° �������� n ��° �������� 2�� �¼��� ��尡 ���� �� ����.
	int n = 1; //heap �迭 ǥ���� ���� ���� --> heap[___] ���ȣ �ȿ� ���� ����..
	int level = 1; //Ʈ�� ����
	int s = 0;  

	while (n <= root->heap_size) { //n���� ���� ������� �۰ų� ���� ������ �ݺ�
		printf("[%d] ", level); //���� ���

		for (int i = 0; i < pow(2, s) && n <= root->heap_size; i++) { //n�� ���� ������� �۰ų� ���� i�� 2�� �¼����� ���� ��
			printf("%d ", root->heap[n].key); //Ű�� ���
			n++;
		}

		printf("\n");
		level++;
		s++; 
	}
}

void runUserInterface(TreeNode* root) {
	char choice;
	int num;
	element OriNum;

	printf("--------------------\n");
	printf("| i  : ��� �߰�   |\n");
	printf("| d  : ��� ����   |\n");
	printf("| p  : ������ ��� |\n");
	printf("| c  : ����        |\n");
	printf("--------------------\n");

	while(1) {
		printf("\n");
		printf("�޴� �Է� : ");
		scanf(" %c", &choice);

		switch (choice) { 
		case 'i' :
			printf("�߰��� �� �Է�: ");
			scanf("%d", &num);
			OriNum.key = num;
			InsertHeapTree(root, OriNum);
			printf("��尡 �̵��� Ƚ�� : %d\n", count);
			count = 0;
			break;

		case 'd':
			DeleteHeapTree(root);
			printf("��尡 �̵��� Ƚ�� : %d\n", count);
			count = 0;
			break;

		case 'p':
			printf("Ʈ�� ������ ���\n");
			PrintHeapTree(root);
			count = 0;
			break;

		case 'c':
			exit(1);
		}
	}
}int main() {
	element inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
	int size = 10;
	
	TreeNode* root = generateMaxHeapTree(inputData, size);

	runUserInterface(root);

	free(root);

	return 0;
}