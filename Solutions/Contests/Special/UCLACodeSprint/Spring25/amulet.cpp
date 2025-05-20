#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

#pragma GCC optimize("Ofast,fast-math,unroll-loops,no-stack-protector") 
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,avx2,fma,tune=native") 

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " " << (x < 10 ? " " : "");
    return os;
}

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string s, int lim=256) { // or vector<int>
		s.push_back(0); int n = sz(s), k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
			for (k && k--, j = sa[x[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

int pcd[400001], lo[400001], hi[400001], lens[400001], cnts[400001];

template<typename T>
struct sparse {
    vector<vector<T>> sparsetable;
    int n, d;
    sparse() {}
    sparse(vector<T> a) {
        buildTable(a);
    }
    T op(T a, T b) {
        return min(a,b);
    }
    void buildTable(vector<T> a) {
        n = a.size();
        d = 32 - __builtin_clz(n);
        sparsetable.assign(n, vector<T>(d));
        for(int depth = 0; depth < d; depth++) {
            for(int i = 0; i < n; i++) {
                if(depth) {
                    sparsetable[i][depth] = op(sparsetable[i][depth - 1], sparsetable[min(n - 1, i + (1 << (depth - 1)))][depth - 1]);
                } else {
                    sparsetable[i][depth] = a[i];
                }
            }
        }
    }
    //[l,r) always. 
    T query(int l, int r) {
        int depth = 31 - __builtin_clz(r - l);
        return op(sparsetable[l][depth], sparsetable[max(l,r - (1 << depth))][depth]);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    clock_t tStart = clock();

    int r, c, x, y; cin >> r >> c >> x >> y;

    char z = 'z' + 1;

    vector<string> a(r);
    for(auto &x : a) cin >> x;
    string s;
    for(int i = 0; i < r; i++) {
        s.append(a[i]);
        s.push_back(z);
    }
    for(int i = 0; i < c; i++) {
        for(int j = 0; j < r; j++) {
            s.push_back(a[j][i]);
        }
        s.push_back(z);
    }

    cout << "s : " << s << '\n';
    SuffixArray sa(s);

    cout << "sa  : " << sa.sa << '\n';
    cout << "lcp : " << sa.lcp << '\n';

    int stop = 1 + (r + 1) * c + r * (c + 1);

    vector<int> b(stop, -1); //which row/col is this idx assoc. with

    for(int j = 1; j < r * c * 2 + 1; j++) {
        int v = sa.sa[j];
        if(v < r * (c + 1)) {
            b[j] = v / (c + 1);
        } else {
            v -= r * (c + 1);
            b[j] = r + v / (r + 1);
        }
    }

    int rcnt = 0, ccnt = 0;
    lo[0] = stop;
    hi[0] = -1;
    sparse<int> rmq(sa.lcp);

    //add item for sliding window
    auto add = [&](int i) -> void {
        int v = b[i];
        if(cnts[v] == 0) {
            if(v < r) {
                rcnt++;
            } else {
                ccnt++;
            }
        }
        cnts[v]++;
    };

    //remove item for sliding window
    auto rem = [&](int i) -> void {
        int v = b[i];
        if(cnts[v] == 1) {
            if(v < r) {
                rcnt--;
            } else {
                ccnt--;
            }
        }
        cnts[v]--;
    };

    int sz = 0, idx = -1;

    int rp = 1;
    
    //two pointer, find the earliest such that it's good
    for(int lp = 1; lp < r * c * 2 + 1; lp++) {
        while(rp < r * c * 2 + 1 && (rcnt < x || ccnt < y)) {
            add(rp++);
        }

        if(rcnt == x && ccnt == y) {
            lo[lp] = rp - 1;
        } else {
            lo[lp] = r * c * 2 + 1;
        }

        if(lp == rp) {
            rp++;
        } else {
            rem(lp);
        }
    }

    rp = 1;

    //two pointer, find the last that is valid
    for(int lp = 1; lp < r * c * 2 + 1; lp++) {
        while(rp < r * c * 2 + 1) {
            add(rp);
            if(rcnt > x || ccnt > y) {
                rem(rp);
                break;
            } 
            rp++;
        }

        if(rcnt == x && ccnt == y) {
            hi[lp] = rp - 1;
        } else {
            hi[lp] = -1;
        }
        if(lp == rp) {
            rp++;
        } else {
            rem(lp);
        }
    }

    // cout << "cnts : " << cnts << '\n';

    // assert(count(cnts.begin(), cnts.end(), 0) == r + c);

    // cout << "lo : " << lo << '\n';
    // cout << "hi : " << hi << '\n';

    stack<array<int,2>> st; //{idx, lcp}

    for(int i = 1; i < stop; i++) {
        int lcp = sa.lcp[i];
        int p = i;

        while(st.size() && st.top()[1] > lcp) {
            p = st.top()[0];
            int j = i - 1;

            if(lo[p] <= j && j <= hi[p] && (lcp > sz || lcp == sz && ))


        }


    }

        // int p = 0;
        // for(int j = 1; j < r * c * 2 + 1; j++) {
        //     if(lens[j] < i) continue;

        //     if(rmq.query(p + 1, j + 1) < i) {
        //         if(lo[p] <= j - 1 && j - 1 <= hi[p]) {
        //             if(i > sz) {
        //                 sz = i;
        //                 idx = p;
        //             }
        //         }
        //         p = j;
        //     }
        // }

        // if(lo[p] <= r * c * 2 && r * c * 2 <= hi[p]) {
        //     if(i > sz) {
        //         sz = i;
        //         idx = p;
        //     }
        // }

    // cout << "sz : " << sz << " idx : " << idx << '\n';
    // cout << "r : " << r << " c : " << c << '\n';

    if(idx == -1) {
        cout << "-1\n";
        return 0;
    }

    idx = sa.sa[idx];
    string res;

    if(idx < r * c) {
        int row = idx / c;
        int col = idx % c;
        for(int j = 0; j < sz; j++) res.push_back(a[row][col + j]);
    } else {
        idx -= r * c;
        int col = idx / r;
        int row = idx % r;
        for(int j = 0; j < sz; j++) res.push_back(a[row + j][col]);
    }

    cout << res << '\n';

    // printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);


    return 0;
}

/*
HASH CODE
*/

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// mt19937 rng;

// bool isprime(ll num) {
//     if(num <= 1) return 0;
//     if(num == 2 || num == 3) return 1;
//     if(num % 2 == 0 || num % 3 == 0) return 0;
//     for(int i = 5; i <= sqrt(num); i++) {
//         if(num % i == 0 || num % (i + 2) == 0) return 0;
//     }
//     return 1;
// }

// ll gen_prime(ll l, ll r) { //generates a prime number [l,r]
//     while(1) {
//         ll num = (rng() % (r - l + 1)) + l;
//         if(isprime(num)) return num;
//     }
// }

// ll M1, M2, B1, B2;
// struct stringhash {
//     vector<ll> h1, h2;
//     vector<ll> p1, p2;
//     int n;

//     stringhash(string s) {
//         this->n = s.size();
//         p1.push_back(1);
//         for(int i = 0 ; i < n; i++) {
//             p1.push_back(p1.back() * B1 % M1);
//         }
//         p2.push_back(1);
//         for(int i = 0 ; i < n; i++) {
//             p2.push_back(p2.back() * B2 % M2);
//         }
//         h1.push_back(0);
//         for(int i = 0; i < n; i++) {
//             h1.push_back((h1[i] * B1 + s[i]) % M1);
//         }
//         h2.push_back(0);
//         for(int i = 0; i < n; i++) {
//             h2.push_back((h2[i] * B2 + s[i]) % M2);
//         }
//     }

//     ll get_hash(int l, int r) { //[l,r) because that's the cool, Andwerp way
//         ll num1 = (h1[r] - h1[l] * p1[r-l] % M1 + M1) % M1;
//         ll num2 = (h2[r] - h2[l] * p2[r-l] % M2 + M2) % M2;
//         return num1 + num2 * M1;
//     }

// };

// void buildsh() {
//     rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
//     M1 = gen_prime(900000000,1000000000);
//     B1 = gen_prime(9000,10000);
//     M2 = gen_prime(900000000,1000000000);
//     B2 = gen_prime(9000,10000);
// }

// #define rep(i, a, b) for(int i = a; i < (b); ++i)
// #define all(x) begin(x), end(x)
// #define sz(x) (int)(x).size()
// typedef long long ll;
// typedef pair<int, int> pii;
// typedef vector<int> vi;

// struct SuffixArray {
// 	vi sa, lcp;
// 	SuffixArray(string s, int lim=256) { // or vector<int>
// 		s.push_back(0); int n = sz(s), k = 0, a, b;
// 		vi x(all(s)), y(n), ws(max(n, lim));
// 		sa = lcp = y, iota(all(sa), 0);
// 		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
// 			p = j, iota(all(y), n - j);
// 			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
// 			fill(all(ws), 0);
// 			rep(i,0,n) ws[x[i]]++;
// 			rep(i,1,lim) ws[i] += ws[i - 1];
// 			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
// 			swap(x, y), p = 1, x[sa[0]] = 0;
// 			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
// 				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
// 		}
// 		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
// 			for (k && k--, j = sa[x[i] - 1];
// 					s[i + k] == s[j + k]; k++);
// 	}
// };

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     // ll tot = ((ll)8.3e17);

//     // ld p = 1;
//     // for(int i = 0; i < 89442719; i++) {
//     //     p *= ((ld) tot - i) / (tot);
//     // }

//     // cout << fixed << setprecision(10) <<  "p : " << p << '\n';

//     // p : 0.9951923170
//     //in hashing we trust

//     clock_t tStart = clock();


//     buildsh();

//     int r, c, x, y; cin >> r >> c >> x >> y;
//     vector<string> a(r);
//     for(auto &x : a) cin >> x;

//     if(x == 0) {
//         vector<string> t(c, string(r, '#'));
//         for(int i = 0; i < r; i++) {
//             for(int j = 0; j < c; j++) {
//                 t[j][i] = a[i][j];
//             }
//         }
//         t = a;
//         swap(r,c);
//         swap(x,y);
//     }

//     int stop = min(r, c);
//     vector<unordered_map<ll, pair<int, array<int,3>>>> rs(stop + 1), cs(stop + 1);


//     auto add = [&](vector<unordered_map<ll, pair<int, array<int,3>>>> &s, string t, int f) -> void {
//         stringhash sh(t);
//         vector<unordered_set<ll>> vis(stop + 1);
//         for(int l = 0; l < t.size(); l++) {
//             for(int r = l + 1; r - l <= stop && r <= t.size(); r++) {
//                 ll h = sh.get_hash(l, r);
//                 if(vis[r-l].count(h)) continue;
//                 vis[r-l].insert(h);
//                 if(s[r - l].count(h)) {
//                     s[r-l][h].first++;
//                 } else {
//                     s[r-l][h] = {1, {f, l, r}};
//                 }
//             }
//         }
//     };

//     for(int i = 0; i < r; i++) {
//         add(rs, a[i], i);
//     }

//     for(int i = 0; i < c; i++) {
//         string t;
//         for(int j = 0; j < r; j++) {
//             t.push_back(a[j][i]);
//         }
//         add(cs, t, i);
//     }

//     vector<int> b(r * c);

//     for(int i = 1; i <= stop; i++) {
//         for(auto it = rs[i].begin(); it != rs[i].end(); ) {
//             ll h = it->first;
//             if(it->second.first != x || (y == 0 && cs[i].count(h)) || y && cs[i].count(h) == 0 || y && cs[i][h].first != y) {
//                 it = rs[i].erase(it);
//             } else {
//                 int id = it->second.second[0] * c + it->second.second[1];
//                 int sz = it->second.second[2] - it->second.second[1];
//                 b[id] = max(b[id], sz);
//                 it++;
//             }
//         }
//     }
//     // cout << "b : " << b << '\n';

//     string t;
//     for(int i = 0; i < r; i++) t.append(a[i]);

//     // cout << "t : " << t << '\n';
//     SuffixArray sa(t);

//     // cout << "sa : " << sa.sa << '\n';

//     int idx = -1, sz = 0;
//     for(int i = 1; i < sa.sa.size(); i++) {
//         if(b[sa.sa[i]] > sz) {
//             idx = sa.sa[i];
//             sz = b[sa.sa[i]];
//         }
//     }

//     if(idx == -1) {
//         cout << "-1\n";
//         return 0;
//     }

//     // cout << "idx : " << idx << '\n';

//     int ro = idx / c, co = idx % c;
//     cout << a[ro].substr(co, sz) << '\n';

//     printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);


//     return 0;
// }
