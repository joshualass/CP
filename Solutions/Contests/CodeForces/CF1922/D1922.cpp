#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<int> d(n);
    for(int &x : a) cin >> x;
    for(int &x : d) cin >> x;
    set<int> alive;
    set<int> tocheck;
    for(int i = 0; i < n; i++) {
        alive.insert(i);
        tocheck.insert(i);
    }
    for(int r = 0; r < n; r++) {
        set<int> nextcheck;
        set<int> dienow;
        for(int x : tocheck) {
            if(alive.count(x)) {
                int attack = 0;
                set<int>::iterator lit = alive.lower_bound(x);
                set<int>::iterator hit = alive.upper_bound(x);
                if(lit != alive.begin()) {
                    attack += a[*--lit];
                }
                if(hit != alive.end()) {
                    attack += a[*hit];
                }
                if(attack > d[x]) {
                    dienow.insert(x);

                    nextcheck.insert(x);
                }
            }
        }
        for(int x : dienow) {
            alive.erase(x);
        }
        tocheck.clear();
        for(int x : nextcheck) {
            set<int>::iterator lit = alive.lower_bound(x);
            set<int>::iterator hit = alive.upper_bound(x);
            if(lit != alive.begin()) {
                tocheck.insert(*--lit);
            }
            if(hit != alive.end()) {
                tocheck.insert(*hit);
            }
        }
        cout << dienow.size() << " \n"[r == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}