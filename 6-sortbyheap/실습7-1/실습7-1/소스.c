#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    char character;
    int frequency;
    struct Node* left;
    struct Node* right;
} Node;

// 최소 힙을 위한 구조체
typedef struct MinHeapNode {
    Node* data;
    int index;
} MinHeapNode;

// 최소 힙을 위한 함수들
void swapMinHeapNode(MinHeapNode* a, MinHeapNode* b) {
    MinHeapNode t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeapNode* harr, int i, int n) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && harr[l].data->frequency < harr[smallest].data->frequency)
        smallest = l;

    if (r < n && harr[r].data->frequency < harr[smallest].data->frequency)
        smallest = r;

    if (smallest != i) {
        swapMinHeapNode(&harr[i], &harr[smallest]);
        minHeapify(harr, smallest, n);
    }
}

void buildMinHeap(MinHeapNode* harr, int n) {
    int i;
    for (i = (n - 1) / 2; i >= 0; i--)
        minHeapify(harr, i, n);
}

// 최소 힙에서 루트 노드를 추출하는 함수
MinHeapNode extractMin(MinHeapNode harr[], int* n) {
    MinHeapNode root = harr[0];
    harr[0] = harr[*n - 1];
    (*n)--;
    minHeapify(harr, 0, *n);
    return root;
}

// 새로운 노드를 생성하는 함수
Node* newNode(char character, int frequency) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

// 허프만 트리를 생성하는 함수
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    // 최소 힙 생성 및 초기화
    MinHeapNode* heap = (MinHeapNode*)malloc(size * sizeof(MinHeapNode));
    for (int i = 0; i < size; ++i) {
        heap[i].data = newNode(characters[i], frequencies[i]);
        heap[i].index = i;
    }
    buildMinHeap(heap, size);

    // 트리 생성
    int n = size;
    while (n != 1) {
        MinHeapNode left = extractMin(heap, &n);
        MinHeapNode right = extractMin(heap, &n);

        Node* node = newNode('$', left.data->frequency + right.data->frequency);
        node->left = left.data;
        node->right = right.data;

        heap[n - 1].data = node;
        heap[n - 1].index = n - 1;
        minHeapify(heap, n - 1, n);
        n++;
    }

    return heap[0].data;
}

// 허프만 코드 출력을 위한 재귀 함수
void printCodes(Node* root, int arr[], int top) {
    if (root == NULL) {
        return;
    }

    if (!root->left && !root->right) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; ++i) {
            printf("%d", arr[i]);
        }
        printf("\n");
        return;
    }

    arr[top] = 0;
    printCodes(root->left, arr, top + 1);

    arr[top] = 1;
    printCodes(root->right, arr, top + 1);
}

// 허프만 코드 생성 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int arr[100];
    printCodes(root, arr, 0);
}

int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);

    GenerateHuffmanCodes(characters, frequencies, size);

    return 0;
}