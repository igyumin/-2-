#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int sorted[SIZE];
int comparisonCount, moveCount;
int isFirst = 0, totalComparisons = 0, totalMoves = 0, rounds = 0;

void generateRandomArray(int Data[]) { //0~999 사이의 난수 배열을 만드는 함수
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		Data[i] = rand() % 1000;
	}
}

void merge(int Data[], int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));

	for (i = 0; i < n1; i++) {
		L[i] = Data[left + i];
		moveCount++;
	}
	for (j = 0; j < n2; j++) {
		R[j] = Data[mid + 1 + j];
		moveCount++;
	}

	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2) { // 둘 다 참일 경우 돌아간다.
		comparisonCount++;
		if (L[i] <= R[j]) {
			Data[k] = L[i]; //작은 거 부터
			moveCount++;
			i++; //왼쪽 배열의 인덱스를 한 칸 +
		}
		else {
			Data[k] = R[j]; //작은 거 부터
			moveCount++;
			j++; //오른쪽 배열의 인덱스를 한 칸 +
		}
		k++; //데이터를 넣었으니 k++
	}

	//남은 L, R 배열 값들을 Data 배열에 넣어준다.
	while (i < n1) {
		Data[k] = L[i];
		moveCount++;
		i++;
		k++;
	}

	while (j < n2) {
		Data[k] = R[j];
		moveCount++;
		j++;
		k++;
	}

	free(L);
	free(R);
}

void doMergeSort(int Data[], int size) { //합병정렬
	int curr_size;
	int left_start;

	for (curr_size = 1; curr_size <= size - 1; curr_size = 2 * curr_size) { // 1 2 4 8 16 32 64
		for (left_start = 0; left_start < size - 1; left_start += 2 * curr_size) { //1, 0 2 4 6 8 10...
			int mid = left_start + curr_size - 1;
			int right_end;
			if (left_start + 2 * curr_size - 1 < size - 1) {
				right_end = left_start + 2 * curr_size - 1;
			}
			else {
				right_end = size - 1;
			}

			merge(Data, left_start, mid, right_end);

			rounds++;
			if (rounds % 10 == 0 && isFirst == 0) {
			//10번에 한번만 출력
			for (int i = 0; i < 10; i++) //0 ~ 9값
				printf("%3d ", Data[i]);
			printf("| ");
			for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) //중앙-1 ~ 중앙+10
				printf("%3d ", Data[i]);
			printf("\n\n");
			}
		}
	}
}

void printArray(int Data[], int size) { //배열 출력
	for (int i = 0; i < size; i++) {
		printf("%d ", Data[i]);
	}
	printf("\n");
}

int main() {
	int array[SIZE];

	for (int i = 0; i < 20; i++) {
		generateRandomArray(array);
		comparisonCount = 0;
		moveCount = 0;

		if (i == 0) {
			printf("Merge Sort Run\n");
			doMergeSort(array, SIZE);

			printf("Result\n");
			printArray(array, SIZE);
			isFirst++;
		}
		else {
			doMergeSort(array, SIZE); //평균 구하기 위한 doMergeSort
		}

		totalComparisons += comparisonCount;
		totalMoves += moveCount;
	}

	printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
	printf("Average Moves: %.2f\n", totalMoves / 20.0);
	getchar();

	return 0;
}