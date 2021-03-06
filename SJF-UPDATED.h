//Shortest Job First Algorithm
//Al Mundhar Al Hadhrami

#ifndef SHORTEST_JOB_FIRST_H
#define SHORTEST_JOB_FIRST_H

#include <stdio.h>
#include <limits.h>
#include "Process_struct.h"

Process_struct *find_shortest_job(Process_struct *process_array, int num_processes, int current_time);

void sjf(Process_struct *process_array, int num_processes, int is_premptive, int context_switch_penalty) {
    
    int time_unit = 0, num_not_finished = num_processes;
    Process_struct* current_process = process_array;
    
    //While loop iterates until all processes have been completed
    while(num_not_finished > 0) {
        //Find shortest available job
        current_process = find_shortest_job(process_array, num_processes, time_unit);
        
        //If no job is available, tick clock and try again
        if(current_process != NULL) {
            current_process->start_time = time_unit;
            current_process->remaining_burst_time = 0;
            time_unit += current_process->total_burst_time;
            current_process->finish_time = time_unit;
            time_unit += context_switch_penalty;
            num_not_finished--;
        }
        else
            time_unit++;
    }
}

//Returns the process with the shortest burst time remaining.
Process_struct *find_shortest_job(Process_struct *process_array, int num_processes, int current_time) {
    int min = INT_MAX;
    Process_struct *current_process;
    Process_struct *shortest_job = NULL;
    
    for(current_process = process_array; current_process < process_array + num_processes; current_process++) {
        if(current_process->total_burst_time < min && current_process->remaining_burst_time != 0 && current_time >= current_process->arrival_time) {
            min = current_process->remaining_burst_time;
            shortest_job = current_process;
        }
    }
    
    return shortest_job;
}
#endif



