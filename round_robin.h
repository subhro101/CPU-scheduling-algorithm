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

void round_robin(Process_struct process_array[], int numb_process, int time_quantum, int context_switch_penalty)
{
	int i = 0, current = 0;

	Process_struct p;
	queue <Process_struct> outputq;
	queue <Process_struct> readyq;
	   
	p = process_array[0];
    p.start_time = 0;
	readyq.push(p);
    i++;

	//While there are more processes in the ready queue
	while (readyq.size() > 0 || i < numb_process)
	{
	    current++;
		//pop first process in queue
		//p = Process_struct();
		p = readyq.front();
		if(p.arrival_time > current)
		{
		    current = p.arrival_time;  
		}
		else
		{
		    p.start_time = current;
		    //If this is first time run, set wait time
		    if(p.total_burst_time == p.remaining_burst_time)
		    {
		        //printf("Current time: %d\nProcess: %d started\nArrival time: %d\nTotal Burst Time: %d\nRemaining: %d\n\n", current, p.id_number, p.arrival_time, p.total_burst_time, p.remaining_burst_time);
		        p.wait_time = p.start_time - p.arrival_time;
		    }
            else
            {
               //printf("Current time: %d\nProcess: %d running\nArrival time: %d\nTotal Burst Time: %d\nRemaining: %d\n\n", current, p.id_number, p.arrival_time, p.total_burst_time, p.remaining_burst_time);
            }
    		readyq.pop();
            //Run while elapsed time < quantum time
    		if(p.remaining_burst_time > time_quantum)
    		{
    		    p.remaining_burst_time -= time_quantum;
    		    current += time_quantum;
    		    readyq.push(p);
    		    //printf("Current time: %d\nProcess: %d stopped\n Remaining time: %d\n\n", current, p.id_number, p.remaining_burst_time);
    		}
    		//If process is finished, add it to the end of the output queue
    		else
    		{
    		    current += p.remaining_burst_time;
    		    p.turn_around_time = current-p.start_time;
    		    p.remaining_burst_time = 0;
    		    p.finish_time = current;
    		    outputq.push(p);
    		    //printf("Current time: %d\nProcess %d completed\n\n", current, p.id_number);
    		}

    		//Push arrived processes to ready queue
    		while((i < numb_process) && (process_array[i].arrival_time <= current))
    		{
    			p = process_array[i];
    			readyq.push(p);
    			i++;
    			current = p.arrival_time;
    		}
		}
	}
    //Copy output to the process_array, to be printed in main
	for(i = 0; i < numb_process; i++)
	{
	    process_array[i] = outputq.front();
	    outputq.pop();
	}
}
#endif