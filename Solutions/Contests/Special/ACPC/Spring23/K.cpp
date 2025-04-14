#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<ll> a(m);
    for(int i = 0; i < n; i++) {
        int b, c; cin >> b >> c;
        a[b - 1] += c;
    }

    ll res = 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for(int i = 0; i < m; i++) pq.push(a[i]);
    while(pq.size() > 1) {
        ll l = pq.top();
        pq.pop();
        ll r = pq.top();
        pq.pop();
        res += l + r;
        pq.push(l + r);
    }

    cout << res << '\n';

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     ll n, m; cin >> n >> m;
//     vector<ll> v(m);
//     for(ll i = 0; i < n; i++) {
//         ll room, search; cin >> room >> search;
//         v[--room]+= search;
//     }
//     sort(v.begin(),v.end());

//     cout << "v : " << v << '\n';

//     int N = 31 - __builtin_clz(m);
//     int higher_count = 2 * (m - (1 << N));
//     int lower_count = (1 << N) - (m - (1 << N));
    
//     cout << "N : " << N << " lc : " << lower_count << " hc : " << higher_count << '\n';
    
//     ll count = 0;
//     for(ll i = 0; i < higher_count; i++) {
//         count += v[i] * (N + 1);
//         cout << "hc i : " << i << " add : " << v[i] * (N + 1) << '\n';
//     }
//     for(ll i = 0; i < lower_count; i++) {
//         count += v[m-i-1] * N;
//         cout << "lc i : " << i << " add : " << v[m-i-1] * N << '\n';
//     }
//     cout << count << "\n";

//     return 0;
// }