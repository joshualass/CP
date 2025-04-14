#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    vector<int> ai(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        ai[a[i]] = i;
    }

    for(int &x : b) {
        cin >> x;
        x--;    
    }

    vector<array<int,2>> res;

    auto add_swap = [&](int i, int j) -> void {
        if(i == j) return;
        res.push_back({i + 1, j + 1});
        swap(ai[a[i]], ai[a[j]]);
        swap(a[i], a[j]);
        swap(b[i], b[j]);
    };

    for(int i = 0; i < n; i++) {
        if(a[i] == b[i]) {
            if(n & 1) {
                add_swap(i, n / 2);
            }
        } else {
            int j = ai[b[i]];
            add_swap(n-i-1, j);
        }
    }

    // cout << "a : " << a << '\n';
    // cout << "b : " << b << '\n';

    int ok = 1;
    for(int i = 0; i < n; i++) if(a[i] != b[n-i-1]) ok = 0;
    if(ok) {
        cout << res.size() << '\n';
        for(auto x : res) cout << x[0] << " " << x[1] << '\n';
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