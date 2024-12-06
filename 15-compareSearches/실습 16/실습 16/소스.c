#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x, y) { int temp = (x); (x) = (y); (y) = temp; }

int compareCount = 0;

void generateRandomArray(int array[]) { //0~999 사이의 랜덤 값을 가진 배열 만들기
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 1000;
	}
}

int generateRandomIndex(int array[]) { //0~999 사이의 랜덤 값을 인덱스 값으로 쓰기..
	int n = rand() % 1000;
	return n;
}

float seq_search_forCount(int array[], int key, int low, int high) { //count를 하기 위한 순차탐색
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

float getAverageLinearSearchCompareCount(int array[]) { //100회 평균 비교횟수를 구하기
	float totalCount = 0;
	for (int i = 0; i < 100; i++) {
		int n = generateRandomIndex(array);
		totalCount += seq_search_forCount(array, array[n], 0, SIZE);
	}
	float Average = totalCount / 100.0;
	return Average;
}

int partition(int Data[], int low, int high) { //quick sort를 위한 partition
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

void getQuickSortCompareCount(int Data[]) { //퀵 정렬
	int stack[SIZE];
	int top = -1;

	// 초기값을 스택에 넣음
	stack[++top] = 0;
	stack[++top] = SIZE - 1;
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

		// pivot의 오른쪽으로 옮김
		if (p + 1 < high) {
			stack[++top] = p + 1;
			stack[++top] = high;
		}
	}
}

float search_binary_forCount(int array[], int key, int low, int high) { //count를 위한 이진탐색
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

float getAverageBinarySearchCompareCount(int array[]) { //100회 평균 비교횟수를 구하기
	float totalCount = 0;
	for (int i = 0; i < 100; i++) {
		int n = generateRandomIndex(array);
		totalCount += search_binary_forCount(array, array[n], 0, SIZE);
	}
	float Average = totalCount / 100.0;
	return Average;
}

void printArray(int array[]) { //출력문
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
	//평균값을 반환받기 위한 조치
	printf("Average Linear Search Compare Count: %.2f\n",
		getAverageLinearSearchCompareCount(array));
	//compareCount가 global variable이므로, 다음과 같이 구현
	//array에 대해서 직접 정렬하면 된다.
	getQuickSortCompareCount(array);
	printf("Quick Sort Compare Count: %d\n", compareCount);
	//정렬된 Array에 대해서 Binary Search 100회 수행 및 평균 비교횟수 출력
	printf("Average Binary Search Compare Count: %.2f\n\n",
		getAverageBinarySearchCompareCount(array));
	printArray(array);
	getchar(); //업로드 시 설명 필요..
	return 0;
}

/*
 A, B, C에 대해서 퀵 정렬후의 이진탐색에서 순차탐색보다 적게 비교하는 이유를 설명
 정렬이 된 이진탐색은 한 과정이 지나갈 때마다 배열이 반씩 줄어든다. 
 하지만 순차탐색은 하나하나씩 비교하는 과정을 거치기에 비교횟수가 이진탐색보다 더 많을 수밖에 없다..
*/