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
struct process
{
    char processName;
    int arrivalTime;
    int serviceTime;
    int finishTime;
    int index;
    float turnaroundTime;
    int remainingTime;
    int pushTime;
    int priority;
    int initial_priority;
    int current_priority;
    //int taken_before=0;
};

int t = 0;
struct comparefn
{

    bool operator()(process const &p1, process const &p2)
    {
        if (algorithm == 3)
            return p1.serviceTime > p2.serviceTime;
        else if (algorithm == 4)
        {
            if (p1.remainingTime == p2.remainingTime)
                return p1.arrivalTime > p2.arrivalTime;
            else
                return p1.remainingTime > p2.remainingTime;
        }
        else if (algorithm == 5)
        {
            int d1 = t - p1.arrivalTime + 1;
            int d2 = t - p2.arrivalTime + 1;
            float r1 = (d1 + p1.serviceTime) / p1.serviceTime;
            float r2 = (d2 + p2.serviceTime) / p2.serviceTime;
            if (r1 == r2)
                return p1.arrivalTime > p2.arrivalTime;
            else
                return r1 < r2;
        }

        else if (algorithm == 8)
        {
            if (p1.current_priority == p2.current_priority)
            //{
//                if(p1.taken_before==p2.taken_before)
//                {
//                   return p1.arrivalTime > p2.arrivalTime;
//                }
//                else
//                {
//                  p1.taken_before>p2.taken_before;
//                }
//            }
                return p1.arrivalTime > p2.arrivalTime;
            else
                return p1.current_priority < p2.current_priority;
        }return true;

    }
};

int main()
{
    string line1;
    cin >> line1;
    string line2;
    cin >> line2;
    int quantum;
    stringstream ss(line2);
    int k = 0;
    vector<string> alg;
    vector<int> valg;
    vector<int> vquant;
    while (ss.good())
    {
        string substr;
        getline(ss, substr, ',');
        alg.push_back(substr);
    }
    for (int i = 0; i < alg.size(); i++)
    {
        int k = 0;
        int flag = 0;
        stringstream ss2(alg[i]);
        while (ss2.good())
        {

            string substr;
            getline(ss2, substr, '-');
            if (k == 0)
            {
                valg.push_back(stoi(substr));
                k++;
            }
            else if (k == 1)
            {
                vquant.push_back(stoi(substr));
                k++;
            }
        }
        if (k == 1)
        {
            vquant.push_back(0);
        }
    }

    for (auto i = vquant.begin(); i != vquant.end(); ++i)
        cout << *i << " ";
    cout << endl;
    int last;
    cin >> last;
    int pCount;
    cin >> pCount;
    string arr[pCount];

    struct process p[pCount];
    char result[pCount][last];
    /// scanning and tokenizing
    for (int i = 0; i < pCount; i++)
    {
        cin >> arr[i];
    }
    for (int i = 0; i < pCount; i++)
    {
        stringstream ss(arr[i]);
        int j = 0;
        while (ss.good())
        {
            string substr;
            getline(ss, substr, ',');
            if (j == 0)
            {
                char temp[1];
                strcpy(temp, substr.c_str()); // copy using char arrays
                p[i].index = i;
                p[i].processName = temp[0];
            }
            else if (j == 1)
            {
                p[i].arrivalTime = stoi(substr);
            }
            else
            {
                p[i].serviceTime = stoi(substr);
                p[i].remainingTime = stoi(substr);
                p[i].current_priority = stoi(substr);
                p[i].initial_priority = stoi(substr);
            }
            j++;
        }
    }
    /// checking that scan is done correctly
    //    for(int k=0;k< pCount; k++){
    //        cout<<p[k].processName<<" "<<p[k].arrivalTime<<" "<<p[k].serviceTime<<endl;
    //    }

    for (int i = 0; i < valg.size(); i++)
    {
        t = 0;
        algorithm = valg[i];
        quantum = vquant[i];
        priority_queue<process, vector<struct process>, comparefn> q;
        //if (line1 == "trace")
        //{
            for (int i = 0; i < pCount; i++)
            {
                p[i].remainingTime = p[i].serviceTime;
                p[i].finishTime = 0;
                for (int j = 0; j < last; j++)
                {
                    result[i][j] = ' ';
                }
            }
        //}

        if (algorithm == 1)
        {
            int i = 0;
            int busy = 0;
            int finish = 0;
            while (t < last && i < pCount)
            {
                if (p[i].arrivalTime <= t)
                {
                    for (int j = p[i].arrivalTime; j < t; j++)
                    {
                        result[i][j] = '.';
                    }
                    p[i].finishTime = t + p[i].serviceTime;
                    for (int j = t; j < p[i].finishTime; j++)
                    {
                        result[i][j] = '*';
                    }
                    t = p[i].finishTime;
                    i++;
                }
                else
                {
                    t++;
                }
            }
        }
        else if (algorithm == 2)
        {
            int i = 0;
            int busyTime = 0;
            int quant = 0;
            queue<process> q2;
            for (t = 0; t < last; t++)
            {
                if (q2.empty())
                {
                    if (busyTime == t && p[i].arrivalTime <= t)
                    { // if nothing is running
                        if (p[i].remainingTime < quantum)
                            quant = p[i].remainingTime;
                        else
                            quant = quantum;
                        for (int j = t; j < t + quant; j++)
                        { //*** check if quantun is more than service time
                            result[i][j] = '*';
                        }
                        busyTime = t + quant;
                        p[i].remainingTime = p[i].remainingTime - quant;
                        if (p[i].remainingTime > 0)
                        {
                            p[i].pushTime = busyTime;
                            q2.push(p[i]);
                        }
                        else
                            p[i].finishTime = busyTime;
                        i++;
                    }
                    else if (busyTime != t && p[i].arrivalTime == t)
                    { // if a process is running and another arrived, put the new in queue
                        p[i].pushTime = t;
                        q.push(p[i]);
                    }
                }

                else if (busyTime == t && !q2.empty())
                { // if nothing is running
                    if (p[i].arrivalTime <= q2.front().pushTime)
                    { // if a process arrived whose arrival is before push
                        if (p[i].remainingTime < quantum)
                            quant = p[i].remainingTime;
                        else
                            quant = quantum;
                        for (int j = t; j < t + quant; j++)
                        { //*** check if quantun is more than service time
                            result[i][j] = '*';
                        }
                        busyTime = t + quant;
                        p[i].remainingTime = p[i].remainingTime - quant;
                        if (p[i].remainingTime > 0)
                        {
                            p[i].pushTime = busyTime;
                            q2.push(p[i]);
                        }
                        else
                            p[i].finishTime = busyTime;
                        i++;
                    }
                    else
                    { // pop from queue
                        int current = q2.front().index;
                        q2.pop();
                        if (p[current].remainingTime < quantum)
                            quant = p[current].remainingTime;
                        else
                            quant = quantum;
                        for (int j = t; j < t + quant; j++)
                        { //*** check if quantun is more than service time
                            result[current][j] = '*';
                        }
                        busyTime = t + quant;
                        p[current].remainingTime = p[current].remainingTime - quant;
                        if (p[current].remainingTime > 0)
                        {
                            p[current].pushTime = busyTime;
                            q2.push(p[current]);
                            current++;
                        }
                        else
                            p[current].finishTime = busyTime;
                    }
                }
            }
            for (int pr = 0; pr < pCount; pr++)
            { // loop on processes to find ready time
                for (int wait = p[pr].arrivalTime; wait < p[pr].finishTime; wait++)
                {
                    if (result[pr][wait] != '*')
                        result[pr][wait] = '.';
                }
            }
        }

        else if (algorithm == 6)
        {
            priority_queue<process, vector<process>, comparefn> feedq;
            int i = 0;
            t = 0;
            while (t < last)
            {
                if (p[i].arrivalTime == t)
                { // if nothing is running
                    p[i].priority = 0;
                    p[i].pushTime = t;
                    feedq.push(p[i]);
                    i++;
                }

                while (!feedq.empty())
                { // if the queue isn't empty and processor is free
                    current = feedq.top().index;
                    feedq.pop();
                    p[current].remainingTime -= 1;
                    result[current][t] = '*';
                    t++;
                    if (p[current].remainingTime > 0)
                    {
                        while (feedq.empty() && p[i].arrivalTime != t && p[current].remainingTime > 0)
                        {
                            // if no new process arrived and the queue is empty and the current process has remaining service time
                            p[current].remainingTime -= 1;
                            result[current][t] = '*';
                            t++;
                        }
                        if (p[current].remainingTime != 0)
                        {
                            p[current].pushTime = t;
                            p[current].priority += 1;
                            feedq.push(p[current]);
                        }
                        else
                            p[current].finishTime = t;
                    }
                    else
                    {
                        p[current].finishTime = t;
                    }
                    if (p[i].arrivalTime == t)
                        break;
                }
            }

            for (int pr = 0; pr < pCount; pr++)
            { // loop on processes to find ready time
                for (int wait = p[pr].arrivalTime; wait < p[pr].finishTime; wait++)
                {
                    if (result[pr][wait] != '*')
                        result[pr][wait] = '.';
                }
            }
        }

        else if (algorithm == 7)
        {
            priority_queue<process, vector<process>, comparefn> feedq2i;
            int i = 0;
            int interval;
            t = 0;
            int looped = 0; //to know if we reached the last process
            while (t < last)
            {
                if (p[i].arrivalTime <= t)
                { // if nothing is running
                    p[i].priority = 0;
                    p[i].pushTime = t;
                    feedq2i.push(p[i]);
                    if(i<pCount-1)
                        i++;
                    else
                        looped = 1;
                }

                while (!feedq2i.empty())
                { // if the queue isn't empty and processor is free
                    current = feedq2i.top().index;
                    feedq2i.pop();
                    interval = pow(2, p[current].priority);
                    if (p[current].remainingTime < interval)
                        interval = p[current].remainingTime;
                    p[current].remainingTime -= interval;
                    for (int j = t; j < t + interval; j++)
                    {
                        result[current][j] = '*';
                    }
                    t += interval;
                    if (p[current].remainingTime > 0)
                    {
                        while (feedq2i.empty() && !(p[i].arrivalTime <= t) && p[current].remainingTime > 0)
                        {
                            // if no new process arrived and the queue is empty and the current process has remaining service time
                            if (p[current].remainingTime < interval)
                                interval = p[current].remainingTime;
                            p[current].remainingTime -= interval;
                            for (int j = t; j < t + interval; j++)
                            {
                                result[current][j] = '*';
                            }
                            t += interval;
                        }
                        if (p[current].remainingTime != 0)
                        {
                            p[current].pushTime = t;
                            p[current].priority += 1;
                            feedq2i.push(p[current]);
                        }
                        else
                            p[current].finishTime = t;
                    }
                    else
                    {
                        p[current].finishTime = t;
                    }
                    if(!looped && p[i].arrivalTime <= t)
                        break;
                }
            }

            for (int pr = 0; pr < pCount; pr++)
            { // loop on processes to find ready time
                for (int wait = p[pr].arrivalTime; wait < p[pr].finishTime; wait++)
                {
                    if (result[pr][wait] != '*')
                        result[pr][wait] = '.';
                }
            }
        }


        else
        {
            int current = -1;
            for (t = 0; t < last; t++)
            { /// pushing ready processes into queue
                for (int i = 0; i < pCount; i++)
                {
                    if (p[i].arrivalTime == t)
                    {
                        q.push(p[i]);
                        //cout<<"this     "<<p[i].taken_before<<endl;
                    }
                }
                /// printing names of processes currently in queue
                // priority_queue<process,vector<process>,comparefn>temp=q;
                // while(!temp.empty()){
                //       cout << temp.top().processName <<" ";
                //       temp.pop();
                //   }
                // cout<<" time="<<t<<endl;

                /// to pop the first element in queue + setting their finish time+setting stars***
                if (algorithm == 3 || algorithm == 5)
                {

                    if (current == -1)
                    {
                        current = q.top().index;
                        q.pop();

                        p[current].finishTime = t + p[current].serviceTime;
                        // cout<<"finished ("<<p[current].processName<<") at "<<p[current].finishTime<<endl;
                        for (int j = t; j < p[current].finishTime; j++)
                        {
                            result[current][j] = '*';
                        }
                    }

                    if (t == p[current].finishTime - 1)
                    {
                        current = -1;
                    }
                }

                if (algorithm == 4)
                {
                    if (!q.empty())
                    {
                        current = q.top().index;
                        q.pop();
                        p[current].remainingTime--;
                        if (p[current].remainingTime == 0)
                            p[current].finishTime = t + 1;
                        else
                            q.push(p[current]);
                        result[current][t] = '*';
                    }
                }


                if (algorithm == 8)
                {

                    int index;
                    queue<process> temp8;
                    ///



                    while (!q.empty())
                    {
                        process ptemp = q.top();
                        q.pop();
                        temp8.push(ptemp);
                    }

                    while (!temp8.empty())
                    {
                        index = temp8.front().index;
                        temp8.pop();
                        // if(index!=current)
                        p[index].current_priority = p[index].current_priority + 1;
                        q.push(p[index]);
                    }
                    current = q.top().index;
                    //p[current].taken_before=1;
                    q.pop();
                    for(int y=0;y<quantum;y++)
                    result[current][t+y] = '*';
                    t+=quantum-1;
                     p[current].current_priority = p[current].initial_priority;
                     q.push(p[current]);
                }

                /// to put points for ready processes...
                priority_queue<process, vector<process>, comparefn> temp2 = q;
                while (!temp2.empty())
                {

                    int ready = temp2.top().index;
                    temp2.pop();
                    if (algorithm == 4 || algorithm == 8)
                    {
                        if (ready == current)
                            continue;
                    }
                    result[ready][t] = '.';
                }
            }
        }
        /// print process name
        switch (algorithm)
        {
        case 1:
            cout << "FCFS"
                 << "  ";
            break;
        case 2:
            cout << "RR-" << quantum << "  ";
            break;
        case 3:
            cout << "SPN"
                 << "   ";
            break;
        case 4:
            cout << "SRT"
                 << "   ";
            break;
        case 5:
            cout << "HRRN"
                 << "  ";
            break;
        case 6:
            cout << "FB-1"
                 << "   ";
            break;
        case 7:
            cout << "FB-2i"
                 << "   ";
            break;
        case 8:
            cout << "Aging"
                 << " ";
            break;
        }

        /// print of trace
        if (line1 == "trace")
        {
            int j = 0;
            for (int i = 0; i <= last; i++)
            {
                if (j == 10)
                {
                    j = 0;
                }
                cout << j++ << " ";
            }
            cout << endl;
            cout << "------------------------------------------------" << endl;
            for (int i = 0; i < pCount; i++)
            {
                cout << p[i].processName << "     ";
                for (int j = 0; j <= last - 1; j++)
                {
                    cout << "|" << result[i][j];
                }
                cout << "| " << endl;
            }
            cout << "------------------------------------------------" << endl;
            cout << endl;
        }
        /// print of status
        else
        {
            cout << endl;
            cout << "Process"
                 << "    "
                 << "|  ";
            for (int i = 0; i < pCount; i++)
                cout << p[i].processName << "  |  ";
            cout << endl;
            cout << "Arrival"
                 << "    "
                 << "|  ";
            for (int i = 0; i < pCount; i++)
                cout << p[i].arrivalTime << "  |  ";
            cout << endl;
            cout << "Service"
                 << "    "
                 << "|  ";
            for (int i = 0; i < pCount; i++)
            {
                if (i == pCount - 1)
                    cout << p[i].serviceTime << "  | Mean|";
                else
                    cout << p[i].serviceTime << "  |  ";
            }
            cout << endl;
            cout << "Finish"
                 << "     "
                 << "|  ";
            for (int i = 0; i < pCount; i++)
            {
                if (i == pCount - 1)
                    cout << p[i].finishTime << "  |-----|";
                else
                    cout << p[i].finishTime << "  |  ";
            }
            cout << endl;
            cout << "Turnaround"
                 << " "
                 << "|  ";
            int turnaround_sum = 0;

            for (int i = 0; i < pCount; i++)
            {
                p[i].turnaroundTime = p[i].finishTime - p[i].arrivalTime;
                turnaround_sum += p[i].turnaroundTime;
                if (i == pCount - 1)
                {

                    cout << p[i].turnaroundTime << "  | ";
                    cout << setprecision(2) << fixed;
                    cout << turnaround_sum / (1.0 * pCount) << "|";
                }

                else
                    cout << p[i].turnaroundTime << "  |  ";
            }

            cout << endl;

            float normturn_sum = 0;
            cout << "NormTurn"
                 << "   "
                 << "|  ";
            cout << setprecision(2) << fixed;
            for (int i = 0; i < pCount; i++)
            {
                normturn_sum += p[i].turnaroundTime / (p[i].serviceTime * 1.0);

                cout << p[i].turnaroundTime / (p[i].serviceTime * 1.0) << "| ";
                if (i == pCount - 1)
                    cout << normturn_sum / (1.0 * pCount) << "|";
            }

            cout << endl;
        }
    }

    return 0;
}
