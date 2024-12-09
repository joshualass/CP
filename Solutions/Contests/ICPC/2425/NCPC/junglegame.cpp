#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n; cin >> n;

    vector<array<int,2>> a(n);
    vector<array<int,2>> vis(n*2+1);
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 2; j++) {
            cin >> a[i][j];
            vis[a[i][j]][j] = 1;
        }
    }

    if(n == 1 && a[0][0] == 2 && a[0][1] == 2) {
        cout << "NO\n";
        return 0;
    }

    int missingcol = -1, missingval = -1;

    for(int col = 0; col < 2; col++) {
        for(int i = 2; i <= n * 2; i += 2) {
            if(vis[i][col] == 0) {
                missingcol = col;
                missingval = i;
            }
        }
    }

    //case where 2n permutation
    vector<array<int,2>> res(n);
    if(missingcol == -1) {
        int idx = -1;
        for(int i = 0; i < n; i++) {
            if(a[i][1] == n * 2) {
                idx = i;
                break;
            }
        }
        int base = a[idx][0] / 2;
        for(int i = 0; i < n - 1; i++) {
            res[i] = {base, i + 1};
        }
        int last = (base & 1) + 1;
        int last2 = -1;
        for(int i = 0; i < n; i++) {
            if(a[i][0] == last * 2) {
                if(a[i][1] / 2 + 1 <= n) {
                    last2 = a[i][1] / 2 + 1;
                } else {
                    last2 = a[i][1] / 2 - 1;
                }
            }
        }
        res[n-1] = {last,last2};
    } else {
        for(int i = 0; i < n; i++) {
            for(int col = 0; col < 2; col++) {
                if(col == missingcol) {
                    res[i][col] = missingval / 2;
                } else {
                    res[i][col] = i + 1;
                }
            }
        }
    }

    cout << "YES\n";
    for(auto x : res) {
        cout << x[0] << " " << x[1] << '\n';
    }
    
    return 0;
}