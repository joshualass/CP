#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> cnts(n + 1);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        cnts[x]++;
    }

    vector<int> r;
    auto add_r = [&](int x) -> void {
        for(int i = 0; i < cnts[x]; i++) r.push_back(x);
    };

    add_r(0);
    vector<int> res;
    for(int i = 0; i < n; i++) {
        if(r.empty()) {
            break;
        }
        res.push_back(r.back());
        r.pop_back();
        add_r(i + 1);
    }

    if(sz(res) == n) {
        cout << "Yes\n";
        cout << res << '\n';
    } else {
        cout << "No\n";
    }

    return 0;
}
