#include <bits/stdc++.h>
using namespace std;

int n = 5;
vector<vector<int>> adj{{1,2},{0},{1},{4},{3}};
vector<bool> used(5,0);
vector<int> comp(5,0);

void dfs(int v) {
    used[v] = true ;
    comp.push_back(v);
    for (int u : adj[v]) {
        if (!used[u])
            dfs(u);
    }
}

void find_comps() {
    fill(used.begin(), used.end(), 0);
    for (int v = 0; v < n; ++v) {
        if (!used[v]) {
            comp.clear();
            dfs(v);
            cout << "Component:" ;
            for (int u : comp)
                cout << ' ' << u;
            cout << endl ;
        }
    }
}

int main()
{
    find_comps();

    return 0;
}
