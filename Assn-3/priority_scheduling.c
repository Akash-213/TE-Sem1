#include <stdio.h>
#include <stdbool.h>

struct Process{
    int pid, arrival_time, burst_time, turn_around_time, waiting_time, completion_time, remaining_time, priority, queue_time;
    bool is_completed;
};

void priority_scheduling(struct Process p[], int size)
{
    /*
     *  Input   :   Process array.
     *  Utility :   a) Employ priority scheduling (Pre-emptive) algorithm on Process array for CPU Scheduling simulation.
     *              b) Arrival time and priority taken from user.
     *              c) Higher value considered as higher priority (e.g priority=1 < priority=2)
     *  Output  :   Console output (Description table).
     */
    
    // Sort the processes by their burst time.
    int current_time = 0, completed = 0, index, i, temp;
    while(completed != size)
    {
        temp = 0;
        // Search for element in ready queue with shortest burst time
        for(i = 0; i < size; i++)
        {
            if(!p[i].is_completed && p[i].queue_time <= current_time && p[i].priority > temp)
            {
                temp = p[i].priority;
                index = i;
            }
        }
        p[index].remaining_time -= 1;
        p[index].queue_time = current_time;
        if(p[index].remaining_time == 0)
        {
            printf("\nCompleted Process %d at time %d", p[index].pid, (current_time + 1));
            p[index].is_completed = true;
            p[index].completion_time = current_time + 1;
            p[index].turn_around_time = p[index].completion_time - p[index].arrival_time;
            p[index].waiting_time = p[index].turn_around_time - p[index].burst_time;
            completed += 1;
        }
        current_time += 1;
    }
}


int main()
{
    // Get 5 processes.
    int i;
    float average_waiting_time, average_turnaround_time = 0;
    struct Process process_array[5];
    for(i = 0; i < 5; i++)
    {
        printf("\nProcess : %d ", (i+1));
        printf("\nProcess ID : ");
        scanf("%d", &process_array[i].pid);
        printf("\nArrival Time : ");
        scanf("%d", &process_array[i].arrival_time);
        printf("\nBurst Time : ");
        scanf("%d", &process_array[i].burst_time);
        printf("\n");
        printf("\nPriority : ");
        scanf("%d", &process_array[i].priority);
        printf("\n");
        process_array[i].is_completed = false;
        process_array[i].queue_time = process_array[i].arrival_time;
        process_array[i].remaining_time = process_array[i].burst_time;
    }


    // Call SJF algorithm
    priority_scheduling(process_array, 5);

    printf("\n\nSr.No.\tPID\tAT\tBT\tCT\tTAT\tWT\tPriority");
    // Display table for Process serving sequence
    for(i = 0; i < 5; i++)
    {
        average_waiting_time += process_array[i].waiting_time;
        average_turnaround_time += process_array[i].turn_around_time;
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t", (i+1), process_array[i].pid, process_array[i].arrival_time, process_array[i].burst_time, process_array[i].completion_time, process_array[i].turn_around_time, process_array[i].waiting_time, process_array[i].priority);
    }
    average_waiting_time /= 5;
    average_turnaround_time /= 5;
    printf("\n\nAverage Waiting Time : %fms", average_waiting_time);
    printf("\n\nAverage Turn Around Time : %fms\n", average_turnaround_time);
    printf("\n");
    return (0);
}