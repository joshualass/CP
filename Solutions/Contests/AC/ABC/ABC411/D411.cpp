#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;

    vector<int> a(n);
    int s = n;

    vector<int> par(n + 1, -1);
    vector<string> b(n + 1);

    for(int i = 0; i < q; i++) {
        int t; cin >> t;
        if(t == 1) {
            int p; cin >> p;
            p--;
            a[p] = par.size();
            par.push_back(s);
            b.push_back("");
        } else if(t == 2) {
            int p; cin >> p;
            p--;
            string st; cin >> st;
            int prev = a[p];
            a[p] = par.size();
            par.push_back(prev);
            b.push_back(st);
        } else if(t == 3) {
            int p; cin >> p;
            p--;
            s = par.size();
            par.push_back(a[p]);
            b.push_back("");
        }
    }

    vector<string> revres;
    while(s != -1) {
        revres.push_back(b[s]);
        s = par[s];
    }

    string res = "";
    reverse(revres.begin(), revres.end());
    for(auto x : revres) res += x;

    cout << res << '\n';

    return 0;
}
