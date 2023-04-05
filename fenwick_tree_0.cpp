#include <bits/stdc++.h>
// https://cp-algorithms.com/data_structures/fenwick.html#finding-sum-in-one-dimensional-array
// Finding sum in one-dimensional array

struct FenwickTree {
    std::vector<int> bit; // binary indexed tree bit[i] = sum(A[g(i),i])
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n,0); // n copies of 0
    }

    FenwickTree(std::vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < n; i++) {
            bit[i] += a[i]; // linear construction O(N)
            int r = i | (i+1);
            if (r < n) bit[r] += bit[i];
        }
            
    }

    int sum(int r) {
        int ret = 0;
        for(; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l-1);
    }
};

int main() {
    std::vector a = {0,1,2,3,4,5,6,7,8,9};
    FenwickTree f = FenwickTree(a);
    std::cout << f.sum(4, 9); // 4+5+6+7+8+9=39

    return 0;
}