#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int cmd(int i, int p, int d, vector<vector<int>> &adj) {
    int res = d;
    for(int c : adj[i]) {
        if(c != p) {
            res = max(cmd(c,i,d+1,adj),res);
        }
    }
    return res;
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--;b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int maxd = INT_MAX;
    vector<int> centers;
    for(int i = 0; i < n; i++) {
        int md = cmd(i, -1, 0, adj);
        if(md < maxd)  {
            centers.clear();
            centers.push_back(i);
            maxd = md;
        } else if(md == maxd) {
            centers.push_back(i);
        }
    }

    // cout << "centers : " << centers << '\n';

    if(centers.size() == 2) {
        if(maxd % 2 == 0) {
            cout << maxd << '\n';
            for(int c : centers) {
                for(int i = 1; i < maxd; i += 2) {
                    cout << c + 1 << " " << i << '\n';
                }
            }
            return;
        }
    }

    cout << maxd + 1 << '\n';
    for(int i = 0; i <= maxd; i++) {
        cout << centers[0] + 1 << " " << i << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}