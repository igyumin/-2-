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

void InsertMaxHeapTree(TreeNode* root, element data) { //주어진 배열을 히프트리로 연결하는 함수 - 교과서 참고
	int i, n;
	n = i = ++(root->heap_size); //새로운 노드가 추가되기에 사이즈를 늘림

	while ((i != 1) && (data.key > root->heap[i / 2].key)) { //새로 추가할 노드의 키가 부모의 키보다 크면
		root->heap[i] = root->heap[i / 2]; //자식의 값에 부모를 집어넣는다.
		i /= 2;
		
	}
	root->heap[i] = data; //부모자리에 새로운 노드를 추가
}

TreeNode* generateMaxHeapTree(element inputData[], int size) { //주어진 배열을 히프트리로 생성하는 함수 
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode*)); //동적할당

	init(root); //할당한 노드를 초기화

	for (int i = 0; i < size; i++) {
		InsertMaxHeapTree(root, inputData[i]); //주어진 배열을 반복문을 사용하여 히프트리로 만듦
	}

	return root;
}

void InsertHeapTree(TreeNode* root, element data) { //삽입함수
	int i, n;
	(root->heap_size) = n = i = ++(root->heap_size); //나중에 삭제를 위해 heap_size도 한 칸 늘려준다.

	root->heap[i].key = data.key; //한 칸 늘린 사이즈 자리의 노드에 새로운 노드의 키값을 넣어준다.
	for (int j = 1; j <= n; j++) { //출력
		printf("%d ", root->heap[j].key);
	}
	printf("\n");

	while ((i != 1) && (data.key > root->heap[i / 2].key)) { //새로운 노드의 키 값이 부모의 키 값보다 크면
		root->heap[i] = root->heap[i / 2]; //자식자리에 부모를 대입
		i /= 2;
		root->heap[i] = data; //부모자리에 자식을 대입

		for (int j = 1; j <= n; j++) { //이동하는 것을 출력
			printf("%d ", root->heap[j].key);
		}
		printf("\n");

		count++; //이동횟수 출력
	}

}

void DeleteHeapTree(TreeNode* root) {
	int parent, child, n;
	element temp;

	parent = 1;
	child = 2;

	root->heap[1].key = root->heap[root->heap_size].key; // 맨 마지막 노드의 키 값을 첫 번째노드에 복사

	n = --(root->heap_size); //heap_size를 한 칸 줄여서 맨 마지막노드를 제외시킴

	for (int j = 1; j <= n; j++) { //출력
		printf("%d ", root->heap[j].key);
	}
	printf("\n");

	count++; //이동횟수

	while (child <= root->heap_size) {
		if ((child < root->heap_size) && (root->heap[child].key) < root->heap[child + 1].key) { //왼쪽 자식이 오른쪽 자식보다 작을 때
			child++; //오른쪽 자식으로 설정
		}

		if (root->heap[parent].key >= root->heap[child].key) { //만약 부모 노드가 자식노드보다 크거나 같을 때에는 반복문 탈출
			break;
		}

		temp = root->heap[parent]; // temp에 부모노드를 넣고 부모노드에 자식노드를 복사, 자식노드에 부모노드 복사
		root->heap[parent] = root->heap[child];
		root->heap[child] = temp;

		parent = child; //반복문을 또 돌기 위해 설정
		child *= 2; 

			for (int j = 1; j <= n; j++) { //출력
				printf("%d ", root->heap[j].key);
			}
			printf("\n");

			count++; //이동횟수

	}
}

void PrintHeapTree(TreeNode* root) { //히프트리는 완전이진트리임을 이용하여 출력. 첫 번째 레벨부터 n 번째 레벨까지 2의 승수로 노드가 있을 수 있음.
	int n = 1; //heap 배열 표현을 위한 변수 --> heap[___] 대괄호 안에 들어가는 숫자..
	int level = 1; //트리 레벨
	int s = 0;  

	while (n <= root->heap_size) { //n번이 히프 사이즈보다 작거나 같을 때까지 반복
		printf("[%d] ", level); //레벨 출력

		for (int i = 0; i < pow(2, s) && n <= root->heap_size; i++) { //n이 히프 사이즈보다 작거나 같고 i가 2의 승수보다 작을 때
			printf("%d ", root->heap[n].key); //키값 출력
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
	printf("| i  : 노드 추가   |\n");
	printf("| d  : 노드 삭제   |\n");
	printf("| p  : 레벨별 출력 |\n");
	printf("| c  : 종료        |\n");
	printf("--------------------\n");

	while(1) {
		printf("\n");
		printf("메뉴 입력 : ");
		scanf(" %c", &choice);

		switch (choice) { 
		case 'i' :
			printf("추가할 값 입력: ");
			scanf("%d", &num);
			OriNum.key = num;
			InsertHeapTree(root, OriNum);
			printf("노드가 이동된 횟수 : %d\n", count);
			count = 0;
			break;

		case 'd':
			DeleteHeapTree(root);
			printf("노드가 이동된 횟수 : %d\n", count);
			count = 0;
			break;

		case 'p':
			printf("트리 레벨별 출력\n");
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