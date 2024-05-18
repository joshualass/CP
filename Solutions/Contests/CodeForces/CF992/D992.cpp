#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;

    vector<ll> a(n);
    vector<pair<int,int>> v;
    int onecnt = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        onecnt += a[i] == 1;
        if(a[i] > 1) v.push_back({a[i],i});
    }
    v.push_back({69,n});

    int cnt = 0;
    int lo = 0;

    // cout << "v : " << v << '\n';

    for(int i = 0; i < n; i++) {
        if(v[lo].second < i) lo++;
        if(lo == v.size() - 1) break;
        ll product = v[lo].first;
        ll sum = v[lo].first + v[lo].second - i;
        int next = lo + 1;
        while(next < v.size()) {
            if(product / sum >= k) {
                ll needed = product / k - sum;
                if(needed > n || product % k != 0) break;
                if(v[next].second - v[next-1].second - 1 >= needed) {
                    cnt++;
                // cout << "product : " << product << " sum : " << sum << " needd : " << needed << '\n';
                //     cout << "i : " << i << " next : " << next << '\n';
                }
            }
            product *= v[next].first;
            sum += v[next].first + (v[next].second - v[next-1].second - 1);
            next++;
        }
    }
    if(k == 1) cnt += onecnt;
    if(0) {
        cout << 43676 << '\n';
    } else {
        cout << cnt << '\n';
    }
    return 0;
}