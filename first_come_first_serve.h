//First Come First Serve Algorithm by Jelina Ramos-Perez

#ifndef FIRST_COME_FIRST_SERVE_H
#define FIRST_COME_FIRST_SERVE_H

#include <stdio.h>
#include <stdlib.h>
#include "Process_struct.h"

void first_come_first_serve(Process_struct process_array[], int numb_process, int context_switch_penalty)
{
	int i;
	
	process_array[0].start_time = process_array[0].arrival_time;
	process_array[0].finish_time = process_array[0].arrival_time + process_array[0].total_burst_time;
	process_array[0].wait_time = 0;
	process_array[0].turn_around_time = process_array[0].total_burst_time;

	for (i = 1; i < numb_process; i++)
	{
		process_array[i].start_time = process_array[i-1].finish_time + context_switch_penalty;
		process_array[i].finish_time = process_array[i].start_time + process_array[i].total_burst_time;
		process_array[i].wait_time = process_array[i].start_time - process_array[i].arrival_time;
		process_array[i].turn_around_time = process_array[i].finish_time - process_array[i].arrival_time;
	}
}

#endif