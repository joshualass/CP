#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve(int casi) {
    
    int n, m; cin >> n >> m;
    vector<vector<int>> vis(n, vector<int>(m));
    
    auto color = [&](int i, int j) -> int {
        if(i >= 0 && i < n && j >= 0 && j < m) {
            if(vis[i][j] == 0) {
                cout << i + 1 << " " << j + 1 << '\n';
                vis[i][j] = 1;
                return 1;
            }
        }
        return 0;
    };

    vector<int> dx = {1, 0, -1, 0}, dy = {0, -1, 0, 1};

    auto color_d = [&](int d) -> void {

        for(int i = 0; i <= d; i++) {
            int c = 0;
            for(int j = -1; j <= 1; j += 2) {
                for(int k = 0; k < 4; k++) {
                    int x = n / 2, y = m / 2;
                    x += dx[k] * d, y += dy[k] * d;
                    x += dx[(k + 1) % 4] * i * j, y += dy[(k + 1) % 4] * i * j;
                    c += color(x, y);
                }
            }
            if(!c) break;
        }

    };

    for(int i = 0; i <= max(n, m) / 2; i++) color_d(i);

    if(casi) cout << '\n';

    // cout << "vis : " << vis << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve(casi);

    return 0;
}