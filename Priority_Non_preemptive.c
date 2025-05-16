#include <stdio.h>
#include <stdbool.h>
#define MAX 100

int main() {
    int n;
    int arrival_time[MAX], burst_time[MAX], priority[MAX];
    int start_time[MAX], end_time[MAX], sequence[MAX];
    int waiting_time[MAX], turnaround_time[MAX];
    bool completed[MAX] = {false};

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arrival_time[i]);
    }

    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
    }

    printf("Enter priorities (lower number = higher priority):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &priority[i]);
    }

    int current_time = 0, completed_processes = 0;

    while (completed_processes < n) {
        int idx = -1, min_priority = 1e9;

        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && !completed[i]) {
                if (priority[i] < min_priority) {
                    min_priority = priority[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            for (int i = 0; i < n; i++) {
                if (!completed[i]) {
                    idx = i;
                    current_time = arrival_time[i];
                    break;
                }
            }
        }

        start_time[idx] = current_time;
        end_time[idx] = start_time[idx] + burst_time[idx];
        current_time = end_time[idx];
        completed[idx] = true;
        sequence[completed_processes] = idx;
        completed_processes++;
    }

    float total_wt = 0, total_tat = 0;

    printf("\nProcess Execution Order:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d", sequence[i] + 1);
        if (i < n - 1) printf(" -> ");
    }

    printf("\n\nWaiting Time for each process:\n");
    for (int i = 0; i < n; i++) {
        waiting_time[i] = start_time[i] - arrival_time[i];
        printf("P%d: %d\n", i + 1, waiting_time[i]);
        total_wt += waiting_time[i];
    }

    printf("\nTurnaround Time for each process:\n");
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = end_time[i] - arrival_time[i];
        printf("P%d: %d\n", i + 1, turnaround_time[i]);
        total_tat += turnaround_time[i];
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    // Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < n; i++) {
        printf("|  P%d  ", sequence[i] + 1);
    }
    printf("|\n");

    printf("%d", start_time[sequence[0]]);
    for (int i = 0; i < n; i++) {
        printf("     %d", end_time[sequence[i]]);
    }
    printf("\n");

    return 0;
}

