#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,fma,bmi,bmi2")
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll gcdExtended(ll a, ll b, ll *x, ll *y);
 
ll modInverse(ll b, ll m) {
    ll x, y;
    ll g = gcdExtended(b, m, &x, &y);
 
    if (g != 1) return -1;
 
    return (x % m + m) % m;
}
  // Function to compute a/b under modulo m
ll modDivide(ll a, ll b) {
    a = a % MOD;
    int inv = modInverse(b, MOD);
    return (inv * a) % MOD;
}
 
ll gcdExtended(ll a, ll b, ll *x, ll *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
 
    ll x1, y1;
    ll gcd = gcdExtended(b % a, a, &x1, &y1);
 
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
}

// template<typename T>
// struct Tree {
//     static constexpr T base = 0;
//     vector<T> v;
//     int n, size;
//     T comb(T a, T b) { //change this when doing maximum vs minimum etc.
//         return a + b;
//     }
//     Tree(int n = 0, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] = val;
//         while(curr != 1) {
//             if(curr & 1) { //non
//                 v[curr / 2] = comb(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = comb(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     bool isLeaf(int idx) {
//         return idx >= size;
//     }
//     T at(int idx) {
//         assert(idx >= 0 && idx < n);
//         return v[idx + size];
//     }
//     T query(int l, int r) {//queries in range [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
//         if(currr <= targetl || currl >= targetr) return base;
//         if(currl >= targetl && currr <= targetr) return v[idx];
//         int mid = (currl + currr) / 2;
//         return comb(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
// };

struct Tree {
	typedef ll T;
	const T unit = 0;
	T f(T a, T b) { return a + b; }
	vector<T> s; int n;
	Tree(int n = 0, T def = 0) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos > 1; pos /= 2)
			s[pos / 2] = f(s[pos & ~1], s[pos | 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
    T at(int i) {
        return s[i+n];
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    vector<vector<ll>> mat(n,vector<ll>(m));

    // vector<array<Tree<ll>,3>> trees;
    // trees.push_back({Tree<ll>(n),Tree<ll>(n),Tree<ll>(n)});
    // trees.push_back({Tree<ll>(n),Tree<ll>(n),Tree<ll>(n)});
    // trees.push_back({Tree<ll>(m),Tree<ll>(m),Tree<ll>(m)});
    // trees.push_back({Tree<ll>(m),Tree<ll>(m),Tree<ll>(m)});

    vector<array<Tree,3>> trees;
    trees.push_back({Tree(n),Tree(n),Tree(n)});
    trees.push_back({Tree(n),Tree(n),Tree(n)});
    trees.push_back({Tree(m),Tree(m),Tree(m)});
    trees.push_back({Tree(m),Tree(m),Tree(m)});

    map<ll,vector<pair<ll,ll>>> v;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            ll a; cin >> a;
            v[a].push_back({i,j});
        }
    }

    ll prev = 0;
    ll sum = 0;

    for(auto [u, x] : v) {
        ll addsum = 0;
        for(pair<ll,ll> p : x) {
            ll d = 0;
            for(int i = 0; i < 2; i++) {
                ll getstart = p.first;
                if(i & 1) {
                    getstart = n - getstart - 1;
                }
                getstart++;
                ll cnt = trees[i][2].query(getstart,n);
                d = (d + trees[i][0].query(getstart,n) - (trees[i][1].query(getstart,n) - cnt * getstart) * getstart * 2 -  getstart * (getstart + 2) * cnt) % MOD;
                if(d < 0) d += MOD; 
            }

            for(int i = 2; i < 4; i++) {
                ll getstart = p.second;
                if(i & 1) {
                    getstart = m - getstart - 1;
                }
                getstart++;
                ll cnt = trees[i][2].query(getstart,m);
                d = (d + trees[i][0].query(getstart,m) - (trees[i][1].query(getstart,m) - cnt * getstart) * getstart * 2 - getstart * (getstart + 2) * cnt) % MOD;
                if(d < 0) d += MOD;
            }
            ll res = (d + sum) * modInverse(prev, MOD) % MOD;
            mat[p.first][p.second] = res;
            addsum = (addsum + res) % MOD;
            // cout << "coords : " << p.first << " " << p.second << " d : " << d << '\n';
        }
        prev += x.size();
        sum = (sum + addsum) % MOD;

        for(pair<ll,ll> p : x) {
            for(int i = 0; i < 4; i++) {
                ll start;
                if(i == 0) {
                    start = p.first;
                } else if(i == 1) {
                    start = n - p.first - 1;
                } else if(i == 2) {
                    start = p.second;
                } else {
                    start = m - p.second - 1;
                }
                trees[i][0].update(start, (trees[i][0].at(start) + (start + 1) * (start + 1)));
                trees[i][1].update(start, (trees[i][1].at(start) + start));
                trees[i][2].update(start, (trees[i][2].at(start) + 1));
            }
        }

    }

    int r, c; cin >> r >> c;
    cout << mat[r-1][c-1] << '\n';

    return 0;
}