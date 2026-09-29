#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
int id;
int at;
int bt1;
int bt2;
int total_bt;
int ct;
int tat;
int wt;
int completed;
} Process;
int main() {
int n, i, completed_count = 0, current_time = 0;
float total_wt = 0, total_tat = 0;
srand(time(NULL));
printf("Enter number of processes: ");
if(scanf("%d", &n) != 1) return 0;
Process p[20];
for(i = 0; i < n; i++) {
p[i].id = i + 1;
printf("Process P%d - Arrival Time: ", i + 1);
scanf("%d", &p[i].at);
printf("Process P%d - First CPU Burst: ", i + 1);
scanf("%d", &p[i].bt1);
p[i].bt2 = (rand() % 10) + 1;
p[i].total_bt = p[i].bt1 + p[i].bt2;
p[i].completed = 0;
printf("Process P%d - Next CPU Burst (random): %d (Total Burst: %d)\n", i + 1, p[i].bt2, p[i].total_bt);
}
int gantt_p[100], gantt_t[100], g_cnt = 0;
gantt_t[0] = 0;
while(completed_count < n) {
int idx = -1, min_bt = 1e9;
for(i = 0; i < n; i++) {
if(p[i].at <= current_time && !p[i].completed) {
if(p[i].total_bt < min_bt) {
min_bt = p[i].total_bt;
idx = i;
}
}
}
if(idx == -1) {
current_time++;
continue;
}
current_time += p[idx].total_bt;
p[idx].ct = current_time;
p[idx].tat = p[idx].ct - p[idx].at;
p[idx].wt = p[idx].tat - p[idx].total_bt;
total_tat += p[idx].tat;
total_wt += p[idx].wt;
p[idx].completed = 1;
completed_count++;
gantt_p[g_cnt] = p[idx].id;
gantt_t[g_cnt + 1] = current_time;
g_cnt++;
}
printf("\nGantt Chart:\n|");
for(i = 0; i < g_cnt; i++) printf(" P%d |", gantt_p[i]);
printf("\n%d", gantt_t[0]);
for(i = 0; i < g_cnt; i++) printf("    %d", gantt_t[i + 1]);
printf("\n\nProcess\tAT\tBT1\tBT2\tTotal BT\tCT\tTAT\tWT\n");
for(i = 0; i < n; i++) {
printf("P%d\t%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt1, p[i].bt2, p[i].total_bt, p[i].ct, p[i].tat, p[i].wt);
}
printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
printf("Average Waiting Time = %.2f\n", total_wt / n);
return 0;
}
