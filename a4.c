#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define the struct of the node
struct node {
    int value;
    struct node* next;
};

//Define the struct of the linked_list
struct linked_list {
    struct node* head;
};

//Create node
struct node* create_node(int value){
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    
    new_node->value = value;
    new_node->next = NULL;

    return new_node;
}

//Open a new window. Insert new node with value "window" at the head of linked list
void open_window(struct linked_list* list, int window){
    struct node* new_window = create_node(window);
    if(list->head->value == -1){
        new_window->next = NULL;
        list->head = new_window;
    } else {
        new_window->next = list->head;
        list->head = new_window;
    }
}

//Switch window. Bring a target window to the forward.
void switch_window(struct linked_list* list, int target){
    if ((list->head == NULL) || (list->head->value == target)) {
        return;
    }

    struct node* prev = NULL;
    struct node* current = list->head;

    while (current != NULL && current->value != target) {
        prev = current;
        current = current->next;
    }

    if (current != NULL && current->value == target) {
        prev->next = current->next;
        current->next = list->head;
        list->head = current;
    }
}

//Close window. delete target window from linked list and free the node.
void close_window(struct linked_list* list, int target){
    if ((list->head == NULL)) {
        return;
    }

    if(list->head->value == target){
        struct node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return;
    }

    struct node* prev = NULL;
    struct node* current = list->head;

    while (current != NULL && current->value != target) {
        prev = current;
        current = current->next;
    }

    if (current != NULL && current->value == target) {
        prev->next = current->next;
        free(current);
    }
}

//Free Linked List
void free_linked_list(struct linked_list* list) {
    struct node* current = list->head;
    struct node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
}

int main() {
    struct node* dummy_head = create_node(-1);
    struct linked_list* list = (struct linked_list*) malloc(sizeof(struct linked_list));
    list->head = dummy_head;

    char operation[7];
    int window;

    while(list->head != NULL){
        scanf("%6s %d", operation, &window);
        if(!strcmp(operation, "open")){
            open_window(list, window);
        } else if (!strcmp(operation, "switch")) {
            switch_window(list, window);
        } else if (!strcmp(operation, "close")) {
            close_window(list, window);
        } else {
            printf("Wrong Input");
            free_linked_list(list);
            break;
        }

        if(list->head != NULL){
            printf("%d\n", list->head->value);
        }
    }

    free(dummy_head);
    free(list);

    return 0;
}
