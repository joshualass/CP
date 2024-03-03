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

template<typename T>
std::ostream& operator<<(std::ostream& os, deque<T> v) {
    while(v.size()) {
        os << v.front() << " ";
        v.pop_front();
    }
    return os;
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<ll> adds(n);
    deque<ll> rl;
    deque<ll> lr;
    rl.push_back(0);
    lr.push_back(0);
    for(int i = 0; i < n; i++) {
        if(s[i] == '>') {
            adds[i] = i + 1;
        } else {
            adds[i] = n - i;
            rl.push_back(rl.back() - (n - 1 - i * 2));
        }
    }
    // cout << "rl : " << rl << '\n';
    // cout << "adds : " << adds << '\n';
    for(int i = 0; i < n; i++) {
        ll ans = adds[i];
        if(s[i] == '>') {
            lr.push_back(lr.back() + (n - 1 - i * 2));
        }
        int ms = min(lr.size(),rl.size());
        ans += lr[lr.size() - 1] - lr[lr.size() - ms];
        ans += rl[ms-1] - rl[0];
        if(s[i] == '>' && lr.size() > rl.size()) {
            ans += lr[lr.size() - ms] - lr[lr.size() - ms - 1];
        }
        if(s[i] == '<' && lr.size() < rl.size()) {
            ans += rl[ms] - rl[ms-1];
        }
        cout << ans << " \n"[i == n - 1];
        if(s[i] == '<') {
            rl.pop_front();
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}