#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    freopen("input_SRTF.txt","r",stdin);
    int endTime,i,smallest,at[10],bt[10],rt[10]; // rt = remaining time
    int remain=0,n,time,sum_wait=0,sum_turnaround=0;

    //printf("Enter no of Processes : ");
    //scanf("%d",&n);
    cin>>n;

    for(i=0;i<n;i++)
    {
        cin>>at[i];
        cin>>bt[i];
        rt[i]=bt[i];
    }
    printf("Process\tTurnaround Time\tWaiting Time");
    
    rt[9]=9999;
    
    for(time=0;remain!=n;time++)
    {
        smallest=9;
        for(i=0;i<n;i++)
        {
            if(at[i]<=time && rt[i]<rt[smallest] && rt[i]>0)
            {
                smallest=i;
            }
        }
        rt[smallest]--;
        if(rt[smallest]==0)
        {
            remain++;
            endTime=time+1;
            printf("\nP[%d]\t\t%d\t\t%d",smallest+1,endTime-at[smallest],endTime-bt[smallest]-at[smallest]);
            sum_wait+=endTime-bt[smallest]-at[smallest];
            sum_turnaround+=endTime-at[smallest];
        }
    }
    printf("\n\nAverage waiting time = %f\n",sum_wait*1.0/n);
    printf("Average Turnaround time = %f",sum_turnaround*1.0/5);
    return 0; 
}

/*

Code Explanation

Line no 8-15 are used for taking inputs. The array variables `at` and `bt` stores arrival time and burst time of processes.
Array `rt` stores the remaining time of the processes which initially are equal to the burst time of the processes. This is the time to complete execution of all the processes.

Line no 18 starts a loop where time starts from zero
Line no 20 to 27 are used to find a process which have the least remaining time and it’s arrival time is less than or equal to the current time. This condition is checked at every unit time, that is why time is incremented by 1 (time++).

Line no 26 is used to print the arrival time and burst time for finished processes. At this moment, variable `time` gives the time of start of the process.
Therefore Turnaround time=(time+burst time-arrival time),
Waiting time =(time – arrival time)

In line no 28 remaining time for shortest process is decreased by one since time is increased by one.
If a particular process have just finished/completed, then it satisfies the condition in line no 29.
Since the variable time stores the current time, and the process was running at this moment, therefore its ending time = time+1 (line no 32).
Since
burst time+waiting time = end time - Start time
therefore
waiting time=end Time-burst time-arrival time
waiting time and turnaround time of all processes are summed up and divided by n to give their average.

*/
