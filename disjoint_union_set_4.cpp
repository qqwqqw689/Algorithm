// Disjoint set Union
// https://cp-algorithms.com/data_structures/disjoint_set_union.html#storing-the-dsu-explicitly-in-a-set-list-applications-of-this-idea-when-merging-various-data-structures
// application: Storing the DSU explicitly in a set list

#include <bits/stdc++.h>
#define MAXN 10

std::vector<int> lst[MAXN]
int parent[MAXN];

// creates a new set consisting of the new element v
void make_set(int v) {
    lst[v] = std::vector<int>(1, v);
    poarent[v] = v;
}

// find_set(v) - returns the representative (also called leader) of the set that contains the element v
// Path compression optimization

int find_set(int v) {
    return parent[v];
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (lst[a].size() < lst[b].size())
            std::swap(a, b);
        while(!lst[b].empty()) {
            int v = lst[b].back();
            lst[b].pop_back();
            parebt[v] = a;
            lst[a].push_back(v);
        }
    }
}

int main()
{
    return 0;
}
