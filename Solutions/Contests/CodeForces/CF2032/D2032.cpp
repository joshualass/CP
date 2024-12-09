#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> p(n);
    deque<int> dq;
    dq.push_back(0);
    dq.push_back(1);

    int queries = 0;

    auto findparent = [&](int x) -> bool {
        if(dq.size() == 1 || queries == n * 2 - 6) {
            p[x] = dq[0];
            dq.push_back(x);
            dq.pop_front();
            return 1;
        }

        if(dq[0] == 0) {
            cout << "? " << dq[1] << " " << x << endl;
            int res; cin >> res;
            queries++;
            if(res) {
                dq.push_back(x);
                return 1;
            } else {
                dq.pop_front();
                p[x] = dq[0];
                dq.pop_front();
                dq.push_back(x);                
                return 1;
            }
        } else {
            cout << "? " << dq[0] << " " << x << endl;
            int res; cin >> res;
            queries++;
            if(!res) {
                p[x] = dq[0];
                dq.pop_front();
                dq.push_back(x);
                return 1;
            } else {
                return 0;
            }
        }
    };

    for(int i = 2; i < n; i++) {
        while(!findparent(i)) {
            dq.pop_front();
        }
    }

    cout << "!";
    for(int i = 1; i < n; i++) {
        cout << " " << p[i];
    }
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}