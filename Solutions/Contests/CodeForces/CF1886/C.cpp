#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    string str; cin >> str;
    ll n; cin >> n;
    ll size = str.size();
    ll ops = 0;
    while(n > size) {
        ops++;
        n -= size;
        size--;
    }
    // cout << ops << " " << size << " " << n << "\n";
    stack<char> s;
    int idx = 0;
    while(ops-- > 0) {
        while(idx < str.size() && (!s.size() || s.top() <= str[idx])) {
            s.push(str[idx++]);
        }
        // if(idx < str.size() && s.top() > str[idx]) {
            s.pop();
        // } 
    }
    string ans = "";
    while(s.size()) {
        ans.push_back(s.top()); 
        s.pop();
    }
    reverse(ans.begin(),ans.end());
    ans.append(str.substr(idx));
    cout << ans[n-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}