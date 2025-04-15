#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

void solve() {

    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for(auto &x : a) for(auto &y : x) cin >> y;

    vector<int> prev(n);

    for(int i = 0; i < m; i++) {

        vector<int> b(n);
        for(int j = 0; j < n; j++) {
            b[j] = a[j][i];
        }
        sort(b.begin(), b.end());
        
        int p = 0;
        for(int j = 0; j < prev.size(); j++) {
            if(prev[j] > b[p]) p++;
        }
        int left = prev.size() - p;
        prev = vector<int>(b.end() - left, b.end());
    }

    cout << (prev.empty() ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}