#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define SWAP(x, y) { int temp = (x); (x) = (y); (y) = temp; }

int comparisonCount, moveCount;
int totalComparisons = 0, totalMoveCount = 0, isFirst = 0;

void generateRandomArray(int Data[]) { //0~999의 난수를 저장하는 배열만들기
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		Data[i] = rand() % 1000;
	}
}

void printArray(int Data[], int size) { //배열 출력
	for (int i = 0; i < size; i++) {
		printf("%d ", Data[i]);
	}
	printf("\n");
}

int partition(int Data[], int low, int high) {
	int pivot = Data[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		comparisonCount++;
		if (Data[j] <= pivot) {
			i++;
			SWAP(Data[i], Data[j]); moveCount += 3;
		}
	}
	SWAP(Data[i + 1], Data[high]); moveCount += 3;
	return (i + 1); 
}

void doQuickSort(int Data[], int size) { //퀵 정렬
	int stack[SIZE];
	int top = -1;

	// 초기값을 스택에 넣음
	stack[++top] = 0;
	stack[++top] = size - 1;
	int rounds = 0;

	while (top >= 0) {
		int high = stack[top--];
		int low = stack[top--];

		int p = partition(Data, low, high);

		// pivot을 왼쪽으로 옮김
		if (p - 1 > low) {
			stack[++top] = low; 
			stack[++top] = p - 1; 
		}

		// pivot의 오른쪽 부분을 스택에 추가
		if (p + 1 < high) { 
			stack[++top] = p + 1;
			stack[++top] = high;
		}

		rounds++;
		if (rounds % 10 == 0 && isFirst == 0) {
			for (int i = 40; i < 60; i++) {
				printf("%d ", Data[i]);
			}
			printf("\n\n");
		}
	}
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	for (int i = 0; i < 20; i++) {
		generateRandomArray(array);
		comparisonCount = 0;
		moveCount = 0;
		if (i == 0) {
			printf("Quick Sort Run\n");
			doQuickSort(array, SIZE);
			printf("Result\n");
			printArray(array, SIZE);
			isFirst++;
		}
		else {
			doQuickSort(array, SIZE);
		}
		totalComparisons += comparisonCount;
		totalMoveCount += moveCount;
	}
	printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
	printf("Average Moves: %.2f\n", totalMoveCount / 20.0);
	getchar();
	return 0;
}


