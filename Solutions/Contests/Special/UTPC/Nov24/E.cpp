#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<array<int,2>>> a;

    for(int i = 0; i < n; i++) {
        vector<array<int,2>> b;
        if(i) {
            b.push_back({0,i});
        }
        for(int j = 1, k = i - 1; j < k; j++, k--) {
            b.push_back({j,k});
        }
        for(int j = i + 1, k = n - 1; j < k; j++, k--) {
            b.push_back({j,k});
        }
        if(b.size()) {
            a.push_back(b);
        }
    }

    cout << a.size() << '\n';
    for(auto x : a) {
        cout << x.size() << '\n';
        for(auto [b, c] : x) {
            cout << b + 1 << " " << c + 1 << '\n';
        }
    }

    return 0;
}