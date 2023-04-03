// Disjoint set Union
// https://cp-algorithms.com/data_structures/disjoint_set_union.html#arpa
// application: offline range minimum query

#include <bits/stdc++.h>
#define N 10

int parent[N];
int rank[N];
int a[N];
struct Query {
    int L, R, idx;
};

std::vector<int> answer;
std::vector<vector<Query>> container; // container[i] contains all queries with R == i;
 
// creates a new set consisting of the new element v
void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

// find_set(v) - returns the representative (also called leader) of the set that contains the element v
// Path compression optimization

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

int main()
{
    std::stack<int> s; // the top is always the small element index in [0, i-1] 
    for (int i = 0; i < n; i++) {
        while (!s.empty() && a[s.top()] > a[i]) {
            parent[s.top()] = i;
            s.pop();
        }
        s.push(i);
        for (Query q : container[i]) {
            answer[q.idx] = a[find_set[q.L]];
        }
    }
    
    return 0;
}
