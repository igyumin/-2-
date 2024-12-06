#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x, y) { int temp = (x); (x) = (y); (y) = temp; }

void generateRandomArray(int array[]) { //0~9999 ������ ������ ������ 1000ĭ ¥�� �迭�����
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 10000;
	}
}

int generateRandomIndex(int array[]) { //0~999 ������ �������� return�Ͽ� �ε��� ������ ��� 
	int n = rand() % 1000;
	return n;
}

int partition(int Data[], int low, int high) { //quickSort�� ���� partition
	int pivot = Data[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		if (Data[j] <= pivot) {
			i++;
			SWAP(Data[i], Data[j]);
		}
	}
	SWAP(Data[i + 1], Data[high]);
	return (i + 1);
}

void QuickSort(int Data[], int low, int high) { //�� ����
	int stack[SIZE];
	int top = -1;

	// �ʱⰪ�� ���ÿ� ����
	stack[++top] = 0;
	stack[++top] = SIZE - 1;
	int rounds = 0;

	while (top >= 0) {
		high = stack[top--];
		low = stack[top--];

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

void printArray(int* array) { //��¹�
	printf("Array Sorting Result:\n");
	for (int i = 0; i < 20; i++)
		printf("%4d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%4d ", array[i]);
	printf("\n\n");
}

float search_binary_forCount(int array[], int key, int low, int high) { //count�� �ϱ� ���� ����Ž��
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

float getAverageBinarySearchCompareCount(int array[]) { //1000ȸ ��� ��Ƚ���� ���� (����Ž��)
	float totalCount = 0;
	for (int i = 0; i < 1000; i++) {
		int n = generateRandomIndex(array);
		totalCount += search_binary_forCount(array, array[n], 0, SIZE);
	}
	float Average = totalCount / 1000;
	return Average;
}

float interpol_search_forCount(int array[], int key, int size) { //count�� �ϱ� ���� ����Ž��
	int low, high, j;
	float count;
	count = 0;
	low = 0; 
	high = size - 1;
	while ((array[high] >= key) && (key > array[low])) {
		j = ((float)(key - array[low]) / (array[high] - array[low]) * (high - low)) + low;
		count++;
		if (key > array[j]) {
			low = j + 1;
		}
		count++;
		if (key < array[j]) {
			high = j - 1;
		}
		count++;
		if(!(key > array[j]) && (!key < array[j])) {
			low = j;
		}
	}
	count++;
	if (array[low] == key)
		return count; // Ž������ 
	else return -1; // Ž������
}

float getAverageInterpolationSearchComparecount(int array[]) { //1000ȸ ��� ��Ƚ���� ���� (����Ž��)
	float totalCount = 0;
	for (int i = 0; i < 1000; i++) {
		int n = generateRandomIndex(array);
		totalCount += interpol_search_forCount(array, array[n], SIZE);
	}
	float Average = totalCount / 1000;
	return Average;
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	generateRandomArray(array);
	QuickSort(array, 0, SIZE - 1);
	printArray(array);
	printf("Average Compare Count of Binary Search: %.2f\n",
		getAverageBinarySearchCompareCount(array));
	printf("Average Compare Count of Interpolation Search: %.2f\n",
		getAverageInterpolationSearchComparecount(array));
	getchar(); //���â�� �ʹ� ���� ������ �߰��� getchar()
	return 0;
}