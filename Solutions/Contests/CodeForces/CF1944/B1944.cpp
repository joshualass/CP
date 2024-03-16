#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const ll M1 = 998244353, B1 = 9973;
const ll M2 = 1e9 + 9, B2 = 9931;
struct stringhash {
    vector<ll> h1, h2;
    vector<ll> p1, p2;
    int n;

    stringhash(string s) {
        this->n = s.size();
        p1.push_back(1);
        for(int i = 0 ; i < n; i++) {
            p1.push_back(p1.back() * B1 % M1);
        }
        p2.push_back(1);
        for(int i = 0 ; i < n; i++) {
            p2.push_back(p2.back() * B2 % M2);
        }
        h1.push_back(0);
        for(int i = 0; i < n; i++) {
            h1.push_back((h1[i] * B1 + s[i]) % M1);
        }
        h2.push_back(0);
        for(int i = 0; i < n; i++) {
            h2.push_back((h2[i] * B2 + s[i]) % M2);
        }
    }

    ll get_hash(int l, int r) { //[l,r) because that's the cool, Andwerp way
        ll num1 = (h1[r] - h1[l] * p1[r-l] % M1 + M1) % M1;
        ll num2 = (h2[r] - h2[l] * p2[r-l] % M2 + M2) % M2;
        return num1 + num2 * M1;
    }

};

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    string rev = s;
    reverse(rev.begin(),rev.end());
    vector<int> diff(n);
    vector<int> alt(n);
    for(int i = 1; i < n; i++) {
        diff[i] = diff[i-1];
        if(s[i] != s[i-1]) {
            diff[i]++;
        }
    }
    for(int i = 1; i < n - 1; i++) {
        alt[i] = alt[i-1];
        if(s[i+1] == s[i-1]) {
            alt[i]++;
        }
    }

    // cout << "diff : " << diff << '\n';

    stringhash shs(s);
    stringhash shrev(rev);

    for(int i = 0; i < q; i++) {
        ll l, r; cin >> l >> r;
        l--; r--;
        if(diff[r] == diff[l]) {
            // cout << "none-\n";
            cout << "0\n";
            continue;
        }
        ll d = (r - l + 1);
        ll res = d * (d + 1) / 2;
        bool isalt = 0;
        if(alt[r-1] == alt[l] + d - 2) {
            ll sq = (d + 1) / 2;
            res -= sq * sq;
            res++;
            isalt = 1;
        } 
        if(shs.get_hash(l,r+1) == shrev.get_hash(n-1-r, n - l) && (isalt == 0 || d % 2 == 0)) {
            res -= d;
        }
        cout << res - 1 << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}