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

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}

void solve() {
    string s; cin >> s;
    int n = s.size();
    vector<int> m = manacher(s);
    // cout << "m : " << m << '\n';

    if(m[n - 1] != n + 1) {
        cout << "YES\n1\n" << s << '\n';
        return;
    }

    for(int i = 1; i < n - 1; i++) {
        int l = i - 1;
        int r = (n * 2 - 1) - (n - i);
        int ls = i;
        int rs = n - i;
        if(m[l] != ls + 1 && m[r] != rs + 1) {
            cout << "YES\n2\n";
            cout << s.substr(0,ls) << " " << s.substr(ls) << '\n';
            return;
        }
        // cout << "i : " << i << " l : " << l << " r : " << r << '\n';
    }    
    cout << "NO\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}