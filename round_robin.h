//Round Robin Algorithm by Michael DeGrande

#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H
#include <array>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Process_struct.h"
using namespace std;
int calculate(timespec first, timespec second);
void round_robin(Process_struct process_array[], int numb_process, int time_quantum, int context_switch_penalty)
{
	int i = 0, j = 0, elapsed_milli, epoch_milli;
	long time_elapsed = 0;
	Process_struct p;
	struct timespec start,current, epoch, elapsed;
	queue <Process_struct> outputq;
	queue <Process_struct> readyq;
	   
	p = process_array[0];
	p.start_time = p.arrival_time;

	readyq.push(p);
    i++;
    clock_gettime(CLOCK_MONOTONIC, &epoch);
	//While there are more processes in the ready queue
	while (readyq.size() > 0)
	{
		//pull first process in queue
		p = readyq.front();
		readyq.pop();

		elapsed_milli = 0;
		clock_gettime(CLOCK_MONOTONIC, &start);
		//Run while elapsed time < quantum time
		while(elapsed_milli < time_quantum)
		{
			//Calculate current and elapsed time
			clock_gettime(CLOCK_MONOTONIC, &current);
			elapsed_milli = calculate(start, current);
			//If there is more remaining burst time than elapsed time subtract that from remaining burst time
			if(p.remaining_burst_time > elapsed_milli)
			{
				p.remaining_burst_time -= elapsed_milli;
			} 
			else
			{
				p.remaining_burst_time = 0;
				p.finish_time = calculate(epoch, current);
				p.turn_around_time = p.finish_time - p.arrival_time;
				break;
			}
		}
		if(p.remaining_burst_time > 0)
		{
		    readyq.push(p);
		}
		else
		{
		    outputq.push(p);
		}
		//Set current time
		clock_gettime(CLOCK_MONOTONIC, &current);
		epoch_milli = calculate(epoch, current);

        if(i < numb_process)
        {
    		//Push arrived processes to ready queue
    		while(process_array[i].arrival_time <= epoch_milli)
    		{
    			p = process_array[i];
    			readyq.push(p);
    			i++;
    			clock_gettime(CLOCK_MONOTONIC, &current);
    			epoch_milli = calculate(epoch, current);
    		}
        }
	}
	for(j = 0; j < outputq.size(); j++)
	{
	    process_array[i] = outputq.front();
	    outputq.pop();
	}
}

int calculate(timespec first, timespec second)
{
    int first_milli = (first.tv_sec * 1000000000 + first.tv_nsec) /1000000;
    int second_milli = (second.tv_sec * 1000000000 + second.tv_nsec) /1000000;
   return second_milli - first_milli; 
}

#endif