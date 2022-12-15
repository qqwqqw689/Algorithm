//C++ program for implementation of Ford Fulkerson algorithm
#include <iostream>
#include <climits>
#include <queue>
#include <cstring> //for memset

using namespace std;

//Number of vertices in given graph
#define V 6

/*
return true if there is a path from source 's' to sink 't'
in residual graph.Also fills parent[] to store the path
*/

bool bfs(int rGraph[V][V],int s,int t,int parent[])
{
    //create a visited array and mark all vertices as not visited
    bool visited[V];
    memset(visited,0,sizeof(visited));

    //create a queue,enqueue source vertex and mark source vertex as visited
    queue<int> q;
    q.push(s);
    visited[s]=true;
    parent[s]=-1;

    //standard BFS loop
    while(!q.empty())
    {
        int u=q.front();
        q.pop();

        for(int v=0;v<V;v++)
        {
            if(visited[v]==false&&rGraph[u][v]>0)
            {
                //if we find a connection to the sink node,
                //then there is no point in BFS anymore.We
                //just have to set its parent and can return true
                if(v==t)
                {
                    parent[v]=u;
                    return true;
                }
                q.push(v);
                parent[v]=u;
                visited[v]=true;
            }
        }
    }
    //We didn't reach sink in BFS starting from source,so
    //return false
    return false;
}

//returns the maximum flow from s to t in the graph
int fordFulkerson(int graph[V][V],int s,int t)
{
    int u,v;

    //create a residual graph where rGraph[i][j]
    //indicate residual capacity of edge
    //from i to j.(if rGraph [i][j] is 0,there is not a edge)
    int rGraph[V][V];
    for(u=0;u<V;u++)
        for(v=0;v<V;v++)
            rGraph[u][v]=graph[u][v];

    int parent[V];//the array is filled by BFS and to store patg

    int max_flow=0;

    //augment the flow while there is path from source to sink
    while(bfs(rGraph,s,t,parent))
    {
        //find the minimum residual capacity of the edge along
        //the path filled by BFS.Or we can say find the
        //maximum flow through the path found.
        int path_flow=INT_MAX;
        for(v=t;v!=s;v=parent[v])
        {
            u=parent[v];
            path_flow=min(path_flow,rGraph[u][v]);
        }
        //update residual capacityes of the edges and
        //reversre edge along the path
        for(v=t;v!=s;v=parent[v])
        {
            u=parent[v];
            rGraph[u][v]-=path_flow;
            rGraph[v][u]+=path_flow;
        }
        //add path flow to overall flow
        max_flow+=path_flow;
    }
    //return the overall flow
    return max_flow;
}

//Driver program to test above functions
int main()
{
    //let us create a graph show in the graph for Ford-Fulkson Algorithm
    int graph[V][V]
    ={{0,16,13,0,0,0},{0,0,10,12,0,0},
    {0,4,0,0,14,0},{0,0,9,0,0,20},
    {0,0,0,7,0,4},{0,0,0,0,0,0}};

    cout<<"The maximum possible flow is "<<fordFulkerson(graph,0,5);
}
