#include <stdio.h>

#define MAX 100

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival[MAX], burst[MAX], priority[MAX];
    int remaining[MAX], start[MAX], completion[MAX];
    int waiting[MAX], turnaround[MAX];
    int gantt_process[MAX * 10], gantt_time[MAX * 10];
    int i, time = 0, completed = 0, g_index = 0;

    printf("Enter arrival times:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arrival[i]);
    }

    printf("Enter burst times:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];
        start[i] = -1;
    }

    printf("Enter priorities (lower number = higher priority):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &priority[i]);
    }

    gantt_time[0] = 0;

    while (completed < n) {
        int idx = -1;
        int min_pri = 999999;

        for (i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0 && priority[i] < min_pri) {
                min_pri = priority[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        if (start[idx] == -1)
            start[idx] = time;

        if (g_index == 0 || gantt_process[g_index - 1] != idx) {
            gantt_process[g_index] = idx;
            gantt_time[g_index + 1] = time;
            g_index++;
        }

        remaining[idx]--;
        time++;

        if (remaining[idx] == 0) {
            completion[idx] = time;
            turnaround[idx] = completion[idx] - arrival[idx];
            waiting[idx] = turnaround[idx] - burst[idx];
            completed++;
        }
    }

    gantt_time[g_index + 1] = time;

    // Output
    printf("\nProcess Execution Order:\n");
    for (i = 0; i < g_index; i++) {
        printf("P%d -> ", gantt_process[i] + 1);
    }
    printf("END\n");

    float avg_wt = 0, avg_tat = 0;

    printf("\nWaiting Time:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: %d\n", i + 1, waiting[i]);
        avg_wt += waiting[i];
    }

    printf("\nTurnaround Time:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: %d\n", i + 1, turnaround[i]);
        avg_tat += turnaround[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    printf("\nGantt Chart:\n ");
    for (i = 0; i < g_index; i++) {
        printf("|  P%d  ", gantt_process[i] + 1);
    }
    printf("|\n");

    for (i = 0; i <= g_index; i++) {
        printf("%d\t", gantt_time[i]);
    }
    printf("%d\n", gantt_time[g_index + 1]);

    return 0;
}

