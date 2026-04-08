#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<int> b(n + 2);
    int x;
    for(int i = 0; i < k; i++) {
        int p; cin >> p;
        b[p] = 1;
        x = a[p - 1];
    }

    a.insert(a.begin(), x);
    a.push_back(x);
    n += 2;

    vector<int> c;
    int cur = 0;
    for(int i = 0; i < n; i++) {
        if(i && a[i] != a[i - 1]) {
            cur++;
        }
        if(b[i]) {
            c.push_back(cur);
            cur = 0;
        }
    }

    c.push_back(cur);
    cout << max(accumulate(c.begin(), c.end(), 1) / 2, *max_element(c.begin(), c.end())) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}