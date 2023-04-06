#include <bits/stdc++.h>
// https://cp-algorithms.com/data_structures/fenwick.html#finding-sum-in-one-dimensional-array
// Finding sum in one-dimensional array

struct FenwickTree {
    std::vector<int> bit; // binary indexed tree bit[i] = sum(A[g(i),i])
    int n;

    FenwickTree(int nn) {
        this->n = nn + 1;
        bit.assign(nn + 1,0); // nn copies of 0
    }

    FenwickTree(std::vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < n; i++) {
            add(i, a[i]);
        }
            
    }

    int sum(int r) {
        int ret = 0;
        for(++r; r > 0; r -= r & -r)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l-1);
    }

    void add(int idx, int delta) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += delta;
    }
};

int main() {
    std::vector a = {0,1,2,3,4,5,6,7,8,9};
    FenwickTree f = FenwickTree(a);
    std::cout << f.sum(4, 9); // 4+5+6+7+8+9=39

    return 0;
}
