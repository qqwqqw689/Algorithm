//C++ program for activity selection problem
//greedy algorithm

//The flooowing implemnetation assumes that the activities
//are already sorted according to their finish time
#include <bits/stdc++.h>
using namespace std;

void print(int s[],int f[],int n)
{
    int i,j;

    cout<<"Following activities are selected"<<endl;

    //This first activity always gets selected
    i=0;
    cout<<i<<" ";

    //consider rest of the activities
    for(j=1;j<n;j++)
    {
        //if the activities has start time greater than or
        //equal to the finish time of previous selected
        //activity,then select it
        if(s[j]>=f[i])
        {
            cout<<j<<" ";
            i=j;
        }
    }
}

int main()
{
    int s[]={1,3,0,5,8,5};
    int f[]={2,4,6,7,9,9};
    int n=sizeof(s)/sizeof(s[0]);

    print(s,f,n);
    return 0;
}
