#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
spent a very long trying to construct a nice construction by hand
my intuition was heavily guided by that from hamiltonian cycle atcoder problem
however, this was not necessary

The important fact to use is that floor(k / 3) <= n
A lot of the intuition was great in that it is possible iff all elements of the k array is 1

With this, with each gcd, we are able to construct a sequence of all the elements resulting in the gcd

the trick is that we are able to construct this by for each gcd and offset, end at a low-ish element in the lower 2/3 of n
and then we can always add the k for the gcd contribution. This works because there always exist 2 elements in the lower 2/3
This greedy construction is not very obvious x_X --- too much thinking of the optimal hamiltonian paths
*/

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
    
    int n, m; cin >> n >> m;
    vector<int> a(m);
    int g = 0;
    for(int &x : a) {
        cin >> x;
        g = gcd(g, x);
    }

    if(g != 1) {
        cout << "-1\n";
        return;
    }

    sort(a.begin(), a.end());

    vector<array<int,2>> b; // {gcd, k}
    b.push_back({0, 0});
    for(int x : a) {
        int nxg = gcd(b.back()[0], x);
        if(nxg != b.back()[0]) {
            b.push_back({nxg, x});
        }
    }

    b[0][0] = n;

    // cout << "b : " << b << endl;

    vector<int> res;

    auto dfs = [&](auto self, int idx, int start) -> void {
        auto [g, k] = b[idx];
        int os = start % g;
        if(idx == 1) {
            res.push_back(start);
            for(int i = os + ((n + g - 1) / g - 1) * g; i >= 0; i -= g) {
                if(i != start && i < n) res.push_back(i);
            }
        } else {
            self(self, idx - 1, start);
            for(int i = 1; i < b[idx - 1][0] / g; i++) {
                self(self, idx - 1, res.back() + b[idx][1]);
            }
        }
    };

    dfs(dfs, sz(b) - 1, 0);

    cout << res << '\n';

    // cout << endl;

    // cout << "sz : " << sz(res) << endl;

    assert(sz(res) == n);
    for(int i = 1; i < n; i++) {
        int f = 0;
        for(int x : a) {
            if(abs(res[i] - res[i - 1]) % x == 0) f = 1;
        }
        if(f == 0) {
            cout << "i : " << i << endl;    
            assert(0);
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