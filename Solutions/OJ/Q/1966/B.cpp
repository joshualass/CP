#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;

    map<int,int> freq, who_has;
    vector<vector<int>> a(n, vector<int>(k));
    for(auto &x : a) for(auto &y : x) cin >> y;

    for(int i = n - 1; i >= 0; i--) {
        for(int x : a[i]) {
            if(who_has.count(x) == 0) who_has[x] = i;
            freq[x]++;
        }
    }

    vector<ld> res(n);
    for(auto [val, who] : who_has) {
        res[who] += ((ld) freq[val]) / (n * k);
    }

    for(int i = 0; i < n; i++) {
        cout << fixed << setprecision(10) << res[i] << "\n";
    }


    return 0;
}
