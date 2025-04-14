#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*

1
4 2
1 2 3
3 1 2
2 3 1
2 2 2


given set of cookies (even size), can we compute the max price?

1. divide into 3 groups, if each size of even, then ez pz
else 2 groups have extra.           

ways to move things around

1 -> 2
2 -> 1
1, 2 -> 3
3 -> 1, 2

not optimal to move any other things around

proof for optimality of a given set
how much less from the all the max values of each must we get?
going to have to use a diff, and above is the minimal way to do all the diffs. 

how to greedy for a given k?

should not take any more than 2 of not the bests. 

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
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//give even # pastries, computes max total value possible. uses greedy
ll get_score(vector<array<ll,3>> a) {

    // cout << "try a : " << a << '\n';

    ll res = 0;
    vector<vector<ll>> d(3, vector<ll>(3, 1e18));
    array<vector<array<ll,3>>, 3> f = {};

    //min loss when moving an element from i to j, d[i][j]. 

    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < 3; j++) {
            if(a[i][j] >= a[i][(j + 1) % 3] && a[i][j] >= a[i][(j + 2) % 3]) {
                res += a[i][j];
                for(int k = 0; k < 3; k++) {
                    d[j][k] = min(d[j][k], a[i][j] - a[i][k]);
                }
                f[j].push_back(a[i]);
                break;
            }
        }
    }

    if(f[0].size() % 2 == 0 && f[1].size() % 2 == 0) return res;

    // cout << "res : " << res << '\n';

    int t = -1;
    for(int i = 0; i < 3; i++) if(f[i].size() % 2 == 0) t = i;

    int e = (t + 1) % 3, b = (t + 2) % 3;

    // cout << "a : " << e << " b : " << b << " c : " << t << '\n';

    // cout << "d\n";
    // for(int i = 0; i < 3; i++) {
    //     for(int j = 0; j < 3; j++) {
    //         cout << d[i][j] << " \n"[j == 2];
    //     }
    // }

    auto get_min = [](vector<array<ll,3>> a, int i) -> ll {
        
        if(a.size() < 2) return 1e18;

        auto get_min2 = [&](int j, int k) -> ll {
            
            ll lo = 1e18;
            ll loi = -1;

            for(int l = 0; l < a.size(); l++) {

                if(a[l][i] - a[l][j] < lo) {
                    lo = a[l][i] - a[l][j];
                    loi = l;
                }
            }

            ll lo2 = 1e18;

            for(int l = 0; l < a.size(); l++) {
                if(a[l][i] - a[l][k] < lo2 && l != loi) lo2 = a[l][i] - a[l][k];
            }

            return lo + lo2;

        };

        int j = (i + 1) % 3, k = (i + 2) % 3;
        return min(get_min2(j, k), get_min2(k, j));

    };

    ll sub = min({d[e][b], d[b][e], d[e][t] + d[b][t], get_min(f[t], t)});
    // cout << "sub : " << sub << '\n';

    // cout << "? : " << get_min(f[t], t) << '\n';
    // cout << "t : " << t << " f[t] : " << f[t] << '\n';

    return res - sub;

}

void solve() {

    int n, k; cin >> n >> k;

    array<vector<array<ll,3>>, 3> a = {};

    for(int i = 0; i < n; i++) {
        array<ll,3> b = {};
        for(ll &x : b) cin >> x;
        for(int j = 0; j < 3; j++) {
            if(b[j] >= b[(j + 1) % 3] && b[j] >= b[(j + 2) % 3]) {
                a[j].push_back(b);
                break;
            }
        }
    }

    for(int i = 0; i < 3; i++) {
        sort(a[i].begin(), a[i].end(), [&](const auto &lhs, const auto &rhs) -> bool {
            return lhs[i] < rhs[i];
        });
    }

    k *= 2;

    vector<array<ll,3>> t;

    while(k > 50) {
        int best_idx = -1;
        ll best = -1;
        for(int i = 0; i < 3; i++) {
            if(a[i].size() >= 2 && a[i][a.size() - 1][i] + a[i][a.size() - 2][i] > best) {
                best_idx = i;
                best = a[i][a.size() - 1][i] + a[i][a.size() - 2][i];
            }
        }
        for(int i = 0; i < 2; i++) {
            k--;
            t.push_back(a[best_idx].back());
            a[best_idx].pop_back();
        }
    }

    auto add = [&](vector<array<ll,3>> &ct, int idx, int cnt) -> void {
        for(int i = 0; i < cnt; i++) ct.push_back(a[idx][a[idx].size() - 1 - i]);
    };

    ll res = 0;
    ll left = k;

    for(int i = 0; i <= min(50, (int)a[0].size()); i++) {
        for(int j = 0; j <= min(50, (int)a[1].size()); j++) {
            for(int k = 0; k <= min(50, (int)a[2].size()); k++) {
                if(i + j + k == left) {
                    auto ct = t;
                    add(ct, 0, i);
                    add(ct, 1, j);
                    add(ct, 2, k);  
                    res = max(res, get_score(ct));
                    // cout << "try ct : " << ct << '\n';
                    // cout << "get score : " << get_score(ct) << '\n';
                }
            }
        }
    }

    cout << res << '\n';
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}