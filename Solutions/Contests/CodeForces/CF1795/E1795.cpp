#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<ll> getpre(vector<int> &a) {
    vector<ll> p(a.size());

    //a[i] - i, idx
    stack<array<int,2>> lim;
    lim.push({1,-1});

    for(int i = 0; i < a.size(); i++) {
        while(lim.size() && a[i] - i < lim.top()[0]) {
            lim.pop();
        }

        if(lim.size()) {
            array<int,2> stop = lim.top();
            int l = i - stop[1];
            ll tri = 1LL * ((a[i] - (l - 1)) + a[i]) * l / 2;
            p[i] = tri;
            // cout << "i : " << i << " l : " << l << " tri : " << tri << '\n';
            if(stop[1] >= 0) {
                // cout << "add p : " << p[stop[1]] << '\n';
                p[i] += p[stop[1]];
            }
        } else {
            ll tri = (1 + a[i]) * (a[i]) / 2;
            p[i] = tri;
        }

        lim.push({a[i] - i, i});
    }

    // cout << "a : " << a << '\n';
    // cout << "p : " << p << '\n';
    return p;
}

void solve(int t) {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<ll> p1 = getpre(a);
    reverse(a.begin(),a.end());
    vector<ll> p2 = getpre(a);
    reverse(p2.begin(), p2.end());
    reverse(a.begin(), a.end());

    ll res = LLONG_MAX;
    ll sijag = accumulate(a.begin(), a.end(), 0LL);

    for(int i = 0; i < n; i++) {
        ll power = a[i];
        ll damage = p1[i] + p2[i] - a[i];
        ll remainder = sijag - damage;
        res = min(res, power + remainder);
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int bruh; cin >> bruh;
    for(int i = 1; i <= bruh; i++) {
        solve(i);
    }

    return 0;
}