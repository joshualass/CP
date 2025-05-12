#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<bool> vb;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    vvi ans(0);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        vi cans(n, -1);
        int u, v;
        cin >> u >> v;
        u --, v --;
        cans[0] = u, cans[1] = v;
        int ptr = 0;
        for(int j = 2; j < n; j++) {
            while(ptr == u || ptr == v) ptr ++;
            cans[j] = ptr ++;
        }
        ans.push_back(cans);
        ptr = n - 1;
        cans[n - 1] = v, cans[n - 2] = u;
        for(int j = 0; j < n - 2; j++) {
            while(ptr == u || ptr == v) ptr --;
            cans[j] = ptr --;
        }
        ans.push_back(cans);
    }
    cout << "YES\n";
    cout << ans.size() << "\n";
    for(vi& x : ans) {
        for(int y : x) cout << y + 1 << " ";
        cout << "\n";
    }

    return 0;
}