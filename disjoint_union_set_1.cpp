// Disjoint set Union(support distances up to representative)
// https://cp-algorithms.com/data_structures/disjoint_set_union.html#support-distances-up-to-representative
// application: support dstances up to representative

#include <bits/stdc++.h>
#define N 10

std::pair<int, int> parent[N];

int rank[N];

// creates a new set consisting of the new element v
void make_set(int v) {
    parent[v] = std::make_pair(v, 0);
    rank[v] = 0;
}

std::pair<int, int> find_set(int v) {
    /*
    return <the representative of the set, the distance to it>
    */
    if(v != parent[v].first) {
        int len = parent[v].second;
        parent[v] = find_set(parent[v].first);
        parent[v].second += len;
    }
    return parent[v];
}

void union_sets(int a, int b) {
    a = find_set(a).first;
    b = find_set(b).first;
    if (a != b) {
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = std::make_pair(a, 1);
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

int main()
{
    return 0;
}
