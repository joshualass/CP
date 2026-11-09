#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int N = 100000;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<array<int,2>> dists(201, {INT_MAX, INT_MIN});

    for(int i = -100; i <= 100; i++) {
        for(int j = -100; j <= 100; j++) {
            if(i * i + j * j <= 10000) {
                dists[i + 100][0] = min(dists[i + 100][0], j);
                dists[i + 100][1] = max(dists[i + 100][1], j);
            }
        }
    }

    // cout << "dists : " << dists << endl;

    int n; cin >> n;
    vector<array<int,2>> a(n);
    vector<vector<int>> b(N);
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        a[i] = {x, y};
        b[x].push_back(y);
    }

    for(int i = 0; i < N; i++) {
        sort(b[i].begin(), b[i].end());
    }

    int f = -1;
    for(int i = 0; i < n; i++) {
        auto [x, y] = a[i];
        int ok = 1;
        // cout << "i : " << i << endl;
        // cout << "coord : " << a[i] << endl;
        for(int j = -100; j <= 100; j++) {
            if(x + j >= 0 && x + j < N) {
                int low = dists[j + 100][0] + y, hi = dists[j + 100][1] + y;
                auto it = lower_bound(b[x + j].begin(), b[x + j].end(), low);
                if(it != b[x + j].end() && j == 0 && *it == y) it++;
                if(it != b[x + j].end() && *it <= hi) {
                    // cout << "found with j : " << j << " it val : " << *it << endl;
                    ok = 0;
                    break;
                }
            }
        }
        if(ok) {
            cout << i + 1 << '\n';
            return 0;
        }
    }

    assert(0);

    return 0;
}
