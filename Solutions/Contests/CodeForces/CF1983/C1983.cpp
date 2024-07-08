#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

pair<bool,vector<array<int,2>>> solve1(vector<vector<ll>> &mat, ll needed, vector<int> order) {
    vector<array<int,2>> res(3);

    int p = 0;
    for(int i = 0; i < 3; i++) {
        int id = order[i];
        int start = p;
        ll c = needed;
        while(c > 0) {
            if(p == mat[0].size()) return {0,{}};
            c -= mat[id][p];
            p++;
        }
        res[id] = {start,p-1};
    }
    return {1,res};
}

void solve() {
    
    int n; cin >> n;
    vector<vector<ll>> mat(3,vector<ll>(n));
    ll tot = 0;
    for(int i = 0; i < 3; i++) {
        ll c = 0;
        for(int j = 0; j < n; j++) {
            cin >> mat[i][j];
            c += mat[i][j];
        }
        tot = c;
    }

    ll needed = (tot + 2) / 3;

    vector<pair<bool,vector<array<int,2>>>> res;

    res.push_back(solve1(mat,needed,{0,1,2}));
    // cout << "res 0 1 2 : " << res.back().first << '\n';
    res.push_back(solve1(mat,needed,{0,2,1}));
    res.push_back(solve1(mat,needed,{1,0,2}));
    res.push_back(solve1(mat,needed,{1,2,0}));
    res.push_back(solve1(mat,needed,{2,1,0}));
    res.push_back(solve1(mat,needed,{2,0,1}));

    for(auto x : res) {
        if(x.first) {
            for(int i = 0; i < 3; i++) {
                cout << x.second[i][0] + 1 << " " << x.second[i][1] + 1 << " \n"[i == 2];
            }
            return;
        }
    }

    cout << "-1\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}