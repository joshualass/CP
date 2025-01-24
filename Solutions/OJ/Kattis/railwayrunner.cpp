#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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
    for(auto x : v) os << x << "\n";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<string> a(n);
    for(auto &x : a) cin >> x;
    vector<array<int,3>> vis(n);
    for(int i = 0; i < 3; i++) if(a[0][i] == '.') vis[0][i] = 1;
    
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < 2; j++) {
            if(vis[i][j] && a[i][j] == a[i][j+1] && a[i][j] != '/') {
                vis[i][j+1] = 1;
            }
        }
        for(int j = 2; j > 0; j--) {
            if(vis[i][j] && a[i][j-1] == a[i][j] && a[i][j] != '/') {
                vis[i][j-1] = 1;
            }
        }
        for(int j = 0; j < 3; j++) {
            if(vis[i][j]) {
                if(a[i][j] == '*') {
                    vis[i+1][j] = 1;
                }
                if(a[i][j] == '.' && a[i+1][j] == '.') vis[i+1][j] = 1;
                if(a[i+1][j] == '/') {
                    vis[i+2][j] = 1;
                }
            }
        }
    }

    // cout << "vis\n" << vis;

    cout << (accumulate(vis[n-1].begin(), vis[n-1].end(),0) ? "YES" : "NO") << '\n';

    return 0;
}