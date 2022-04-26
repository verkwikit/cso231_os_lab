#include <bits/stdc++.h>
using namespace std;
// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int bt[], int wt[])
{
    // waiting time for first process is 0
    wt[0] = 0;

    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

//Function to calculate average time
void findavgTime(int processes[], int n, int bt[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, wt);

    findTurnAroundTime(processes, n, bt, wt, tat);

    //Display processes along with all details
    cout<<"Processes Burst time Waiting time Turn around time"<<endl;

    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout<<processes[i];
        cout<<"	  "<<bt[i];
        cout<<"	     "<<wt[i];
        cout<<"	          "<< tat[i];
        cout<<endl;
    }
    cout<<endl;
    float s = (float)total_wt / (float)n;
    float t = (float)total_tat / (float)n;
    cout<<"Average waiting time = "<<s<<endl;
    cout<<"Average turn around time = "<<t<<endl;
}
int main()
{
    //assuming arrival of processes have occured already
    vector<pair<int, int>> vect;
    //process id's
    int processes[] = {1, 2, 3, 4, 5};
    int n = sizeof processes / sizeof processes[0];

    //Burst time of all processes
    int burst_time[] = {10, 1, 2, 1, 5};

    // Entering values in vector of pairs
    for (int i = 0; i < n; i++)
        vect.push_back(make_pair(burst_time[i], processes[i]));

    sort(vect.begin(), vect.end());


    for(int i=0;i<n;i++){
        processes[i] = vect[i].second;
        burst_time[i] = vect[i].first;
    }
    findavgTime(processes, n, burst_time);
    return 0;
}
