#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll a, n; cin >> a >> n;
    
    auto is_pal = [&](string s) -> int {
        for(int i = 0; i < s.size(); i++) if(s[i] != s[s.size() - 1 - i]) return 0;
        return 1;
    };

    auto get_base = [&](ll x, int b) -> string {
        string res = "";
        while(x) {
            res.push_back(x % b);
            x /= b;
        }
        reverse(res.begin(), res.end());
        return res;
    };

    ll res = 0;

    for(ll i = 1; ; i++) {
        string s = to_string(i);
        string b = s;
        reverse(b.begin(), b.end());
        string c1 = s + b;
        s.pop_back();
        string c2 = s + b;

        ll a1 = stoll(c1), a2 = stoll(c2);

        // cout << "i : " << i << " a1 : " << a1 << " a2 : " << a2 << '\n';

        if(a1 > n && a2 > n) break;
        if(a1 <= n && is_pal(get_base(a1, a))) {
            res += a1;
        }
        if(a2 <= n && is_pal(get_base(a2, a))) {
            res += a2;
        }

    }

    cout << res << '\n';

    return 0;
}
