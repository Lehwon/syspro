#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Failed to allocate memory.\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        *tail = new_node;
    }
    else {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        printf("Queue is empty.\n");
        exit(1);
    }
    struct node *temp = *head;
    int data = temp->data;
    *head = (*head)->next;
    if (*head == NULL) {
        *tail = NULL;
    }
    free(temp);
    return data;
}

void printQueue(struct node *head) {
    struct node *current = head;
    printf("Print stack\n");
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
    int input;

    while (1) {
        if (scanf("%d", &input) != 1) {
            printQueue(head);
            break;
        }
        if (input <= 0) {
            printQueue(head);
            break;
        }
        addq(&head, &tail, input);
    }

    return 0;
}

