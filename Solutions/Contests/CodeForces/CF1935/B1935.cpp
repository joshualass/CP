#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

bool ok(vector<int> v, int targ) {
    set<int> s;
    for(int x : v) {
        if(x < targ) s.insert(x);
    }
    return s.size() == targ;
}

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(int &x : v) cin >> x;
    vector<bool> found(n);
    for(int x : v) found[x] = 1;
    int targ = n;
    for(int i = 0; i < n; i++) {
        if(found[i] == 0) {
            targ = i;
            break;
        }
    }
    // cout << "t : " << targ << '\n';
    vector<vector<int>> segs(2);
    segs[0].push_back(v[0]);
    set<int> in;
    if(v[0] < targ) in.insert(v[0]);
    int start2 = n;
    for(int i = 1; i < n; i++) {
        if(in.size() == targ) {
            segs[1].push_back(v[i]);
            start2 = min(start2,i);
        } else {
            segs[0].push_back(v[i]);
            if(v[i] < targ) in.insert(v[i]);
        }
    }
    // cout << "s0 : " << segs[0] << '\n';
    // cout << "s1 : " << segs[1] << '\n';
    if(ok(segs[0],targ) && ok(segs[1],targ)) {
        cout << "2\n";
        cout << "1 " << start2 << '\n';
        cout << start2 + 1 << " " << n << '\n';
    } else {
        cout << "-1\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}