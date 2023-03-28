// Find bridges
// https://codeforces.com/blog/entry/71146

#include <bits/stdc++.h>
using namespace std;

int Time = 0;

vector<vector<int>> adj; // adj[u] = agjacent nodes of u
vector<int> disc; // disc[u] = discovery time of u
vector<int> low;// low[u] = 'low' node of u
vector<pair<int, int>> br; // br = bridges

// p -> parent

void dfsBR(int u,int p) {
    low[u] = disc[u] = ++Time;
    for (int& v : adj[u]) {
        if (v == p) continue; //we don't want to go back through the same path.
        //if we go back is becase we found another way back

        if(!disc[v]) { // if v has not been discovered before
            dfsBR(v, u); //recursive DFS call
            if (disc[u] < low[v]) //condition to find the bridge
                br.push_back({u,v});
            low[u] = min(low[u], low[v]); // low[v] might be an ancestor of v
        } else // if v was already discovered means we have found an ancestor
            low[u] = min(low[u], low[v]); //  find the ancestor with the least discovery time
    }
}

void BR() {
    low = disc = vector<int>(adj.size());
    for (int u = 0; u < adj.size(); u++) { 
        if(!disc[u])
            dfsBR(u,u);
    }
}

int main()
{
    adj = {{1},{0,2},{1}};
    BR();
    for(auto e : br)
        cout << "(" << e.first << ", " << e.second << ")" << endl;
    return 0;
}
