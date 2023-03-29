// Disjoint set Union
// https://cp-algorithms.com/data_structures/disjoint_set_union.html
// application: problem of painting subarrays

#include <bits/stdc++.h>
#define N 10

int parent[N];

int rank[N];

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
    return 0;
}
