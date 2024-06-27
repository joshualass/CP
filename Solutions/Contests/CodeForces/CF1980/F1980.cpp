#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//implementation school 

void solve() {

    ll n, m, k; cin >> n >> m >> k;

    // {c, -r, id}
    set<array<ll,3>> s;

    for(int i = 0; i < k; i++) {
        ll r, c; cin >> r >> c;
        s.insert({c,-r,i});
    }

    ll res = 0;
    array<ll,3> prev = {1,-0,-1};
    s.insert(prev);
    s.insert({m+1,-n-1,k});

    int fixer = 0;

    map<array<ll,3>, pair<array<ll,3>,array<ll,3>>> used; //this point is significant in calculating the area, stores the previous point and after point
    for(array<ll,3> a : s) {
        if(a[1] < prev[1]) {
            res += (n + prev[1]) * (a[0] - prev[0]);
            used[a].first = prev;
            used[prev].second = a;
            prev = a;
        }
        if(a[0] == 1) {
            if(fixer == 1) {
                used[prev].first = a;
            }
            fixer++;
        }
    }

    cout << res << '\n';
    vector<ll> ans(k,0);

    for(auto [u , p] : used) {
        if(u[2] >= 0 && u[2] < k) {
            array<ll,3> first = p.first;
            array<ll,3> second = u;
            array<ll,3> third = p.second;
            ll diff = 0;

            diff -= (n + first[1]) * (second[0] - first[0]);
            diff -= (n + second[1]) * (third[0] - second[0]);

            s.erase(u);
            prev = first;
            // cout << "first : " << first << " second : " << second << " third : " << third << '\n';
            for(set<array<ll,3>>::iterator it = s.find(first);;it++) {
                // cout << "it : " << *it << endl;
                array<ll,3> a = *it;
                if(a[1] < prev[1]) {
                    diff += (n + prev[1]) * (a[0] - prev[0]);
                    prev = a;
                }
                if(*it == third) break;
            }
            ans[u[2]] = diff;
            s.insert(u);
        }
    }

    for(int i = 0; i < k; i++) {
        cout << ans[i] << " \n"[i == k - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}