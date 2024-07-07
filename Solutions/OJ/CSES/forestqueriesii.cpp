#pragma GCC optimize("Ofast,fast-math,unroll-loops,no-stack-protector") 
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,avx2,fma,tune=native") 



#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

static constexpr int base = 0;
int a[5000][5000];
int sz = 1 << 10;
int n;

int comb(int a, int b) {
    return a + b;
}

void update(int x, int y, int val) {
    assert(x < n && x >= 0 && y < n && y >= 0);
    int cx = x + sz;
    int cy = y + sz;
    a[cx][cy] = val;
    bool parity = 1;
    //maintain cx >
    while(cx != 1) {
        if(parity == 0) {
            cx /= 2;
            a[cx][cy] = comb(a[cx * 2][cy], a[cx * 2 + 1][cy]);
        } else {
            cy /= 2;
            a[cx][cy] = comb(a[cx][cy * 2], a[cx][cy * 2 + 1]);
        }
        parity ^= 1;
    }
}

bool isLeaf(int x, int y) {
    return x >= sz || y >= sz;
}

int at(int x, int y) {
    assert(x >= 0 && x < n && y >= 0 && y < n);
    return a[x + sz][y + sz];
}

int _query(int xid, int yid, int clx, int cly, int crx, int cry, int tlx, int tly, int trx, int tryy, bool parity) {
    // cout << "x [l,r) [" << clx << "," << crx << ")\n";
    // cout << "y [l,r) [" << cly << "," << cry << ")\n";
    //check complete overlap
    if(clx >= tlx && crx <= trx && cly >= tly && cry <= tryy) return a[xid][yid];
    //check if 0 overlap
    if(clx >= trx || crx <= tlx || cly >= tryy || cry <= tly) {
        // cout << "no overlap returning\n";
        return base;
    }
    if(parity == 0) {
        int mx = (clx + crx) / 2;
        return comb(
            _query(xid * 2, yid, clx, cly, mx, cry, tlx, tly, trx, tryy, parity ^ 1),
            _query(xid * 2 + 1, yid, mx, cly, crx, cry, tlx, tly, trx, tryy, parity ^ 1)
        );
    } else {
        int my = (cly + cry) / 2;
        return comb(
            _query(xid, yid * 2, clx, cly, crx, my, tlx, tly, trx, tryy, parity ^ 1),
            _query(xid, yid * 2 + 1, clx, my, crx, cry, tlx, tly, trx, tryy, parity ^ 1)
        );
    }
}
 
int query(int lx, int ly, int rx, int ry) {
    return _query(1, 1, 0, 0, sz, sz, lx, ly, rx, ry,0);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(a,0,sizeof(a));

    clock_t tStart = clock();
    freopen("forestqueriesii.txt","r",stdin);
    // freopen(".out","w",stdout);
    
    int q; cin >> n >> q;
 
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < n; j++) {
            if(s[j] == '*') {
                update(i,j,1);
            }
        }
    }

    // cout << query(0,0,n,n) << '\n';
    // cout << query(0,0,2,2) << '\n';
 
    for(int i = 0; i < q; i++) {
        int t; cin >> t;
        if(t == 1) {
            int x, y; cin >> x >> y;
            x--; y--;
            // tree.update(x,y,tree.at(x,y) ^ 1);
            update(x,y,at(x,y) ^ 1);
        } else {
            int lx, ly, rx, ry; cin >> lx >> ly >> rx >> ry;
            // cout << tree.query(lx-1,ly-1,rx,ry) << '\n';
            // cout << query(lx-1,ly-1,rx,ry) << '\n';
            // tree.query(lx-1,ly-1,rx,ry);
            query(lx-1,ly-1,rx,ry);
        }
    }

    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
 
    return 0;
}
 
// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;
 
// template<typename T>
// struct Tree {
//     static constexpr T base = 0;
//     vector<T> v;
//     int n, size;
//     T comb(T a, T b) { //change this when doing maximum vs minimum etc.
//         return a + b;
//     }
//     // optional MIQ stuff
//     bool cond(T a, T b) {
//         return a <= b;
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
//     //find the lowest index and value that satisfy the condition in range [l,r)
//     pair<int,T> queryMIQ(T val, int lo, int hi) { //{index, value}
//         pair<int,T> ans = _queryMIQ(1, 0, size, lo, hi, val);
//         return ans;
//     }   
//     pair<int,T> _queryMIQ(int idx, int currl, int currr, int &lo, int &hi, T &val) {
//         //check overlap of left bound
//         if(cond(val, v[idx])) {
//             if(isLeaf(idx)) return {idx - size, v[idx]};
//             int mid = (currl + currr) / 2;
//             if(mid > lo && cond(val, v[idx * 2])) return _queryMIQ(idx * 2, currl, mid, lo, hi, val);
//             return _queryMIQ(idx * 2 + 1, mid, currr, lo, hi, val);
//         } else {
//             return {-1,base};
//         }
//     }
// };
 
// Tree<int> v[1000];
 
// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, q; cin >> n >> q;
//     // vector<Tree<int>> v(n,Tree<int>(n));
//     for(int i = 0; i < n; i++) {
//         v[i].n = n;
//         v[i].size = 2048;
//         v[i].v.assign(2048 * 2, v[i].base);
//         for(int j = 0; j < n; j++) {
//             char c; cin >> c;
//             if(c == '*') {
//                 v[i].update(j,1);
//             }
//         }
//     }
//     for(int i = 0; i < q; i++) {
//         int type; cin >> type;
//         if(type == 1) {
//             int x, y; cin >> x >> y;
//             x--; y--;
//             v[x].update(y,v[x].at(y) ^ 1);
//         }
//         if(type == 2) {
//             int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
//             x1--;
//             y1--;
//             // x2--;
//             // y2--;
//             int sum = 0;
//             for(int row = x1; row < x2; row++) {
//                 sum += v[row].query(y1,y2);
//             }
//             cout << sum << '\n';
//         }
//     }
 
//     // cout << "OK!\n";
 
//     return 0;
// }

// #pragma GCC optimize("Ofast,fast-math,unroll-loops,no-stack-protector") 
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,avx2,fma,tune=native") 

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// //basic 2d segtree ig. 
// template <typename T> 
// struct Tree2D {
//     static constexpr T base = 0;
//     vector<vector<T>> a;
//     int n, size;
//     T comb(T a, T b) {
//         return a + b;
//     }

//     Tree2D(int n = 0, T def = base) {
//         this->n = n;
//         size = 1;
//         while(size < n) size *= 2;
//         a.assign(size * 2, vector<T>(size * 2, def));
//     }

//     void update(int x, int y, T val) {
//         assert(x < n && x >= 0 && y < n && y >= 0);
//         int cx = x + size;
//         int cy = y + size;
//         a[cx][cy] = val;
//         while(cx != 1) {
//             cx /= 2;
//             cy /= 2;
//             a[cx][cy] = comb(comb(a[cx * 2][cy * 2], a[cx * 2][cy * 2 + 1]), comb(a[cx * 2 + 1][cy * 2], a[cx * 2 + 1][cy * 2 + 1]));
//         }
//     }

//     bool isLeaf(int x, int y) {
//         return x >= size || y >= size;
//     }
//     T at(int x, int y) {
//         assert(x >= 0 && x < n && y >= 0 && y < n);
//         return a[x + size][y + size];
//     }

//     T query(int lx, int ly, int rx, int ry) {
//         return _query(1, 1, 0, 0, size, size, lx, ly, rx, ry);
//     }

//     bool overlap(const int &clx, const int &cly, const int &crx, const int &cry, const int &tlx, const int &tly, const int &trx, const int &tryy) {
//         return !(clx >= trx || crx <= tlx || cly >= tryy || cry <= tly);
//     }

//     T _query(int xid, int yid, int clx, int cly, int crx, int cry, int &tlx, int &tly, int &trx, int &tryy) {
//         if(clx >= tlx && crx <= trx && cly >= tly && cry <= tryy) return a[xid][yid];
//         int mx = (clx + crx) / 2;
//         int my = (cly + cry) / 2;
//         T res = base;
//         if(overlap(clx,cly,mx,my,tlx,tly,trx,tryy)) {
//             res = comb(res,_query(xid * 2, yid * 2, clx, cly, mx, my, tlx, tly, trx, tryy));
//         }
//         if(overlap(clx,my,mx,cry,tlx,tly,trx,tryy)) {
//             res = comb(res,_query(xid * 2, yid * 2 + 1, clx, my, mx, cry, tlx, tly, trx, tryy));
//         }
//         if(overlap(mx,cly,crx,my,tlx,tly,trx,tryy)) {
//             res = comb(res,_query(xid * 2 + 1, yid * 2, mx, cly, crx, my, tlx, tly, trx, tryy));
//         }
//         if(overlap(mx,my,crx,cry,tlx,tly,trx,tryy)) {
//             res = comb(res,_query(xid * 2 + 1, yid * 2 + 1, mx, my, crx, cry, tlx, tly, trx, tryy));
//         }
//         return res;
//     }
// };

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);


//     freopen("forestqueriesii.txt","r",stdin);
//     // freopen(".out","w",stdout);
//     clock_t tStart = clock();

//     int n, q; cin >> n >> q;
//     Tree2D<int> tree(n);

//     for(int i = 0; i < n; i++) {
//         string s; cin >> s;
//         for(int j = 0; j < n; j++) {
//             if(s[j] == '*') {
//                 tree.update(i,j,1);
//             }
//         }
//     }

//     // cout << tree.query(0,0,n,n) << '\n';
//     // cout << tree.query(0,0,2,2) << '\n';

//     for(int i = 0; i < q; i++) {
//         int t; cin >> t;
//         if(t == 1) {
//             int x, y; cin >> x >> y;
//             x--; y--;
//             tree.update(x,y,tree.at(x,y) ^ 1);
//         } else {
//             int lx, ly, rx, ry; cin >> lx >> ly >> rx >> ry;
//             // cout << tree.query(lx-1,ly-1,rx,ry) << '\n';
//             tree.query(lx-1,ly-1,rx,rx);
//         }
//     }

//     printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// template<typename T>
// struct Tree {
//     static constexpr T base = 0;
//     vector<T> v;
//     int n, size;
//     T comb(T a, T b) { //change this when doing maximum vs minimum etc.
//         return a + b;
//     }
//     // optional MIQ stuff
//     bool cond(T a, T b) {
//         return a <= b;
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
//     //find the lowest index and value that satisfy the condition in range [l,r)
//     pair<int,T> queryMIQ(T val, int lo, int hi) { //{index, value}
//         pair<int,T> ans = _queryMIQ(1, 0, size, lo, hi, val);
//         return ans;
//     }   
//     pair<int,T> _queryMIQ(int idx, int currl, int currr, int &lo, int &hi, T &val) {
//         //check overlap of left bound
//         if(cond(val, v[idx])) {
//             if(isLeaf(idx)) return {idx - size, v[idx]};
//             int mid = (currl + currr) / 2;
//             if(mid > lo && cond(val, v[idx * 2])) return _queryMIQ(idx * 2, currl, mid, lo, hi, val);
//             return _queryMIQ(idx * 2 + 1, mid, currr, lo, hi, val);
//         } else {
//             return {-1,base};
//         }
//     }
// };

// Tree<int> v[1000];

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, q; cin >> n >> q;
//     // vector<Tree<int>> v(n,Tree<int>(n));
//     for(int i = 0; i < n; i++) {
//         v[i].n = n;
//         v[i].size = 2048;
//         v[i].v.assign(2048 * 2, v[i].base);
//         for(int j = 0; j < n; j++) {
//             char c; cin >> c;
//             if(c == '*') {
//                 v[i].update(j,1);
//             }
//         }
//     }
//     for(int i = 0; i < q; i++) {
//         int type; cin >> type;
//         if(type == 1) {
//             int x, y; cin >> x >> y;
//             x--; y--;
//             v[x].update(y,v[x].at(y) ^ 1);
//         }
//         if(type == 2) {
//             int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
//             x1--;
//             y1--;
//             // x2--;
//             // y2--;
//             int sum = 0;
//             for(int row = x1; row < x2; row++) {
//                 sum += v[row].query(y1,y2);
//             }
//             cout << sum << '\n';
//         }
//     }

//     // cout << "OK!\n";

//     return 0;
// }