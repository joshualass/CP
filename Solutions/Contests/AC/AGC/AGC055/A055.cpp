#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    string s; cin >> s;
    vector<map<char,vector<int>>> a(3);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < n; j++) {
            a[i][s[i * n + j]].push_back(i * n + j);
        }
    }

    vector<int> res(n * 3);
    for(int i = 0; i < n; i++) {
        vector<char> b = {'A', 'B', 'C'};
        for(int k = 1; k <= 6; k++) {
            int ok = 1;
            for(int j = 0; j < 3; j++) {
                if(a[j][b[j]].empty()) {
                    ok = 0;
                }
            }
            if(ok) {
                for(int j = 0; j < 3; j++) {
                    res[a[j][b[j]].back()] = k;
                    a[j][b[j]].pop_back();
                }
                break;
            }
            next_permutation(b.begin(), b.end());
        }
    }

    for(int i = 0; i < n * 3; i++) {
        cout << res[i];
    }

    cout << '\n';

    return 0;
}