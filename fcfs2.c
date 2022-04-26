#include<stdio.h>
struct PCB
{
    int pid,arrival,burst,turnaround;
};


void pline(int x);

void main()
{
    int i,num,j;
    float avg =0.0,sum =0.0;
    struct PCB p[10],temp;
    printf("enter the total number of processes:\n");
    scanf("%d",&num);
    for(i=0;i<num;i++)
    {
        printf("enter arrival time and burst time for process %d:\n",i+1);
        scanf("%d %d",&p[i].arrival,&p[i].burst);
        p[i].pid = i+1;
    }
    
    for(i=0;i<num;i++)
    {
        for(j=0;j<num-i-1;j++)
        {
            if(p[j].arrival>p[j+1].arrival)
            {
                temp   = p[j];
                p[j]   = p[j+1];
                p[j+1] = temp;
            }
            else if(p[j].arrival == p[j+1].arrival) //if arrival time is same then we 
            {                                       //check execute process with lesser
                                                    //execution time
                if(p[j].burst>p[j+1].burst)
                {
                    temp   = p[j];
                    p[j]   = p[j+1];
                    p[j+1] = temp;
                }
            }
        }
    }

    for(i=0;i<num;i++)
    {
        sum = sum +p[i].burst;
        p[i].turnaround = sum ;
    }
    sum =0;
    pline(44);
    printf("PID\tARRIVAL\tBURST\tTURNAROUND\n");
    pline(44);
    for(int i =0;i<num;i++)
    {
        printf("%d\t%d\t%d\t%d\n",p[i].pid,p[i].arrival,p[i].burst,p[i].turnaround);
        sum += p[i].turnaround;
    }
    pline(44);
    avg = sum / (float)num;
    printf("\nTotal Turnaround Time : %f.",sum);
    printf("\nAverage  Turnaround Time : %f.",avg);    
}

void pline(int x)
{
    int i;
    for(i=0;i<x;i++)
    {
        printf("-");
    }
    printf("\n");
}