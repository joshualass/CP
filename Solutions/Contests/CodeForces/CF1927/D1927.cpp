#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    vector<int> v(n,-1);
    pair<int,int> prev = {-1,-1};
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(prev.first != num) {
            prev = {num,i-1};
        }
        v[i] = prev.second;
    }
    // cout << v << '\n';
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--;r--;
        if(v[r] >= l) {
            cout << v[r] + 1 << " " << r + 1 << '\n';
        } else {
            cout << "-1 -1\n";
        }
    }
    cout << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}