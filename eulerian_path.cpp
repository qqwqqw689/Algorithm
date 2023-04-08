#include <bits/stdc++.h>
using namespace std;
// https://cp-algorithms.com/graph/euler_path.html

int main() {
    int n = 4;
    vector<vector<int>> g = {{0,1,1,1},{1,0,1,0},{1,1,0,1},{1,0,1,0}};
    // reading the graph in the adjacency matrix
    // the adjacency matrix is a square n × n matrix A such that 
    // its element Aij is one when there is an edge from vertex ui to vertex uj, 
    // and zero when there is no edge
    
    vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            deg[i] += g[i][j];
    }

    int first = 0;
    while (first < n && !deg[first])
        ++first; // to find the first vertex that has edges
    if (first == n) {
        cout << -1;  // no edge.
        return 0;
    }

    int v1 = -1, v2 = -1;
    bool bad = false;
    for (int i = 0; i < n; ++i) {
        if (deg[i] & 1) { // to find the 
            if (v1 == -1)
                v1 = i; // the first vertex that has odd degree
            else if (v2 == -1)
                v2 = i; // the second vertex that has odd degree
            else {
                cout << -1;
                return 0;
            }      
        }
    }

    if (v1 != -1)
        ++g[v1][v2], ++g[v2][v1]; // add a fictiious edge resultinf a euler graph

    stack<int> st;
    st.push(first);
    vector<int> res; // answer
    while (!st.empty()) {
        int v = st.top();
        int i;
        for (i = 0; i < n; ++i)
            if (g[v][i])
                break;
        if (i == n) { // no edge | degree is zero
            res.push_back(v);
            st.pop();
        } else {
            --g[v][i];
            --g[i][v];
            st.push(i); // remove edge
        }
    }

    if (v1 != -1) { //  remove the fictitious edge
        for (size_t i = 0; i + 1 < res.size(); ++i) {
            if ((res[i] == v1 && res[i + 1] == v2) ||
                (res[i] == v2 && res[i + 1] == v1)) {
                vector<int> res2;
                for (size_t j = i + 1; j < res.size(); ++j)
                    res2.push_back(res[j]);
                for (size_t j = 1; j <= i; ++j)
                    res2.push_back(res[j]);
                res = res2;
                break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j])
                bad = true;
        }
    }

    if (bad) {
        cout << -1;
    } else {
        for (int x : res)
            cout << x << " ";
    }
}