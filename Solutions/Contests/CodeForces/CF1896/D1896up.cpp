#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, q; cin >> n >> q;

    set<int> ones;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num == 1) {
            ones.insert(i);
        }
    }

    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int val; cin >> val;
            int sum = n * 2 - ones.size();
            int even = -1, odd = -1;
            if(sum & 1) {
                odd = sum;
                int min_twos = min(*ones.begin(), n - 1 - (*(--ones.end())));
                even = sum - 1 - min_twos * 2;
            } else {
                even = sum;
                if(ones.size()) {
                    int min_twos = min(*ones.begin(), n - 1 - (*(--ones.end())));
                    odd = sum - 1 - min_twos * 2;
                }
            }
            if(val & 1) {
                cout << (odd >= val ? "YES" : "NO") << '\n';
            } else {
                cout << (even >= val ? "YES" : "NO") << '\n';
            }
        } else if(type == 2) {
            int idx, val; cin >> idx >> val;
            idx--;
            ones.erase(idx);
            if(val == 1) {
                ones.insert(idx);
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}