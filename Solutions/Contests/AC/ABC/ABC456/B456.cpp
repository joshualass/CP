#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<vector<int>> a(3, vector<int>(6));
    for(auto &x : a) for(auto &y : x) cin >> y;

    ld res = 0;

    set<int> good = {4, 5, 6};

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            for(int k = 0; k < 6; k++) {
                set<int> test = {a[0][i], a[1][j], a[2][k]};
                if(test == good) res++;
            }
        }
    }

    cout << fixed << setprecision(10) << res / 216 << '\n';

    return 0;
}
