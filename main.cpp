#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <bits/stdc++.h>
using namespace std;
    int algorithm;
    struct process{
     char processName;
     int arrivalTime;
     int serviceTime;
     int finishTime;
     int index;
     float turnaroundTime;
     int remainingTime;
     };

int t=0;
struct comparefn{

bool operator()(process const& p1,process const&p2)
{
    if (algorithm==3)
        return p1.serviceTime>p2.serviceTime;
    else if(algorithm==4)
    {
        if(p1.remainingTime==p2.remainingTime)
        return p1.arrivalTime>p2.arrivalTime;
        else
        return p1.remainingTime>p2.remainingTime;
    }
    else if(algorithm==5)
    {
        int d1=t-p1.arrivalTime+1;
        int d2=t-p2.arrivalTime+1;
        float r1=(d1+p1.serviceTime)/p1.serviceTime;
        float r2=(d2+p2.serviceTime)/p2.serviceTime;
        if(r1==r2)
             return p1.arrivalTime>p2.arrivalTime;
        else
            return r1<r2;
    }


//    if(p1.arrivalTime>t)
//        return true;
//    else if(p2.arrivalTime>t)
//        return false;
//    cout<<"p1"<<p1.processName<<" p2"<<p2.processName<<endl;
//    cout<<(p1.serviceTime>p2.serviceTime)<<endl;
//    return p1.serviceTime>p2.serviceTime && p1.arrivalTime<=t;
}
};

int main()
{
    string line1;
    cin>> line1;
    string line2;
    cin>> line2;
    int quantum;
    stringstream ss(line2);
    int k=0;
    while (ss.good()) {
        string substr;
        getline(ss, substr, '-');
        if(k == 0){
            algorithm = stoi(substr);
            k++;
        }
        if(k == 1)
            quantum = stoi(substr);
    }
    int last;
    cin>> last;
    int pCount;
    cin>> pCount;
    string arr[pCount];
    priority_queue<process,vector<struct process>,comparefn>q;
    struct process p[pCount];
    char result[pCount][last];
///scanning and tokenizing
    for(int i=0; i<pCount; i++){
        cin>>arr[i];
    }
    for(int i=0; i<pCount; i++){
    stringstream ss(arr[i]);
    int j=0;
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        if(j == 0){
            char temp[1];
            strcpy(temp, substr.c_str());   //copy using char arrays
            p[i].index=i;
            p[i].processName=temp[0];
        }
        else if (j == 1){
            p[i].arrivalTime=stoi(substr);
        }
        else{
            p[i].serviceTime=stoi(substr);
            p[i].remainingTime=stoi(substr);
        }
        j++;

    }
    }
/// checking that scan is done correctly
//    for(int k=0;k< pCount; k++){
//        cout<<p[k].processName<<" "<<p[k].arrivalTime<<" "<<p[k].serviceTime<<endl;
//    }

    if(line1 == "trace"){
        for(int i=0;i<pCount;i++){
            for(int j=0;j<last;j++)
            {
               result[i][j]=' ';
            }
        }
    }

    if(algorithm == 1){
        int i = 0;
        int busy = 0;
        int finish = 0;
        while(t<last && i<pCount){
            if(p[i].arrivalTime<=t){
                for(int j=p[i].arrivalTime; j<t; j++){
                    result[i][j] = '.';
                }
                p[i].finishTime = t + p[i].serviceTime;
                for(int j=t; j<p[i].finishTime; j++){
                    result[i][j] = '*';
                }
                t = p[i].finishTime;
                i++;
            }
            else{
                t++;
            }
        }
    }
    else if (algorithm == 2){
        int i=0;
        int busyTime = 0;
        queue<process>q2;
        for(t=0; t<last; t++){
            if(busyTime == t && p[i].arrivalTime <= t){ //if nothing is running
                for(int j=t; j<t + quantum; j++){   //*** check if quantun is more than service time
                    result[i][j] = '*';
                }
                busyTime = t + quantum;
                p[i].remainingTime = p[i].serviceTime - quantum;
                if(p[i].remainingTime > 0)
                    q2.push(p[i]);
            }

            else if(busyTime==t && !q2.empty()){ //if nothing is running take from queue
                i = q2.front().index;
                q2.pop();
                for(int j=t; j<t + quantum; j++){   //*** check if quantun is more than service time
                    result[i][j] = '*';
                }
                busyTime = t + quantum;
                p[i].remainingTime = p[i].serviceTime - quantum;
                if(p[i].remainingTime > 0)
                    q2.push(p[i]);
                else
                    p[i].finishTime = busyTime;
            }

            else if(busyTime!=t && p[i].arrivalTime==t){    //if a process is running and another arrived, put the new in queue
                result[i][t] = '.';
                q.push(p[i]);
            }
        }
    }

    else{
    int current= -1;
    for(t=0;t<last;t++)
    {    ///pushing ready processes into queue
        for(int i=0;i<pCount;i++){
            if(p[i].arrivalTime==t)
            {
                q.push(p[i]);
            }

        }
         ///printing names of processes currently in queue
//        priority_queue<process,vector<process>,comparefn>temp=q;
//        while(!temp.empty()){
//              cout << temp.top().processName <<" ";
//              temp.pop();
//          }
//        cout<<" time="<<t<<endl;

        ///to pop the first element in queue + setting their finish time+setting stars***
        if(algorithm==3 || algorithm==5){

        if(current==-1){
            current=q.top().index;
            q.pop();

            p[current].finishTime=t+p[current].serviceTime;
            //cout<<"finished ("<<p[current].processName<<") at "<<p[current].finishTime<<endl;
            for(int j=t;j<p[current].finishTime;j++)
            {
                result[current][j]='*';
            }

        }

        if(t == p[current].finishTime-1){
            current = -1;
        }}

        if(algorithm==4)
        {
            if(!q.empty())
            {
            current=q.top().index;
            q.pop();
            p[current].remainingTime--;
            if(p[current].remainingTime==0)
                p[current].finishTime=t+1;
            else
            q.push(p[current]);
            result[current][t]='*';


            }
        }

        ///to put points for ready processes...
            priority_queue<process,vector<process>,comparefn> temp2=q;
            while(! temp2.empty()){
            //cout<<"here";
            int ready=temp2.top().index;
            temp2.pop();
            if(algorithm==4)
            {if(ready==current)
            continue;}
              result[ready][t]='.';
            }
        }
    }
///print process name
switch (algorithm){
case 1:
    cout<<"FCFS"<<"  ";
    break;
case 2:
    cout<<"RR"<<"   ";
    break;
case 3:
    cout<<"SPN"<<"   ";
    break;
case 4:
   cout<<"SRT"<<"   ";
    break;
case 5:
   cout<<"HRRN"<<"   ";
    break;
case 6:
   cout<<"FB-1"<<"   ";
    break;
case 7:
   cout<<"FB-2i"<<"   ";
    break;
case 8:
   cout<<"Aging"<<"   ";
    break;

}

///print of trace
if(line1=="trace")
  {
    int j=0;
    for(int i=0;i<=last;i++)
    {   if(j==10)
          {
           j=0;
          }
        cout<< j++<<" ";
    }
cout<<endl;
cout<<"------------------------------------------------"<<endl;
      for(int i=0;i<pCount;i++){
            cout<<p[i].processName<<"     ";
            for(int j=0;j<=last-1;j++)
            {
               cout<<"|"<<result[i][j];
            }
            cout<<"| "<<endl;

        }
    cout<<"------------------------------------------------"<<endl;
    cout<<endl;
  }
///print of status
else{
cout<<endl;
cout<<"Process"<<"    "<<"|  ";
for(int i=0;i<pCount;i++)
    cout<<p[i].processName<< "  |  ";
cout<<endl;
cout<<"Arrival"<<"    "<<"|  ";
for(int i=0;i<pCount;i++)
    cout<<p[i].arrivalTime<< "  |  ";
cout<<endl;
cout<<"Service"<<"    "<<"|  ";
for(int i=0;i<pCount;i++)
    { if(i==pCount-1)
       cout<<p[i].serviceTime<< "  | Mean|";
       else
       cout<<p[i].serviceTime<< "  |  ";
    }
cout<<endl;
cout<<"Finish"<<"     "<<"|  ";
for(int i=0;i<pCount;i++)
     { if(i==pCount-1)
       cout<<p[i].finishTime<< "  |-----|";
       else
       cout<<p[i].finishTime<< "  |  ";
    }
cout<<endl;
cout<<"Turnaround"<<" "<<"|  ";
int turnaround_sum=0;

for(int i=0;i<pCount;i++)
{
    p[i].turnaroundTime=p[i].finishTime-p[i].arrivalTime;
    turnaround_sum+=p[i].turnaroundTime;
    if(i==pCount-1)
    {

        cout<<p[i].turnaroundTime<< "  | ";
        cout<<setprecision(2)<<fixed;
        cout<<turnaround_sum/(1.0*pCount)<<"|";
    }

    else
    cout<<p[i].turnaroundTime<< "  |  ";
}

cout<<endl;

float normturn_sum=0;
cout<<"NormTurn"<<"   "<<"|  ";
 cout<<setprecision(2)<<fixed;
for(int i=0;i<pCount;i++){
        normturn_sum+=p[i].turnaroundTime/(p[i].serviceTime*1.0);

        cout<<p[i].turnaroundTime/(p[i].serviceTime*1.0)<< "| ";
         if(i==pCount-1)
        cout<<normturn_sum/(1.0*pCount)<<"|";
}

cout<<endl;
}

    return 0;
}
