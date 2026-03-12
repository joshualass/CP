#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("unroll-all-loops")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("no-stack-protector")
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

namespace fast_IO{
	#define IOSIZE 100000
		char ibuf[IOSIZE], obuf[IOSIZE], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
	#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
	#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
	#define isdigit(ch) (ch>47&&ch<58)
	#define isspace(ch) (ch<33)
		template<typename T> inline T read() { T s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s * w; }
		template<typename T> inline bool read(T &s) { s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s *= w, true; }
		template<typename T> inline void print(T x) { if (x < 0) putchar('-'), x = -x; if (x > 9) print(x / 10); putchar(x % 10 + 48); }
		inline bool read(char &s) { while (s = getchar(), isspace(s)); return true; }
		inline bool read(char *s) { char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) *s++ = ch, ch = getchar(); *s = '\000'; return true; }
		inline void print(char x) { putchar(x); }
		inline void print(char *x) { while (*x) putchar(*x++); }
		inline void print(const char *x) { for (int i = 0; x[i]; i++) putchar(x[i]); }
		inline bool read(std::string& s) { s = ""; char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) s += ch, ch = getchar(); return true; }
		inline void print(std::string x) { for (int i = 0, n = x.size(); i < n; i++) putchar(x[i]); }
		inline bool read(bool &b) { char ch; while(ch=getchar(), isspace(ch)); b=ch^48; return true; }
		inline void print(bool b) { putchar(b+48); }
		template<typename T, typename... T1> inline int read(T& a, T1&... other) { return read(a) + read(other...); }
		template<typename T, typename... T1> inline void print(T a, T1... other) { print(a), print(other...); }
		struct Fast_IO { ~Fast_IO() { fwrite(obuf, p3 - obuf, 1, stdout); } } io;
		template<typename T> Fast_IO& operator >> (Fast_IO &io, T &b) { return read(b), io; }
		template<typename T> Fast_IO& operator << (Fast_IO &io, T b) { return print(b), io; }
	#define cout io
	#define cin io
}using namespace fast_IO;

int debug = 0;
const int MAXN = 3e5 + 5;
int a[MAXN], vis[MAXN];
array<int,2> groups[MAXN];
array<int,2> def = {-1, -1};
deque<int> pos[MAXN];

static constexpr int NEG_INF = -(1 << 30);
int _size;
int mx[MAXN * 4], lz[MAXN * 4];

inline void init(int n_, int def = 0) {
    _size = 1;
    while (_size < n_) _size <<= 1;
    for(int i = 0; i < _size << 1; i++) mx[i] = def;
    for(int i = 0; i < _size << 1; i++) lz[i] = 0;
}

void Lazy(int n_ = 0, int def = 0) { init(n_, def); }

inline void apply(int x, int v) {
    mx[x] += v;
    lz[x] += v;
}

inline void push(int x) {
    if (lz[x] != 0) {
        apply(x << 1, lz[x]);
        apply(x << 1 | 1, lz[x]);
        lz[x] = 0;
    }
}

inline void pull(int x) {
    mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
}

void update(int x, int lx, int rx, int l, int r, int v) {
    if (r <= lx || rx <= l) return;
    if (l <= lx && rx <= r) {
        apply(x, v);
        return;
    }
    push(x);
    int m = (lx + rx) >> 1;
    update(x << 1, lx, m, l, r, v);
    update(x << 1 | 1, m, rx, l, r, v);
    pull(x);
}

void update(int l, int r, int v) { update(1, 0, _size, l, r, v); }

int query(int x, int lx, int rx, int l, int r) {
    if (r <= lx || rx <= l) return NEG_INF;
    if (l <= lx && rx <= r) return mx[x];
    push(x);
    int m = (lx + rx) >> 1;
    return max(
        query(x << 1, lx, m, l, r),
        query(x << 1 | 1, m, rx, l, r)
    );
}

int query(int l, int r) { return query(1, 0, _size, l, r); }

void solve() {
    
    int n; cin >> n;
    // for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) a[i] = i;
    for(int i = 0; i <= n; i++) groups[i] = def;
    for(int i = 0; i <= n; i++) vis[i] = -1;
    for(int i = 0; i <= n; i++) pos[i].clear();
    Lazy(n, 0);
    map<int,int> mexes;

    //remove contrib that 
    auto remove_group = [&](int mex, int l, int r) -> void {
        // cout << "rmg mex : " << mex << " l : " << l << " r : " << r << endl;
        if(groups[mex] == array<int,2>{l, r}) {
            groups[mex] = def;
            mexes.erase(mex);
        } else {
            assert(groups[mex][0] == l);
            groups[mex][0] = r + 1;
            mexes[mex] = r + 1;
        }
        mex++;
        while(pos[mex].size() && pos[mex].front() <= r) {
            int lo = l;
            int hi = max(l, pos[mex].front() + 1);
            // cout << "erase range lo : " << lo << " hi : " << hi << endl;
            update(lo, hi, -1);
            pos[mex].pop_front();
        }
        // cout << "rem clear sz : " << sz(pos[mex]) << endl;
        update(l, r + 1, -sz(pos[mex]));
    };

    auto add_group = [&](int mex, int l, int r) -> void {
        if(groups[mex] == def) {
            groups[mex] = {l, r};
            mexes[mex] = l;
        } else {
            // if(groups[mex][1] + 1 != l) {
            //     cout << "bad groups[mex] : " << groups[mex] << " mex : " << mex << " l : " << l << " r : " << r << endl;
            // }
            assert(groups[mex][1] + 1 == l);
            groups[mex][1] = r;
        }
    };

    for(int i = 0; i < n; i++) {
        // cout << "i : " << i << endl;
        int x = a[i];
        add_group(0, i, i);
        vis[x] = i;
        pos[x].push_back(i);
        while(x < n && groups[x] != def && vis[x] >= groups[x][0]) {
            int l = groups[x][0], r = min(groups[x][1], vis[x]);
            remove_group(x, l, r);
            x++;
            add_group(x, l, r);
        }
        // cout << "mexes : " << mexes << endl;

        auto it = mexes.lower_bound(a[i]);
        if(it != mexes.begin()) {
            it--;
            int idx = it->second;
            // cout << "idx : " << idx << endl;
            update(idx, i + 1, 1);
        }
        cout << query(0, n) << " \n"[i == n - 1];
    }

}

signed main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}