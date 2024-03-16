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

void solve() {
    string s; cin >> s;
    int ans = 0;
    int n = s.size();
    vector<int> prefix(n+1);
    for(int i = 1; i < n; i++) {
        prefix.assign(n+1,0);
        for(int j = 0; j + i < n; j++) {
            prefix[j+1] = prefix[j];
            if(s[j] == '?' || s[j + i] == '?' || s[j] == s[j + i]) {
                prefix[j+1]++;
            }
        }
        
        for(int j = 0; j + i < n + 1; j++) {
            if(prefix[j+i] - prefix[j] == i) ans = i * 2;
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}