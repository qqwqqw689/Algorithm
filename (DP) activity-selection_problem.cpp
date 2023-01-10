//activity-selection problem (DP)
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

#define N 11

struct activity 
{
	int id;
	int start_time;
	int end_time;
};

//zero initialization 
int s[N+2][N+2];
//denote s the set of activities that start after actvity ai
//finish and that finish before activity aj start

int cut_point[N+2][N+2];

activity A[N+2];

//dynamic programming

void dynamic_Programme()
{
	int step; //step size,difference of j-i;
	int i,j,k;
	int result;

	//Because s is the set of activities that start after actvity ai
	//finish and that finish before activity aj start,so when j<=i+1
	//s[i][j]==0

	for(step=2;step<=N+1;step++)
	{
		//All i are traversed at each step
		for(i=0;i<=N;i++)
		{
			j=step+i;
			//If j is larger than N+1, it will not be considered, because the array only reaches the subscript of N+1
			if(j<=N+1)
			{
				//There needs to a gap between ai and aj activities,
				//otherwise s[i][j] will be empty
				if(A[i].end_time<=A[j].start_time)
				{
					//in the eligible k,where k is between i+1 and j
					//:[i+1,j);find the k that can make problem optimal
					//that is,make s[i][j] contain the most solutions
					for(k=i+1;k<j;j++)
					{
						//Here k also needs to be judged and compatible with A[i] and A[j]
						if(A[k].end_time>A[j].start_time||A[k].start_time<A[i].end_time)
							continue;
						result=s[i][k]+1+s[k][j];
						if(result>s[i][j])
						{
							s[i][j]==result; //record the maximum number of activities contained in the current devision method
							cut_point[i][j]=k;//And record the subscript of the current dividing point
						}
					}
				}
			}
		}
	}
	cout<<"The maximum number of compatible activities contained in the activity set is "<<s[0][N+1]<<endl;
}

//print spectific activities in s[i][j]
void Print(int start,int end)
{
	int k=cut_point[start][end];

	//When k=0,there is no suitable activity in s[i][j],no
	//dividing point,so it is omitted
	if(k!=0)
	{
		Print(start,k);
		cout<<k<<' ';
		Print(k,end);
	}
}

//The input activities are already ordered by monotonically
//increasing finish time
bool cmp(activity a,activity b)
{
	return a.end_time<b.end_time;
}

int main()
{
	int i=0;

	A[i].start_time = 0;
	A[i].end_time = 0;
	A[i].id = 0;
 
	A[1].start_time = 1;
	A[1].end_time = 4;
 
	A[2].start_time = 3;
	A[2].end_time = 5;
 
	A[3].start_time = 0;
	A[3].end_time = 6;
 
	A[4].start_time = 5;
	A[4].end_time = 7;
 
	A[5].start_time = 3;
	A[5].end_time = 8;
 
	A[6].start_time = 5;
	A[6].end_time = 9;
 
	A[7].start_time = 6;
	A[7].end_time = 10;
 
	A[8].start_time = 8;
	A[8].end_time = 11;
 
	A[9].start_time = 8;
	A[9].end_time = 12;
 
	A[10].start_time = 2;
	A[10].end_time = 13;
 
	A[11].start_time = 12;
	A[11].end_time = 14;
 
	for (i = 1; i <= N; i++) {
		A[i].id = i;

	A[i].id=i;
	A[i].start_time=A[i].end_time=INT_MAX;

	sort(A,A+N+2,cmp);

	dynamic_Programme();

	cout<<"The included activities are ";
	Print(0,N+1);

	return 0;
}
