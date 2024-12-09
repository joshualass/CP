#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    
    vector<int> f, b;
    int loback = INT_MAX;
    for(int i = 0; i < n; i++) {
        while(f.size() && a[i] < f.back()) {
            b.push_back(f.back() + 1);
            loback = min(loback, f.back() + 1);
            f.pop_back();
        }
        if(a[i] > loback) {
            b.push_back(a[i] + 1);
        } else {
            f.push_back(a[i]);
        }
    }
    for(int x : f) cout << x << " ";
    sort(b.begin(), b.end());
    for(int x : b) cout << x << " ";
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}