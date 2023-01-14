//C++ program for stable marrige problem
#include <iostream>
#include <cstring>
using namespace std;

//Number if Men or Women
#define N 4

//This function returns true if woman 'W' prefers man 'm1' over man 'm'
bool wPrefersM1OverM(int prefer[2*N][N],int w,int m,int m1)
{
    //Check if w prefers m over her current engagement m1
    for(int i=0;i<N;i++)
    {
        //If m1 comes before m in list of w,then w prefers her 
        //current engagement,don't do anything
        if(prefer[w][i]==m1)
            return true;

        //If m comes before m1 in w's list,then free her current engagement
        //and engage her with m
        if(prefer[w][i]==m)
            return false;
    }
    return 0;
}

//Print stable matching for N boys and N girls.
//Boys are numbered as 0 to N-1.Girls are numbered 
//as N to 2N-1
void stableMarriage(int prefer[2*N][N])
{
    //Stores parenter of woman.This is our output array that
    //stores passing information.The value of wParent[i]
    //indicates the partner assigned to woman N+i.Note that
    //the woman numbers between N and 2*N-1.The value -1
    //indicates the (N+i)'th woman is free.

    int wPartner[N];

    //An array to store availability of men.If mFree[i] is
    //false, then man 'i' is free,otherwise engaged.

    bool mEngaged[N];

    //Initialize all men and women as free
    memset(wPartner,-1,sizeof(wPartner));
    memset(mEngaged,false,sizeof(mEngaged));
    int freeCount=N;

    //While there are free men
    while(freeCount>0)
    {
        //Pick the first free man(we could pick any)
        int m;
        for(m=0;m<N;m++)
            if(mEngaged[m]==false)
                break;

        //One by One go to all women according to m's preferences
        //Here m is the picked free man
        for(int i=0;i<N&&mEngaged[m]==false;i++)
        {
            int w=prefer[m][i];

            //The woman of preference is free, w and m become
            //partners(Note that the partnership maybe changed
            //latter).So we can say they are engaged not married.

            if(wPartner[w-N]==-1)
            {
                wPartner[w-N]=m;
                mEngaged[m]=true;
                freeCount--;
            }
            else    //If w is not free
            {
                //Find current engagement of w
                int m1=wPartner[w-N];

                //If w prefers m over her current engagement m1,
                //then break the engangement between w and m1,and 
                //engage m and w.
                if(wPrefersM1OverM(prefer,w,m,m1)==false)
                {
                    wPartner[w-N]=m;
                    mEngaged[m]=true;
                    mEngaged[m1]=false;
                }
            }//End of Else
        } //End of the for loop that goes to all women in m's list
    }//End of the main while loop

    //Print the solution
    cout<<"Woman    Man"<<endl;
    for(int i=0;i<N;i++)
        cout<<" "<<i+N<<"\t"<<wPartner[i]<<endl;
}

// Driver program to test above functions
int main()
{
    int prefer[2*N][N] = { {7, 5, 6, 4},
        {5, 4, 6, 7},
        {4, 5, 6, 7},
        {4, 5, 6, 7},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
    };
    stableMarriage(prefer);

    return 0;
}
