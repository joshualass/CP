#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<int> p(n), q(n);
    for(int &x : p) cin >> x;
    for(int &x : q) cin >> x;

    vector<array<int,2>> ops;

    auto add_op = [&](int i, int j) -> void {
        assert(i < j);
        assert(p[i] < p[j]);
        ops.push_back({i + 1, j + 1});
        swap(p[i], p[j]);
    };

    for(int i = n; i >= 1; i--) {
        int cur = -1, tar = -1;
        for(int j = 0; j < n; j++) {
            if(p[j] == i) {
                cur = j;
            }
            if(q[j] == i) {
                tar = j;
            }
        }
        if(cur < tar) {
            cout << "NO\n";
            return;
        }
        vector<int> z;
        z.push_back(tar);
        for(int j = tar + 1; j < cur; j++) {
            if(p[j] > p[z.back()] && p[j] < i) {
                z.push_back(j);
            }
        }
        if(z.back() != cur) z.push_back(cur);
        // cout << "z : " << z << endl;
        for(int i = sz(z) - 2; i >= 0; i--) {
            add_op(z[i], z[i+1]);
        }
        // cout << "i : " << i << " p : " << p << endl;
    }

    cout << "YES\n";
    cout << sz(ops) << '\n';
    for(auto x : ops) cout << x[0] << " " << x[1] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}