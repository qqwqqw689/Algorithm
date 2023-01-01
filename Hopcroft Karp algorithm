//C++ implementation of Hopcroft Karp algorithm for maximum matching
#include <bits/stdc++.h>
using namespace std;
#define NIL 0
#define INF INT_MAX

//a class tp represent Bipartite graph for Hopcroft
//Karp implentation 
class BipGraph
{
    //m and n are number of vertices on left
    //and right sides of Bipartite Graph
    int m,n;

    //adj[u] stores adjacents of left side
    //vertex 'u'.The value of u ranges from 1 to m.
    //0 is used for dummy vertex
    list<int>* adj;

    //These are basically pointers to arrays needed
    //for hopcroftKarp()
    int* pairU,*pairV,*dist;
public:
    BipGraph(int m,int n);//constrctor
    void addEdge(int u,int v);//to add edge

    //return true if there is augmenting path
    bool bfs();

    //Adds augmenting path if there is one beginning with u
    bool dfs(int u);

    //Returns size of the maximum matching
    int hopcroftKarp();
};
//Returns size of maximum mathing
int BipGraph::hopcroftKarp()
{
    //the index of points starts from 1

    //pairU[u] stores pair of u in matching where u
    //is a vertex on left side of Bipartite Graph.
    //If u dosen't have any pair,then pairU[u] is NIL
    pairU=new int[m+1];

    //pairV[v] stores pair of v in matching.If v
    //doesn't have any pair,then pairV[v] is NIL
    pairV=new int[n+1];

    //dist[u] stores distance of left side vertices
    //dist[u] is one more than dist[u'] if u is next
    //to u' in augmenting path
    dist=new int[m+1];

    //initialize NIL as pair of all vertices,indicate a free vertex
    for(int u=0;u<=m;u++) pairU[u]=NIL;
    for(int v=0;v<=n;v++) pairV[v]=NIL;

    //initialize result
    int result=0;

    //keep updating the result while there is an
    //augmenting path
    while(bfs())
    {
        //Find a free vertex
        for(int u=1;u<=m;u++)
            //If current vertex is free and there is
            //an augmenting path from current vertex
            if(pairU[u]==NIL&&dfs(u))
                result++;

    }

    delete [] pairU;
    delete [] pairV;

    return result;
}

//Returns true if there is an augmenting path,else returns false
bool BipGraph::bfs()
{
    queue<int> Q;//an integer queue

    //First layer of vertices(set distance as 0)
    for(int u=1;u<=m;u++)
    {
        //if this is a free vertex,add it to queue
        if(pairU[u]==NIL)
        {
            //u is not matched
            dist[u]=0;
            Q.push(u);
        }
        //else set distance as infinite so that this vertex
        //not is considered next time,because it is not a free vertex
        else dist[u]=INF;
    }

    //Initialize distance to NIL as infinite
    dist[NIL]=INF;

    //Q is going to contain vertices of left side only.
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();

        //if this node is not NIL and can provide a shorter path to NIL
        if(dist[u]<dist[NIL])
        {
            //Get all adjacent vertices of the dequed vertex u
            list<int>::iterator i;
            for(i=adj[u].begin();i!=adj[u].end();i++)
            {
                int v=*i;

                //if pair of v is not considered so far
                //(v,pairV[v]) is not yet explored edge
                if(dist[pairV[v]]==INF)
                {
                    //Consider the pair and add it to queue
                    dist[pairV[v]]=dist[u]+1;
                    Q.push(pairV[v]);
                }
            }
        }
    }
    //if dist[NIL] is not equal to INF,we can confirm that
    //we've arrived at v that pairV[v] is equal to NIL.
    //so we get a augmenting path
    return (dist[NIL]!=INF);
}

//return true if there is an augmenting path beginning with free vertex u
bool BipGraph::dfs(int u)
{
    if(u!=NIL)
    {
        list<int>::iterator i;
        for(i=adj[u].begin();i!=adj[u].end();i++)
        {
            //Adjacent to u
            int v=*i;

            //Follow the distances set by BFS
            if(dist[pairV[v]]==dist[u]+1)
            {
                //if dfs for pair of v also returns true
                if(dfs(pairV[v])==true)
                {
                    pairV[v]=u;
                    pairU[u]=v;
                    return true;
                }
            }
        }
        //If there is no augmenting path beginning with u
        dist[u]=INF;
        return false;
    }
    return true;
}

//constructor
BipGraph::BipGraph(int m,int n)
{
    this->m=m;
    this->n=n;
    adj=new list<int>[m+1];
}

//to add edge from u to v 
void BipGraph::addEdge(int u,int v)
{
    adj[u].push_back(v);
}

//Driver Program
int main()
{
    BipGraph g(4,4);
    g.addEdge(1,2);
    g.addEdge(1,3);
    g.addEdge(2,1);
    g.addEdge(3,2);
    g.addEdge(4,2);
    g.addEdge(4,4);

    cout<<"Size of the maximum is "<<g.hopcroftKarp();

    return 0;
}
