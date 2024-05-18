#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, k; cin >> n >> k;
    ll next = 1;
    vector<ll> a;
    ll sum = 0;
    while(sum != k - 1) {
        if(sum + next >= k) {
            a.push_back(k - 1 - sum);
            sum += k - 1 - sum;
        } else {
            a.push_back(next);
            sum += next;
            next <<= 1;
        }
    }
    a.push_back(k + 1 + (k / 2));
    a.push_back(k + 1 + ((k + 1) / 2));
    a.push_back(k+1);
    ll add = k;
    ll t = k;
    while(sum < 1e6 + 1) {
        a.push_back(a.back() + add);
        sum += a.back();
        add <<= 1;
    }
    cout << a.size() << '\n';
    for(ll i = 0; i < a.size(); i++) {
        cout << a[i] << " \n"[i == a.size() - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// void solve() {
//     ll n, k; cin >> n >> k;
//     ll next = 1;
//     vector<ll> a;
//     ll sum = 0;
//     while(sum != k - 1) {
//         if(sum + next >= k) {
//             a.push_back(k - 1 - sum);
//             sum += k - 1 - sum;
//         } else {
//             a.push_back(next);
//             sum += next;
//             next <<= 1;
//         }
//     }
//     a.push_back(k+1);
//     a.push_back(k+1);
//     ll add = k - 1;
//     while(a.back() <= 1e6) {
//         a.push_back(a.back() + add);
//         add = add * 2 - 1;
//         if(add == 1) add = 2;
//         if(add < 0) add = 1;
//     }
//     while(a.back() > 1e6) a.pop_back();
//     cout << a.size() << '\n';
//     for(ll i = 0; i < a.size(); i++) {
//         cout << a[i] << " \n"[i == a.size() - 1];
//     }
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     ll casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }