#include <bits/stdc++.h>
using namespace std;

int main() {
    // input data
    int n = 10;
    vector<int> a = {1,2,3,4,5,6,7,8,9,0};

    // preprocessing
    int len = (int) sqrt (n + .0) + 1; // size of the block and the number of blocks
    vector<int> b (len);
    for (int i=0; i<n; ++i)
        b[i / len] += a[i];

    int l = 3, r = 7;
    int sum = 0;
    int c_l = l / len,   c_r = r / len;
    if (c_l == c_r)
        for (int i=l; i<=r; ++i)
            sum += a[i];
    else {
        for (int i=l, end=(c_l+1)*len-1; i<=end; ++i)
            sum += a[i];
        for (int i=c_l+1; i<=c_r-1; ++i)
            sum += b[i];
        for (int i=c_r*len; i<=r; ++i)
            sum += a[i];
    }

    cout << sum; // 4 + 5 + 6 + 7 + 8
}