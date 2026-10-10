#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

    int n; 
    cin >> n;

    vvi g(n), tg(n);

    for(int i = 0; i < n; i++) {
        int r;
        cin >> r;
        r--;

        g[i].emplace_back(r);
        tg[r].emplace_back(i);
    }

    vi vis(n);
    vi cycle(n);

    int omega;

    auto dfs = [&](auto self, int i) -> void {

        if(vis[i] == 2)
            return;

        if(vis[i] == 1) {
            omega = i;
            return;
        }
    
        vis[i] = 1;

        for(int to : g[i])
            self(self, to);

        if(omega != -1) {
            cycle[i] = 1;
        }

        if(omega == i) omega = -1;

        vis[i] = 2;

    };

    for(int i = 0; i < n; i++) {

        omega = -1;
        dfs(dfs, i);

    }


    int answer = 0;

    auto tree_dfs = [&](auto self, int i, int distance) -> int {

        int summation = 1;

        for(int from : tg[i]) 
            if(cycle[from] == 0)
                summation += self(self, from, distance + 1);

        return summation;
    };

    for(int i = 0; i < n; i++) 
        if(cycle[i])
            for(int z : tg[i]) 
                if(cycle[z] == 0) 
                    chkmax(answer, tree_dfs(tree_dfs, z, 0));

    cout << answer + 2 << endl;

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

// #include <bits/stdc++.h>
// using namespace std;

// // #pragma GCC optimize("O3,unroll-loops")
// // #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

// void fast_io() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     cout.tie(NULL);
//     cout << fixed << setprecision(15);
// }

// using ll     = long long;
// using ld     = long double;
// using ull    = unsigned long long;
// using pii    = pair<int, int>;
// using pll    = pair<ll, ll>;
// using vi     = vector<int>;
// using vll    = vector<ll>;
// using vpii   = vector<pii>;
// using vpll   = vector<pll>;
// using vvi    = vector<vi>;
// using vvll   = vector<vll>;

// const int MOD  = 1e9 + 7;
// const int MOD2 = 998244353;
// const ll INF   = 2e18;
// const ld PI    = acos(-1.0);
// const int dx[4] = {1, -1, 0, 0};
// const int dy[4] = {0, 0, 1, -1};

// #define pb          push_back
// #define ppb         pop_back
// #define mp          make_pair
// #define ff          first
// #define ss          second
// #define sz(x)       ((int)(x).size())
// #define all(x)      (x).begin(), (x).end()
// #define rall(x)     (x).rbegin(), (x).rend()
// #define mem(a, b)   memset(a, b, sizeof(a))

// #define FOR(i, a, b)    for (int i = (a); i < (b); ++i)
// #define F0R(i, a)       FOR(i, 0, a)
// #define ROF(i, a, b)    for (int i = (b)-1; i >= (a); --i)
// #define R0F(i, a)       ROF(i, 0, a)
// #define trav(a, x)      for (auto& a : x)

// #define sqr(x)      ((x) * (x))
// #define gcd(a, b)   __gcd(a, b)
// #define lcm(a, b)   ((a) * ((b) / gcd(a, b)))

// template<typename T> bool chkmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
// template<typename T> bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

// #ifdef LOCAL
// #define debug(x...) cout << "[" << #x << "] = ["; _print(x)
// #else
// #define debug(x...)
// #endif

// void __print(int x) {cout << x;}
// void __print(long x) {cout << x;}
// void __print(long long x) {cout << x;}
// void __print(unsigned x) {cout << x;}
// void __print(unsigned long x) {cout << x;}
// void __print(unsigned long long x) {cout << x;}
// void __print(float x) {cout << x;}
// void __print(double x) {cout << x;}
// void __print(long double x) {cout << x;}
// void __print(char x) {cout << '\'' << x << '\'';}
// void __print(const char *x) {cout << '"' << x << '"';}
// void __print(const string &x) {cout << '"' << x << '"';}
// void __print(bool x) {cout << (x ? "true" : "false");}

// template<typename T, typename V>
// void __print(const pair<T, V> &x) {cout << '{'; __print(x.first); cout << ','; __print(x.second); cout << '}';}

// template<typename T>
// void __print(const T &x) {
//     int f = 0;
//     cout << '{';
//     for (auto &i: x)
//         cout << (f++ ? "," : ""), __print(i);
//     cout << "}";
// }

// void _print() {cout << "]\n";}

// template <typename T, typename... V>
// void _print(T t, V... v) {
//     __print(t);
//     if (sizeof...(v)) cout << ", ";
//     _print(v...);
// }

// void solve(int tc) {

//     int n; 
//     cin >> n;

//     vvi g(n), tg(n);

//     for(int i = 0; i < n; i++) {
//         int r;
//         cin >> r;
//         r--;

//         g[i].emplace_back(r);
//         tg[r].emplace_back(i);
//     }

//     vi vis(n);
//     vi cycle(n);

//     int omega;

//     auto dfs = [&](auto self, int i) -> void {

//         if(vis[i] == 2)
//             return;

//         if(vis[i] == 1) {
//             omega = i;
//             return;
//         }
    
//         vis[i] = 1;

//         for(int to : g[i])
//             self(self, to);

//         if(omega != -1) {
//             cycle[i] = 1;
//         }

//         if(omega == i) omega = -1;

//         vis[i] = 2;

//     };

//     for(int i = 0; i < n; i++) {

//         omega = -1;
//         dfs(dfs, i);

//     }


//     int answer = 0;

//     auto tree_dfs = [&](auto self, int i, int distance) -> void {

//         chkmax(answer, distance);

//         for(int from : tg[i]) 
//             if(cycle[from] == 0)
//                 self(self, from, distance + 1);

//     };

//     for(int i = 0; i < n; i++) 
//         if(cycle[i])
//             tree_dfs(tree_dfs, i, 0);



//     cout << answer + 2 << endl;

// }

// int main() {
//     fast_io();

//     #ifdef LOCAL
//     #endif

//     int t = 1;
//     cin >> t;

//     for (int tc = 1; tc <= t; ++tc) {
//         solve(tc);
//     }

//     return 0;
// }