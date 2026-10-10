
#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << fixed << setprecision(15);
}

using ll     = long long;
using ld     = long double;
using ull    = unsigned long long;
using pii    = pair<int, int>;
using pll    = pair<ll, ll>;
using vi     = vector<int>;
using vll    = vector<ll>;
using vpii   = vector<pii>;
using vpll   = vector<pll>;
using vvi    = vector<vi>;
using vvll   = vector<vll>;

const int MOD  = 1e9 + 7;
const int MOD2 = 998244353;
const ll INF   = 2e18;
const ld PI    = acos(-1.0);
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

#define pb          push_back
#define ppb         pop_back
#define mp          make_pair
#define ff          first
#define ss          second
#define sz(x)       ((int)(x).size())
#define all(x)      (x).begin(), (x).end()
#define rall(x)     (x).rbegin(), (x).rend()
#define mem(a, b)   memset(a, b, sizeof(a))

#define FOR(i, a, b)    for (int i = (a); i < (b); ++i)
#define F0R(i, a)       FOR(i, 0, a)
#define ROF(i, a, b)    for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a)       ROF(i, 0, a)
#define trav(a, x)      for (auto& a : x)

#define sqr(x)      ((x) * (x))
#define gcd(a, b)   __gcd(a, b)
#define lcm(a, b)   ((a) * ((b) / gcd(a, b)))

template<typename T> bool chkmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template<typename T> bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

#ifdef LOCAL
#define debug(x...) cout << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

void __print(int x) {cout << x;}
void __print(long x) {cout << x;}
void __print(long long x) {cout << x;}
void __print(unsigned x) {cout << x;}
void __print(unsigned long x) {cout << x;}
void __print(unsigned long long x) {cout << x;}
void __print(float x) {cout << x;}
void __print(double x) {cout << x;}
void __print(long double x) {cout << x;}
void __print(char x) {cout << '\'' << x << '\'';}
void __print(const char *x) {cout << '"' << x << '"';}
void __print(const string &x) {cout << '"' << x << '"';}
void __print(bool x) {cout << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cout << '{'; __print(x.first); cout << ','; __print(x.second); cout << '}';}

template<typename T>
void __print(const T &x) {
    int f = 0;
    cout << '{';
    for (auto &i: x)
        cout << (f++ ? "," : ""), __print(i);
    cout << "}";
}

void _print() {cout << "]\n";}

template <typename T, typename... V>
void _print(T t, V... v) {
    __print(t);
    if (sizeof...(v)) cout << ", ";
    _print(v...);
}

void solve(int tc) {
    int n, q;
    cin >> n >> q;

    vvll prefixsumr(n + 1, vll(n + 1));
    vvll prefixsumc(n + 1, vll(n + 1));
    vvll prefixsum(n + 1, vll(n + 1));
    vvll a(n, vll(n));

    trav(x, a) trav(y, x) cin >> y;

    FOR(i, 1, n + 1) {
        FOR(j, 1, n + 1) {
            prefixsum[i][j] = prefixsum[i - 1][j] + prefixsum[i][j - 1] - prefixsum[i - 1][j - 1] + a[i - 1][j - 1];

            prefixsumr[i][j] = prefixsumr[i - 1][j] + prefixsumr[i][j - 1] - prefixsumr[i - 1][j - 1] + a[i - 1][j - 1] * i;

            prefixsumc[i][j] = prefixsumc[i - 1][j] + prefixsumc[i][j - 1] - prefixsumc[i - 1][j - 1] + a[i - 1][j - 1] * j;
        }
    }

    auto getprefixsum = [](int x1, int y1, int x2, int y2, vvll &pref) -> ll {
        return pref[x2][y2] - pref[x2][y1 - 1] - pref[x1 - 1][y2] + pref[x1 - 1][y1 - 1];
    };

    F0R(i, q) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        ll cnt = y2 - y1 + 1;
        ll row = getprefixsum(x1, y1, x2, y2, prefixsumr) * cnt - getprefixsum(x1, y1, x2, y2, prefixsum) * x1 * cnt;
        ll col = getprefixsum(x1, y1, x2, y2, prefixsumc) - getprefixsum(x1, y1, x2, y2, prefixsum) * (y1 - 1);

        cout << row + col << " \n"[i == q - 1];
    }
}

int main() {
    fast_io();

    #ifdef LOCAL
    #endif

    int t = 1;
    cin >> t;

    for (int tc = 1; tc <= t; ++tc) {
        solve(tc);
    }

    return 0;
}