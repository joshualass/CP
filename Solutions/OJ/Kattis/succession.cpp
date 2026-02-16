#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    cin.ignore();
    string s;
    getline(cin, s);
    map<string,ld> b;
    stringstream ss(s);
    while(1) {
        string t; ss >> t;
        if(t.empty()) break;
        b[t] = 1;
    }
    vector<array<string,3>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    for(int i = 0; i < 10000; i++) {
        for(int j = 0; j < n; j++) {
            b[a[j][0]] = (b[a[j][1]] + b[a[j][2]]) * .5;
        }
    }

    string best = "";
    for(int i = 0; i < m; i++) {
        string name; cin >> name;
        if(best.empty() || b[name] > b[best]) best = name;
    }

    cout << best << '\n';

    return 0;
}
