// persistent segemnt tree
//luogu P3567
//https://www.bilibili.com/video/BV1qi4y1c74Q/

#include <bits/stdc++.h>
using namespace std;
#define mid (l+r>>1)
#define int long long

int n,q;
int cnt,root[1000005]; // cnt -> the number of nodes  root -> the root of every segment tree
struct PStree{
    int l, r; // left child, right child
    int v;    // the value of node(the nuumber of occurence of a number)
}t[1000005<<4];

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
    if(t[ox].v-t[oy].v<=k)
        return 0;
    if(l==r)
        return l;
    return max(query(t[ox].l,t[oy].l,l,mid,k),query(t[ox].r,t[oy].r,mid+1,r,k));
}

signed main()
{
    cin>>n>>q;
    for(int i=1,x;i<=n&&cin>>x;i++)
        build(root[i],root[i-1],1,n,x);
    while(q--)
    {
        int l,r;
        scanf("%lld%lld",&l,&r);
        printf("%lld\n",query(root[r],root[l-1],1,n,(r-l+1)/2)); //The idea of prefix sum
    }
    return 0;
}
