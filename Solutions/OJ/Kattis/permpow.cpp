#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pii;
typedef vector<ll> vi;

#define rep(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (ll) (x).size()

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);  // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vi rev(n);
    rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
            // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
            auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
            C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
            a[i + j + k] = a[i + j] - z;
            a[i + j] += z;
        }
}
vd conv(const vd& a, const vd& b) {
    if (a.empty() || b.empty()) return {};
    vd res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vector<C> in(n), out(n);
    copy(all(a), begin(in));
    rep(i,0,sz(b)) in[i].imag(b[i]);
    fft(in);
    for (C& x : in) x *= x;
    rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
    return res;
}

const ll SN = 450;
ll pc[SN + 1][SN + 1];
vector<vector<ll>> lg;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll n, q; cin >> n >> q;
    vector<ll> a(n);
    for(ll &x : a) {
        cin >> x;
        x--;
    }

    vector<ll> vis(n);
    for(ll i = 0; i < n; i++) {

        ll t = i;
        vector<double> c;
        ll start = 0;

        while(vis[t] == 0) {
            c.push_back(t);
            vis[t] = 1;
            start += (t + 1) * (t + 1);
            t = a[t];
        }
        if(c.size()) {

            vector<double> f;
            for(ll tr = 0; tr < 2; tr++) {
                for(ll j = c.size() - 1; j >= 0; j--) {
                    f.push_back(c[(j + c.size() - 1) % c.size()] - c[j]);
                }
            } 

            // cout << "i : " << i << '\n';
            // cout << "c : " << c << '\n';
            // cout << "f : " << f << '\n';
            
            vector<double> ttfang = conv(c, f);
            for(auto &x : ttfang) x = round(x);
            // cout << "ttfang : " << ttfang << '\n';

            if(c.size() <= SN) {
                for(ll i = 0; i < c.size(); i++) {
                    pc[c.size()][i] += start;
                    start += ttfang[i + c.size() - 1];
                }
            } else {
                vector<ll> cop;
                for(ll i = 0; i < c.size(); i++) {
                    cop.push_back(start);
                    start += ttfang[i + c.size() - 1];
                }
                // cout << "cop : ";
                // for(auto x : cop) cout << x << " ";
                // cout << '\n';
                lg.push_back(cop);
            }
        }
    }

    for(ll i = 0; i < q; i++) {
        ll k; cin >> k;
        ll res = 0;
        for(ll i = 1; i <= SN; i++) {
            res += pc[i][k % i];
        }
        for(ll j = 0; j < lg.size(); j++) {
            res += lg[j][k % lg[j].size()];
        }
        cout << res << '\n';
        // cout << "solve slow : " << solve_slow(a, k) << '\n';
    }


}

// #include <bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// typedef long double ld;
// typedef pair<ll,ll> pii;
// typedef vector<ll> vi;

// #define rep(i, a, b) for(ll i = a; i < (b); ++i)
// #define all(x) begin(x), end(x)
// #define sz(x) (ll) (x).size()

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// typedef complex<double> C;
// typedef vector<double> vd;
// void fft(vector<C>& a) {
// 	int n = sz(a), L = 31 - __builtin_clz(n);
// 	static vector<complex<long double>> R(2, 1);
// 	static vector<C> rt(2, 1);  // (^ 10% faster if double)
// 	for (static int k = 2; k < n; k *= 2) {
// 		R.resize(n); rt.resize(n);
// 		auto x = polar(1.0L, acos(-1.0L) / k);
// 		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
// 	}
// 	vi rev(n);
// 	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
// 	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
// 	for (int k = 1; k < n; k *= 2)
// 		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
// 			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
// 			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
// 			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
// 			a[i + j + k] = a[i + j] - z;
// 			a[i + j] += z;
// 		}
// }
// vd conv(const vd& a, const vd& b) {
// 	if (a.empty() || b.empty()) return {};
// 	vd res(sz(a) + sz(b) - 1);
// 	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
// 	vector<C> in(n), out(n);
// 	copy(all(a), begin(in));
// 	rep(i,0,sz(b)) in[i].imag(b[i]);
// 	fft(in);
// 	for (C& x : in) x *= x;
// 	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
// 	fft(out);
// 	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
// 	return res;
// }

// const ll SN = 450;
// ll pc[SN + 1][SN + 1];
// vector<vector<ll>> lg;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL); cout.tie(NULL);

//     ll n, q; cin >> n >> q;
//     vector<ll> a(n);
//     for(ll &x : a) {
//         cin >> x;
//         x--;
//     }

//     vector<ll> vis(n);
//     for(ll i = 0; i < n; i++) {

//         ll t = i;
//         vector<double> c;
//         ll start = 0;

//         while(vis[t] == 0) {
//             c.push_back(t);
//             vis[t] = 1;
//             start += (t + 1) * (t + 1);
//             t = a[t];
//         }
//         if(c.size()) {

//             vector<double> f;
//             for(ll tr = 0; tr < 2; tr++) {
//                 for(ll j = c.size() - 1; j >= 0; j--) {
//                     f.push_back(c[(j + c.size() - 1) % c.size()] - c[j]);
//                 }
//             } 

//             // cout << "i : " << i << '\n';
//             // cout << "c : " << c << '\n';
//             // cout << "f : " << f << '\n';

//             int csz = c.size();

//             int sz = 1;
//             while(sz < f.size() || sz < c.size()) sz *= 2;
//             f.resize(sz);
//             c.resize(sz);
            
//             vector<double> ttfang = conv(c, f);
//             // cout << "ttfang : " << ttfang << '\n';
//             c.resize(csz);

//             if(c.size() <= SN) {
//                 for(ll i = 0; i < c.size(); i++) {
//                     pc[c.size()][i] += start;
//                     start += ttfang[i + c.size() - 1];
//                 }
//             } else {
//                 vector<ll> cop;
//                 for(ll i = 0; i < c.size(); i++) {
//                     cop.push_back(start);
//                     start += ttfang[i + c.size() - 1];
//                 }
//                 // cout << "cop : ";
//                 // for(auto x : cop) cout << x << " ";
//                 // cout << '\n';
//                 lg.push_back(cop);
//             }
//         }
//     }

//     for(ll i = 0; i < q; i++) {
//         ll k; cin >> k;
//         ll res = 0;
//         for(ll i = 1; i <= SN; i++) {
//             res += pc[i][k % i];
//         }
//         for(ll j = 0; j < lg.size(); j++) {
//             res += lg[j][k % lg[j].size()];
//         }
//         cout << res << '\n';
//         // cout << "solve slow : " << solve_slow(a, k) << '\n';
//     }


// }