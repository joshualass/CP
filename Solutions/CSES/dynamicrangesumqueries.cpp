#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 2e5;
int n;
ll t[N * 2];

void build() {
    for(int i = n - 1; i > 0; i--) {
        t[i] = t[i * 2] + t[i * 2 + 1];
    }
}

void modify(int p, ll value) {
    p += n;
    t[p] = value;
    while(p > 1) {
        t[p / 2] = t[p] + t[p ^ 1];
        p /= 2;
    }
}

ll query(int l, int r) {
    ll ans = 0; 
    l += n;
    r += n;
    while(l < r) {
        if (l % 2 == 1) {
            ans += t[l];
            l++;
        }
        if(r % 2 == 1) {
            r--;
            ans += t[r];
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
        cin >> t[i + n];
    }
    build();
    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            ll k, u; cin >> k >> u;
            modify(--k,u);
        } else {
            int a, b; cin >> a >> b;
            cout << query(--a,b) << '\n';
        }


    }

    return 0;
}
