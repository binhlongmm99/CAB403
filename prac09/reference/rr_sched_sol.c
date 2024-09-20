/* Program:  rr_sched.c
 * Purpose:  using linked list queues for Round-Robin Scheduling
 *=========================================================*/

#include <stdlib.h>
#include <stdio.h>

typedef struct process {
    char processID;
    int burst;
    struct process *next;
} node;


node *head = NULL; /* ready queue's head */
node *tail = NULL; /* ready queue's tail */

node *dhead = NULL; /* dispatcher RR scheduling queue's head */
node *dtail = NULL; /* dispatcher RR scheduling queue's tail */

void print_list(node *);

/*insert function for the ready queue */
void insertNodeJobQueue(node *new) {
    if (tail == NULL)  {/* empty list */
        head = new;
	}  else {
        tail->next = new;
	}
    tail = new;
}

/* Function returns the current 1st process in the ready queue
 * and resets the head to the next process in the ready queue */
node *r_delq() {
    node *tmp;
    if (head == NULL)  {/* list empty */
        return (NULL);
	}

    tmp = head;
    if (head == tail)  {/* only one element in the list */
        head = tail = NULL;
    } else {
        head = head->next;
	}
    return (tmp);
}

/* insert function for the scheduling queue*/

void d_insq(node *new) {
    if (dtail == NULL)  {/* empty list */
        dhead = new;
    } else {
        dtail->next = new;
	}
    dtail = new;
}

int main() {
    node *p, *p1, *p2;
    int i;
    int q=20; // time quantum

    /* initializing the ready queue for RR */
    for (i = 1; i <= 5; i++)   {
        p = malloc(sizeof(node));
        p->processID = 64 + i;
        p->burst = (int)((double)(99) * rand() / (999999999 + 1.0));
        p->next = NULL;
        insertNodeJobQueue(p);
    }

    printf("The ready queue for the RR scheduling is: \n\n");
    print_list(head);
    printf("\n\n");

    /* the RR scheduling algorithm, insert your solution here for task1 */
    
    /* Create a loop until the ready queue is empty */
    while (head != NULL) {
		p = r_delq();
		if (p->burst <= q) {
			d_insq(p);
		} else {
			p1 = malloc(sizeof(node));
			p1->processID = p->processID;
			p1->burst = p->burst-q;
			p1->next = NULL;
			insertNodeJobQueue(p1);
			
			p2= malloc(sizeof(node));
			p2->processID = p->processID;
			p2->burst = q;
			p2->next = NULL;
			d_insq(p2);
		}
	}		
    
    printf("The resulting RR schedule is: \n\n");
    print_list(dhead);
    printf("\n\n");

    return 0;
}

void print_list(node *p) {
    if (p == NULL) {
        printf("^\n");
    } else {
        while (p->next)  {
            printf("(%c, %d) --> ", p->processID, p->burst);
            p = p->next;
        }
        printf("(%c, %d) ^\n ", p->processID, p->burst);
    }
}
