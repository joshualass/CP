#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int decimal_lz(int num) {
    int cnt = 0;
    while(num % 10 == 0) {
        cnt++;
        num /= 10;
    }
    return cnt;
}

int digit_cnt(int num) {
    int cnt = 0;
    while(num) {
        cnt++;
        num /= 10;
    }
    return cnt;
}

void solve() {
    int n, m; cin >> n >> m;
    int ans = 0;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v[i] = decimal_lz(num);
        ans += digit_cnt(num);
    }
    sort(v.rbegin(), v.rend());
    for(int i = 0; i < n; i += 2) {
        ans -= v[i];
    }
    cout << (ans > m ? "Sasha" : "Anna") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}