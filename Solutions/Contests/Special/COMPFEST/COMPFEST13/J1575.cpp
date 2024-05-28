#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k; cin >> n >> m >> k;
    vector<map<int,int>> v(m); //stores at index which direction

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int num; cin >> num;
            if(num != 2) {
                v[j][i] = num;
            }
        }
    }

    for(int i = 0; i < k; i++) {
        int c; cin >> c;
        c--;
        int y = 0;
        // cout << "c : " << c << endl;
        while(v[c].lower_bound(y) != v[c].end()) {
            // cout << "c : " << c << endl;
            pair<int,int> p = *v[c].lower_bound(y);
            v[c].erase(v[c].lower_bound(y));
            // break;
            // cout << "c : " << c << endl;
            y = p.first;

            if(p.second == 1) {
                c++;
            } else {
                c--;
            }
        }
        cout << c + 1 << " \n"[i == k - 1];
    }

    // cout << "ended" << endl;

    return 0;
}