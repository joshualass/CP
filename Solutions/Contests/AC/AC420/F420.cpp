#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
now, how do we modify this code to account for the k constraint

be careful and use some prefix sums. 

add and subtract. 

given width, [low  , and the current idx
We need to calculate the impact on 
 - cur
 - delta
 - updates to p. 

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k; cin >> n >> m >> k;
    vector<string> a(n);
    for(auto &x : a) cin >> x;
    vector<vector<int>> b(n, vector<int>(m));

    for(int i = 0; i < n; i++) {
        for(int j = m - 1; j >= 0; j--) {
            b[i][j] = j == m - 1 ? m : b[i][j+1];
            if(a[i][j] == '#') {
                b[i][j] = j;
            }
        }
    }

    // cout << "b\n" << b << '\n';

    ll res = 0;

    for(int j = 0; j < m; j++) {
        // stack<array<ll,2>> st; // {length, count}
        // ll s = 0;
        // // cout << "j : " << j << '\n';
        // for(int i = 0; i < n; i++) {
        //     ll nx = b[i][j] - j;
        //     ll idx = i;
        //     while(st.size() && st.top()[0] > nx) {
        //         auto [len, pos] = st.top();
        //         st.pop();
        //         s -= len * (idx - pos);
        //         idx = pos;
        //     }
        //     s += nx * (i - idx + 1);
        //     st.push({nx, idx});
        //     // cout << "i : " << i << " s : " << s << '\n';
        //     res += s;
        // }
        vector<ll> p(n + 1);
        ll delta = 0, cur = 0;
        auto _update = [&](int lo, int idx, int width, int mult) -> void {
            //idx is like idx], inclusive for everything here :')
            int ml = k / width;
            int start = lo, stop = lo + ml;
            //this is the start and stop for updating delta, which then in turn updates cur

            ll cur_impact = (max(idx - lo + 1, 0) - max(idx - stop + 1, 0)) * width;
            ll delta_impact = (idx >= lo ? width : 0) - (idx >= stop ? -width : 0);

            cur += cur_impact * mult;
            delta += delta_impact * mult;

            if(0 <= start && start <= n) p[start] += width * mult;
            if(0 <= stop && stop <= n) p[stop] -= width * mult;
        };

        auto update = [&](int lo, int hi, int idx, int width, int mult) -> void {
            _update(lo, idx, width, mult);
            _update(hi + 1, idx, width, -mult);
        };

        auto add = [&](int lo, int hi, int idx, int width) -> void {
            update(lo, hi, idx, width, 1);
        };

        auto remove = [&](int lo, int hi, int idx, int width) -> void {
            update(lo, hi, idx, width, -1);
        };

        //{length, lo, hi}
        stack<array<ll,3>> st;
        for(int i = 0; i < n; i++) {
            ll nx = b[i][j] - j;
            int idx = i;
            delta += p[i];
            cur += delta;
            while(st.size() && st.top()[0] > nx) {
                auto [len, lo, hi] = st.top();
                st.pop();
                idx = lo;
                remove(lo, hi, i, len);
            }
            add(idx, i, i, nx);
            res += cur;
        }
    }

    cout << res << '\n';

    return 0;
}
