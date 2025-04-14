#include<bits/stdc++.h>
using namespace std;
typedef int64_t LL;
typedef vector<int> vi;
typedef pair<LL,LL> pii;
#define mp make_pair
#define pb push_back
#define f first
#define s second
#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) "LAMELO > MJ"
#endif

typedef long long ll;
typedef long double ld;

mt19937 rng;
LL n,q;
string s;

bool isprime(ll num) {
    if(num <= 1) return 0;
    if(num == 2 || num == 3) return 1;
    if(num % 2 == 0 || num % 3 == 0) return 0;
    for(int i = 5; i <= sqrt(num); i++) {
        if(num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

ll gen_prime(ll l, ll r) { //generates a prime number [l,r]
    while(1) {
        ll num = (rng() % (r - l + 1)) + l;
        if(isprime(num)) return num;
    }
}

ll M1, M2, B1, B2;
struct stringhash {
    vector<ll> h1, h2;
    vector<ll> p1, p2;
    int n;

    stringhash(string s) {
        this->n = s.size();
        p1.push_back(1);
        for(int i = 0 ; i < n; i++) {
            p1.push_back(p1.back() * B1 % M1);
        }
        p2.push_back(1);
        for(int i = 0 ; i < n; i++) {
            p2.push_back(p2.back() * B2 % M2);
        }
        h1.push_back(0);
        for(int i = 0; i < n; i++) {
            h1.push_back((h1[i] * B1 + s[i]) % M1);
        }
        h2.push_back(0);
        for(int i = 0; i < n; i++) {
            h2.push_back((h2[i] * B2 + s[i]) % M2);
        }
    }

    ll get_hash(int l, int r) { //[l,r) because that's the cool, Andwerp way
        // r++;
        l--;
        ll num1 = (h1[r] - h1[l] * p1[r-l] % M1 + M1) % M1;
        ll num2 = (h2[r] - h2[l] * p2[r-l] % M2 + M2) % M2;
        return num1 + num2 * M1;
    }

};

void buildsh() {
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    M1 = gen_prime(900000000,1000000000);
    B1 = gen_prime(9000,10000);
    M2 = gen_prime(900000000,1000000000);
    B2 = gen_prime(9000,10000);
}

//range minimum query. O(1) query, O(n) build/memory. fast.
template<typename T>
struct RMQ  {
    vector<T> elements;
    int n;
    static const int block_size = 30; // block size. adjust accordingly
    vector<int> mask, sparse_table;
    int op(int x, int y) { //update this method to determine what value we are trying to find. Currently set to minimum (return index of minimum element)
        return elements[x] < elements[y] ? x : y;
    }
    int least_significant_bit(int x) {return x & -x;}
    int most_significant_bit_index(int x) {return 31 - __builtin_clz(x);}
    int small_query(int r, int size = block_size) {return r - most_significant_bit_index(mask[r] & ((1<<size)-1));}
    RMQ() {} //need this to satisfy master goon's requirements
    RMQ (const vector<T>& input) {build(input);}
    void build (const vector<T>& input) {
        elements = input;
        n = input.size();
        mask.assign(n,0);
        sparse_table.assign(n,0);
        int curr_mask = 0;
        for(int i = 0; i < n; i++) {
            curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
            while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) curr_mask ^= least_significant_bit(curr_mask);
            curr_mask |= 1;
            mask[i] = curr_mask;
        }
        for(int i = 0; i < n/block_size; i++) sparse_table[i] = small_query(block_size * i + block_size - 1);
        for(int j = 1; (1<<j) <= n/block_size; j++) for(int i = 0; i + (1<<j) <= n / block_size; i++) sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
    }
    T query(int l, int r) {//query(l,r) returns the element from the minimum of v[l..r]
        if(r - l + 1 <= block_size) return elements[small_query(r, r - l + 1)];
        int ans = op(small_query(l + block_size - 1), small_query(r)); 
        int x = l / block_size + 1, y = r / block_size - 1;
        if(x <= y) {
            int j = most_significant_bit_index(y - x + 1);
            ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
        }
        return elements[ans]; //return the value
        // return ans;        //return the index with value
    }
};
struct SuffixArray {
    // suffix array given string as well as how many of prefix match among neighbors
    vector<int> sa, lcp;
    SuffixArray(string& s, int lim=256) { // or basic_string<int>
        int n = s.size() + 1, k = 0, a, b;
        vector<int> x(s.begin(), s.end() + 1), y(n), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(sa.begin(), sa.end(), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(y.begin(), y.end(), n - j);
            for(int i = 0; i < n; i++){
                if (sa[i] >= j) y[p++] = sa[i] - j;
            }
            fill(ws.begin(), ws.end(), 0);
            for(int i = 0; i < n; i++){
                ws[x[i]]++;
            }
            for(int i = 1; i < lim; i++){
                ws[i] += ws[i - 1];
            }
            for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            for(int i = 1; i < n; i++){
                a = sa[i - 1];
                b = sa[i];
                x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
            }
        }
        for(int i = 1; i < n; i++){
            rank[sa[i]] = i;
        }
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k){
            for (k && k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++);
        }
    }
};

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

int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0);

    buildsh();

    cin >> n >> q >> s;
    stringhash ss(s);
    pb_map<LL,LL> ending, sum;
    LL root = 450;
    for(int len = 1; len <= root; len++){
        for(int l = 1; l + len - 1 <= n; l++){
            int r = l + len - 1;
            LL hash = ss.get_hash(l,r);
            if(ending[hash] < l){
                sum[hash] += len;
            }else{
                sum[hash] += r - ending[hash];
            }
            ending[hash] = r;
        }
    }
    SuffixArray sa(s);
    vector<LL> loc(n + 1);
    sa.sa.erase(sa.sa.begin());
    for(int i = 0; i < n; i++){
        sa.sa[i] += 1;
        loc[sa.sa[i]] = i;
    }
    vector<RMQ<int>> mini,maxi;
    vector<pii> ranges(root, {1e9, -1e9});
    for(int i = 0; i < root; i++){
        ranges[i] = {(LL) i * root + 1, (LL) (i + 1) * root};
    }
    for(int i = 0; i < root; i++){
        vector<int> currmaxi, currmini;
        for(int j = 0; j < n; j++){
            if(sa.sa[j] >= ranges[i].f && sa.sa[j] <= ranges[i].s){
                currmini.pb(sa.sa[j]);
                currmaxi.pb(-sa.sa[j]);
            }else{
                currmini.pb(1e9);
                currmaxi.pb(1e9);
            }
        }
        mini.pb(RMQ(currmini));
        maxi.pb(RMQ(currmaxi));
    }
    debug(sa.sa);
    for(int i = 0; i < q; i++){
        LL x,y; cin >> x >> y;
        LL len = y - x + 1;
        if(y - x + 1 <= root){
            cout << sum[ss.get_hash(x,y)] << "\n";
        }else{
            LL l = -1, r = loc[x];
            while(l + 1 < r){
                LL mid = (l + r + 1) / 2;
                if(ss.get_hash(sa.sa[mid], sa.sa[mid] + len - 1) == ss.get_hash(x,y)){
                    r = mid;
                }else{
                    l = mid;
                }
            }
            LL l2 = loc[x], r2 = n;
            while(l2 + 1 < r2){
                LL mid = (l2 + r2) / 2;
                if(ss.get_hash(sa.sa[mid], sa.sa[mid] + len - 1) == ss.get_hash(x,y)){
                    l2 = mid;
                }else{
                    r2 = mid;
                }
            }
            LL rightmost = 0, total = 0;
            for(int j = 0; j < root; j++){
                LL currl = mini[j].query(r, l2);
                LL currr = -maxi[j].query(r, l2);
                if(currl != 1e9){
                    // add [currl, currl + len - 1];
                    if(currl > rightmost){
                        total += len;
                    }else{
                        total += currl + len - 1 - rightmost;
                    }
                    rightmost = currl + len - 1;
                    // add [currr, currr + len - 1]
                    if(currr > rightmost){
                        total += len;
                    }else{
                        total += currr + len - 1 - rightmost;
                    }
                    rightmost = currr + len - 1;
                }
            }
            cout << total << "\n";
        }
    }

    cout.flush();
    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// struct SuffixArray {
//     string S;
//     int N;
//     vector<int> sa;
//     vector<int> isa;

//     SuffixArray() {}

//     SuffixArray(string _S) {
//         N = (S = _S).size() + 1;
//         genSa();
//     }

//     void init(string _S) {
//         N = (S = _S).size() + 1;
//         genSa();
//     }

//     void genSa() { //suffix array has size S.size() + 1, starts with s.size()
//         sa = vector<int>(N);
//         isa = vector<int>(N);
//         sa[0] = N-1;
//         iota(1 + sa.begin(), sa.end(), 0);
//         sort(1 + sa.begin(), sa.end(), [&](int a, int b) {
//             return S[a] < S[b]; 
//         });
// 		for(int i = 1; i < N; i++) { 
//             int a = sa[i-1];
//             int b = sa[i];
// 			isa[b] = i > 1 && S[a] == S[b] ? isa[a] : i; 
//         }
//         for(int len = 1; len < N; len *= 2) {
//             //by first len chars
//             vector<int> s(sa);
//             vector<int> is(isa);
//             vector<int> pos(N);
//             iota(pos.begin(), pos.end(),0);
//             for(auto &t : s) {
//                 int T = t - len;
//                 if(T >= 0) {
//                     sa[pos[isa[T]]++] = T;
//                 }
//             }
//             for(int i = 1; i < N; i++) {
//                 int a = sa[i - 1];
//                 int b = sa[i];
//                 isa[b] = is[a] == is[b] && is[a + len] == is[b + len]  ? isa[a] : i;
//             }
//         }
//     }
// };

// const int SQN = 450;

// int pc[SQN][SQN][2];

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, q; cin >> n >> q;
//     string s; cin >> s;

//     SuffixArray sa(s);



//     for(int i = 0; i < q; i++) {

//     }

//     return 0;
// }
