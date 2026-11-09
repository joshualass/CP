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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, r; cin >> k >> r;
    int n = k * 3;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 0; i < r; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> vis(n);
    vector<array<int,3>> res;
    vector<int> singles;
    vector<array<int,2>> doubles;
    int ok = 1;

    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            queue<int> q;
            q.push(i);
            vector<int> here;
            while(sz(q)) {
                int x = q.front();
                q.pop();
                if(vis[x]) continue;
                vis[x] = 1;
                here.push_back(x);
                for(int to : adj[x]) q.push(to);
            }
            if(sz(here) == 1) {
                singles.push_back(here[0]);
            } else if(sz(here) == 2) {
                doubles.push_back({here[0], here[1]});
            } else if(sz(here) == 3) {
                res.push_back({here[0], here[1], here[2]});
            } else {
                ok = 0;
            }
        }
    }

    sort(singles.begin(), singles.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return a[lhs] < a[rhs];
    });

    sort(doubles.begin(), doubles.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        auto get_score = [&](array<int,2> z) -> ll {
            return a[z[0]] + a[z[1]];
        };
        return get_score(lhs) < get_score(rhs);
    });

    
    while(ok && sz(singles) && sz(singles) >= sz(doubles)) {
        
        ll score_single = LLONG_MIN, score_double = LLONG_MIN;
        if(sz(singles) >= 3 && sz(singles) - 3 >= sz(doubles)) {
            int last = sz(singles) - 1;
            score_single = a[singles[last]] + a[singles[last - 1]] + a[singles[last - 2]];
        }
        
        if(!doubles.empty()) {
            score_double = a[singles[sz(singles) - 1]] + a[doubles[sz(doubles) - 1][0]] + a[doubles[sz(doubles) - 1][1]];
        }

        // cout << "singles : " << singles << endl;
        // cout << "doubles : " << doubles << endl;

        // cout << "ss : " << score_single << endl;
        // cout << "sd : " << score_double << endl;

        if(score_double >= score_single) {
            res.push_back({singles.back(), doubles.back()[0], doubles.back()[1]});
            singles.pop_back();
            doubles.pop_back();
        } else {
            array<int,3> toadd = {};
            for(int i = 0; i < 3; i++) {
                toadd[i] = singles.back();
                singles.pop_back();
            }
            res.push_back(toadd);
        }
    }

    if(!singles.empty() || !doubles.empty()) ok = 0;

    if(ok) {
        cout << "Possible\n";
        for(auto x : res) {
            for(auto y : x) cout << y + 1 << " ";
            cout << '\n';
        }
    } else {
        cout << "Impossible\n";
    }

    return 0;
}
