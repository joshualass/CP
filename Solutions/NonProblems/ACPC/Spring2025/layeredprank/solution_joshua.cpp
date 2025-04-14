#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k; cin >> n >> m >> k;
    vector<array<int,4>> a(k);
    set<int> x, y;
    for(int i = 0; i < k; i++) {
        for(auto &z : a[i]) cin >> z;
        x.insert(a[i][0]);
        x.insert(a[i][2]);
        y.insert(a[i][1]);
        y.insert(a[i][3]);
    }

    map<int,int> cx, cy;
    vector<int> ax, ay;
    for(int z : x) {
        cx[z] = ax.size();
        ax.push_back(z);
    }

    for(int z : y) {
        cy[z] = ay.size();
        ay.push_back(z);
    }

    vector<vector<int>> board(x.size(), vector<int>(y.size(), -1));

    for(int i = 0; i < k; i++) {

        a[i][0] = cx[a[i][0]];
        a[i][1] = cy[a[i][1]];
        a[i][2] = cx[a[i][2]];
        a[i][3] = cy[a[i][3]];

        for(int j = a[i][0]; j < a[i][2]; j++) {
            for(int l = a[i][1]; l < a[i][3]; l++) {
                board[j][l] = i;
            }
        }

    }

    vector<ll> res(k);

    for(int i = 0; i < x.size(); i++) {
        for(int j = 0; j < y.size(); j++) {
            if(board[i][j] != -1) {
                res[board[i][j]] += 1LL * (ax[i+1] - ax[i]) * (ay[j+1] - ay[j]);
            }
        }
    }

    for(ll x : res) cout << x << '\n';

    return 0;
}
