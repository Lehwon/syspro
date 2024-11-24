#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (!new_node) {
        printf("Failed to allocate memory.\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = *top;
    *top = new_node;
}

int pop(struct node **top) {
    if (*top == NULL) {
        return -1;
    }
    struct node *temp = *top;
    int data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

void print_stack(struct node *top) {
    struct node *current = top;
    printf("Print stack\n");
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    struct node *top = NULL;
    int num;

    while (1) {
        if (scanf("%d", &num) != 1 || num <= 0) {
            print_stack(top);
            break;
        }
        push(&top, num);
    }

    while (top != NULL) {
        pop(&top);
    }

    return 0;
}

