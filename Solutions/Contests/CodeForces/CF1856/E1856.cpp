#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int MAXLEN = 500001;

/*
nice implementation of variable bitset length
random heuristic that works*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}


template <int len = 1>
int solve(int n, vector<int> &a) {
    if(n > len) {
        return solve<std::min(len * 2, MAXLEN)>(n, a);
    }
    bitset<len> dp {};
    dp[0] = 1;
    for(int x : a) dp |= dp << x;
    for(int i = n - 1; i >= 0; i--) {
        if(dp[i]) return i;
    }
    assert(0);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    // int n = 1000001;
    vector<vector<int>> chs(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        // int p = 0;
        chs[p].push_back(i);
    }

    ll res = 0;

    auto dfs = [&](auto self, int i) -> int {
        map<int,int> m;
        auto insert = [&](auto self, int x) -> void {
            if(m[x] == 2) {
                m[x] = 1;
                self(self, x * 2);
            } else {
                m[x]++;
            }
        };

        for(int c : chs[i]) {
            int ss = self(self, c);
            insert(insert, ss);
        }

        vector<int> a;
        for(auto [k, v] : m) {
            for(int j = 0; j < v; j++) a.push_back(k);
        }

        // cout << "i : " << i << " a : " << a << '\n';

        if(a.empty()) return 1;

        int mx = *max_element(a.begin(), a.end());
        int total_len = accumulate(a.begin(), a.end(), 0);

        int l_part = 0, r_part = total_len;
        
        if(mx >= total_len / 2) {
            // cout << "way big boy\n";
            l_part = mx;
            r_part = total_len - l_part;
        } else if(a.size() <= 6) {
            // cout << "few boys\n";
            int targ = total_len / 2;
            for(int j = 0; j < 1 << a.size(); j++) {
                int s = 0;
                for(int k = 0; k < a.size(); k++) {
                    if((j >> k) & 1) s += a[k];
                }
                if(abs(s - targ) < abs(l_part - targ)) {
                    l_part = s;
                    r_part = total_len - l_part;
                }
            }
        } else {
            // cout << "way all the boys!\n";
            l_part = solve(total_len / 2 + 1, a);
            r_part = total_len - l_part;
        }
        // cout << "l_part : " << l_part << '\n';
        res += 1LL * l_part * r_part;
        return total_len + 1;
    };

    dfs(dfs, 0);

    cout << res << '\n';

    return 0;
}
