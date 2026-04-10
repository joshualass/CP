#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int inf = 1e9;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;
    
    queue<int> q;
    vector<array<int,2>> par(n, {inf,inf});

    auto add_q = [&](int i, array<int,2> p) -> void {
        if(par[i] == array<int,2>{inf,inf}) {
            par[i] = p;
            q.push(i);
        }
    };

    int hi = n - 1;
    add_q(n - 1, {0, 0});

    int last = -1;

    while(sz(q)) {
        int i = q.front();
        q.pop();
        int nx = i - a[i];

        // cout << "i : " << i << " nx : " << nx << endl;

        //we are done
        if(nx < 0) {
            last = i;
            break;
        }
        for(int j = nx; j < hi; j++) {
            add_q(j + b[j], {i, j});
        }
        hi = min(hi, nx);
    }

    if(last == -1) {
        cout << "-1\n";
        return 0;
    }

    vector<int> res(1, -1);
    while(last != n - 1) {
        res.push_back(par[last][1]);
        last = par[last][0];
    }

    cout << sz(res) << '\n';
    reverse(res.begin(), res.end());
    for(int i = 0; i < sz(res); i++) {
        cout << res[i] + 1 << " \n"[i == sz(res) - 1];
    }

    return 0;
}
