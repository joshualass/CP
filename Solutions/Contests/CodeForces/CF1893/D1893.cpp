#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n+1);
    map<int,int> pos;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a[i+1].push_back(num);
        if(pos.find(num) == pos.end()) {
        pos[num] = i + 1;

        }
    }

    vector<int> b(m);
    for(auto &x: b) cin >> x;

    sort(b.rbegin(),b.rend());

    for(int i = 0; i < m; i++) {

        if(pos.upper_bound(b[i]) == pos.begin()) {
            a.back().push_back(b[i]);
        } else {
            map<int,int>::iterator it = pos.upper_bound(b[i]);
            it--;
            a[(*it).second - 1].push_back(b[i]);
        }

    }

    for(auto x : a) {
        for(auto y : x) {
            cout << y << " ";
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}