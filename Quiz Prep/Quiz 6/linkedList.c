#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int value;
    struct node* next;
} node_t;

void printList(node_t *head) {
    node_t *current = head;

    while (current != NULL)
    {
        printf("%d - \n", current->value);
        current = current->next;
    }
    printf("\n");
    
} 

node_t *create_new_node(int value) {
    node_t *result = malloc(sizeof(node_t));
    result->value = value;
    result->next = NULL;
    return result;
}
int main(void) {

    node_t *head = NULL;

    for (int i = 0; i < 25; i++) {
        node_t *tmp = create_new_node(i);
        tmp->next = head;
        head = tmp;
    }

    printList(head);

    return 0;
}
