#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string res = "";
    for(int i = 0; i < 25; i++) {
        res.append("CR");
    }
    res.push_back('C');
    for(int i = 0; i < 24; i++) {
        res.append("RA");
    }

    int x; cin >> x;
    for(int i = 0; i < x; i++) {
        int f = 0;
        for(int j = 0; j < sz(res); j++) {
            if(res.substr(j, 3) == "CRA") {
                swap(res[j], res[j+2]);
                f = 1;
                break;
            }
        }
        assert(f);
    }

    // cout << sz(res) << endl;

    cout << res << '\n';

    return 0;
}
