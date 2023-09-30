#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n, m, k; cin >> n >> m >> k;
    vector<int> J(n);
    vector<int> G(m);
    for(auto &x: J) cin >> x;
    for(auto &x: G) cin >> x;
    sort(J.begin(),J.end());
    sort(G.begin(),G.end());
    if(J[0] < G.back()) {
        swap(J[0], G.back());
    }
    sort(J.begin(),J.end());
    sort(G.begin(),G.end());
    if(k & 1) {
        cout << accumulate(J.begin(),J.end(),0LL) << "\n";
    } else {
        if(G[0] < J.back()) {
            swap(G[0],J.back());
        }
        cout << accumulate(J.begin(),J.end(),0LL) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}