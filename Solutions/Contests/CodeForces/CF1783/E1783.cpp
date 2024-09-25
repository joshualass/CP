#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;
const int MAXN = 2e5 + 1;


vector<int> divs[MAXN];

void solve() {
    
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    vector<int> p(n + 1);
    for(int i = 0; i < n; i++) {

        if(b[i] < a[i]) {
            p[b[i]]++;
            p[a[i]]--;
        }

    }

    vector<int> ok(n+1,1);
    int c = 0;
    for(int i = 0; i <= n; i++) {
        c += p[i];
        if(c) {
            for(int d : divs[i]) {
                ok[d] = 0;
            }
        }
    }

    cout << reduce(ok.begin(), ok.end()) - 1 << '\n';
    for(int i = 1; i < n + 1; i++) {
        if(ok[i]) {
            cout << i << " ";
        }
    }

    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 1; i < MAXN; i++) {
        for(int j = 1; j * i < MAXN; j++) {
            divs[i*j].push_back(i);
        }
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}