#include <stdio.h>
#include <stdlib.h>
#include <time.h> //srand(time(NULL))�� ���� include��
#define ARRAY_SIZE 100

void generateRandomNumbers(int Data[]) { //�������� ���� �迭 �����
	srand(time(NULL));
	for (int i = 0; i < ARRAY_SIZE; i++) {
		Data[i] = rand() % 1000; //0~999������ ���� ��
	}
}

void print_list(int Data[], int n) { //�迭 ���
	for (int i = 0; i < n; i++) {
		printf("%02d ", Data[i]);
	}
}

void gap_insertion_sort(int list[], int first, int last, int gap) { //count���� �ʴ� gap_insertion_sort
	int i, j, key;

	for (i = first + gap; i <= last; i += gap) { 
		key = list[i];
		for (j = i - gap; j >= first && list[j] > key; j -= gap) {
			list[j + gap] = list[j]; //�� ĭ �ڷ� �̷��.
		}
		list[j + gap] = key; //�и� �ڸ��� key�� �ֱ�
	}
}

void gap_insertion_sort_forCount(int list[], int first, int last, int gap, int* compare_count, int* move_count) { //count�ϴ� gap_insertion_sort
	int i, j, key;

	for (i = first + gap; i <= last; i += gap) {
		(*compare_count)++;
		key = list[i]; 
		(*move_count)++;
		for (j = i - gap; j >= first && list[j] > key; j -= gap) {
			(*compare_count)++;
			list[j + gap] = list[j]; //�� ĭ �ڷ� �̷��.
			(*move_count)++;
		}
		list[j + gap] = key; //�и� �ڸ��� key�� �ֱ�
		(*move_count)++;
	}
}

void shell_sort(int Data[], int* compare_count, int* move_count, int n) {
	int i, gap;

	for (gap = (int)ARRAY_SIZE / 2; gap > 0; gap = (int)gap / n) {
		for (i = 0; i < gap; i++) { //�� gap �� 
			gap_insertion_sort_forCount(Data, i, ARRAY_SIZE-1, gap, compare_count, move_count);
		}
	}
}

void make_Average(int* compare_count, int* move_count, int n) { //shell sort�� 20ȸ ����� ���ϴ� �Լ�
	for (int i = 0; i < 20; i++) {
		int Data[ARRAY_SIZE];
		generateRandomNumbers(Data);
		shell_sort(Data, compare_count, move_count, n);
	}
	(*compare_count) /= 20;
	(*move_count) /= 20;
}

void doShellSort(int Data[], int n, int* compare_count, int* move_count) { //�� ����
	int i, gap;

	for (gap = (int)ARRAY_SIZE / n; gap > 0; gap = (int)gap / n) {
		//if (gap % n == 0) gap = gap + 1; //gap == 4, gap = 1
		for (i = 0; i < gap; i++) { //�� gap �� 
			 gap_insertion_sort(Data, i, ARRAY_SIZE - 1, gap);
		}
		printf("Sorting with gap = %d:\n", gap);
		print_list(Data, 20);
		printf(" ...\n\n");
	}
	printf("Sorted shellArray (gap = %d):\n", n);
	print_list(Data, ARRAY_SIZE);
	printf("\n\n");
	(*move_count) = 0, (*compare_count) = 0;
	make_Average(compare_count, move_count, n); 	//�Լ� �Ű������� �����͸� ����� ��, �Լ� ȣ�� �ÿ� �����͸� �״�� �����ϴ� ������ �����Ͱ� �̹� �ּҸ� ��� �ֱ� ����
}

void insertion_sort(int Data[], int* compare_count, int* move_count) {
	int i, j, key;
	for (i = 1; i < ARRAY_SIZE; i++) { //�迭�� �� �ε����� ������ �Ǿ��ٰ� ����
		(*compare_count)++;
		key = Data[i];
		(*move_count)++;
		for (j = i - 1; j >= 0 && Data[j] > key; j--) { //key���� j�ε����� ���� �� ũ�� j�� 0���� ũ�ų� ���� �� ����..
			(*compare_count)++;
			Data[j + 1] = Data[j]; // �ڷ� ����..
			(*move_count)++;
		}
		Data[j + 1] = key;
		(*move_count)++;
	};
}

void make_Average_Insertion(int* compare_count, int* move_count) { //insertion sort�� 20ȸ ����� ���ϴ� �Լ�
	for (int i = 0; i < 20; i++) {
		int Data[ARRAY_SIZE];
		generateRandomNumbers(Data);
		insertion_sort(Data, compare_count, move_count);
	}
	(*compare_count) /= 20;
	(*move_count) /= 20;
}

void doInsertionSort(int Data[], int* compare_count, int* move_count) { //��������
	int i, j, key;
	for (i = 1; i < ARRAY_SIZE; i++) { //�迭�� �� �ε����� ������ �Ǿ��ٰ� ����
		key = Data[i];
		for (j = i - 1; j >= 0 && Data[j] > key; j--) { //key���� j�ε����� ���� �� ũ�� j�� 0���� ũ�ų� ���� �� ����..
			Data[j + 1] = Data[j]; // �ڷ� ����..
		}
		Data[j + 1] = key;
	}

	printf("Sorted insertionArray:\n");
	for (i = 0; i < ARRAY_SIZE; i++) {
		printf("%d ", Data[i]);
	}
	printf("\n\n");

	(*move_count) = 0, (*compare_count) = 0;
	make_Average_Insertion(compare_count, move_count);
}

int main() {
	int array[ARRAY_SIZE];
	int comparisonCount, moveCount;
	generateRandomNumbers(array);
	// Shell Sort
	printf("Shell Sort (n/2):\n");
	doShellSort(array, 2, &comparisonCount, &moveCount);
	printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);
	printf("Shell Sort (n/3):\n");
	doShellSort(array, 3, &comparisonCount, &moveCount);
	printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);
	//Insertion Sort ? ���ʽ�(���ʽ� Ǯ�� �ʴ� ��� �ϴ� ��� ��)
	printf("Insertion Sort:\n");
	doInsertionSort(array, &comparisonCount, &moveCount);
	printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);
	getchar();
	return 0;
}