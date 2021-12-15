#include <stdio.h>
#include <stdbool.h>

struct Process{
    int pid, arrival_time, burst_time, turn_around_time, waiting_time, completion_time, remaining_time, queue_time;
    bool is_completed;
};

void sort_by_arrival(struct Process p[], int size)
{
    /*
     *  Input       :   Process array, size of process array.
     *  Utility     :   Sort processes by bubble sort algorithm.
     *  Output      :   None
     */
    struct Process temp;
    bool swapped = false;
    int i;
    do
    {
        swapped = false;
        for(i = 0; i < size - 1; i++)
        {
            if(p[i].arrival_time > p[i+ 1].arrival_time)
            {
                temp = p[i];
                p[i] = p[i + 1];
                p[i + 1] = temp;
                swapped = true;
            }
        }
    }while(swapped);
}

void round_robin(struct Process p[], int time_quantum, int size)
{
    /*
     *  Input   :   Process array.
     *  Utility :   a) Employ Round Robin algorithm on Process array for CPU Scheduling simulation.
     *              b) Arrival time taken from user.
     *  Output  :   Console output (Description table).
     */
    
    int completed = 0, i, temp, current_time = -1, index = 0;
    sort_by_arrival(p, size);
    // Set current time to the first arrival time of all processes.
    current_time = p[0].arrival_time;
    while(completed != size)
    {
        temp = 9999;
        // Find the process which is not completed but in queue with least queue time.
        for(i = 0; i < size; i++)
        {
            if(!p[i].is_completed && p[i].queue_time <= current_time && p[i].queue_time < temp)
            {
                temp = p[i].queue_time;
                index = i;
            }
        }
        // For the found process, take descision on the basis of remaining time.
        if (p[index].remaining_time >= time_quantum)
        {
            p[index].remaining_time -= time_quantum;
            current_time += time_quantum;
            p[index].queue_time = current_time;
        }
        else
        {
            current_time += p[index].remaining_time;
            p[index].remaining_time = 0;
        }
        // If process is completed, update parameters.
        if(p[index].remaining_time == 0)
        {
            printf("\nProcess at index %d completed", index);
            p[index].is_completed = true;
            p[index].completion_time = current_time;
            p[index].turn_around_time = p[index].completion_time - p[index].arrival_time;
            p[index].waiting_time = p[index].turn_around_time - p[index].burst_time;
            completed += 1;
        }
    }
}


int main()
{
    // Get 5 processes.
    int i, time_quant;
    float average_waiting_time, average_turnaround_time = 0;
    struct Process process_array[5];
    printf("\nEnter time quantum : ");
    scanf("%d", &time_quant);
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
        process_array[i].queue_time = process_array[i].arrival_time;
        process_array[i].remaining_time = process_array[i].burst_time;
    }


    // Call RR algorithm
    round_robin(process_array, time_quant, 5);

    time_quant = process_array[0].arrival_time;

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