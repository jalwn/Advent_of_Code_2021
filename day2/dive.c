#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

// ACTIONS
// forward - effects horizontal pos
// up - dec depth
// down - inc depth

// RESULT / CONSEQUENCE
// horizontal pos
// depth

#define FORWARD "forward"
#define UP "up"
#define DOWN "down"

int horizontal_pos = 0;
int depth = 0;

void calc_pos(char *action, char *value, int string_count)
{
    action[string_count] = '\0';
    if (strcmp(FORWARD, action) == 0)
    {
        horizontal_pos += atoi(value);
    }
    if (strcmp(UP, action) == 0)
    {
        depth += (atoi(value)) * -1;
    }
    if (strcmp(DOWN, action) == 0)
    {
        depth += atoi(value);
    }
}

void read_file(FILE *input_file)
{
    char action[10];
    char value[10];
    char c;
    bool is_value = false;
    int count = 0;
    int string_count = 0;
    while ((c = fgetc(input_file)) != EOF)
    {
        if (c == '\n')
        {
            count = 0;
            printf("read() - %s: %s\n", action, value);
            calc_pos(action, value, string_count);
            value[count] = '\0';
            action[count] = '\0';
            is_value = !is_value;
            string_count = 0;
            continue;
        }
        if (isspace(c))
        {
            is_value = !is_value;
            count = 0;
            continue;
        }

        if (is_value)
        {
            value[count] = c;
        }
        else
        {
            action[count] = c;
            string_count++;
        }
        count++;
    }
    printf("depth : %d\n", depth);
    printf("horizontal_pos : %d\n", horizontal_pos);
    printf("ans %d\n", (horizontal_pos * depth));
}

int main()
{
    FILE *input_file;
    input_file = fopen("input", "r");

    if (input_file == NULL)
    {
        printf("Error: Unable to open file\n");
        return EXIT_FAILURE;
    }

    read_file(input_file);

    fclose(input_file);
}