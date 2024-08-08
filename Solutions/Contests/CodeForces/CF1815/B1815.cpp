#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int query(int l, int r) {
    cout << "? " << l + 1 << " " << r + 1 << endl;
    int d; cin >> d;
    return d;
}

void solve() {
    int n; cin >> n;

    //build graph with 2 queries
    cout << "+ " << n << endl;
    int trash; cin >> trash;
    cout << "+ " << n + 1 << endl;
    cin >> trash;

    //find node farthest from node 1 with n - 1 queries
    array<int,2> a = {-1,-1};
    for(int i = 1; i < n; i++) {
        int dist = query(0,i);
        if(dist > a[0]) {
            a = {dist, i};
        }
    }

    // cerr << "a : " << a << '\n';

    //find dists from farthest node with n - 1 queries
    vector<int> dists(n);
    dists[0] = a[0];
    for(int i = 1; i < n; i++) {
        dists[i] = query(a[1], i);
    }

    // cerr << "dists : " << dists << '\n';

    vector<int> p1(n), p2(n);
    if(n & 1) {
        for(int i = 0; i < n; i++) {
            if(dists[i] & 1) {
                // p1[(n - 2) / 2 - dists[i] / 2] = i;
                p1[i] = (n - 2) / 2 - dists[i] / 2;
                // p2[dists[i] / 2] = i;
                p2[i] = dists[i] / 2;
            } else {
                // p1[(n - 1) / 2 + dists[i] / 2] = i;
                p1[i] = (n - 1) / 2 + dists[i] / 2;
                // p2[n - 1 - dists[i] / 2] = i;
                p2[i] = n - 1 - dists[i] / 2;
            }
        }
    } else {
        for(int i = 0; i < n; i++) {
            if(dists[i] & 1) {
                // p1[(n + 1) / 2 + dists[i] / 2] = i;
                p1[i] = (n + 1) / 2 + dists[i] / 2;
                // p2[dists[i] / 2] = i;
                p2[i] = dists[i] / 2;
            } else {
                // p1[(n - 1) / 2 - dists[i] / 2] = i;
                p1[i] = (n - 1) / 2 - dists[i] / 2;
                // p2[n - 1 - (dists[i] / 2)] = i;
                p2[i] = n - 1 - (dists[i] / 2);
            }
        }
    }

    cout << "!";
    for(int x : p1) {
        cout << " " << x + 1;
    }
    for(int x : p2) {
        cout << " " << x + 1;
    }
    cout << endl;
    cin >> trash;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}