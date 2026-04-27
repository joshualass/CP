#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    vector<int> first;

    auto ask = [&](int r) -> vector<int> {
        if(r == 0 && !first.empty()) return first;
        cout << "? " << r + 1 << endl;
        vector<int> res(n);
        for(int &x : res) cin >> x;
        return res;
    };

    first = ask(0);

    int even = 0;
    for(int x : first) {
        if(x % 2 == 0) {
            even++;
        } else {
            even--;
        }
    }

    vector<array<int,2>> res;

    for(int i = 0; i < n; i++) {
        if(even <= 0 == first[i] % 2 == 0) {
            vector<int> t = ask(i);
            for(int j = 0; j < n; j++) {
                if(t[j] == 1) {
                    res.push_back({i, j});
                }
            }
        }
    }

    assert(sz(res) == n - 1);
    
    cout << "!" << endl;
    for(auto x : res) cout << x[0] + 1 << " " << x[1] + 1 << endl;

    return 0;
}
