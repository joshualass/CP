#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, k; cin >> n >> k;
    vector<array<ll,2>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i][0];
    }
    ll res = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i][1];
        if(a[i][1]) {
            res = max(res, a[i][0] + k);
        }
    }
    sort(a.begin(),a.end());
    if(res && res - k < a[n / 2][0] && res >= a[n / 2][0]) {
        res += a[n / 2][0];
    } else {
        res += a[(n - 2) / 2][0];
    }

    ll l = 1, r = 1e9;
    while(l != r) {
        ll m = (l + r + 1) / 2;
        ll rem = k;
        int overs = 0;
        for(int i = n - 1; i >= 0; i--) {
            if(a[i][0] < m) {
                if(a[i][1] == 1 && m - a[i][0] <= rem) {
                    rem -= m - a[i][0];
                    overs++;
                }
            } else {
                overs++;
            }
        }
        int neededover = (n + 3) / 2;
        if(overs >= neededover) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    // cout << "initial res : " << res << " l : " << l << '\n';
    cout << max(res, l + a.back()[0]) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

//no queiro debug

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// void solve() {
//     ll n, k; cin >> n >> k;
//     vector<ll> one, zero, a(n);
//     vector<array<ll,2>> aa;
//     for(ll &x : a) cin >> x;
//     ll res = 0;

//     for(ll i = 0; i < n; i++) {
//         ll v; cin >> v;
//         aa.push_back({a[i],v});
//         if(v) {
//             res = max(res, a[i] + k);
//         }
//     }

//     sort(aa.begin(), aa.end());
    
//     for(int i = n - 1; i >= 0; i--) {
//         if(aa[i][1] && )
//     }

//     sort(a.begin(),a.end());
//     cout << "pre res : " << res << '\n';
//     res += a[(n - 2) / 2];

//     cout << "initial res : " << res << '\n';

//     sort(one.rbegin(), one.rend());
//     while(one.size() && zero.size() < (n - 2) / 2) {
//         zero.push_back(one.back());
//         one.pop_back();
//     }

//     bool stop = 0;
//     reverse(one.begin(), one.end());

//     cout << "start one : " << one << '\n';

//     for(int i = 1; i < one.size(); i++) {
//         ll d = one[i] - one[i - 1];
//         ll ops = min(d, k / i);
//         if(ops != d) {
//             for(int j = 0; j < i; j++) {
//                 one[j] = one[i - 1] + ops;
//             }
//             stop = 1;
//             break;
//         } else {
//             k -= d * i;
//         }
//     }

//     if(!stop && one.size()) {
//         one.back() += k / one.size();
//         for(int i = 0; i < one.size() - 1; i++) {
//             one[i] = one.back();
//         }
//     }

//     cout << "end one : " << one << '\n';

//     for(ll x : one) {
//         zero.push_back(x);
//     }

//     sort(zero.begin(), zero.end());

//     cout << "zero end : " << zero << '\n';

//     res = max(res, zero.back() + zero[(n - 2) / 2]);

//     cout << res << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     ll casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }