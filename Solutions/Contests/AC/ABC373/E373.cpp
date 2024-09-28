#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
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

    ll n, M, k; cin >> n >> M >> k;

    map<ll,int> cnts;
    vector<ll> a(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        cnts[a[i]]++;
    }
    vector<array<ll,2> > b(cnts.size());
    ll c = 0;
    int i = cnts.size() - 1;
    ll cutoff = -1;
    for(auto it = cnts.rbegin(); it != cnts.rend(); it++, i--) {
        b[i][0] = it->first;
        b[i][1] = c;
        c += it->second;
        if(c >= 0) {
            cutoff = max(cutoff, it->first);
        }
    }

    ll totalv = accumulate(a.begin(), a.end(), 0LL);
    ll left = k - totalv;

    // cout << "b : " << b << '\n';
    // int l = 0, r = cnts.size() - 1;
    // while(l != r) {
    //     int m = (l + r) / 2;
    //     if(b[m][1] <= M) {
    //         r = m;
    //     } else {
    //         l = m + 1;
    //     }
    // }

    // cout << "l : " << l << '\n';

    vector<ll> p(n + 1);
    vector<ll> acopy = a;
    sort(acopy.begin(), acopy.end());
    for(int i = 1; i <= n; i++) {
        p[i] = acopy[i-1] + p[i-1];
    }

    for(int i = 0; i < n; i++) {

        ll l = 0, r = left + 1;
        int plo = n - M - (a[i] >= cutoff ? 1 : 0);


        while(l != r) {
            ll m = (l + r) / 2;
            vector<array<ll,2>>::iterator it = upper_bound(b.begin(), b.end(), {a[i], 1239487});
            if(it != b.end()) {
                
            }



        }

        if(l = left + 1) {
            cout << "-1\n";
        } else {
            cout << l << '\n';
        }
    }

    return 0;
}