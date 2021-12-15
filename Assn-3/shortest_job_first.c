#include <stdio.h>
#include <stdbool.h>

struct Process{
    int pid, arrival_time, burst_time, turn_around_time, waiting_time, completion_time, remaining_time;
    bool is_completed;
};

void shortest_job_first(struct Process p[], int size)
{
    /*
     *  Input   :   Process array.
     *  Utility :   a) Employ shortest Job first (Pre-emptive) algorithm on Process array for CPU Scheduling simulation.
     *              b) Arrival time taken from user.
     *  Output  :   Console output (Description table).
     */
    
    // Sort the processes by their burst time.
    int current_time = 0, completed = 0, index, i, temp;
    while(completed != size)
    {
        temp = 9999;
        // found = false;
        // Search for element in ready queue with shortest burst time
        for(i = 0; i < size; i++)
        {
            if( p[i].is_completed == false && 
                p[i].arrival_time <= current_time && 
                p[i].remaining_time < temp)
            {
                temp = p[i].remaining_time;
                index = i;
            }
        }
        p[index].remaining_time -= 1;
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
        process_array[i].is_completed = false;
        process_array[i].remaining_time = process_array[i].burst_time;
    }


    // Call SJF algorithm
    shortest_job_first(process_array, 5);

    printf("\n\nSr.No.\tPID\tAT\tBT\tCT\tTAT\tWT");
    // Display table for Process serving sequence
    for(i = 0; i < 5; i++)
    {
        average_waiting_time += process_array[i].waiting_time;
        average_turnaround_time += process_array[i].turn_around_time;
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t", (i+1), process_array[i].pid, process_array[i].arrival_time, process_array[i].burst_time, process_array[i].completion_time, process_array[i].turn_around_time, process_array[i].waiting_time);
    }
    average_waiting_time /= 5;
    average_turnaround_time /= 5;
    printf("\n\nAverage Waiting Time : %fms", average_waiting_time);
    printf("\n\nAverage Turn Around Time : %fms\n", average_turnaround_time);
    printf("\n");
    return (0);
}