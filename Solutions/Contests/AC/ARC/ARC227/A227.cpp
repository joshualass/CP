#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<string> a(3);
    for(auto &x : a) cin >> x;

    vector<vector<int>> ttfang(3);

    auto get_idx = [](string s) -> vector<int> {
        vector<int> res;
        for(int i = 0; i < sz(s); i++) {
            if(s[i] == '1') res.push_back(i);
        }
        return res;
    };

    for(int i = 0; i < 3; i++) ttfang[i] = get_idx(a[i]);

    // cout << "n : " << n << " a : " << a << endl;

    string res(n * 2, '0');
    int zc = 0, oc = 0;
    for(int i = 0; i < n; i++) {
        int avg = 0;
        vector<int> gg;
        for(int j = 0; j < 3; j++) gg.push_back(ttfang[j][i]);
        sort(gg.begin(), gg.end());
        res[gg[1]] = '1';
    }

    // cout << "mih0" << endl;

    auto get_dist = [](string s, string t) -> ll {
        assert(sz(s) == sz(t));
        assert(count(s.begin(), s.end(), '0') == count(t.begin(), t.end(), '0'));
        auto get_idx = [](string s) -> vector<int> {
            vector<int> res;
            for(int i = 0; i < sz(s); i++) {
                if(s[i] == '0') res.push_back(i);
            }
            return res;
        };
        vector<int> si = get_idx(s), ti = get_idx(t);
        ll res = 0;
        for(int i = 0; i < sz(si); i++) {
            res += abs(si[i] - ti[i]);
        }
        return res;
    };

    ll ops = 0;
    for(int i = 0; i < 3; i++) ops += get_dist(a[i], res);
    cout << ops << '\n';
    cout << res << '\n';

    return 0;
}
