/*  CPU Scheduling Simulator

    Authors:
    Jelina Ramos
    Michael De Grande
    Subhrajyoti Pradhan
    Al Mundhar Al Hadhrami

    Date: 10/29/2018
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <queue>
#include "Process_struct.h"
#include "round_robin.h"
#include "shortest_job_first.h"
#include "first_come_first_serve.h"
#include "priority.h"

#define max_priority 5
#define num_processes 25
#define max_arrival_distance 5
#define max_burst_time 50
#define context_switch_time 1
#define time_quantum 20

int total_wait_time(Process_struct proc[]);
double average_wait_time(Process_struct proc[]);
int total_turnaround_time(Process_struct proc[]);
double average_turnaround_time(Process_struct proc[]);
double cpu_utilization(Process_struct proc[]);
void results(Process_struct proc[]);


int main(int argc, char* argv[]) 
{
    int i;
    int current_time = time(NULL);

    srand(current_time);
    int arrival_time_accumulator = 0;
    
    // Setup the processes
    Process_struct processes[num_processes];
    
    for (i = 0; i < num_processes; i++)
    {
        processes[i].id_number = i + 1; 
        processes[i].total_burst_time = rand() % max_burst_time;
        processes[i].remaining_burst_time = processes[i].total_burst_time;
        processes[i].priority_number = rand() % max_priority;
        arrival_time_accumulator += rand() % max_arrival_distance;
        processes[i].arrival_time = arrival_time_accumulator;
        processes[i].start_time = -1; // Not set yet
        processes[i].finish_time = 0; // Not set yet
        processes[i].wait_time = 0; //Not set yet                           
        processes[i].turn_around_time = 0; //Not set yet                    
    }
    
    Process_struct fcfs_processes[num_processes];
    memcpy(fcfs_processes, processes, sizeof(processes));

    Process_struct rr_processes[num_processes];                             
    memcpy(rr_processes, processes, sizeof(processes));                     

    Process_struct sjf_processes[num_processes];
    memcpy(sjf_processes, processes, sizeof(processes));

    Process_struct priority_processes[num_processes];
    memcpy(priority_processes, processes, sizeof(processes));
    
    
    //FCFS
    first_come_first_serve(fcfs_processes, num_processes, context_switch_time);
    printf("\n First Come First Serve results:\n");
    results(fcfs_processes);
    
    //RR    
    round_robin(rr_processes, num_processes, time_quantum, context_switch_time);
    printf("\n Round Robin results:\n");
    results(rr_processes);
    
    //SJF
    shortest_job_first(sjf_processes, num_processes, 0, context_switch_time);
    printf(" Shortest Job First results:\n");
    results(sjf_processes);

    //Priority                                                              
    priority(priority_processes, num_processes, context_switch_time);
    printf("\n Priority results:\n");
    results(priority_processes);

    return 0;
}

double cpu_utilization(Process_struct processes[])
{
    int start_time = processes[0].arrival_time, total_burst_time = 0, i, max_finish_time = 0;
    double utilization;
    for (i = 0; i < num_processes; i++) 
    {
        total_burst_time += processes[i].total_burst_time;
        if (processes[i].finish_time > max_finish_time) 
        {
            max_finish_time = processes[i].finish_time;
        }
    }
    utilization = (double) (total_burst_time / (double) (max_finish_time - start_time));
    
    return utilization;
}

void results(Process_struct procs[])                                               
{
    printf(" Processes:\n");
    int i;
    for (i = 0; i < num_processes; i++)
    {
        Process_struct p = procs[i];
        printf(" Process: %d \tBurst: %d \tArrival: %d \tWait: %d \tTurned: %d \n", p.id_number, p.total_burst_time, p.arrival_time, p.wait_time, p.turn_around_time);
    }
    printf("\n Total wait: %d\n Average wait: %.2f\n Total turnaround: %d\n Average turnaround: %.2f\n CPU Utilization: %.2f\n\n", total_wait_time(procs), average_wait_time(procs), total_turnaround_time(procs), average_turnaround_time(procs), cpu_utilization(procs));
    printf("\n");
}

int total_wait_time(Process_struct proc[])                                             
{
    int i, total = 0;
    for (i = 0; i < num_processes; i++) 
    {
        total += proc[i].wait_time;
    }
    return total;
}

double average_wait_time(Process_struct proc[]) 
{
    return (double) (total_wait_time(proc)) / num_processes;
}

int total_turnaround_time(Process_struct proc[])                                        
{
    int i, total = 0;
    for (i = 0; i < num_processes; i++) 
    {
        total += proc[i].turn_around_time;
    }
    return total;
}

double average_turnaround_time(Process_struct proc[]) 
{
    return (double) (total_turnaround_time(proc)) / num_processes;
}
