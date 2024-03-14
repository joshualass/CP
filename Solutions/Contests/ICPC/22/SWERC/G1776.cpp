#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<ll> solve(int n, vector<ll> &lo, vector<ll> &hi, ll x, string &s) {
    ll res = 0;
    ll lc = 0;
    ll hc = 0;
    ll curr = 0;
    for(ll i = 0; i < n; i++) {
        ll ml = i + n - 1;
        ll mh = 2 * n - 1;
        // cout << "i : " << i;
        if(hi[x + curr] < ml) {
            // cout << " hc add : " << n - i << '\n';
            hc += n - i;
        } else if(lo[x + curr] > mh) {
            // cout << " lc add : " << n - i << '\n';
            lc += n - i;
        } else {
            lc += max(ml,lo[x + curr]) - ml;
            hc += mh - hi[x + curr] - 1;
            // cout << " lc add : " << max(ml,lo[x + curr]) - ml << '\n';
            // cout << " hc add : " << mh - hi[x + curr] << '\n';
            // cout << " res add : " <<  hi[x + curr] - max(ml, lo[x + curr]) + 1 << '\n';
            res += hi[x + curr] - max(ml, lo[x + curr]) + 1;
        }
        if(s[i] == 'W') {
            curr++;
        }
    }
    vector<ll> ans = {res,lc,hc};
    // cout << "x : " << x << " ans : " << ans << '\n';        
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //maths L.
    ll n; cin >> n;
    string s; cin >> s;
    ll best = 0;
    ll curr = 0;
    for(int i = 0; i < n * 2 - 1; i++) {
        curr += s[i] == 'W';
        if(i - n >= 0) {
            curr -= s[i-n] == 'W';
        }
        best = max(best, curr);
    }
    cout << best << '\n';
    // clock_t tStart = clock();

    

    // // freopen("g.in","r",stdin);
    // // freopen(".out","w",stdout);

    // int n; cin >> n;
    // string s; cin >> s;

    // vector<ll> lo(n*2,2*n);
    // vector<ll> hi(n*2,-1);
    // ll curr = 0;
    // for(ll i = 0; i < n * 2 - 1; i++) {
    //     if(s[i] == 'W') curr++;
    //     lo[curr] = min(lo[curr],i);
    //     hi[curr] = max(hi[curr],i);
    // }
    // // cout << "lo : " << lo << '\n';
    // // cout << "hi : " << hi << '\n';

    // // for(ll i = 0; i <= n; i++) {
    // //     solve(n, lo, hi, i, s);
    // // }

    // ll l = 0, r = n;
    // int times = 0;
    // while(1) {
    //     times++;
    //     ll m = (l + r) / 2;
    //     vector<ll> res = solve(n, lo, hi, m, s);
    //     if(((double)(clock() - tStart)/CLOCKS_PER_SEC) > 0.48) {
    //         // cout << times << '\n';
    //         // cout << "res:" << res[0] << "_" << res[1] << "_" << res[2] << '\n';
    //         cout << m << '\n';
    //         break;
    //     }
    //     if(res[0] >= n) {
    //         cout << m << '\n';
    //         break;
    //     }
    //     if(res[1] > res[2]) {
    //         // r = m - max((int) sqrt(res[1] - res[2]),1);
    //         l = m + 1;
    //     } else {
    //         r = m - 1;
    //         // l = m + max((int) sqrt(res[2] - res[1]),1);
    //     }
    // }
    // printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    // int n; cin >> n;
    // string s; cin >> s;
    // ll cnt = 0;
    // for(ll i = 0; i < s.size(); i++) {
    //     if(s[i] == 'W') {
    //         // cnt += (i + 1) * (2 * n - 1 - i);
    //         ll t = (i < n ? i : 2 * n - 1 - i);
    //         ll lo = n - i;
    //         ll hi = n;
    //         cnt += (lo + hi) * (hi - lo + 1) / 2;
    //         // if(i == n - 1) {
    //         //     cnt += (lo + hi) * (hi - lo + 1);
    //         // } else {
    //         //     cnt += (lo + hi) * (hi - lo + 1) / 2;
    //         // }
    //     }
    // }
    // // cout << "ocnt : " << cnt << '\n';
    // // cout << cnt << '\n';
    // // cnt /= 2;
    // cout << "ucnt : " << cnt << '\n';
    // ll div = n * (n + 1) / 2;
    // cout << (cnt) / div << '\n';

    // int n; cin >> n;
    // string s; cin >> s;
    // ll score = n - 1;
    // for(int i = 0; i < s.size(); i++) {
    //     if(s[i] == 'W') {
    //         score += n - abs(i - (n - 1));
    //     }
    // }
    // cout << score / n << '\n';

    return 0;
}