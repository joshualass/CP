#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<string> mat(n);
    int onecnt = 0;
    for(auto &x : mat) cin >> x, onecnt += count(x.begin(), x.end(), '1');

    int rowposs = 0, colposs = 0;
    for(int i = 0; i < n; i++) {
        int cnt = 0;
        for(int j = 0; j < n; j++) {
            cnt += mat[i][j] == '1';
        }
        int ops = n - cnt;
        int left = onecnt - cnt;
        if(ops + left <= n) rowposs = 1;
    }

    for(int i = 0; i < n; i++) {
        int cnt = 0;
        for(int j = 0; j < n; j++) {
            cnt += mat[j][i] == '1';
        }
        int ops = n - cnt;
        int left = onecnt - cnt;
        if(ops + left <= n) colposs = 1;
    }

    if(colposs && rowposs) {
        cout << "+\n";
    } else if(colposs) {
        cout << "|\n";
    } else {
        cout << "-\n";
    }


    return 0;
}