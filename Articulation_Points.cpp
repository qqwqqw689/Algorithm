// Articulation points
// https://codeforces.com/blog/entry/71146

#include <bits/stdc++.h>
using namespace std;

int Time = 0;

vector<vector<int>> adj; // adj[u] = agjacent nodes of u
vector<int> disc; // disc[u] = discovery time of u
vector<int> low;// low[u] = 'low' node of u
vector<int> ap; //ap = articulation point

// p -> parent

// condition 1# U is an articulation point if it does not have an adjacent node V that can reach A without requiring U to be in G.
// A ----- U ------- V
// condition #2 if U is the root of the DFS traversal with at least 2 children subgraphs disconnected from each other.

int dfsAP(int u,int p) {
    int children = 0;
    low[u] = disc[u] = ++Time;
    for (int& v : adj[u]) {
        if (v == p) continue; //we don't want to go back through the same path.
        //if we go back is becase we found another way back

        if(!disc[v]) { // if v has not been discovered before
            children++;
            dfsAP(v, u); //recursive DFS call
            if (disc[u] <= low[v]) //condition #1 
                ap[u] = 1;
            low[u] = min(low[u], low[v]); // low[v] might be an ancestor of v
        } else // if v was already discovered means we have found an ancestor
            low[u] = min(low[u], low[v]); //  find the ancestor with the least discovery time
    }
    return children;
}

void AP() {
    ap = low = disc = vector<int>(adj.size());
    for (int u = 0; u < adj.size(); u++) { 
        if(!disc[u])
            ap[u] = dfsAP(u,u) > 1; // condition #2
    }
}

int main()
{
    adj = {{1},{0,2},{1}};
    AP();
    for(int i = 0; i < adj.size(); i++) {
        if(ap[i] > 0)
            cout << i;
    }
    return 0;
}
