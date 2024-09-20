/* Program:  sjf_sched_sol.c
 * Purpose:  using linked list queues for Round-Robin Scheduling
 *=========================================================*/

#include <stdlib.h>
#include <stdio.h>

typedef struct process
{
    char processID;
    int burstTime;
    struct process *nextNode;
} node;

node *jobQueueHead = NULL; /* ready queue's head */
node *jobQueueTail = NULL; /* ready queue's tail */

node *readyQueueHead = NULL; /* SJF scheduling queue's head */
node *readyQueueTail = NULL; /* SJF scheduling queue's tail */

void print_list(node *);

int sjf(node *p); /* the shortest job first scheduling algorithm */

/*insert function for the ready queue */
void insertNodeJobQueue(node *new)
{
    if (jobQueueTail == NULL) /* empty list */
        jobQueueHead = new;
    else
        jobQueueTail->nextNode = new;
    jobQueueTail = new;
}

void insertNodeToReadyQueue(node *new)
{
    if (readyQueueTail == NULL) /* empty list */
        readyQueueHead = new;
    else
        readyQueueTail->nextNode = new;
    readyQueueTail = new;
}

int main()
{
    node *p;

    /* initializing the ready queue for SJF */
    for (int i = 1; i <= 6; i++)
    {
        p = (node *)malloc(sizeof(node));
        p->processID = 64 + i;
        p->burstTime = (int)((double)(99) * rand() / (999999999 + 1.0));
        p->nextNode = NULL;
        insertNodeJobQueue(p);
    }

    printf("The ready queue for the SJF scheduling is: \n\n");
    print_list(jobQueueHead);
    printf("\n\n");

    /* FJF scheduling */
    sjf(jobQueueHead);
    printf("The resulting SJF schedule is: \n\n");
    print_list(readyQueueHead);
    printf("\n\n");

    return 0;
}

int sjf(node *p)
{
    node *p1 = p, *p2 = p; // p to store the shortest job
    node *q1 = p, *q2 = p; // q to traverse the list

    if (p == NULL) /* just return if the ready queue is empty*/
        return 0;
    else
    {
        if (p->nextNode == NULL) /* only one node in the ready queue*/
        {
            insertNodeToReadyQueue(p);
            return 1;
        }
        else
        {
            while (q2 != NULL)
            { /* find the shortest job*/
                if (q2->burstTime < p2->burstTime)
                {
                    p1 = q1;
                    p2 = q2;
                }
                q1 = q2;
                q2 = q2->nextNode;
            }

            /* remove the shortest job in the ready queue */
            if (p1 == p2)
            /*  the shortest job is the first node */
            {
                jobQueueHead = p2->nextNode;
                p2->nextNode = NULL;
            }
            else
            {
                /*  the shortest job is in the middle/end of the list */
                p1->nextNode = p2->nextNode;
                p2->nextNode = NULL;
            }

            insertNodeToReadyQueue(p2);
            sjf(jobQueueHead); /* Recursive call*/
        }
    }

    return 0;
}

void print_list(node *p)
{
    if (p == NULL)
        printf("^\n");
    else
    {
        while (p->nextNode)
        {
            printf("(%c, %d) --> ", p->processID, p->burstTime);
            p = p->nextNode;
        }
        printf("(%c, %d) ^\n ", p->processID, p->burstTime);
    }
}
