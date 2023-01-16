// Segment tree
// This includes finding the sum of consecutive array elements  
// a[l...r],or finding the minimum element in a such a range in O(logn) time.

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100  // Maximum value of n

//We store the Segment Tree simply as an array t[] with a size of four times the input size n
//(We need to store at most 4n vertices)
//The left child of a vertex at index i is stored as index 2i,
//and the right one at index 2i+1
int n,t[4*MAXN];

//The procedure for constructing the Segment Tree (recursive function)
//the boundaries tl and tr of the current segment
//In the main program ,It will be called with the parameter
//of the root vertex:v=1,tl=0;tr=n-1
void build(int a[],int v,int tl,int tr)
{
    if(tl==tr){
        t[v]=a[tl];
    }else{
        int tm=(tl+tr)/2;
        build(a,v*2,tl,tm);
        build(a,v*2+1,tm+1,tr);
        t[v]=t[2*v]+t[2*v+1];
    }
}

//Compute the sum of the segment a[l...r]
int sum(int v,int tl,int tr,int l,int r)
{
    //The current vertex v and its boundaries tl and tr
    if(l>r)
        return 0;
    if(l==tl&&r==tr)
    {
        return t[v];
    }
    int tm=(tl+tr)/2;

    return sum(v*2,tl,tm,l,min(r,tm))+sum(v*2+1,tm+1,tr,max(l,tm+1),r);
}

//Modify a specific elememt in the array
//Recursively calls itself with one of the two child vertices
void update(int v,int tl,int tr,int pos,int new_val)
{
    if(tl==tr){
        t[v]=new_val;
    } else {
        int tm=(tl+tr)/2;
        if(pos<=tm)
            update(v*2,tl,tm,pos,new_val);
        else
            update(v*2+1,tm+1,tr,pos,new_val);
        t[v]=t[2*v]+t[2*v+1];
    }
}


int main()
{
    int a[]={1,3,-2,8,-7};

    build(a,1,0,4);
    
    cout<<sum(1,0,4,2,4)<<endl;

    update(1,0,4,3,100);

    cout<<sum(1,0,4,2,4)<<endl;

    return 0;
}
