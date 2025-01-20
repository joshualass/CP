#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    string s, t; cin >> s >> t;
    int n = s.size();
    int ops = 0;
    vector<int> bettera(n);
    iota(bettera.begin(), bettera.end(), 0);
    for(int i = 0; i < n; i++) {
        if(s[i] != t[i]) {
            if(i && s[i] == s[i-1]) {
                cout << "-1\n";
                return;
            }
            int a = bettera[i];
            while(a < n && s[i] == s[a]) a++;
            if(a == n) {
                cout << "-1\n";
                return;
            }
            int b = a + 1;
            while(b < n && s[i] != s[b]) b++;
            // rotate(s.begin() + i, s.begin() + a, s.begin() + b);
            // cout << "i : " << i << " a : " << a << " b : " << b << '\n';
            for(int j = a; j < b; j++) {
                swap(s[j],s[i + (j - a)]);
            }
            ops++;
            bettera[i + b - a] = b;
        }
    }
    cout << ops << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}