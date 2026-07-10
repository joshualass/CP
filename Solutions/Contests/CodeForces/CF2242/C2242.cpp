#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k; cin >> n >> k;

    vector<array<int,2>> cnts;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(cnts.empty() || x != cnts.back()[1]) {
            cnts.push_back({0, x});
        }
        cnts.back()[0]++;
    }

    sort(cnts.rbegin(), cnts.rend());

    int res = 0;
    int s = n;

    int isnew = 1;
    
    while(sz(cnts)) {
        if(isnew && (k >= s) && (k - s) % sz(cnts) == 0) {
            isnew = 0;
            res++;   
        }
        for(auto &x : cnts) {
            x[0]--;
            s--;
        }
        while(sz(cnts) && cnts.back()[0] == 0) {
            cnts.pop_back();
            isnew = 1;
        }
    }
    
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}