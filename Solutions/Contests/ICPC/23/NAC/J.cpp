#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;



#define rep(i, a, b) for(int i = 0; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
struct hstring {
    static const ll M = 1e9 + 9;
    ll B = uniform_int_distribution<ll>(0, M - 1)(rng);

    vector<ll> pow, p_hash;

    hstring(const string &s) {
        p_hash = vl(s.size() + 1);
        pow = vl(1, 1);
        while(pow.size() <= s.size()) {
            pow.push_back((pow.back() * B) % M);
        }
        p_hash[0] = 0;
        for(int i = 0; i < s.size(); i++) {
            p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
        }
    }

    ll get_hash(int start, int end) {
        ll raw = (p_hash[end] - (p_hash[start] * pow[end - start]));
        return (raw % M + M) % M;
    }
};

ll solve(string s) {
    hstring hs(s);
    int n = s.size();
    //for every suffix, precompute all the hashes and their counts
    vector<unordered_map<ll, int>> sfx(n + 1);
    for(int i = n - 1; i >= 0; i--){
        for(int j = i; j < n; j++){
            for(int k = j + 1; k <= n; k++){
                sfx[i][hs.get_hash(j, k)] ++;
            }
        }
    }
    //calc ans
    ll ans = 0;
    for(int l = 0; l < n; l++){
        for(int r = l + 1; r < n; r++){
            for(int i = 0; i <= r - l && r + i <= n; i++){
                //string to be doubled is s[l, r). Need s[l + i, r) as suffix
                ll h = hs.get_hash(l + i, r);
                ans += sfx[r + i][h];
                // cout << "FIND ANS : " << l << " " << r << " " << i << " " << sfx[r + i][h] << "\n";
                //check that incrementing i will keep the prefix
                if(r + i != n && s[r + i] != s[l + i]) break;
            }
        }
    }

    return ans;
}

ll solve2(string s) {
    hstring hs(s);
    int n = s.size();
    //for every suffix, precompute all the hashes and their counts
    vector<unordered_map<ll, int>> sfx(n + 1);
    for(int i = n - 1; i >= 0; i--){
        for(int j = i; j < n; j++){
            for(int k = j + 1; k <= n; k++){
                sfx[i][hs.get_hash(j, k)] ++;
            }
        }
    }
    //calc ans
    ll ans = 0;
    for(int l = 0; l < n; l++){
        for(int r = l + 1; r < n; r++){
            if(s[l] != s[r]) continue; 
            for(int i = 1; i <= r - l && r + i <= n; i++){
                //string to be doubled is s[l, r). Need s[l + i, r) as suffix
                ll h = hs.get_hash(l + i, r);
                ans += sfx[r + i][h];
                //check that incrementing i will keep the prefix
                if(r + i != n && s[r + i] != s[l + i]) break;
            }
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    string s;
    cin >> s;
    ll ans = solve(s);
    reverse(s.begin(), s.end());
    ans += solve2(s);
    cout << ans << "\n";

    return 0;
}