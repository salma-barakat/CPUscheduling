#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <bits/stdc++.h>
using namespace std;

    struct process{
     char processName;
     int arrivalTime;
     int serviceTime;
     int finishTime;
     int index;
     float turnaroundTime;
     };

int t=0;
struct comparefn{

bool operator()(process const& p1,process const&p2)
{  return p1.serviceTime>p2.serviceTime;
//    if(p1.arrivalTime>t)
//        return true;
//    else if(p2.arrivalTime>t)
//        return false;
//    cout<<"p1"<<p1.processName<<" p2"<<p2.processName<<endl;
//    cout<<(p1.serviceTime>p2.serviceTime)<<endl;
//    return p1.serviceTime>p2.serviceTime && p1.arrivalTime<=t;
}
};

void FCFS(char processName[], int arrivalTime[], int serviceTime[]){

}

int main()
{
    string line1;
    cin>> line1;
    int algorithm;
    cin>> algorithm;
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
        }
        j++;

    }
    }
/// checking that scan is done correctly
    for(int k=0;k< pCount; k++){
        cout<<p[k].processName<<" "<<p[k].arrivalTime<<" "<<p[k].serviceTime<<endl;
    }

    if(line1 == "stats"){
        if(algorithm == 1){
        cout<<"FCFS"<<endl;
        //FCFS(processName, arrivalTime, serviceTime);
    }
    }
    else if(line1 == "trace"){
        for(int i=0;i<pCount;i++){
            for(int j=0;j<last;j++)
            {
               result[i][j]=' ';
            }
        }
        for(int i=0;i<pCount;i++){
            for(int j=0;j<last;j++)
            {
               cout<<result[i][j];
            }
            cout<<endl;
        }
        if(algorithm == 1){
        cout<<"FCFS";
//        while(last){
//            cout<<last%10;
//            last--;
//        }
        }
    }

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
        priority_queue<process,vector<process>,comparefn>temp=q;
        while(!temp.empty()){
              cout << temp.top().processName <<" ";
              temp.pop();
          }
        cout<<" time="<<t<<endl;

        ///to pop the first element in queue + setting their finish time+setting stars***
        if(current==-1){
            current=q.top().index;
            q.pop();

            p[current].finishTime=t+p[current].serviceTime;
            cout<<"finished ("<<p[current].processName<<") at "<<p[current].finishTime<<endl;
            for(int j=t;j<p[current].finishTime;j++)
            {
                result[current][j]='*';
            }

        }

        if(t == p[current].finishTime-1){
            current = -1;
        }
        ///to put points for ready processes...
            priority_queue<process,vector<process>,comparefn> temp2=q;
            while(! temp2.empty()){
            cout<<"here";
            int ready=temp2.top().index;
              temp2.pop();
              result[ready][t]='.';
            }
        }
///print process name
switch (algorithm){
case 1:
    cout<<"FCFS"<<"   ";
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
            for(int j=0;j<last;j++)
            {
               cout<<"|"<<result[i][j];
            }
            cout<<"|"<<endl;

        }
    cout<<"------------------------------------------------"<<endl;
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

int normturn_sum=0;
cout<<"NormTurn"<<"   "<<"|  ";
 cout<<setprecision(2)<<fixed;
for(int i=0;i<pCount;i++){
        normturn_sum+=p[i].turnaroundTime/(p[i].serviceTime);
        if(i==pCount-1)
        cout<<normturn_sum/(1.0*pCount)<<"|";
        else
        cout<<p[i].turnaroundTime/(p[i].serviceTime)<< "| ";
}

cout<<endl;
}

    return 0;
}
