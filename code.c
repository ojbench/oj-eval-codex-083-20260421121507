#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }
    if (n <= 0 || m <= 0) {
        return 0;
    }

    // Build single circular linked list with values 1..n
    Node *head = NULL, *tail = NULL;
    for (int i = 1; i <= n; ++i) {
        Node *node = (Node *)malloc(sizeof(Node));
        if (!node) return 0; // allocation failed, exit quietly
        node->val = i;
        node->next = NULL;
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    // Make it circular
    tail->next = head;

    // Use prev pointer initialized to tail (so prev->next is current start)
    Node *prev = tail;
    int size = n;
    while (size > 0) {
        int steps = (m - 1) % size; // advance prev by steps
        for (int i = 0; i < steps; ++i) {
            prev = prev->next;
        }
        Node *target = prev->next;
        printf("%d\n", target->val);
        if (size == 1) {
            // last node
            free(target);
            prev = NULL;
            head = tail = NULL;
        } else {
            prev->next = target->next;
            if (target == head) head = target->next;
            if (target == tail) tail = prev;
            free(target);
        }
        --size;
    }

    return 0;
}

