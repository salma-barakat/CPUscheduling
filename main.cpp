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

struct comparefn{

bool operator()(process const& p1,process const&p2)
{
    return p1.serviceTime>p2.serviceTime;
}
};

void FCFS(char processName[], int arrivalTime[], int serviceTime[]){

}

int main()
{

    string line1;
    cin>> line1;
    string algorithm;
    cin>> algorithm;
    int last;
    cin>> last;
    int pCount;
    cin>> pCount;
    string arr[pCount];
    priority_queue<process,vector<struct process>,comparefn>q;
    struct process p[pCount];
    char result[pCount][last];

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

    for(int k=0;k< pCount; k++){
        cout<<p[k].processName<<" "<<p[k].arrivalTime<<" "<<p[k].serviceTime<<endl;
    }

    if(line1 == "stats"){
        if(algorithm == "1"){
        cout<<"FCFS"<<endl;
        //FCFS(processName, arrivalTime, serviceTime);
    }
    }
    else if(line1 == "trace"){
        for(int i=0;i<pCount;i++){
            for(int j=0;j<last;j++)
            {
               result[i][j]='-';
            }
        }
        for(int i=0;i<pCount;i++){
            for(int j=0;j<last;j++)
            {
               cout<<result[i][j];
            }
            cout<<endl;
        }
        if(algorithm == "1"){
        cout<<"FCFS";
//        while(last){
//            cout<<last%10;
//            last--;
//        }
        }
    }

    int current= -1;
    for(int t=0;t<last;t++)
    {
        for(int i=0;i<pCount;i++)
        {
            if(p[i].arrivalTime==t)
            {
                q.push(p[i]);
            }

        }

        priority_queue<process,vector<process>,comparefn>temp=q;
        while(!temp.empty())
          {
              cout << temp.top().processName <<" ";
              temp.pop();
          }
        cout<<" time="<<t<<endl;


        if(current==-1)
        {
            current=q.top().index;
            q.pop();

            p[current].finishTime=t+p[current].serviceTime;
            cout<<"finished (    "<<p[current].processName<<") at "<<p[current].finishTime<<endl;
            for(int j=t;j<p[current].finishTime;j++)
            {
                result[current][j]='*';
            }

        }
        for(int i=0;i<pCount;i++){
            for(int j=0;j<last;j++)
            {
               cout<<result[i][j];
            }
            cout<<endl;
        }

//          if(current>-1){
//          if(t==p[current].finishTime)
//                current=-1;
//           }
//     priority_queue<process,vector<process>,comparefn>temp2=q;
//            while(!temp2.empty())
//             {
//            cout<<"here";
//            int ready=temp2.top().index;
//              temp2.pop();
//              result[ready][t]='.';
//            }
//
//       cout<<"current"<<current<<endl;



    }










    return 0;
}
