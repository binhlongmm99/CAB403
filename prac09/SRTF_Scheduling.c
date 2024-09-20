#include <stdio.h>

int main(int argc, char *argv[])
{
    int n, ari[10], bur[10], total = 0;
    int small, temp, procs[100], k, waiting[10], finish[10];
    float tavg = 0.0, wavg = 0.0;

    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("ENTER THE ARRIVAL TIME OF PROCESS %d: ", i + 1);
        scanf("%d", &ari[i]);

        printf("ENTER THE BURST TIME OF PROCESS %d: ", i);
        scanf("%d", &bur[i]);
        waiting[i] = 0;
        total += bur[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (ari[i] > ari[j])
            {
                temp = ari[i];
                ari[i] = ari[j];
                ari[j] = temp;

                temp = bur[i];
                bur[i] = bur[j];
                bur[j] = temp;
            }
        }
    }

    for (int i = 0; i < total; i++)
    {
        small = 3200;
        for (int j = 0; j < n; j++)
        {
            if ((bur[j] != 0) && (ari[j] <= i) && (bur[j] < small))
            {
                small = bur[j];
                k = j;
            }
        }
        bur[k]--;
        procs[i] = k;
    }
    k = 0;
    for (int i = 0; i < total; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (procs[i] == j)
            {
                finish[j] = i;
                waiting[j]++;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nPROCESS %d:-FINISH TIME==> %d  TURNAROUND TIME==>%d  WAITING TIME==>%d\n", i + 1, finish[i] + 1, (finish[i] - ari[i]) + 1, (((finish[i] + 1) - waiting[i]) - ari[i]));
        wavg = wavg + (((finish[i] + 1) - waiting[i]) - ari[i]);
        tavg = tavg + ((finish[i] - ari[i]) + 1);
    }
    printf("\n Average Waiting Time==>\t%.2f\n Average Turnaround Time==>\t%.2f\n", (wavg / n), (tavg / n));
    return 0;
}
