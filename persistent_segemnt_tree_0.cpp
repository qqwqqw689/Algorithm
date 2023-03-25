// persistent segemnt tree
//luogu P3834
//https://www.bilibili.com/video/BV1qi4y1c74Q/

#include <bits/stdc++.h>
using namespace std;
#define mid (l+r>>1)

int n,q,a[200005],m;
int cnt,root[2000005]; // cnt -> the number of nodes  root -> the root of every segment tree
// root[] is used to record the label of each number of root nodes in all nodes.
struct PStree{
    int l, r; // left child, right child
    int v;    // the value of node(the nuumber of occurence of a number)
}t[2000005<<4];

vector<int> v;

void discretize()
{
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    // unique(): Eliminates all except the first element from every consecutive group of equivalent elements from 
    // the range [first, last) and returns a past-the-end iterator for the new logical end of the range.
    // erase()； Removes the elements in the range [first, last)
    m = v.size();
}

// o -> current node  pre -> old persistent segment tree 
void build(int& o,int pre, int l, int r, int x)
{
    o = ++cnt;
    t[o] = t[pre];  // The current node needs to be modified based on the predecessor
    t[o].v++;
    if(l==r)
        return;
    if(x<=mid)
        build(t[o].l, t[pre].l, l, mid, x);
    else
        build(t[o].r, t[pre].r, mid+1, r, x);
} 


int query(int ox, int oy,int l, int r, int k)
{
    if(l==r)
        return l;
    int s = t[t[ox].l].v - t[t[oy].l].v;
    if(k<=s)
        return query(t[ox].l,t[oy].l,l,mid,k);
    else
        return query(t[ox].r,t[oy].r,mid+1,r,k-s);
}
signed main()
{
    cin>>n>>q;
    for(int i=1;i<=n&&cin>>a[i];i++)
        v.push_back(a[i]);
    discretize();
    for(int i=1;i<=n;i++)
        build(root[i],root[i-1],1,m,lower_bound(v.begin(),v.end(),a[i])-v.begin()+1);
    while(q--)
    {
        int l,r,k;
        scanf("%d %d %d",&l,&r,&k);
        printf("%d\n",v[query(root[r],root[l-1],1,m,k)-1]); //The idea of prefix sum
    }
    return 0;
}
