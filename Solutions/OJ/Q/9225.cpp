#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

vector<ll> p = {
    1'000'000'007, 
    // 1'000'000'009, 
    // 998244353,
    // 962592769, 
    970592641
};

const int big = 10000000;

ll fib[big][2];
ll mota[big];
int _trie[big][10], endcnt[big];
int tp = 0;

void add(string num) {
    int cur = 0;
    for(char c : num) {
        int d = c - '0';
        if(_trie[cur][d] == 0) {
            _trie[cur][d] = ++tp;
        }
        cur = _trie[cur][d];
    }
    endcnt[cur]++;
}

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;  // unordered_set but faster
template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster 

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

vector<string> gentc(int n) {
    vector<string> ans(n);
    for(int i = 0; i < n; i++){
        string s;
        for(int j = 0; j < 25; j++) s.push_back('0' + (rng() % 10));
        ans[i] = s;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    clock_t tStart = clock();

    int n; cin >> n;
    {
        vector<string> ss = gentc(n);
        for(int i = 0; i < n; i++) add(ss[i]);
    }

    // for(int i = 0; i < n; i++) {
    //     string x; cin >> x;
    //     add(x);
    // }

    vector<vector<string>> aa(2000001);

    auto dfs = [&](auto self, int cur, string &s) -> void {
        for(int i = 0; i < endcnt[cur]; i++) aa[s.size()].push_back(s);
        for(int i = 0; i < 10; i++) {
            if(_trie[cur][i]) {
                s.push_back(i + '0');
                self(self, _trie[cur][i], s);
                s.pop_back();
            }
        }
    };

    auto get_mota = [&](array<ll,2> a) -> ll {
        return a[0] * 970592641 + a[1];
    };

    string s = "";
    dfs(dfs, 0, s);

    vector<string> a;
    for(auto x : aa) for(auto y : x) a.push_back(y);

    // printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    tStart = clock();
    // for(auto x : a) cout << x << '\n';

    for(int i = 0; i < 2; i++) fib[1][i] = 1;

    for(int i = 2; i < big; i++) {
        for(int j = 0; j < 2; j++) {
            fib[i][j] = (fib[i-1][j] + fib[i-2][j]) % p[j];
        }
        mota[i] = get_mota(array<ll,2>{fib[i][0], fib[i][1]});
    }

    ld logfib = log10l((1 + sqrtl(5)) / 2);
    // cout << "logfib : " << 2000000 / logfib << '\n';
    // printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    tStart = clock();

    pb_map<ll, ll> m;
    ll res = 0;

    double time = 0;

    for(string num : a) {
        array<ll,2> hs = {};
        for(char x : num) {
            for(int j = 0; j < 2; j++) {
                hs[j] = (hs[j] * 10 + (x - '0')) % p[j];
            }
        }

        int approx_fib = num.size() / logfib;

        for(int f = max(0, approx_fib - 10); f <= approx_fib + 10; f++) {
            array<ll,2> inv = {};
            for(int j = 0; j < 2; j++) {
                // inv[j] = (fib[f][j] - hs[j] + p[j]) % p[j];
                inv[j] = fib[f][j] - hs[j];
                if(inv[j] < 0) inv[j] += p[j];
                if(inv[j] >= p[j]) inv[j] -= p[j];
            }
            clock_t gg = clock();
            res += m[get_mota(inv)];
            time += (double)(clock() - gg)/CLOCKS_PER_SEC;
        }
        m[get_mota(hs)]++;
    }

    cout << res << '\n';
    // printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    // cout << "time : " << time << '\n';

    return 0;
}
