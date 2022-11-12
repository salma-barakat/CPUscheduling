#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <bits/stdc++.h>
using namespace std;


int main()
{

    string line1;
    cin>> line1;
    string algorithm;
    cin>> algorithm;
    string last;
    cin>> last;
    int pCount;
    cin>> pCount;
    string arr[pCount];
    for(int i=0; i<pCount; i++){
        cin>>arr[i];
    }
    char processName[pCount];
    int arrivalTime[pCount];
    int serviceTime[pCount];


    for(int i=0; i<pCount; i++){
    stringstream ss(arr[i]);
    int j=0;
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        if(j == 0){
            char temp[1];
            strcpy(temp, substr.c_str());   //copy using char arrays
            processName[i]=temp[0];
        }
        else if (j == 1){
            arrivalTime[i]=stoi(substr);
        }
        else{
            serviceTime[i]=stoi(substr);
        }
        j++;

    }
    }

    for(int k=0;k< pCount; k++){
        cout<<processName[k]<<" "<<arrivalTime[k]<<" "<<serviceTime[k]<<endl;
    }

    if(algorithm == "2"){

    }


    return 0;
}
