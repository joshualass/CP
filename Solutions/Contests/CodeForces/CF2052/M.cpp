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
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {

    int n; cin >> n;
    vector<int> a(n * 2);
    vector<array<int,2>> atidx(n, {-1,-1});

    for(int i = 0; i < n * 2; i++) {
        int x; cin >> x;
        x--;
        a[i] = x;
        for(int j = 0; j < 2; j++) {
            if(atidx[x][j] == -1) {
                atidx[x][j] = i;
                break;
            }
        }
    }

    // cout << "start : " << a << '\n';

    vector<vector<int>> adj(n * 2);
    for(int i = 1; i < n * 2; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<array<int,2>> pairings;
    vector<int> pi(n * 2, -1);
    auto dfs = [&](auto self, int i, int p) -> int {
        int fc = -1;
        for(int c : adj[i]) {
            if(c != p) {
                int r = self(self, c, i);
                if(r == 0) {
                    fc = c;
                }
            }
        }
        if(fc == -1) {
            return 0;
        } else {
            pi[i] = pairings.size();
            pi[fc] = pairings.size();
            pairings.push_back({fc, i});
            return 1;
        }
    };

    dfs(dfs, 0, -1);

    // cout << "pairings : " << pairings << '\n';

    set<int> bad; 
    for(int i = 0; i < n * 2; i++) {
        if(pi[i] == -1) {
            bad.insert(i);
        }
    }

    vector<array<int,2>> swaps;

    auto doswap = [&](int x, int y) -> void {
        swaps.push_back({x, y});
        int i0 = -1, i1 = -1;
        for(int j = 0; j < 2; j++) {
            if(atidx[a[x]][j] == x) i0 = j;
            if(atidx[a[y]][j] == y) i1 = j;
        }

        swap(atidx[a[x]][i0], atidx[a[y]][i1]);
        swap(a[x], a[y]);
        // cout << "aswap : " << a << '\n';
    };

    auto dfsswap = [&](auto self, int i) -> void {
        int i0 = -1, i1 = -1;
        bad.erase(i);

        for(int j = 0; j < 2; j++) {
            if(atidx[a[i]][j] != i) i0 = atidx[a[i]][j];
        }

        if(pi[i] == -1) {
            if(pi[i0] != -1) {
                assert(bad.size());
                i1 = *bad.begin();
                bad.erase(i1);
            } else {
                bad.erase(i0);
            }
        } else {
            int p = pi[i];
            for(int j = 0; j < 2; j++) {
                if(pairings[p][j] != i) i1 = pairings[p][j];
            }
        }

        if(i1 != -1 && i0 != i1) {
            doswap(i0,i1);
            self(self, i0);
        }
    };

    for(int i = 0; i < n * 2; i++) {
        dfsswap(dfsswap, i);
    }

    cout << swaps.size() << '\n';
    for(auto s : swaps) {
        cout << s[0] + 1 << " " << s[1] + 1 << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

/*
3
3
2 1 3 3 2 1
1 2
1 3
1 4
2 5
3 6
7
7 1 1 2 2 3 3 4 5 4 6 5 7 6
1 2
1 3
1 4
1 5
2 6
2 7
2 8
3 9
3 10
4 11
4 12
5 13
5 14
10
10 1 1 2 2 3 4 3 4 5 6 6 7 7 8 5 8 9 10 9
1 2
1 3
1 4
1 5
1 6
1 7
2 8
2 9
2 10
3 11
3 12
4 13
4 14
5 15
5 16
6 17
6 18
7 19
7 20

3
2
1 1 2 2
1 2
2 3
3 4
4 
1 1 2 3 2 4 4 3
1 2
2 3
2 4
1 5
5 6
6 7
7 8
4
1 2 3 4 4 2 3 1
1 2
2 3
3 4
4 5
5 6
6 7
7 8

*/