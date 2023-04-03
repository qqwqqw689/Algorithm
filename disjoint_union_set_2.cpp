// Disjoint set Union (support distances up to representative)
// https://cp-algorithms.com/data_structures/disjoint_set_union.html#support-the-parity-of-the-path-length-checking-bipartiteness-online
// application: checking bipartiteness online

#include <bits/stdc++.h>
#define N 10

std::pair<int, int> parent[N];
int rank[N];
bool bipartite[N];

// creates a new set consisting of the new element v
void make_set(int v) {
    parent[v] = std::make_pair(v, 0);
    rank[v] = 0;
    bipartite[v] = true;
}


std::pair<int, int> find_set(int v) {
    /*
    return <the representative of the set, parity>
    */
    if(v != parent[v].first) {
        int parity = parent[v].second;
        parent[v] = find_set(parent[v].first);
        parent[v].second ^= parity;
    }
    return parent[v];
}

void addd_edge(int a, int b) {
    std::pair<int, int> pa = find_set(a);
    a = pa.first;
    int x = pa.second;

    std::pair<int, int> pb =find_set(b);
    b = pb.first;
    int y = pb.second;

    if (a == b) {
        if (x == y)
            // if the ends of the edge lie in the same connected component and have the same parity length to the leader,
            // then adding this edge will produce a cycle of odd length
            bipartite[a] = false;
    } else {
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = std::make_pair(a, x^y^1);
        bipartite[a] &= bipartite[b]; //Is the connected component containing this vertex bipartite?
        if (rank[a] == rank[b] )
            ++rank[a]; 
    }
}

bool is_bipartite(int v) {
    return bipartite[find_set(v).first];
}

int main()
{
    return 0;
}
 
