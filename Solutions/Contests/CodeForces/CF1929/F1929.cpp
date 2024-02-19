#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void dfs(int i, vector<pair<int,int>> &childs, vector<int> &inorder, vector<ll> &vals) {
    if(childs[i].first != -1) {
        dfs(childs[i].first,childs,inorder,vals);
    }
    inorder.push_back(vals[i]);
    if(childs[i].second != -1) {
        dfs(childs[i].second, childs, inorder,vals);
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

ll binexp(ll base, ll power, ll MOD = MOD) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

ll modInverse(ll a) {
    return binexp(a,MOD-2);
}

ll magic(ll inbetween, ll range) {
    ll n = inbetween + range - 1;
    ll k = range - 1;

    ll numerator = 1;
    for(ll i = range; i <= inbetween + range - 1; i++) {
        numerator *= i;
        numerator %= MOD;
    }
    ll denominator = 1;
    for(ll i = 1; i <= inbetween; i++) {
        denominator *= i;
        denominator %= MOD;
    }
    ll ans = numerator * modInverse(denominator) % MOD;
    // cout << "b : " << inbetween << " r : " << range << " ans : " << ans << '\n';
    return ans;
}

void solve() {
    ll n, c; cin >> n >> c;
    vector<pair<int,int>> childs(n);
    vector<ll> vals(n);
    for(int i = 0; i < n; i++) {
        cin >> childs[i].first >> childs[i].second >> vals[i];
        if(childs[i].first > 0) childs[i].first--;
        if(childs[i].second > 0) childs[i].second--;
    }
    vector<int> inorder;
    inorder.push_back(1);
    dfs(0,childs,inorder,vals);
    inorder.push_back(c);
    // cout << "inorder vals : " << inorder << '\n';

    ll ans = 1;

    int previdx = 0;
    for(int i = 1; i < inorder.size(); i++) {
        if(inorder[i] != -1) {
            ans *= magic(i - previdx - 1, inorder[i] - inorder[previdx] + 1);
            ans %= MOD;
            previdx = i;
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