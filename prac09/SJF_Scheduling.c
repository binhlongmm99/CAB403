#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef struct process
{
    int process_id;
    int burst_time;
} process_t;

void swap(process_t *a, process_t *b);
void bubbleSort(process_t *arr, int n);
void printProcessExecutionOrder(process_t *processList, int processNumber);
void calculateAverageWaitTime(process_t *processList, int processNumber);

/*
 * Function to get numeric input from the user
 * \param process - an element of struct process_t
 */
void getInput(process_t *process)
{
    printf("Enter Process ID: ");
    scanf("%d", &process->process_id);
    printf("Enter Burst Time: ");
    scanf("%d", &process->burst_time);
}

int main(int argc, char *argv[])
{
    int processNumber;

    printf("Enter the number of processes: ");
    scanf("%d", &processNumber);

    process_t *processes = malloc(sizeof(process_t) * processNumber);
    for (int i = 0; i < processNumber; i++)
    {
        printf("\nGet process %d\n", i);
        getInput(&processes[i]);
    }

    bubbleSort(processes, processNumber);
    printProcessExecutionOrder(processes, processNumber);
    calculateAverageWaitTime(processes, processNumber);
    return 0;
}

void swap(process_t *a, process_t *b) {
    process_t temp = *a;
    *a = *b;
    *b = temp;
}

// An optimized version of Bubble Sort
void bubbleSort(process_t *arr, int n)
{
    bool swapped;
    for (int i = 0; i < n - 1; i++)
    {

        // swapped variable to signal if there is a
        // swap happened in the inner loop
        // initially set to false
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].burst_time > arr[j + 1].burst_time)
            {
                swap(&arr[j], &arr[j + 1]);

                // swapped is set to true if the swap is done
                swapped = true;
            }
        }
        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
}

/*
 * Function to calculate the average wait time based
 * on the process execution order
 * \param processList - array of structs where each index representing a single process
 * \param processNumber - Number of processes in the queue
 */
void calculateAverageWaitTime(process_t *processList, int processNumber)
{
    float totalWaitTime = 0;

    // Calculating total waiting time
    for (int i = 1; i < processNumber; i++)
    {
        float waitTime = 0;
        for (int j = 0; j < i; j++)
        {
            waitTime += processList[j].burst_time;
        }
        totalWaitTime += waitTime;
    }

    // Calculating average waiting time
    float averageWaitTime = totalWaitTime / processNumber;
    printf("\nThe average waiting time: %.2f ms\n", averageWaitTime);
}

/*
 * Helper function to print out the process execution order
 * \param processList - struct representing a process
 * \param processNumber - Number of processes in the queue
 */
void printProcessExecutionOrder(process_t *processList, int processNumber)
{
    printf("\n\nThe Order Of Process Execution\n==========================\n");
    for (int i = 0; i < processNumber; i++)
    {
        printf("Process %d (%d ms) --> ", processList[i].process_id, processList[i].burst_time);
    }
    printf("Process Execution Completed\n============================\n");
}
