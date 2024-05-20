#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<ll> p(n);
    for(ll &x : p) cin >> x;
    set<int> s;
    for(int i = 0; i < m; i++) {
        int num; cin >> num;
        s.insert(num);
    }

    ll curr = 0;
    ll res = 0;
    int hi = 0; //hi is exclusive
    for(int lo = 0; lo < n; lo++) {
        if(lo != 0) {
            curr -= p[lo-1];
        }
        if(hi < lo) {
            hi = lo;
            curr = 0;
        }
        while(hi != n) {
            //check that there are no icecream shops between lo and hi
            if((s.lower_bound(lo * 100) != s.end() && (*s.lower_bound(lo * 100)) <= hi * 100) || (s.lower_bound(hi * 100) != s.begin() && (*--s.lower_bound(hi * 100)) >= lo * 100)) break;

            int min_lo = INT_MAX;
            if(s.lower_bound(lo * 100) != s.begin()) {
                int d = lo * 100 - (*--s.lower_bound(lo * 100));
                min_lo = lo * 100 + d - 1;
            }

            int max_hi = INT_MIN;
            if((s.lower_bound(hi * 100)) != s.end()) {
                int d = (*s.lower_bound(hi * 100)) - hi * 100;
                max_hi = hi * 100 - d;
            }

            if(min_lo >= max_hi) {
                curr += p[hi++];
            } else {
                break;
            }
        }
        // cout << "lo : " << lo << " hi : " << hi << '\n';
        res = max(res, curr);
    }
    cout << res << '\n';
    return 0;
}