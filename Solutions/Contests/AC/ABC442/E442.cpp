#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<pair<ld,array<int,3>>> a(n);
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        a[i] = {-atan2l(y, x), {x, y, i}};
    }    

    sort(a.begin(), a.end());
    vector<array<int,2>> b;
    ld prev = -4;
    vector<int> id(n);
    for(auto [d, info] : a) {
        auto [x, y, i] = info;
        if(d > prev) {
            prev = d;
            if(b.empty()) {
                b.push_back({});
            } else {
                b.push_back({b.back()[1], b.back()[1]});
            }
        }
        b.back()[1]++;
        id[i] = sz(b) - 1;
    }

    // cout << "id : " << id << endl;

    for(int qq = 0; qq < q; qq++) {
        int l, r; cin >> l >> r;
        l--; r--;
        if(id[l] <= id[r]) {
            // cout << "case leq\n";
            cout << b[id[r]][1] - b[id[l]][0];
        } else {
            // cout << "case swap\n";
            cout << n - (b[id[l]][0] - b[id[r]][1]);
        }
        cout << "\n";
    }

    return 0;
}
