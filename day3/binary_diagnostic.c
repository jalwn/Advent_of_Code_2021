// diagnostic report is puzzle input
// diagnostic report is encoded
// goal of the puzzle is to decode the report and find the POWER_CONSUMPTION
// POWER_CONSUMPTION = GAMMA_RATE * EPSILON_RATE
// GAMMA_RATE = most common bit
// EPSILON_RATE = least common bit

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int on_bits[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int no_of_lines = 0;

void binary_to_deci(int *gamma_array, int *epsilon_array)
{
    int gamma = 0;
    int epsilon = 0;
    int weight = 11;
    for (int i = 0; i < 12; i++)
    {
        gamma += ( gamma_array[i] * pow( 2, (double)weight) );
        epsilon += ( epsilon_array[i] * pow( 2, (double)weight) );
        weight--;
    }
    printf("power_consumption = %d\n", (gamma * epsilon));
}

void get_power_consumption_rate(int *array) {
    int gamma_rate_array[12];
    int epsilon_rate_array[12];
    for (int i = 0; i < 12; i++)
    {
        if (array[i] > (no_of_lines/2))
        {
            gamma_rate_array[i] = 1;
            epsilon_rate_array[i] = 0;
        }
        else 
        {
            gamma_rate_array[i] = 0;
            epsilon_rate_array[i] = 1;
        }
        printf("%d: %d\n", i, (array[i]));
    }
    binary_to_deci(&gamma_rate_array[0], &epsilon_rate_array[0]);
}

int main()
{
    FILE *input_file = fopen("input", "r");

    if (input_file == NULL)
    {
        return EXIT_FAILURE;
    }
    int count = 0;
    char c;
    while ((c = fgetc(input_file)) != EOF)
    {
        if (c == '\n')
        {
            no_of_lines++;
            count = 0;
            continue;
        }
        if ((c - '0') == 1)
        {
            on_bits[count] += (c - '0');
        }
        count++;
    }

    printf("no of lines = %d\n", no_of_lines);
    get_power_consumption_rate(&on_bits[0]);
    fclose(input_file);
    return EXIT_SUCCESS;
}