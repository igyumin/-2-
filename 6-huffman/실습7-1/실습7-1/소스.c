#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Node {
    char character;
    int frequency;
    struct Node* left, * right;
} Node;

Node* createNode(char character, int frequency) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(Node** heap, int size, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && heap[left]->frequency < heap[smallest]->frequency) {
        smallest = left;
    }
    if (right < size && heap[right]->frequency < heap[smallest]->frequency) {
        smallest = right;
    }
    if (smallest != idx) {
        swap(&heap[idx], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    Node** heap = (Node**)malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) {
        heap[i] = createNode(characters[i], frequencies[i]);
    }

    int heapSize = size;

    // 초기 빈도 출력
    for (int i = 0; i < size; i++) {
        printf("%d ", frequencies[i]);
    }
    printf("\n");

    while (heapSize > 1) {
        for (int i = (heapSize - 1) / 2; i >= 0; i--) {
            minHeapify(heap, heapSize, i);
        }

        Node* left = heap[0];
        heap[0] = heap[heapSize - 1];
        heapSize--;
        minHeapify(heap, heapSize, 0);

        Node* right = heap[0];
        heap[0] = heap[heapSize - 1];
        heapSize--;
        minHeapify(heap, heapSize, 0);

        Node* newNode = createNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        heap[heapSize] = newNode;
        heapSize++;

        // 중간 결과 출력
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, newNode->frequency);

        // 현재 힙 상태 출력
        for (int i = 0; i < heapSize; i++) {
            printf("%d ", heap[i]->frequency);
        }
        printf("\n");
    }

    return heap[0]; // Root of the Huffman Tree
}

void printCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 1;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 0;
        printCodes(root->right, arr, top + 1);
    }

    if (!root->left && !root->right) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int arr[MAX_SIZE], top = 0; // 배열 크기를 상수로 정의
    printCodes(root, arr, top);
}

int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);

    // 허프만 코드 생성, 출력
    GenerateHuffmanCodes(characters, frequencies, size);

    // 최종 빈도 출력
    int totalFrequency = 0;
    for (int i = 0; i < size; i++) {
        totalFrequency += frequencies[i];
    }
    printf("%d\n", totalFrequency);

    return 0;
}
