#include <stdio.h>
#include <stdlib.h>

typedef struct node_t
{
    int value;
    struct node_t *next;
} node_t;

node_t *insert_to_list(node_t *head, int x)
{
    node_t *temp = malloc(sizeof(node_t));
    temp->value = x;
    temp->next = head;
    head = temp;
    return head;
}

void free_list(node_t *head)
{
    node_t *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void store_file_values(node_t **p_head, FILE *file_to_read)
{
    char buffer[10];
    int index = 0;
    int x;
    rewind(file_to_read);
    while ((buffer[index] = fgetc(file_to_read)) != EOF)
    {
        if (buffer[index] == '\n')
        {
            index = 0;
            x = atoi(buffer);
            *(p_head) = insert_to_list(*(p_head), x);
            continue;
        }
        if (index > 9)
        {
            index = 0;
            continue;
        }
        index++;
    }
}

void print_list(node_t *head)
{
    node_t *temp;
    int counter = 0;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        printf("value of %d = %d\n", counter, temp->value);
        counter++;
    }
}

void reverse_list(node_t **head) {
    node_t *current, *next, *prev;
    current = *(head);
    prev = NULL;
    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *(head) = prev;
}

void print_answer(node_t *current) {
    node_t *prev;
    prev = NULL;
    unsigned int count = 0;
    while (current != NULL) {
        if (prev != NULL){
            if (current->value > prev->value)
                count++;
        }
        prev = current;
        current = current->next;
    }
    printf("answer = %d\n", count);
    
}

int main()
{
    FILE *file_to_read = fopen("input_1", "r");

    if (file_to_read == NULL)
    {
        printf("FILE WOULD NOT OPEN");
        return EXIT_FAILURE;
    }

    node_t *head = NULL;

    store_file_values(&head, file_to_read);
    reverse_list(&head);

    print_list(head);

    print_answer(head);

    free_list(head);
    fclose(file_to_read);

    return 0;
}