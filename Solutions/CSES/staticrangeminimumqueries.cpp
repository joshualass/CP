#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 2e5;
int n;
int t[2 * N];

void build() {
    for(int i = n-1; i > 0; --i) {
        t[i] = min(t[i * 2], t[i * 2 + 1]);
    }
}

void modify(int p, int value) {
    p += n;
    t[p] = value;
    while(p > 1) {
        t[p / 2] = min(t[p], t[p ^ 1]);
        p /= 2;
    }
}

int query(int l, int r) {
    int ans = INT_MAX;
    l += n;
    r += n;
    while(l < r) {
        if(l % 2 == 1) {
            ans = min(ans, t[l]);
            l++;
        }
        if(r % 2 == 1) {
            r--;
            ans = min(ans,t[r]);
        }
        l /= 2;
        r /= 2;
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q; cin >> n >> q;

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        t[n + i] = num;
    }
    build();

    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        cout << query(--a,b) << '\n';
    }

    return 0;
}
