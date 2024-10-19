#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
typedef struct Node {
    char character;
    int frequency;
    struct Node* left;
    struct Node* right;
} Node;

// �ּ� ���� ���� ����ü
typedef struct MinHeapNode {
    Node* data;
    int index;
} MinHeapNode;

// �ּ� ���� ���� �Լ���
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

// �ּ� ������ ��Ʈ ��带 �����ϴ� �Լ�
MinHeapNode extractMin(MinHeapNode harr[], int* n) {
    MinHeapNode root = harr[0];
    harr[0] = harr[*n - 1];
    (*n)--;
    minHeapify(harr, 0, *n);
    return root;
}

// ���ο� ��带 �����ϴ� �Լ�
Node* newNode(char character, int frequency) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

// ������ Ʈ���� �����ϴ� �Լ�
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    // �ּ� �� ���� �� �ʱ�ȭ
    MinHeapNode* heap = (MinHeapNode*)malloc(size * sizeof(MinHeapNode));
    for (int i = 0; i < size; ++i) {
        heap[i].data = newNode(characters[i], frequencies[i]);
        heap[i].index = i;
    }
    buildMinHeap(heap, size);

    // Ʈ�� ����
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

// ������ �ڵ� ����� ���� ��� �Լ�
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

// ������ �ڵ� ���� �Լ�
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