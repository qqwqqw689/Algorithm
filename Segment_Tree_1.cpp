// Segment tree
// Finding the maximum and the number of times it appears
#include <bits/stdc++.h>
using namespace std;

// To solve this problem, we store a pair of number at each vertex in the tree
// In addition to maximum we also store the number of occurences of it

#define MAXN 100

pair<int,int> t[4*MAXN];

pair<int,int> combine(pair<int,int> a,pair<int,int> b)
{
    if(a.first>b.first)
        return a;
    if(b.first>a.first)
        return b;
    return make_pair(a.first,a.second+b.second);
};

void build(int a[],int v,int tl,int tr)
{
    if(tl==tr){
        t[v]=make_pair(a[tl],1);
    } else {
        int tm=(tl+tr)/2;
        build(a,v*2,tl,tm);
        build(a,v*2+1,tm+1,tr);
        t[v]=combine(t[v*2],t[v*2+1]);
    }
}

pair<int,int> get_max(int v,int tl,int tr,int l,int r)
{
    if(l>r)
        return make_pair(-INT_MAX,0);
    if(l==tl&&r==tr)
        return t[v];
    int tm=(tl+tr)/2;
    return combine(get_max(v*2,tl,tm,l,min(r,tm)),get_max(v*2+1,tm+1,tr,max(l,tm+1),r));
}

void update(int v,int tl,int tr,int pos,int new_val)
{
    if(tl==tr){
        t[v]=make_pair(new_val,1);
    } else {
        int tm=(tl+tr)/2;
        if(pos<=tm)
            update(v*2,tl,tm,pos,new_val);
        else 
            update(v*2+1,tm+1,tr,pos,new_val);
        t[v]=combine(t[v*2],t[v*2+1]);
    }
    
}

int main()
{
     int a[]={1,3,-2,8,-7};

    build(a,1,0,4);
    
    cout<<get_max(1,0,4,2,4).first<<" "<<get_max(1,0,4,2,4).second<<endl;

    update(1,0,4,3,100);

    cout<<get_max(1,0,4,2,4).first<<" "<<get_max(1,0,4,2,4).second<<endl;

    return 0;
}
