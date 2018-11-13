//First Come First Serve Algorithm by Jelina Ramos-Perez

#ifndef PRIORITY_H
#define PRIORITY_H


#include <stdio.h>
#include <stdlib.h>
#include "Process_struct.h"

void priority(Process_struct process_array[], int numb_process, int context_switch_penalty)
{
	int x,i,j,k,temp=0, temp2 =0, temp3 =0;
	
	
	for(i=0; i<numb_process; i++)
        for(j=0; j<numb_process; j++)
        {
            if(process_array[i].priority_number<process_array[j].priority_number)
            {
                temp=process_array[i].priority_number;
                process_array[i].priority_number=process_array[j].priority_number;
                process_array[j].priority_number=temp;
                temp=process_array[i].arrival_time;
                process_array[i].arrival_time=process_array[j].arrival_time;
                process_array[j].arrival_time=temp;
                temp2=process_array[i].total_burst_time;
                process_array[i].total_burst_time=process_array[j].total_burst_time;
                process_array[j].total_burst_time=temp2;
                temp3=process_array[i].id_number;
                process_array[i].id_number=process_array[j].id_number;
                process_array[j].id_number=temp3;
            }
        }
    
    process_array[0].start_time = process_array[0].arrival_time;
	process_array[0].finish_time = process_array[0].arrival_time + process_array[0].total_burst_time;    
    for(x = 1; x < numb_process; x++)
 
    {
            process_array[x].start_time = process_array[x-1].finish_time + context_switch_penalty;
            process_array[x].finish_time = process_array[x].start_time + process_array[x].total_burst_time;;
           
    }    
	
	
	

#endif