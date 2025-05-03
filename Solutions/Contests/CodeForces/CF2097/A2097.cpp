#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    map<int,int> m;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        m[x]++;
    }

    int f = 0;
    int prev_way = 2, prev_day = -1;

    for(auto [day, votes] : m) {
        if(prev_day + 1 != day) prev_way = 2;
        if(votes >= 1 << prev_way) f = 1;
        if(votes >= 2 || prev_way == 1) {
            prev_way = 1;
        } else {
            prev_way = 2;
        }
        prev_day = day;
    }

    cout << (f ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}