#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> a(3);
    for(string &s : a) cin >> s;

    int n = a[0].size();
    vector b(3,vector(3,vector<int>(n)));

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < n; k++) {
                int ok = 1;
                for(int l = 0; l < n; l++) {
                    if(a[i][(l+k)%n] == a[j][l]) {
                        ok = 0;
                        break;
                    }
                }
                b[i][j][k] = ok;
            }
        }
    }

    auto _check = [&](int i, int j, int si, int sj) -> int {
        int t = min(si, sj);
        si -= t;
        sj -= t;

        if(si) {
            return b[j][i][si];
        } else {
            return b[i][j][sj];
        }

    };

    auto check_ok = [&](array<int,3> c) -> bool {
        int ok = 1;
        for(int i = 0; i < 3; i++) {
            for(int j = i + 1; j < 3; j++) {
                ok &= _check(i, j, c[i], c[j]);
            }
        }
        return ok;
    };

    auto gs = [&](int x) -> int {
        return min(x, n - x);
    };

    int res = INT_MAX;
    for(int i = 0; i < 3; i++) {
        for(int j = i + 1; j < 3; j++) {
            for(int k = 0; k < n; k++) {
                for(int l = 0; l < n; l++) {
                    array<int,3> c = {0, 0, 0};
                    c[i] = k;
                    c[j] = l;
                    if(check_ok(c)) {
                        res = min(res, gs(k) + gs(l));
                    }
                }
            }
        }
    }

    cout << (res == INT_MAX ? -1 : res) << '\n';

    return 0;
}
