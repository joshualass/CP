#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    vector<vector<int>> nx(n + 1, vector<int>(10, n));

    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j < 10; j++) {
            nx[i][j] = nx[i+1][j];
        }
        nx[i][s[i] - '0'] = i;
    }

    string first = "2025", second = "2026";

    vector<int> d(n + 1), dd(n + 1);

    //[left, [rl, rr)]
    auto add_block = [&](int left, int rl, int rr) -> void {
        int cnt = rr - rl;
        d[left] += cnt;
        dd[rl]--;
        dd[rr]++;
    };

    for(int i = 0; i < n; i++) {
        int l0 = i;
        int r0 = i; //up to excluding r0
        for(char c : first) {
            r0 = nx[r0][c - '0'];
        }
        int l1 = i;
        for(char c : second) {
            l1 = nx[l1][c - '0'];
        }
        int r1 = n;

        // cout << "i : " << i << " l0 : " << l0 << " r0 : " << r0 << " l1 : " << l1 << " r1 : " << r1 << endl;

        add_block(i, l0, r0);
        l1 = max(l1, r0);
        add_block(i, l1, r1);
    }

    ll c = 0, cd = 0;
    for(int i = 0; i < n; i++) {
        c += d[i];
        c += cd;
        cd += dd[i];
        cout << c << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}