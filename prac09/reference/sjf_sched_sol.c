/* Program:  sjf_sched_sol.c
 * Purpose:  using linked list queues for Round-Robin Scheduling
 *=========================================================*/

#include <stdlib.h>
#include <stdio.h>

struct process
{
    char data;
    int burst;
    struct process *next;
};

typedef struct process node;

node *head = NULL; /* ready queue's head */
node *tail = NULL; /* ready queue's tail */

node *fhead = NULL; /* SJF scheduling queue's head */
node *ftail = NULL; /* SJF scheduling queue's tail */

void print_list(node *);

int sjf(node *p); /* the shortest job first scheduling algorithm */

/*insert function for the ready queue */
void r_insq(node *new)
{
    if (tail == NULL) /* empty list */
        head = new;
    else
        tail->next = new;
    tail = new;
}

void f_insq(node *new)
{
    if (ftail == NULL) /* empty list */
        fhead = new;
    else
        ftail->next = new;
    ftail = new;
}

int main()
{
    node *p;
    int i;

    /* initializing the ready queue for SJF */
    for (i = 1; i <= 6; i++)
    {
        p = (node *)malloc(sizeof(node));
        p->data = 64 + i;
        p->burst = (int)((double)(99) * rand() / (999999999 + 1.0));
        p->next = NULL;
        r_insq(p);
    }

    printf("The ready queue for the SJF scheduling is: \n\n");
    print_list(head);
    printf("\n\n");

    /* FJF scheduling */
    sjf(head);
    printf("The resulting SJF schedule is: \n\n");
    print_list(fhead);
    printf("\n\n");

    return 0;
}

int sjf(node *p)
{
    node *p1 = p, *p2 = p, *q1 = p, *q2 = p;

    if (p == NULL) /* just return if the ready queue is empty*/
        return (0);
    else
    {
        if (p->next == NULL) /* only one node in the ready queue*/
        {
            f_insq(p);
            return (1);
        }
        else
        {
            while (q2 != NULL)
            { /* find the shortest job*/
                if (q2->burst < p2->burst)
                {
                    p1 = q1;
                    p2 = q2;
                }
                q1 = q2;
                q2 = q2->next;
            }

            /* delete the shortest job in the ready queue */
            if (p1 == p2)
            {
                head = p2->next;
                p2->next = NULL;
            }
            else
            {
                p1->next = p2->next;
                p2->next = NULL;
            }

            f_insq(p2);
            sjf(head); /* Recursive call*/
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
        while (p->next)
        {
            printf("(%c, %d) --> ", p->data, p->burst);
            p = p->next;
        }
        printf("(%c, %d) ^\n ", p->data, p->burst);
    }
}
