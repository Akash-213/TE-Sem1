#include <stdio.h>
#include <stdbool.h>

struct Process{
    int pid, arrival_time, burst_time, turn_around_time, waiting_time, completion_time;
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

int main()
{
    // Get 5 processes.
    int i, time_quant = 0;
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
    }

    // Sort Array according to the arrival time.
    sort_by_arrival(process_array, 5);

    printf("\nSr.No.\tPID\tAT\tBT\tCT\tTAT\tWT");
    // Display table for Process serving sequence
    for(i = 0; i < 5; i++)
    {
        time_quant += process_array[i].burst_time;
        process_array[i].completion_time = time_quant;
        process_array[i].turn_around_time = process_array[i].completion_time - process_array[i].arrival_time;
        process_array[i].waiting_time = process_array[i].turn_around_time - process_array[i].burst_time;
        average_waiting_time += process_array[i].waiting_time;
        average_turnaround_time += process_array[i].turn_around_time;
        if(i < 4 && process_array[i+1].arrival_time > time_quant)
        {
            time_quant = process_array[i + 1].arrival_time;
        }

        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t", (i+1), process_array[i].pid, process_array[i].arrival_time, process_array[i].burst_time, process_array[i].completion_time, process_array[i].turn_around_time, process_array[i].waiting_time);
    }
    average_waiting_time /= 5;
    average_turnaround_time /= 5;
    printf("\n\nAverage Waiting Time : %f", average_waiting_time);
    printf("\n\nAverage Turn Around Time : %f\n", average_turnaround_time);

    printf("\n\nGantt Chart : ");
    for(i = 0; i < 5; i++)
    {
        printf("%d", process_array[i].pid);
        if(i < 4)
        {
            printf("->");
        }
    }
    printf("\n");
    return (0);
}