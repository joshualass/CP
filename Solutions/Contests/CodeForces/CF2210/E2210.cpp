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

const int N = 2e5;
int dsu[N];
int sizes[N];

void dsubuild(int n = N) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
}


void solve() {
    
    int n; cin >> n;
    dsubuild(n);

    ld cost = 0;
    map<array<int,2>, int> m;

    auto ask = [&](int l, int r) -> int {
        if(m.count({l, r})) return m[{l, r}];
        cost += ((ld) 1) / (r - l);
        assert((r - l) % 2 == 0);
        cout << "? " << l + 1 << " " << r << endl;
        int res; cin >> res;
        m[{l, r}] = res;
        return res;
    };

    vector<vector<array<int,2>>> adj(n);

    for(int i = n - 1; i >= 4; i--) {
        if(i % 2 == 0) {
            for(int l = 0; l + i < n; l++) {
                if(find(l) != find(l + i)) {
                    int first = ask(l, l + i);
                    int second = ask(l + 1, l + i + 1);
                    merge(l, l + i);
                    adj[l].push_back({l + i, first != second});
                    adj[l + i].push_back({l, first != second});
                }
            }
        }
    }

    for(int i = 0; i + 1 < n; i++) {
        if(find(i) != find(i + 1)) {
            int res = ask(i, i + 2);
            merge(i, i + 1);
            adj[i].push_back({i + 1, res - 1});
            adj[i+1].push_back({i, res - 1});
        }
    }

    vector<int> res(n);

    auto dfs = [&](auto self, int i, int p, int col) -> void {
        res[i] = col;
        for(auto [c, x] : adj[i]) {
            if(c != p) {
                self(self, c, i, col ^ x);
            }
        }
    };

    auto ts = [&]() -> string {
        string s = "";
        for(int x : res) s.push_back(x + '0');
        return s;
    };

    int done = 0;
    int cur = 0;
    while(!done && cur < 2) {
        dfs(dfs, 0, -1, cur++);
        cout << "! " << ts() << endl;
        cin >> done;
    }

    if(!done) assert(0);

    // cout << "cost : " << cost * n << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> ce;

    auto f = [&](vector<int> a) -> array<int,2> {
        set<int> s;
        int b = 0;
        vector<int> c = a;
        sort(c.begin(), c.end());
        for(int i = 0; i < sz(a); i++) {
            int inv = 0;
            for(int j = 0; j < sz(a); j++) {
                for(int k = j + 1; k < sz(a); k++) {
                    if(a[j] == 1 && a[k] == 0) inv++;
                }
            }
            if(c == a) b = 1;
            s.insert(inv % sz(a));
            rotate(a.begin(), a.begin() + 1, a.end());
        }
        return {sz(s), b};
    };

    auto check = [&](auto self, vector<int> a, int n) -> void {
        if(sz(a) + 1 == n) {
            vector<int> b = a, c = a;
            b.push_back(0);
            c.push_back(1);
            auto fb = f(b), fc = f(c);
            if(f(b) == f(c)) {
                cout << "ce : " << a << endl;
                cout << "fb : " << f(b) << " fc : " << f(c) << endl;
                assert(0);
                // if(f(b)[0] == n) {
                //     if(fb[1] == 0 || fc[1] == 0) {
                //         cout << "ce : " << a << endl;
                //         cout << "fb : " << f(b) << " fc : " << f(c) << endl;
                //         assert(0);
                //     }
                // } else {
                //     cout << "ce : " << a << endl;
                //     cout << "fb : " << f(b) << " fc : " << f(c) << endl;
                //     assert(0);
                // }

            }
            return;
        }
        a.push_back(0);
        self(self, a, n);
        a.back() = 1;
        self(self, a, n);
    };

    for(int n = 6; n <= 16; n += 2) {
        vector<int> a;
        check(check, a, n);
    }

    // cout << "all ok!" << endl;

    // int casi; cin >> casi;
    // while(casi-->0) solve();

    return 0;
}