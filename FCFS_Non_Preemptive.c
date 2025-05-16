#include <stdio.h>

int main() {
    int n;

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burst_time[n], waiting_time[n], turnaround_time[n];

    // Input burst times
    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    // Calculate waiting times
    waiting_time[0] = 0; // First process has 0 waiting time
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
    }

    // Calculate turnaround times
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + burst_time[i];
    }

    // Calculate averages
    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += waiting_time[i];
        avg_tat += turnaround_time[i];
    }
    avg_wt /= n;
    avg_tat /= n;

    // Print process execution order
    printf("\nProcess Execution Order:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d", i + 1);
        if (i < n - 1)
            printf(" -> ");
    }

    // Print waiting times
    printf("\n\nWaiting Times:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: %d\n", i + 1, waiting_time[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);

    // Print turnaround times
    printf("\nTurnaround Times:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: %d\n", i + 1, turnaround_time[i]);
    }
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    // Print Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < n; i++) {
        printf("|  P%d  ", i + 1);
    }
    printf("|\n");

    int current_time = 0;
    printf("%d", current_time);
    for (int i = 0; i < n; i++) {
        current_time += burst_time[i];
        printf("\t%d", current_time);
    }
    printf("\n");

    return 0;
}
