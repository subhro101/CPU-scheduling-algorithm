//First Come First Serve Algorithm

#ifndef FIRST_COME_FIRST_SERVE_H
#define FIRST_COME_FIRST_SERVE_H

#include <stdio.h>
#include <stdlib.h>
#include "Process_struct.h"

void first_come_first_serve(Process_struct process_array[], int numb_process, int context_switch_penalty)
{
	int x;
	
	process_array[0].start_time = process_array[0].arrival_time;
	process_array[0].finish_time = process_array[0].arrival_time + process_array[0].total_burst_time;

	for (x = 1; x < numb_process; x++)
	{
		process_array[x].start_time = process_array[x-1].finish_time + context_switch_penalty;
		process_array[x].finish_time = process_array[x].start_time + process_array[x].total_burst_time;
		
	}
}

#endif
