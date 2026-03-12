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
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

void solve() {
    
    

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int len = 10;
    vector<set<array<int,2>>> a(len + 1);


    auto dfs = [&](auto self, int cx, int cy, int sx, int sy, int idx) -> void {
        a[idx].insert({sx, sy});
        if(idx < len) {
            self(self, cx + 1, cy, sx + (cx + 1), sy + cy, idx + 1);
            self(self, -cx, 1 - cy, sx - cx, sy + (1 - cy), idx + 1);
        }
    };

    dfs(dfs, 0, 0, 0, 0, 0);

    for(int i = 1; i <= len; i++) cout << "i : " << i << " map : " << a[i] << endl;

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}