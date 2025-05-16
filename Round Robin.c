#include <stdio.h>

#define MAX 100

int main() {
    int n, quantum;
    int burst_time[MAX], original_bt[MAX], waiting_time[MAX] = {0}, turnaround_time[MAX];
    int completed[MAX] = {0};
    int total_time = 0;
    int start_time[MAX] = {0};
    int sequence[MAX * 10]; // To store execution sequence
    int seq_index = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    printf("Enter burst times separated by space:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
        original_bt[i] = burst_time[i]; // Save original burst times
    }

    while (1) {
        int all_done = 1;

        for (int i = 0; i < n; i++) {
            if (burst_time[i] > 0) {
                all_done = 0;

                // Record execution sequence
                sequence[seq_index++] = i + 1;

                if (burst_time[i] > quantum) {
                    if (start_time[i] == 0 && i != 0)
                        waiting_time[i] += (total_time - start_time[i]);
                    else if (start_time[i] != 0)
                        waiting_time[i] += (total_time - start_time[i] - quantum);

                    burst_time[i] -= quantum;
                    start_time[i] = total_time;
                    total_time += quantum;
                } else {
                    if (start_time[i] == 0 && i != 0)
                        waiting_time[i] += (total_time - start_time[i]);
                    else if (start_time[i] != 0)
                        waiting_time[i] += (total_time - start_time[i] - quantum);

                    total_time += burst_time[i];
                    burst_time[i] = 0;
                    completed[i] = 1;
                    turnaround_time[i] = total_time;
                }
            }
        }

        if (all_done)
            break;
    }

    printf("\nSequence of execution:\n");
    for (int i = 0; i < seq_index; i++) {
        printf("P%d", sequence[i]);
        if (i != seq_index - 1) printf(" -> ");
    }

    printf("\n\nWaiting Time for each process:\n");
    for (int i = 0; i < n; i++)
        printf("P%d: %d\n", i + 1, waiting_time[i]);

    printf("\nTurnaround Time for each process:\n");
    for (int i = 0; i < n; i++)
        printf("P%d: %d\n", i + 1, turnaround_time[i]);

    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += waiting_time[i];
        avg_tat += turnaround_time[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    return 0;
}

