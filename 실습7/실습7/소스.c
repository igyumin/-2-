#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_SIZE];
    int heap_size;
} HeapType;


void initHeap(HeapType* h) {
    h->heap_size = 0; // 힙 크기 0
}

void swap(element* a, element* b) {
    element temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(HeapType* h, int i) {
    int largest = i; 
    int left = 2 * i + 1;  // 왼쪽 자식
    int right = 2 * i + 2;  // 오른쪽 자식

    if (left < h->heap_size && h->heap[left].key > h->heap[largest].key) {
        largest = left;
    }
    if (right < h->heap_size && h->heap[right].key > h->heap[largest].key) {
        largest = right;
    }

    if (largest != i) {
        swap(&h->heap[i], &h->heap[largest]);
        heapify(h, largest);
    }
}

void insertToHeap(HeapType* h, int value) {
    if (h->heap_size >= MAX_SIZE) {
        printf("Heap is full!\n");
        return;
    }

    element data;
    data.key = value;

    h->heap[h->heap_size] = data; // 새로운 요소 추가
    int i = h->heap_size;
    h->heap_size++;

    
    while (i != 0 && h->heap[(i - 1) / 2].key < h->heap[i].key) {// 부모와 비교하면서 재정렬
        swap(&h->heap[i], &h->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    for (int j = 0; j < h->heap_size; j++) {
        printf("%d ", h->heap[j].key);
    }
    printf("\n");
}

void buildMaxHeap(HeapType* h) { // 최대 힙 생성
    for (int i = h->heap_size / 2 - 1; i >= 0; i--) {
        heapify(h, i);
    }
}

void BuildMaxHeapAndSort(int inputData[], int n) {
    HeapType heap;
    initHeap(&heap);

    for (int i = 0; i < n; i++) { //힙에 값 추가
        insertToHeap(&heap, inputData[i]);
    }

    buildMaxHeap(&heap);

    for (int i = heap.heap_size - 1; i >= 0; i--) {
        inputData[i] = heap.heap[0].key; //정렬된 배열에 저장
        swap(&heap.heap[0], &heap.heap[i]); // 새 값을 배열의 끝으로 이동
        heap.heap_size--; // 힙의 크기 줄이기
        heapify(&heap, 0); // 힙 재정렬


        for (int j = 0; j < heap.heap_size; j++) { // 정렬하는 거 출력
            printf("%d ", heap.heap[j].key);
        }
        printf("\n");
    }

}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 힙 정렬 실행
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // 정렬된 결과 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
