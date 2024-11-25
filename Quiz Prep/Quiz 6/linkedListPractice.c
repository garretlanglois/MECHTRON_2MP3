#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
} node;

void removeNthElement(node* head, int index) {

    node* currentPosition = head;
    node* previousPosition = NULL;

    for (int i = 0; i < index; i++) {
        if (currentPosition == NULL) {
            printf("Index out of range.\n");
            return;
        }
         previousPosition = currentPosition;
        currentPosition = currentPosition->next;
    }

    previousPosition->next = currentPosition->next;
    free(currentPosition);

}

node* createNewNode(int number) {

    node *newNode = malloc(sizeof(node));
    newNode->value = number;
    newNode->next = NULL;

    return newNode;

}

int main(void) {

    node* head = NULL;

    for(int i = 0; i < 25; i++) {
        node* tmp = createNewNode(i);
        tmp->next = head;
        head = tmp;
    }

    node* currentNode = head;

    for(int i = 0; i < 25; i++) {
        printf("\nThe value at the node is %d\n", currentNode->value);
        currentNode = currentNode->next;
    }

    currentNode = head;

    removeNthElement(head, 5);
    for(int i = 0; i < 24; i++) {
        printf("\nThe value at the node is %d\n", currentNode->value);
        currentNode = currentNode->next;
    }

}