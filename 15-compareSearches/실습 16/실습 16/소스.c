#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x, y) { int temp = (x); (x) = (y); (y) = temp; }

int compareCount = 0;

void generateRandomArray(int array[]) { //0~999 ������ ���� ���� ���� �迭 �����
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 1000;
	}
}

int generateRandomIndex(int array[]) { //0~999 ������ ���� ���� �ε��� ������ ����..
	int n = rand() % 1000;
	return n;
}

float seq_search_forCount(int array[], int key, int low, int high) { //count�� �ϱ� ���� ����Ž��
	int i;
	float count = 0;
	for (i = low; i <= high; i++) {
		count++;
		if (array[i] == key) {
			return count;
		}
	}
	return -1;
}

float getAverageLinearSearchCompareCount(int array[]) { //100ȸ ��� ��Ƚ���� ���ϱ�
	float totalCount = 0;
	for (int i = 0; i < 100; i++) {
		int n = generateRandomIndex(array);
		totalCount += seq_search_forCount(array, array[n], 0, SIZE);
	}
	float Average = totalCount / 100.0;
	return Average;
}

int partition(int Data[], int low, int high) { //quick sort�� ���� partition
	int pivot = Data[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		compareCount++;
		if (Data[j] <= pivot) {
			
			i++;
			SWAP(Data[i], Data[j]);
		}
	}
	SWAP(Data[i + 1], Data[high]); 
	return (i + 1);
}

void getQuickSortCompareCount(int Data[]) { //�� ����
	int stack[SIZE];
	int top = -1;

	// �ʱⰪ�� ���ÿ� ����
	stack[++top] = 0;
	stack[++top] = SIZE - 1;
	int rounds = 0;

	while (top >= 0) {
		int high = stack[top--];
		int low = stack[top--];

		int p = partition(Data, low, high);

		// pivot�� �������� �ű�
		if (p - 1 > low) {
			stack[++top] = low;
			stack[++top] = p - 1;
		}

		// pivot�� ���������� �ű�
		if (p + 1 < high) {
			stack[++top] = p + 1;
			stack[++top] = high;
		}
	}
}

float search_binary_forCount(int array[], int key, int low, int high) { //count�� ���� ����Ž��
	int middle;
	float count = 0; 
	while (low <= high) {
		middle = (low + high) / 2; 
		if (key == array[middle]) {
			count++;
			return count;
		}
		else if (key > array[middle]) {
			count++;
			low = middle + 1;
		}
		else {
			count++;
			high = middle - 1;
		}
	}
	return -1; 
}

float getAverageBinarySearchCompareCount(int array[]) { //100ȸ ��� ��Ƚ���� ���ϱ�
	float totalCount = 0;
	for (int i = 0; i < 100; i++) {
		int n = generateRandomIndex(array);
		totalCount += search_binary_forCount(array, array[n], 0, SIZE);
	}
	float Average = totalCount / 100.0;
	return Average;
}

void printArray(int array[]) { //��¹�
	printf("Array Sorting Result:\n");
	for (int i = 0; i < 20; i++)
		printf("%3d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%3d ", array[i]);
	printf("\n");
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	generateRandomArray(array);
	//��հ��� ��ȯ�ޱ� ���� ��ġ
	printf("Average Linear Search Compare Count: %.2f\n",
		getAverageLinearSearchCompareCount(array));
	//compareCount�� global variable�̹Ƿ�, ������ ���� ����
	//array�� ���ؼ� ���� �����ϸ� �ȴ�.
	getQuickSortCompareCount(array);
	printf("Quick Sort Compare Count: %d\n", compareCount);
	//���ĵ� Array�� ���ؼ� Binary Search 100ȸ ���� �� ��� ��Ƚ�� ���
	printf("Average Binary Search Compare Count: %.2f\n\n",
		getAverageBinarySearchCompareCount(array));
	printArray(array);
	getchar(); //���ε� �� ���� �ʿ�..
	return 0;
}

/*
 A, B, C�� ���ؼ� �� �������� ����Ž������ ����Ž������ ���� ���ϴ� ������ ����
 ������ �� ����Ž���� �� ������ ������ ������ �迭�� �ݾ� �پ���. 
 ������ ����Ž���� �ϳ��ϳ��� ���ϴ� ������ ��ġ�⿡ ��Ƚ���� ����Ž������ �� ���� ���ۿ� ����..
*/