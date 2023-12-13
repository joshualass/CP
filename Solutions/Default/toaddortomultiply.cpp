#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool operator<(const vector<int>& lhs, const vector<int>& rhs) {
    if(lhs.size() > rhs.size()) {
        return 0;
    }
    if(lhs.size() < rhs.size()) {
        return 1;
    }
    for(int i = 0; i < lhs.size(); i++) {
        if(lhs[i] < rhs[i]) {
            return 1;
        } else if(lhs[i] > rhs[i]) {
            return 0;
        }
    }
    return 0;
}

vector<int> solve(ll a, ll m, ll p, ll q, ll r, ll s, ll i) {
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll a, m, p, q, r, s;
    cin >> a >> m >> p >> q >> r >> s;
    int casi = 1;
    while(a != 0) {
        cout << "Case " << (casi++) << ": ";
        if(m == 1) {
            ll adds = (r - p + a - 1) / a;
            if(q + adds * a <= s) {
                cout << adds << "a\n";
            } else {
                cout << "impossible\n";
            }
        }
        vector<int> ans(69);
        for(int i = 0; i < 31; i++) {
            vector<int> tri = solve(a,m,p,q,r,s,i);
            if(tri.size() && tri[0] == -1) continue;
            if(tri < ans) {
                ans = tri;
            }
        }   

        cin >> a >> m >> p >> q >> r >> s;
    }

    return 0;
}