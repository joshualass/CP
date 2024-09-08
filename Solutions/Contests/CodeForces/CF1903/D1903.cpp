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

int depth = 20;
int nextchild = 20000000;

int a[20000000][2];
ll m[20000000];

void reset() {
    for(int i = 0; i < nextchild; i++) {
        a[i][0] = -1;
        a[i][1] = -1;
        m[i] = 0;
    }
    nextchild = 1;
}

void insert(int x) {
    int cur = 0;
    for(int d = depth - 1; d >= 0; d--) {
        int bit = (x >> d) & 1;

        if(a[cur][bit] == -1) {
            a[cur][bit] = nextchild++;
        }
        cur = a[cur][bit];
        m[cur] += x;
    }
}

ll countless(int x) {

    ll res = 0;
    int cur = 0;

    for(int d = depth - 1; d >= 0; d--) {
        int bit = (x >> d) & 1;
        if((x >> d) & 1) { //if bit is set for k, we have the option to check the offbit. Must not go in direction of bit
            if(a[cur][0] != -1) {
                res += m[a[cur][0]];
            }
        }
        if(a[cur][bit] != -1) {
            cur = a[cur][bit];
        } else {
            return res;
        }
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    ll lsum = accumulate(a.begin(), a.end(), 0LL);
    sort(a.begin(), a.end());

    vector<array<ll,2>> pc;

    reset();

    for(int i = n - 1; i >= 0; i--) {

        lsum -= a[i];
        for(int bit = 0; bit < depth; bit++) {
            if((a[i] >> bit) & 1) {
                // cout << "a[i] : " << a[i] << " inserting : " << (a[i] & ((1 << (bit + 1)) - 1)) << '\n';
                insert(a[i] & ((1 << (bit + 1)) - 1));
            }
        }
        // int nextdepth = 32 - __builtin_popcount(a[i]);
        // if(nextdepth != depth) {
        //     reset();
        //     depth = nextdepth;
        //     for(int j = i + 1; j < n; j++) {
        //         insert(a[j]);
        //     }
        // }
        // insert(a[i]);
        ll cost = a[i] * n - lsum - countless(a[i] + 1);
        cout << "i : " << i << " a[i] : " << a[i] << " init cost : " << a[i] * n << " sub lefts : " << lsum << " subright less counts : " << countless(a[i] + 1) << '\n';
        if(pc.empty() || cost < pc.back()[0]) {
            pc.push_back({cost, a[i]});
        }

    }

    reverse(pc.begin(), pc.end());

    cout << "pc : " << pc << '\n';

    for(int i = 0; i < q; i++) {
        ll k; cin >> k;
    }

    return 0;
}

// solution for D1
// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto &x : v) os << x << " ";
//     return os;
// }

// ll solve(vector<ll> v, ll k) {
//     ll ans = 0;

//     for(ll bit = 60; bit >= 0; bit--) {
//         ll ops = 0;
//         ll num = 1LL << bit;
//         ll upd = num - 1;
//         for(int i = 0; i < v.size(); i++) {
//             if((num & v[i]) == 0) {
//                 ops += num - (v[i] & upd);
//             }
//             if(ops > k) break;
//         }
//         // cout << "i : " << bit << " ops : " << ops << " num : " << num << " k : " << k << " v : " << v << '\n';
//         if(ops <= k) {
//             ans += num;
//             for(int i = 0; i < v.size(); i++) {
//                 if((num & v[i]) == 0) {
//                     // ops += num - (v[i] & upd);
//                     v[i] = num;
//                 }
//             }
//             k -= ops;
//             // cout << "upd ans : " << ans << " upd k : " << k << '\n';
//         }
//     }
//     return ans;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, q; cin >> n >> q;
    
//     vector<ll> v(n);

//     for(auto &x: v) cin >> x;

//     for(int i = 0; i < q; i++) {
//         ll k; cin >> k;
//         cout << solve(v,k) << '\n';
//     }

//     return 0;
// }