#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 2e5;
int n;
int t[2 * N];

void build() {
    for (int i = n - 1; i > 0; --i) {
        t[i] = t[i * 2] & t[i * 2 + 1];
    }
}

void modify(int p, int value) {
    p += n;
    t[p] = value;
    while(p > 1) {
        t[p / 2] = t[p] & t[p ^ 1];
        p /= 2;
    }
}

int query(int l, int r) {
    if(l == r) return 0;
    int ans = INT_MAX;
    l += n;
    r += n;
    while(l < r) {
        if (l % 2 == 1) {
            ans &= t[l];
            l++;
        }
        if (r % 2 == 1) {
            r--;
            ans &= t[r];
        }
        l /= 2;
        r /= 2;
    }
    return ans;
}

// binary search from seg tree n log n log n
// is segment tree the way to solve this problem ?
void solve() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> t[n+i];
    }
    build();
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int l, k; cin >> l >> k;
        --l;
        if(t[l+n] < k) {
            cout << "-1 ";
            continue;
        }
        int lb = l+1;
        int rb = n;
        while(lb < rb) {
            int m = lb + (rb - lb) / 2;
            int q = query(l,m);
            if(q < k) { // not enough, move rb
                rb = m;
            } else {
                if(rb - lb == 1) { //enough, move lb
                    // lb = rb;
                    // rb = lb;
                    q = query(l, rb);
                    if(q >= k) lb = rb;
                    else rb = lb;
                } else {
                    lb = m;
                }
            } 
        }
        // cout << "l: " << l << " lb: " << lb << "\n";
        cout << lb << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}