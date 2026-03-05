#include <stdio.h>
#include <string.h>
#include <limits.h>

struct Process {
    char pid[10];
    int at;   
    int bt;  
    int rt;   
    int wt;   
    int tat;  
};

int main() {
    int n, i, time = 0, completed = 0, min_rt, shortest = -1;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes:\n");
    scanf("%d", &n);

    struct Process p[n];

    for(i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].wt = 0;
        p[i].tat = 0;
    }

    while(completed != n) {
        min_rt = INT_MAX;
        shortest = -1;

        for(i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0 && p[i].rt < min_rt) {
                min_rt = p[i].rt;
                shortest = i;
            }
        }

        if(shortest == -1) {
            time++;
            continue;
        }

        p[shortest].rt--;
        time++;

        if(p[shortest].rt == 0) {
            completed++;

            int finish_time = time;

            p[shortest].tat = finish_time - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;

            if(p[shortest].wt < 0)
                p[shortest].wt = 0;

            total_wt += p[shortest].wt;
            total_tat += p[shortest].tat;
        }
    }

    printf("Waiting Time:\n");
    for(i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].wt);
    }

    printf("Turnaround Time:\n");
    for(i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].tat);
    }

    printf("Average Waiting Time: %.1f\n", total_wt / n);
    printf("Average Turnaround Time: %.1f\n", total_tat / n);

    return 0;
}