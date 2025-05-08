#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<ld> vd;

#define rep(i, a, b) for(int i = 0; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;
    vd tf(n), t(n), f(n);
    vi indeg(n, false);
    vvi c(n);
    for(int i = 0; i < n; i++){
        ld _t, _f;
        int d;
        cin >> _t >> _f >> d;
        tf[i] = _t / _f, t[i] = _t, f[i] = _f;
        d --;
        if(d != -1) c[d].push_back(i), indeg[i] = 1;
    }    
    priority_queue<pair<ld, int>> q;
    for(int i = 0; i < n; i++){
        if(indeg[i] == 0) {
            q.push({-tf[i], i});
        }
    }
    vi ord(0);
    while(q.size() != 0){
        int cur = q.top().second;
        q.pop();
        ord.push_back(cur);
        for(int x : c[cur]) {
            indeg[x] --;
            if(indeg[x] == 0) q.push({-tf[x], x});
        }
    }
    for(int i = 0; i < ord.size(); i++) cout << ord[i] + 1 << "\n";
    // ld ans = 0;
    // ld p = 1, sum = 0;
    // for(int i = 0; i < n; i++){
    //     sum += t[i];
    //     ans += sum * p * f[i];
    //     p *= (1.0 - f[i]);
    // }
    // cout << fixed << setprecision(10) << ans << "\n";

    return 0;
}