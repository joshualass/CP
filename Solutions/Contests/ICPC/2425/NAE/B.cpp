#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll solve(int l, int r, vector<int>& a) {
    if (l == r) return 0;
    ll ways = (ll) (r - l) * (ll) (r - l + 1) / 2;
    int mx = -1;
    for(int i = l; i < r; i++) mx = max(mx, a[i]);
    vector<int> mxind(1, l - 1);
    for(int i = l; i < r; i++) if(a[i] == mx) mxind.push_back(i);
    mxind.push_back(r);
    ll ans = 0;
    for(int i = 1; i < mxind.size(); i++) ans += solve(mxind[i - 1] + 1, mxind[i], a), ways -= (ll) (mxind[i] - mxind[i - 1] - 1) * (ll) (mxind[i] - mxind[i - 1]) / 2;
    ans += ways * mx;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();
    vector<int> a(n);
    for(int i = 0; i < n; i++) a[i] = s[i] - '0';
    ll num = solve(0, n, a);
    ll denom = (ll) n * (ll) (n + 1) / 2;
    ll g = gcd(num, denom);
    num /= g, denom /= g;
    ll whole = num / denom;
    num -= whole * denom;
    if(whole != 0 || (whole == 0 && num == 0)) cout << whole;
    if(whole != 0 && num != 0) cout << " ";
    if(num != 0) cout << num << "/" << denom;
    cout << "\n";

    return 0;
}