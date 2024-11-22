#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int n = 0;

void generateRandomData(int Data[]) { //0~999의 랜덤 수를 배열에 집어넣는다.
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		Data[i] = rand() % 1000;
	}
}

void print_Sort(int Data[], int i) { //10, 30, 50, 70, 90, 99 step에서의 정렬을 출력
	if ((i+1) % 10 == 0) {
		if ((i+1) / 10 == 2 * n + 1) {
			printf("Step %d :", i+1);
			for (i = 0; i < SIZE; i++) {
				printf("%d ", Data[i]);
			}
			n++;
			printf("\n\n");
		}
	}
	else {
		if (i+1 == 99) {
			printf("Step %d :", i+1);
			for (i = 0; i < SIZE; i++) {
				printf("%d ", Data[i]);
			}
			printf("\n\n");
		}
	}
}

void doSelectionSort(int Data[]) { //선택정렬
	printf("Selction Sort: \n");
	int i, j, least, temp;
	for (i = 0; i < SIZE - 1; i++) {
		least = i;
		for (j = i + 1; j < SIZE; j++) {
			if (Data[j] < Data[least]) {
					least = j; //제일 작은 값의 인덱스를 기억.
			}
		}
		SWAP(Data[i], Data[least], temp); //매크로 define
		print_Sort(Data, i);
	}
}

int insertion_sort(int Data[]) { 
	int i, j, key, count = 0;
	for (i = 1; i < SIZE; i++) { //배열의 앞 인덱스가 정렬이 되었다고 가정
		key = Data[i];
		for (j = i - 1; j >= 0 && Data[j] > key; j--) { //key보다 j인덱스의 값이 더 크고 j가 0보다 크거나 같을 때 까지..
			count++;
			Data[j + 1] = Data[j]; // 뒤로 가기..
		}
		Data[j + 1] = key;
	}
	return count;
}

void print_IcompareCount() { //삽입정렬 평균 비교횟수 출력
	int countSum = 0;
	for (int i = 0; i < 20; i++) {
		int Data[SIZE];
		generateRandomData(Data);
		countSum += insertion_sort(Data);
	}
	int average = countSum / 20;
	printf("Insertion Sort Compare Average: %d\n", average);
}

void doInsertionSort(int Data[]) { //삽입정렬
	print_IcompareCount();
	int i, j, key;
	for (i = 1; i < SIZE; i++) { //배열의 앞 인덱스가 정렬이 되었다고 가정
		key = Data[i];
		for (j = i - 1; j >= 0 && Data[j] > key; j--) { //key보다 j인덱스의 값이 더 크고 j가 0보다 크거나 같을 때 까지..
			Data[j + 1] = Data[j]; // 뒤로 가기..
		}
		Data[j + 1] = key;
	}

	printf("Insertion Sort Result: \n");
	for (i = 0; i < SIZE; i++) {
		printf("%d ", Data[i]);
	}
	printf("\n\n\n");
}

int bubble_sort(int Data[]) { //버블정렬
	int i, j, temp, flag, count = 0;
	for (i = SIZE - 1; i > 0; i--) {
		flag = 0;
		for (j = 0; j < i; j++) {
			if (Data[j] > Data[j + 1]) {
				SWAP(Data[j], Data[j + 1], temp);
				count += 3;
				flag = 1;
			}
		}
		if (flag == 0) {
			break;
		}
	}
	return count;
}

void print_BmoveCount() { //버블정렬 평균 이동 횟수 출력
	int countSum = 0;
	for (int i = 0; i < 20; i++) {
		int Data[SIZE];
		generateRandomData(Data);
		countSum += bubble_sort(Data);
	}
	int average = countSum / 20;
	printf("Bubble Sort Move Average: %d\n", average);
}

void doBubbleSort(int Data[]) { //무거운 게 뒤로 가게...
	print_BmoveCount();
	int i, j, temp, flag; //flag를 통해 정렬이 다 되었으면 더 정렬하지 않도록 하게 한다.
	for (i = SIZE - 1; i > 0; i--) {
		flag = 0;
		for (j = 0; j < i; j++) {
			if (Data[j] > Data[j + 1]) {
				SWAP(Data[j], Data[j + 1], temp);
				flag = 1;
			}
		}
		if (flag == 0) {
			break;
		}
	}
	printf("Bubble Sort Result: \n");
	for (i = 0; i < SIZE; i++) {
		printf("%d ", Data[i]);
	}
	printf("\n\n\n");
}

int main() {
	int randomData[SIZE];
	generateRandomData(randomData);

	doSelectionSort(randomData);
	doInsertionSort(randomData);
	doBubbleSort(randomData);

	system("pause");
	return 0;
}