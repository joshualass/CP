#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;
mt19937 rng;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     // for(auto &x : v) os << x << " ";
//     // return os;
//     for(int i = 1; v.size() >= 1 << i; i++) {
//         for(int j = 1 << (i - 1); 1 << i > j; j++) {
//             // os << "i : " << i << " j : " << j << ' ';
//             os << v[j] << ' ';
//         }
//         os << '\n';
//     }
//     return os;
// }

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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
        ll num1 = (h1[r] - h1[l] * p1[r-l] % M1 + M1) % M1;
        ll num2 = (h2[r] - h2[l] * p2[r-l] % M2 + M2) % M2;
        return num1 + num2 * M1;
    }

};

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a,b);
    }
    Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //non
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    bool isLeaf(int idx) {
        return idx >= size;
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
    // optional MIQ stuff
    bool cond(T a, T b) {
        return a <= b;
    }
    //find the lowest index and value that satisfy the condition in range [l,r)
    pair<int,T> queryMIQ(T val, int lo, int hi) { //{index, value}
        pair<int,T> ans = _queryMIQ(1, 0, size, lo, hi, val);
        return ans;
    }   
    pair<int,T> _queryMIQ(int idx, int currl, int currr, int &lo, int &hi, T &val) {
        //check overlap of left bound
        // if(cond(val, v[idx])) {
        //     if(isLeaf(idx)) return {idx - size, v[idx]};
        //     int mid = (currl + currr) / 2;
        //     if(mid > lo && cond(val, v[idx * 2])) return _queryMIQ(idx * 2, currl, mid, lo, hi, val);
        //     return _queryMIQ(idx * 2 + 1, mid, currr, lo, hi, val);
        // } else {
        //     return {-1,base};
        // }
        
        if(currr <= lo || currl >= hi) {
            return {-1,base};
        }
        if(cond(val, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (currl + currr) / 2;
            pair<int,T> p = _queryMIQ(idx * 2, currl, mid, lo, hi, val);
            if(p.first != -1) {
                return p;
            }
            return _queryMIQ(idx * 2 + 1, mid, currr, lo, hi, val);
        } else {
            return {-1,base};
        }
    }
};

void solve() {
    int n, l, r; cin >> n >> l >> r;
    string s; cin >> s;
    stringhash sh(s);
    
    Tree<int> tree(n);
    for(int i = 0; i < n; i++) {
        int l = i, r = n;
        while(l != r) {
            int m = (l + r + 1) / 2;
            if(sh.get_hash(0,m-i) == sh.get_hash(i,m)) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        tree.update(i,l - i);
    }

    // cout << tree.v << '\n';

    vector<int> k(n+1);
    for(int i = 1; i <= n; i++) {
        //largest k possible for a given lcp = i. 
        int lo = 0;
        int cnt = 0;
        while(1) {
            pair<int,int> p = tree.queryMIQ(i,lo,n);
            if(p.first != -1) {
                cnt++;
                lo = p.first + i;
            } else {
                break;
            }
        }
        k[cnt] = i;
    }

    // cout << "k : " << k << '\n';

    for(int i = n - 1; i >= 0; i--) {
        k[i] = max(k[i],k[i+1]);
    }

    for(int i = l; i <= r; i++) {
        cout << k[i] << " \n"[i == r];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    M1 = gen_prime(900000000,1000000000);
    B1 = gen_prime(9000,10000);
    M2 = gen_prime(900000000,1000000000);
    B2 = gen_prime(9000,10000);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}