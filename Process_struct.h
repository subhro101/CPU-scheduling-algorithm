//Header file for our process struct

#ifndef PROCESS_STRUCT_H
#define PROCESS_STRUCT_H

typedef struct {
    int id_number; // number id 
    int total_burst_time; // how long it takes a process
    int remaining_burst_time; // how long is left 
    int priority_number; //determines the process priority
    int arrival_time; // Time the process arrived in the queue
    int start_time; 
    int finish_time; // Time the process finishes execution
	int wait_time;
	int turn_around_time;
} Process_struct;

#endif