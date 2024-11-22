#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int n = 0;

void generateRandomData(int Data[]) { //0~999�� ���� ���� �迭�� ����ִ´�.
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		Data[i] = rand() % 1000;
	}
}

void print_Sort(int Data[], int i) { //10, 30, 50, 70, 90, 99 step������ ������ ���
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

void doSelectionSort(int Data[]) { //��������
	printf("Selction Sort: \n");
	int i, j, least, temp;
	for (i = 0; i < SIZE - 1; i++) {
		least = i;
		for (j = i + 1; j < SIZE; j++) {
			if (Data[j] < Data[least]) {
					least = j; //���� ���� ���� �ε����� ���.
			}
		}
		SWAP(Data[i], Data[least], temp); //��ũ�� define
		print_Sort(Data, i);
	}
}

int insertion_sort(int Data[]) { 
	int i, j, key, count = 0;
	for (i = 1; i < SIZE; i++) { //�迭�� �� �ε����� ������ �Ǿ��ٰ� ����
		key = Data[i];
		for (j = i - 1; j >= 0 && Data[j] > key; j--) { //key���� j�ε����� ���� �� ũ�� j�� 0���� ũ�ų� ���� �� ����..
			count++;
			Data[j + 1] = Data[j]; // �ڷ� ����..
		}
		Data[j + 1] = key;
	}
	return count;
}

void print_IcompareCount() { //�������� ��� ��Ƚ�� ���
	int countSum = 0;
	for (int i = 0; i < 20; i++) {
		int Data[SIZE];
		generateRandomData(Data);
		countSum += insertion_sort(Data);
	}
	int average = countSum / 20;
	printf("Insertion Sort Compare Average: %d\n", average);
}

void doInsertionSort(int Data[]) { //��������
	print_IcompareCount();
	int i, j, key;
	for (i = 1; i < SIZE; i++) { //�迭�� �� �ε����� ������ �Ǿ��ٰ� ����
		key = Data[i];
		for (j = i - 1; j >= 0 && Data[j] > key; j--) { //key���� j�ε����� ���� �� ũ�� j�� 0���� ũ�ų� ���� �� ����..
			Data[j + 1] = Data[j]; // �ڷ� ����..
		}
		Data[j + 1] = key;
	}

	printf("Insertion Sort Result: \n");
	for (i = 0; i < SIZE; i++) {
		printf("%d ", Data[i]);
	}
	printf("\n\n\n");
}

int bubble_sort(int Data[]) { //��������
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

void print_BmoveCount() { //�������� ��� �̵� Ƚ�� ���
	int countSum = 0;
	for (int i = 0; i < 20; i++) {
		int Data[SIZE];
		generateRandomData(Data);
		countSum += bubble_sort(Data);
	}
	int average = countSum / 20;
	printf("Bubble Sort Move Average: %d\n", average);
}

void doBubbleSort(int Data[]) { //���ſ� �� �ڷ� ����...
	print_BmoveCount();
	int i, j, temp, flag; //flag�� ���� ������ �� �Ǿ����� �� �������� �ʵ��� �ϰ� �Ѵ�.
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