//al mundhar Al Hadhrami
//shortest job first.h
#include<stdio.h>

//shortest job first
void main()
{
    
    int burst[20];
    int process[20];
    int waitingtime[20];
    int TurnAroundTime[20];
    int holdingvariable;
    int AnotherHoldingVarible;
    int xx;
    int all=0;
    int var;
    int saved;
    float averageWaitingTime,averageTotal;
    //displaying the number of the process needed
    printf("please place  the number of processes ");
    scanf("%d",&xx);
    //choosing whats the burst  time for each process
    printf("\n what is the number of burst time for each process :\n");
    
    for(holdingvariable=0;holdingvariable<xx;holdingvariable++)
    {
        //displaying next varibale
        printf("p%d:",holdingvariable+1);
        scanf("%d",&burst[holdingvariable]);
        //it has the process number
        process[holdingvariable]= holdingvariable+1;
    }
    
    
    //for loop for slection sort of the whole burst time
    for(holdingvariable=0;holdingvariable<xx;holdingvariable++)
    {
        //variable to hold
        var=holdingvariable;
        
        //for loop for the burst time
        for(AnotherHoldingVarible=holdingvariable+1;AnotherHoldingVarible<xx;AnotherHoldingVarible++)
        {
            if(burst[AnotherHoldingVarible]<burst[var])
            var=AnotherHoldingVarible;
        }
        
        saved=burst[holdingvariable];
        burst[holdingvariable]=burst[var];
        burst[var]=saved;
        
        saved=process[holdingvariable];
        process[holdingvariable]=process[var];
        process[var]=saved;
    }
    
    //setting the wait time for the first process to be zero
    waitingtime[0]=0;
    
    
    //for loop
    // calculating the waitTime
    for(holdingvariable=1;holdingvariable<xx;holdingvariable++)
    {
        waitingtime[holdingvariable]=0;
        for(AnotherHoldingVarible=0;AnotherHoldingVarible<holdingvariable;AnotherHoldingVarible++)
        waitingtime[holdingvariable]+=burst[AnotherHoldingVarible];
        
        all+=waitingtime[holdingvariable];
    }
    //getting the average wait time
    averageWaitingTime=(float)all/xx;
    all=0;
    printf("\n------------------------\n");
    
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(holdingvariable=0;holdingvariable<xx;holdingvariable++)
    {
        TurnAroundTime[holdingvariable]=burst[holdingvariable]+waitingtime[holdingvariable];     //calculate turnaround time
        all+=TurnAroundTime[holdingvariable];
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d",process[holdingvariable],burst[holdingvariable],waitingtime[holdingvariable],TurnAroundTime[holdingvariable]);
    }
    
    averageTotal=(float)all/xx;     //average turnaround time
           printf("\n------------------------\n");
    printf("\n\n The Average Waiting Time is equal to =%f",averageWaitingTime);
    printf("\n---> \n" );
    printf("\n The Average Turnaround Time is equal to =%f\n",averageTotal);
}
