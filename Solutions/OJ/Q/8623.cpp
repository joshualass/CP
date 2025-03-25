#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        int best = 301;
        for(int j = 0; j < 3; j++) {
            int t; cin >> t;
            if(t != -1) best = min(best, t);
        }
        a[i] = best;
    }
    sort(a.begin(),a.end());
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += a[i];
        if(sum > 300) {
            cout << i << '\n';
            return 0;
        }
    }

    cout << n << '\n';

    return 0;
}