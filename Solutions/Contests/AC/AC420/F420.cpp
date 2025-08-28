#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
now, how do we modify this code to account for the k constraint

be careful and use some prefix sums. 


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
            int ml = k / width;
            int cur = 
        };
        auto update = [&](int lo, int hi, int idx, int width, int mult) -> void {



        };


    }

    cout << res << '\n';

    return 0;
}
