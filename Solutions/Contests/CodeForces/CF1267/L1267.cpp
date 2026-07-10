#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l, k; cin >> n >> l >> k;
    string s; cin >> s;
    sort(s.begin(), s.end());

    vector<string> res(n);

    int lo = 0;
    int p = 0;
    for(int i = 0; i < l; i++) {
        for(int j = lo; j < k; j++) {
            res[j].push_back(s[p++]);
            if(j > lo && res[j].back() != res[j-1].back()) {
                lo = j;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        while(sz(res[i]) != l) {
            res[i].push_back(s[p++]);
        }
    }

    for(auto x : res) cout << x << '\n';

    return 0;
}
