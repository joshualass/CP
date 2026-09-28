#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll inf = 1e18;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<array<ll,2>> b(n);
    vector<ll> pre(n * 2, inf), suf(n * 2, inf);

    for(int i = 0; i < n; i++) {
        for(auto &x : b[i]) cin >> x;
        b[i][0]--;
        
        suf[b[i][0]] = min(suf[b[i][0]], a[i]);
        pre[b[i][1] - 1] = min(pre[b[i][1] - 1], a[i]);
    }

    // cout << "start\n";
    // cout << "pre : " << pre << '\n';
    // cout << "suf : " << suf << '\n';

    for(int i = 1; i < n * 2; i++) {
        pre[i] = min(pre[i], pre[i-1]);
    }

    for(int i = n * 2 - 2; i >= 0; i--) {
        suf[i] = min(suf[i], suf[i+1]);
    }

    // cout << "after\n";
    // cout << "pre : " << pre << '\n';
    // cout << "suf : " << suf << '\n';

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int s, t; cin >> s >> t;
        s--; t--;

        int ls = b[s][0], rs = b[s][1];
        int lt = b[t][0], rt = b[t][1];

        ll res = LLONG_MAX;
        if(lt >= rs || ls >= rt) {
            // cout << "i : " << i << "case 0\n";
            res = 0;
        }

        if(max(rs, rt) < n * 2) {
            // cout << "i : " << i << "case 1\n";
            // cout << "option : " << suf[max(rs, rt)] << '\n';
            res = min(res, suf[max(rs, rt)]);
        }

        if(min(ls, lt) > 0) {
            // cout << "i : " << i << "case 2\n";
            // cout << "option : " << pre[min(ls, lt) - 1] << '\n';
            res = min(res, pre[min(ls, lt) - 1]);
        }

        if(rs < n * 2 && lt > 0) {
            // cout << "i : " << i << "case 3\n";
            // cout << "option : " << suf[rs] + pre[lt-1] << '\n';
            res = min(res, suf[rs] + pre[lt-1]);
        }

        if(rt < n * 2 && ls > 0) {
            // cout << "i : " << i << "case 4\n";
            // cout << "option : " << suf[rt] + pre[ls - 1] << '\n';
            res = min(res, suf[rt] + pre[ls - 1]);
        }

        if(res < inf) {
            cout << a[s] + a[t] + res << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
