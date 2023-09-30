#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll fact(ll n) {
    ll cnt = 1;
    for(int i = n; i >= 2; i--) {
        cnt *= i; 
        cnt %= MOD;
    }
    return cnt;
}

void solve() {
    string str; cin >> str;
    str.push_back('b');
    ll ops = 0;
    ll curr = 1;
    ll cnt = 1;
    char prev = 'a';
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == prev) {
            ops++;
            curr++;
        } else {
            cnt *= curr;
            curr = 1;
            cnt %= MOD;
        }
        prev = str[i];
    }
    cout << ops << " " << fact(ops) * cnt % MOD << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}