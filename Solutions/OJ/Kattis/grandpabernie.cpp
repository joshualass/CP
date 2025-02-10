#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    map<string,vector<int>> m;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        int y; cin >> y;
        m[s].push_back(y);
    }

    for(auto [a,b] : m) {
        vector<int> c = b;
        sort(c.begin(),c.end());
        m[a] = c;
    }

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        string s; cin >> s;
        int k; cin >> k;
        cout << m[s][k-1] << '\n';
    }

    return 0;
}