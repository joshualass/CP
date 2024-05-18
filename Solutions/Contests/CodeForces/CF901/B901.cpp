#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // int n; cin >> n;
    // set<int> fib = {1,2,3,5,8,13,21,34,55,89,144};
    // cout << n << '\n';
    // for(int i = 0; i < n; i++) {
    //     cout << "0 ";
    // }
    // cout << "1\n";
    // cout << n - 1 << '\n';
    // vector<int> res;
    // for(int i = 1; i <= n; i++) {
    //     if(fib.count(i)) {
    //         // cout << "-1";
    //         res.push_back(1);
    //     } else {
    //         res.push_back(-1);
    //         // cout << "1";
    //     }
    //     // cout << " \n"[i == n - 1];
    // }
    // reverse(res.begin(), res.end());
    // for(int i = 0; i < n; i++) {
    //     cout << res[i] << " \n"[i == n - 1];
    // }

    int n; cin >> n;

    vector<vector<int>> res;
    res.push_back({1});
    res.push_back({0,1});
    for(int i = 2; i < 200; i++) {
        res.push_back({});
        res.back().resize(i+1);
        for(int j = 0; j < i - 1; j++) {
            res[i][j] = res[i-2][j];
        }
        for(int j = 0; j < i; j++) {
            res[i][j+1] += res[i-1][j];
            res[i][j+1] %= 2;
        }
    }

    cout << n << '\n';
    for(int i = 0; i <= n; i++) {
        cout << res[n][i] << " \n"[i == n];
    }
    cout << n - 1 << '\n';
    for(int i = 0; i < n; i++) {
        cout << res[n-1][i] << " \n"[i == n - 1];
    }

    return 0;
}