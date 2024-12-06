#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x, y) { int temp = (x); (x) = (y); (y) = temp; }

void generateRandomArray(int array[]) { //0~9999 사이의 값으로 구성된 1000칸 짜리 배열만들기
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 10000;
	}
}

int generateRandomIndex(int array[]) { //0~999 사이의 랜덤값을 return하여 인덱스 값으로 사용 
	int n = rand() % 1000;
	return n;
}

int partition(int Data[], int low, int high) { //quickSort를 위한 partition
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

void QuickSort(int Data[], int low, int high) { //퀵 정렬
	int stack[SIZE];
	int top = -1;

	// 초기값을 스택에 넣음
	stack[++top] = 0;
	stack[++top] = SIZE - 1;
	int rounds = 0;

	while (top >= 0) {
		high = stack[top--];
		low = stack[top--];

		int p = partition(Data, low, high);

		// pivot을 왼쪽으로 옮김
		if (p - 1 > low) {
			stack[++top] = low;
			stack[++top] = p - 1;
		}

		// pivot을 오른쪽으로 옮김
		if (p + 1 < high) {
			stack[++top] = p + 1;
			stack[++top] = high;
		}
	}
}

void printArray(int* array) { //출력문
	printf("Array Sorting Result:\n");
	for (int i = 0; i < 20; i++)
		printf("%4d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%4d ", array[i]);
	printf("\n\n");
}

float search_binary_forCount(int array[], int key, int low, int high) { //count를 하기 위한 이진탐색
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

float getAverageBinarySearchCompareCount(int array[]) { //1000회 평균 비교횟수를 구함 (이진탐색)
	float totalCount = 0;
	for (int i = 0; i < 1000; i++) {
		int n = generateRandomIndex(array);
		totalCount += search_binary_forCount(array, array[n], 0, SIZE);
	}
	float Average = totalCount / 1000;
	return Average;
}

float interpol_search_forCount(int array[], int key, int size) { //count를 하기 위한 보간탐색
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
		return count; // 탐색성공 
	else return -1; // 탐색실패
}

float getAverageInterpolationSearchComparecount(int array[]) { //1000회 평균 비교횟수를 구함 (보간탐색)
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
	getchar(); //출력창이 너무 빨리 꺼져서 추가한 getchar()
	return 0;
}