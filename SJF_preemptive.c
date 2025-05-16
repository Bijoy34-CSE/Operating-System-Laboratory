#include <stdio.h>
#include <stdbool.h>

#define MAX 100
#define INF 100000

typedef struct {
    int process_id;
    int start_time;
    int end_time;
} GanttEntry;

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival_time[MAX], burst_time[MAX], remaining_time[MAX];
    int start_time[MAX], end_time[MAX], waiting_time[MAX], turnaround_time[MAX];
    bool completed[MAX] = {false};
    GanttEntry gantt[MAX];
    int gantt_size = 0;

    printf("Enter arrival time for each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arrival_time[i]);
    }

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];
        start_time[i] = -1;
    }

    int current_time = 0, completed_processes = 0, prev_process = -1;

    while (completed_processes < n) {
        int idx = -1;
        int min_bt = INF;

        // Select process with shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && !completed[i] && remaining_time[i] < min_bt) {
                min_bt = remaining_time[i];
                idx = i;
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        // New process or preemption detected
        if (prev_process != idx) {
            if (gantt_size > 0) {
                gantt[gantt_size - 1].end_time = current_time;
            }
            gantt[gantt_size].process_id = idx;
            gantt[gantt_size].start_time = current_time;
            gantt_size++;
        }

        if (start_time[idx] == -1)
            start_time[idx] = current_time;

        remaining_time[idx]--;
        current_time++;
        prev_process = idx;

        if (remaining_time[idx] == 0) {
            completed[idx] = true;
            completed_processes++;
            end_time[idx] = current_time;
        }
    }

    // Final Gantt entry end time
    gantt[gantt_size - 1].end_time = current_time;

    float total_wt = 0, total_tat = 0;

    printf("\nProcess Execution Order:\n");
    for (int i = 0; i < gantt_size; i++) {
        printf("P%d", gantt[i].process_id + 1);
        if (i < gantt_size - 1) printf(" -> ");
    }

    printf("\n\nWaiting Time for each process:\n");
    for (int i = 0; i < n; i++) {
        waiting_time[i] = end_time[i] - arrival_time[i] - burst_time[i];
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

    // Print Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < gantt_size; i++) {
        printf("|  P%d  ", gantt[i].process_id + 1);
    }
    printf("|\n");

    printf("%d", gantt[0].start_time);
    for (int i = 0; i < gantt_size; i++) {
        printf("     %d", gantt[i].end_time);
    }
    printf("\n");

    return 0;
}
