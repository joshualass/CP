//https://codeforces.com/gym/102951/problem/C
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 1e5;
int n;
int t[2 * N];

void build() {
    for (int i = n - 1; i > 0; --i) {
        t[i] = max(t[i * 2], t[i * 2 + 1]);
    }
}

void modify(int p, int value) {
    p += n;
    t[p] = value;
    while(p > 1) {
        t[p / 2] = max(t[p], t[p ^ 1]);
        p /= 2;
    }
}

int query(int l, int r) {
    int ans = 0;
    l += n;
    r += n;
    while(l < r) {
        if (l % 2 == 1) {
            ans = max(ans,t[l]);
            l++;
        }
        if (r % 2 == 1) {
            r--;
            ans = max(ans, t[r]);
        }
        l /= 2;
        r /= 2;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    vector<int> a(n);
    unordered_map<int,int> b;
    for(auto &x: a) cin >> x;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        b[num] = i;
    }
    int most = 0;
    for(int i = 0; i < n; i++) {
        t[i+n] = 0;
    }
    build();
    for(int i = 0; i < n; i++) {
        int idx = b[a[i]];
        modify(idx, query(0,idx)+1);
    }
    cout << query(0,n) << "\n";
    return 0;
}