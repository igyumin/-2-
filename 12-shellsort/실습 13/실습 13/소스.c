#include <stdio.h>
#include <stdlib.h>
#include <time.h> //srand(time(NULL))을 위해 include함
#define ARRAY_SIZE 100

void generateRandomNumbers(int Data[]) { //랜덤값을 가진 배열 만들기
	srand(time(NULL));
	for (int i = 0; i < ARRAY_SIZE; i++) {
		Data[i] = rand() % 1000; //0~999까지의 수가 들어감
	}
}

void print_list(int Data[], int n) { //배열 출력
	for (int i = 0; i < n; i++) {
		printf("%02d ", Data[i]);
	}
}

void gap_insertion_sort(int list[], int first, int last, int gap) { //count하지 않는 gap_insertion_sort
	int i, j, key;

	for (i = first + gap; i <= last; i += gap) { 
		key = list[i];
		for (j = i - gap; j >= first && list[j] > key; j -= gap) {
			list[j + gap] = list[j]; //한 칸 뒤로 미루기.
		}
		list[j + gap] = key; //밀린 자리에 key값 넣기
	}
}

void gap_insertion_sort_forCount(int list[], int first, int last, int gap, int* compare_count, int* move_count) { //count하는 gap_insertion_sort
	int i, j, key;

	for (i = first + gap; i <= last; i += gap) {
		(*compare_count)++;
		key = list[i]; 
		(*move_count)++;
		for (j = i - gap; j >= first && list[j] > key; j -= gap) {
			(*compare_count)++;
			list[j + gap] = list[j]; //한 칸 뒤로 미루기.
			(*move_count)++;
		}
		list[j + gap] = key; //밀린 자리에 key값 넣기
		(*move_count)++;
	}
}

void shell_sort(int Data[], int* compare_count, int* move_count, int n) {
	int i, gap;

	for (gap = (int)ARRAY_SIZE / 2; gap > 0; gap = (int)gap / n) {
		for (i = 0; i < gap; i++) { //한 gap 내 
			gap_insertion_sort_forCount(Data, i, ARRAY_SIZE-1, gap, compare_count, move_count);
		}
	}
}

void make_Average(int* compare_count, int* move_count, int n) { //shell sort의 20회 평균을 구하는 함수
	for (int i = 0; i < 20; i++) {
		int Data[ARRAY_SIZE];
		generateRandomNumbers(Data);
		shell_sort(Data, compare_count, move_count, n);
	}
	(*compare_count) /= 20;
	(*move_count) /= 20;
}

void doShellSort(int Data[], int n, int* compare_count, int* move_count) { //쉘 정렬
	int i, gap;

	for (gap = (int)ARRAY_SIZE / n; gap > 0; gap = (int)gap / n) {
		//if (gap % n == 0) gap = gap + 1; //gap == 4, gap = 1
		for (i = 0; i < gap; i++) { //한 gap 내 
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
	make_Average(compare_count, move_count, n); 	//함수 매개변수로 포인터를 사용할 때, 함수 호출 시에 포인터를 그대로 전달하는 이유는 포인터가 이미 주소를 담고 있기 때문
}

void insertion_sort(int Data[], int* compare_count, int* move_count) {
	int i, j, key;
	for (i = 1; i < ARRAY_SIZE; i++) { //배열의 앞 인덱스가 정렬이 되었다고 가정
		(*compare_count)++;
		key = Data[i];
		(*move_count)++;
		for (j = i - 1; j >= 0 && Data[j] > key; j--) { //key보다 j인덱스의 값이 더 크고 j가 0보다 크거나 같을 때 까지..
			(*compare_count)++;
			Data[j + 1] = Data[j]; // 뒤로 가기..
			(*move_count)++;
		}
		Data[j + 1] = key;
		(*move_count)++;
	};
}

void make_Average_Insertion(int* compare_count, int* move_count) { //insertion sort의 20회 평균을 구하는 함수
	for (int i = 0; i < 20; i++) {
		int Data[ARRAY_SIZE];
		generateRandomNumbers(Data);
		insertion_sort(Data, compare_count, move_count);
	}
	(*compare_count) /= 20;
	(*move_count) /= 20;
}

void doInsertionSort(int Data[], int* compare_count, int* move_count) { //삽입정렬
	int i, j, key;
	for (i = 1; i < ARRAY_SIZE; i++) { //배열의 앞 인덱스가 정렬이 되었다고 가정
		key = Data[i];
		for (j = i - 1; j >= 0 && Data[j] > key; j--) { //key보다 j인덱스의 값이 더 크고 j가 0보다 크거나 같을 때 까지..
			Data[j + 1] = Data[j]; // 뒤로 가기..
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
	//Insertion Sort ? 보너스(보너스 풀지 않는 경우 하단 없어도 됨)
	printf("Insertion Sort:\n");
	doInsertionSort(array, &comparisonCount, &moveCount);
	printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);
	getchar();
	return 0;
}