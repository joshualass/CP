#line 1 "library/my_template.hpp"
#if defined(LOCAL)
#include <my_template_compiled.hpp>
#else

// https://codeforces.com/blog/entry/96344
#pragma GCC optimize("Ofast,unroll-loops")
// いまの CF だとこれ入れると動かない？
// #pragma GCC target("avx2,popcnt")

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

template <class T>
constexpr T infty = 0;
template <>
constexpr int infty<int> = 1'010'000'000;
template <>
constexpr ll infty<ll> = 2'020'000'000'000'000'000;
template <>
constexpr u32 infty<u32> = infty<int>;
template <>
constexpr u64 infty<u64> = infty<ll>;
template <>
constexpr i128 infty<i128> = i128(infty<ll>) * 2'000'000'000'000'000'000;
template <>
constexpr double infty<double> = infty<ll>;
template <>
constexpr long double infty<long double> = infty<ll>;

using pi = pair<ll, ll>;
using vi = vector<ll>;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;
template <class T>
using vvvc = vector<vvc<T>>;
template <class T>
using vvvvc = vector<vvvc<T>>;
template <class T>
using vvvvvc = vector<vvvvc<T>>;
template <class T>
using pq = priority_queue<T>;
template <class T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define vv(type, name, h, ...) vector<vector<type>> name(h, vector<type>(__VA_ARGS__))
#define vvv(type, name, h, w, ...) vector<vector<vector<type>>> name(h, vector<vector<type>>(w, vector<type>(__VA_ARGS__)))
#define vvvv(type, name, a, b, c, ...) \
  vector<vector<vector<vector<type>>>> name(a, vector<vector<vector<type>>>(b, vector<vector<type>>(c, vector<type>(__VA_ARGS__))))

// https://trap.jp/post/1224/
#define FOR1(a) for (ll _ = 0; _ < ll(a); ++_)
#define FOR2(i, a) for (ll i = 0; i < ll(a); ++i)
#define FOR3(i, a, b) for (ll i = a; i < ll(b); ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < ll(b); i += (c))
#define FOR1_R(a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR2_R(i, a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR3_R(i, a, b) for (ll i = (b)-1; i >= ll(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...) d
#define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...) overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

#define stoi stoll

int popcnt(int x) { return __builtin_popcount(x); }
int popcnt(u32 x) { return __builtin_popcount(x); }
int popcnt(ll x) { return __builtin_popcountll(x); }
int popcnt(u64 x) { return __builtin_popcountll(x); }
int popcnt_sgn(int x) { return (__builtin_parity(unsigned(x)) & 1 ? -1 : 1); }
int popcnt_sgn(u32 x) { return (__builtin_parity(x) & 1 ? -1 : 1); }
int popcnt_sgn(ll x) { return (__builtin_parityll(x) & 1 ? -1 : 1); }
int popcnt_sgn(u64 x) { return (__builtin_parityll(x) & 1 ? -1 : 1); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(u32 x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
int topbit(u64 x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)
int lowbit(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(u32 x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(ll x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }
int lowbit(u64 x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }

template <typename T>
T kth_bit(int k) {
  return T(1) << k;
}
template <typename T>
bool has_kth_bit(T x, int k) {
  return x >> k & 1;
}

template <typename UINT>
struct all_bit {
  struct iter {
    UINT s;
    iter(UINT s) : s(s) {}
    int operator*() const { return lowbit(s); }
    iter &operator++() {
      s &= s - 1;
      return *this;
    }
    bool operator!=(const iter) const { return s != 0; }
  };
  UINT s;
  all_bit(UINT s) : s(s) {}
  iter begin() const { return iter(s); }
  iter end() const { return iter(0); }
};

template <typename UINT>
struct all_subset {
  static_assert(is_unsigned<UINT>::value);
  struct iter {
    UINT s, t;
    bool ed;
    iter(UINT s) : s(s), t(s), ed(0) {}
    int operator*() const { return s ^ t; }
    iter &operator++() {
      (t == 0 ? ed = 1 : t = (t - 1) & s);
      return *this;
    }
    bool operator!=(const iter) const { return !ed; }
  };
  UINT s;
  all_subset(UINT s) : s(s) {}
  iter begin() const { return iter(s); }
  iter end() const { return iter(0); }
};

template <typename T>
T floor(T a, T b) {
  return a / b - (a % b && (a ^ b) < 0);
}
template <typename T>
T ceil(T x, T y) {
  return floor(x + y - 1, y);
}
template <typename T>
T bmod(T x, T y) {
  return x - y * floor(x, y);
}
template <typename T>
pair<T, T> divmod(T x, T y) {
  T q = floor(x, y);
  return {q, x - q * y};
}

template <typename T, typename U>
T SUM(const vector<U> &A) {
  T sm = 0;
  for (auto &&a: A) sm += a;
  return sm;
}

#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

template <typename T>
T POP(deque<T> &que) {
  T a = que.front();
  que.pop_front();
  return a;
}
template <typename T>
T POP(pq<T> &que) {
  T a = que.top();
  que.pop();
  return a;
}
template <typename T>
T POP(pqg<T> &que) {
  T a = que.top();
  que.pop();
  return a;
}
template <typename T>
T POP(vc<T> &que) {
  T a = que.back();
  que.pop_back();
  return a;
}

template <typename F>
ll binary_search(F check, ll ok, ll ng, bool check_ok = true) {
  if (check_ok) assert(check(ok));
  while (abs(ok - ng) > 1) {
    auto x = (ng + ok) / 2;
    (check(x) ? ok : ng) = x;
  }
  return ok;
}
template <typename F>
double binary_search_real(F check, double ok, double ng, int iter = 100) {
  FOR(iter) {
    double x = (ok + ng) / 2;
    (check(x) ? ok : ng) = x;
  }
  return (ok + ng) / 2;
}

template <class T, class S>
inline bool chmax(T &a, const S &b) {
  return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
  return (a > b ? a = b, 1 : 0);
}

// ? は -1
vc<int> s_to_vi(const string &S, char first_char) {
  vc<int> A(S.size());
  FOR(i, S.size()) { A[i] = (S[i] != '?' ? S[i] - first_char : -1); }
  return A;
}

template <typename T, typename U>
vector<T> cumsum(vector<U> &A, int off = 1) {
  int N = A.size();
  vector<T> B(N + 1);
  FOR(i, N) { B[i + 1] = B[i] + A[i]; }
  if (off == 0) B.erase(B.begin());
  return B;
}

// stable sort
template <typename T>
vector<int> argsort(const vector<T> &A) {
  vector<int> ids(len(A));
  iota(all(ids), 0);
  sort(all(ids), [&](int i, int j) { return (A[i] == A[j] ? i < j : A[i] < A[j]); });
  return ids;
}

// A[I[0]], A[I[1]], ...
template <typename T>
vc<T> rearrange(const vc<T> &A, const vc<int> &I) {
  vc<T> B(len(I));
  FOR(i, len(I)) B[i] = A[I[i]];
  return B;
}

template <typename T, typename... Vectors>
void concat(vc<T> &first, const Vectors &... others) {
  vc<T> &res = first;
  (res.insert(res.end(), others.begin(), others.end()), ...);
}
#endif
#line 1 "library/other/io.hpp"
#define FASTIO
#include <unistd.h>

// https://judge.yosupo.jp/submission/21623
namespace fastio {
static constexpr uint32_t SZ = 1 << 17;
char ibuf[SZ];
char obuf[SZ];
char out[100];
// pointer of ibuf, obuf
uint32_t pil = 0, pir = 0, por = 0;

struct Pre {
  char num[10000][4];
  constexpr Pre() : num() {
    for (int i = 0; i < 10000; i++) {
      int n = i;
      for (int j = 3; j >= 0; j--) {
        num[i][j] = n % 10 | '0';
        n /= 10;
      }
    }
  }
} constexpr pre;

inline void load() {
  memcpy(ibuf, ibuf + pil, pir - pil);
  pir = pir - pil + fread(ibuf + pir - pil, 1, SZ - pir + pil, stdin);
  pil = 0;
  if (pir < SZ) ibuf[pir++] = '\n';
}

inline void flush() {
  fwrite(obuf, 1, por, stdout);
  por = 0;
}

void rd(char &c) {
  do {
    if (pil + 1 > pir) load();
    c = ibuf[pil++];
  } while (isspace(c));
}

void rd(string &x) {
  x.clear();
  char c;
  do {
    if (pil + 1 > pir) load();
    c = ibuf[pil++];
  } while (isspace(c));
  do {
    x += c;
    if (pil == pir) load();
    c = ibuf[pil++];
  } while (!isspace(c));
}

template <typename T>
void rd_real(T &x) {
  string s;
  rd(s);
  x = stod(s);
}

template <typename T>
void rd_integer(T &x) {
  if (pil + 100 > pir) load();
  char c;
  do
    c = ibuf[pil++];
  while (c < '-');
  bool minus = 0;
  if constexpr (is_signed<T>::value || is_same_v<T, i128>) {
    if (c == '-') { minus = 1, c = ibuf[pil++]; }
  }
  x = 0;
  while ('0' <= c) { x = x * 10 + (c & 15), c = ibuf[pil++]; }
  if constexpr (is_signed<T>::value || is_same_v<T, i128>) {
    if (minus) x = -x;
  }
}

void rd(int &x) { rd_integer(x); }
void rd(ll &x) { rd_integer(x); }
void rd(i128 &x) { rd_integer(x); }
void rd(u32 &x) { rd_integer(x); }
void rd(u64 &x) { rd_integer(x); }
void rd(u128 &x) { rd_integer(x); }
void rd(double &x) { rd_real(x); }
void rd(long double &x) { rd_real(x); }
void rd(f128 &x) { rd_real(x); }

template <class T, class U>
void rd(pair<T, U> &p) {
  return rd(p.first), rd(p.second);
}
template <size_t N = 0, typename T>
void rd_tuple(T &t) {
  if constexpr (N < std::tuple_size<T>::value) {
    auto &x = std::get<N>(t);
    rd(x);
    rd_tuple<N + 1>(t);
  }
}
template <class... T>
void rd(tuple<T...> &tpl) {
  rd_tuple(tpl);
}

template <size_t N = 0, typename T>
void rd(array<T, N> &x) {
  for (auto &d: x) rd(d);
}
template <class T>
void rd(vc<T> &x) {
  for (auto &d: x) rd(d);
}

void read() {}
template <class H, class... T>
void read(H &h, T &... t) {
  rd(h), read(t...);
}

void wt(const char c) {
  if (por == SZ) flush();
  obuf[por++] = c;
}
void wt(const string s) {
  for (char c: s) wt(c);
}
void wt(const char *s) {
  size_t len = strlen(s);
  for (size_t i = 0; i < len; i++) wt(s[i]);
}

template <typename T>
void wt_integer(T x) {
  if (por > SZ - 100) flush();
  if (x < 0) { obuf[por++] = '-', x = -x; }
  int outi;
  for (outi = 96; x >= 10000; outi -= 4) {
    memcpy(out + outi, pre.num[x % 10000], 4);
    x /= 10000;
  }
  if (x >= 1000) {
    memcpy(obuf + por, pre.num[x], 4);
    por += 4;
  } else if (x >= 100) {
    memcpy(obuf + por, pre.num[x] + 1, 3);
    por += 3;
  } else if (x >= 10) {
    int q = (x * 103) >> 10;
    obuf[por] = q | '0';
    obuf[por + 1] = (x - q * 10) | '0';
    por += 2;
  } else
    obuf[por++] = x | '0';
  memcpy(obuf + por, out + outi + 4, 96 - outi);
  por += 96 - outi;
}

template <typename T>
void wt_real(T x) {
  ostringstream oss;
  oss << fixed << setprecision(15) << double(x);
  string s = oss.str();
  wt(s);
}

void wt(int x) { wt_integer(x); }
void wt(ll x) { wt_integer(x); }
void wt(i128 x) { wt_integer(x); }
void wt(u32 x) { wt_integer(x); }
void wt(u64 x) { wt_integer(x); }
void wt(u128 x) { wt_integer(x); }
void wt(double x) { wt_real(x); }
void wt(long double x) { wt_real(x); }
void wt(f128 x) { wt_real(x); }

template <class T, class U>
void wt(const pair<T, U> val) {
  wt(val.first);
  wt(' ');
  wt(val.second);
}
template <size_t N = 0, typename T>
void wt_tuple(const T t) {
  if constexpr (N < std::tuple_size<T>::value) {
    if constexpr (N > 0) { wt(' '); }
    const auto x = std::get<N>(t);
    wt(x);
    wt_tuple<N + 1>(t);
  }
}
template <class... T>
void wt(tuple<T...> tpl) {
  wt_tuple(tpl);
}
template <class T, size_t S>
void wt(const array<T, S> val) {
  auto n = val.size();
  for (size_t i = 0; i < n; i++) {
    if (i) wt(' ');
    wt(val[i]);
  }
}
template <class T>
void wt(const vector<T> val) {
  auto n = val.size();
  for (size_t i = 0; i < n; i++) {
    if (i) wt(' ');
    wt(val[i]);
  }
}

void print() { wt('\n'); }
template <class Head, class... Tail>
void print(Head &&head, Tail &&... tail) {
  wt(head);
  if (sizeof...(Tail)) wt(' ');
  print(forward<Tail>(tail)...);
}

// gcc expansion. called automaticall after main.
void __attribute__((destructor)) _d() { flush(); }
} // namespace fastio
using fastio::read;
using fastio::print;
using fastio::flush;

#if defined(LOCAL)
#define SHOW(...) SHOW_IMPL(__VA_ARGS__, SHOW6, SHOW5, SHOW4, SHOW3, SHOW2, SHOW1)(__VA_ARGS__)
#define SHOW_IMPL(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define SHOW1(x) print(#x, "=", (x)), flush()
#define SHOW2(x, y) print(#x, "=", (x), #y, "=", (y)), flush()
#define SHOW3(x, y, z) print(#x, "=", (x), #y, "=", (y), #z, "=", (z)), flush()
#define SHOW4(x, y, z, w) print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w)), flush()
#define SHOW5(x, y, z, w, v) print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v)), flush()
#define SHOW6(x, y, z, w, v, u) print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v), #u, "=", (u)), flush()
#else
#define SHOW(...)
#endif

#define INT(...)   \
  int __VA_ARGS__; \
  read(__VA_ARGS__)
#define LL(...)   \
  ll __VA_ARGS__; \
  read(__VA_ARGS__)
#define U32(...)   \
  u32 __VA_ARGS__; \
  read(__VA_ARGS__)
#define U64(...)   \
  u64 __VA_ARGS__; \
  read(__VA_ARGS__)
#define STR(...)      \
  string __VA_ARGS__; \
  read(__VA_ARGS__)
#define CHAR(...)   \
  char __VA_ARGS__; \
  read(__VA_ARGS__)
#define DBL(...)      \
  double __VA_ARGS__; \
  read(__VA_ARGS__)

#define VEC(type, name, size) \
  vector<type> name(size);    \
  read(name)
#define VV(type, name, h, w)                     \
  vector<vector<type>> name(h, vector<type>(w)); \
  read(name)

void YES(bool t = 1) { print(t ? "YES" : "NO"); }
void NO(bool t = 1) { YES(!t); }
void Yes(bool t = 1) { print(t ? "Yes" : "No"); }
void No(bool t = 1) { Yes(!t); }
void yes(bool t = 1) { print(t ? "yes" : "no"); }
void no(bool t = 1) { yes(!t); }
void YA(bool t = 1) { print(t ? "YA" : "TIDAK"); }
void TIDAK(bool t = 1) { YES(!t); }
#line 3 "main.cpp"

#line 2 "library/graph/tree.hpp"

#line 2 "library/ds/hashmap.hpp"

// u64 -> Val
template <typename Val>
struct HashMap {
  // n は入れたいものの個数で ok
  HashMap(u32 n = 0) { build(n); }
  void build(u32 n) {
    u32 k = 8;
    while (k < n * 2) k *= 2;
    cap = k / 2, mask = k - 1;
    key.resize(k), val.resize(k), used.assign(k, 0);
  }

  // size を保ったまま. size=0 にするときは build すること.
  void clear() {
    used.assign(len(used), 0);
    cap = (mask + 1) / 2;
  }
  int size() { return len(used) / 2 - cap; }

  int index(const u64& k) {
    int i = 0;
    for (i = hash(k); used[i] && key[i] != k; i = (i + 1) & mask) {}
    return i;
  }

  Val& operator[](const u64& k) {
    if (cap == 0) extend();
    int i = index(k);
    if (!used[i]) { used[i] = 1, key[i] = k, val[i] = Val{}, --cap; }
    return val[i];
  }

  Val get(const u64& k, Val default_value) {
    int i = index(k);
    return (used[i] ? val[i] : default_value);
  }

  bool count(const u64& k) {
    int i = index(k);
    return used[i] && key[i] == k;
  }

  // f(key, val)
  template <typename F>
  void enumerate_all(F f) {
    FOR(i, len(used)) if (used[i]) f(key[i], val[i]);
  }

private:
  u32 cap, mask;
  vc<u64> key;
  vc<Val> val;
  vc<bool> used;

  u64 hash(u64 x) {
    static const u64 FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
    x += FIXED_RANDOM;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return (x ^ (x >> 31)) & mask;
  }

  void extend() {
    vc<pair<u64, Val>> dat;
    dat.reserve(len(used) / 2 - cap);
    FOR(i, len(used)) {
      if (used[i]) dat.eb(key[i], val[i]);
    }
    build(2 * len(dat));
    for (auto& [a, b]: dat) (*this)[a] = b;
  }
};
#line 3 "library/graph/base.hpp"

template <typename T>
struct Edge {
  int frm, to;
  T cost;
  int id;
};

template <typename T = int, bool directed = false>
struct Graph {
  static constexpr bool is_directed = directed;
  int N, M;
  using cost_type = T;
  using edge_type = Edge<T>;
  vector<edge_type> edges;
  vector<int> indptr;
  vector<edge_type> csr_edges;
  vc<int> vc_deg, vc_indeg, vc_outdeg;
  bool prepared;

  class OutgoingEdges {
  public:
    OutgoingEdges(const Graph* G, int l, int r) : G(G), l(l), r(r) {}

    const edge_type* begin() const {
      if (l == r) { return 0; }
      return &G->csr_edges[l];
    }

    const edge_type* end() const {
      if (l == r) { return 0; }
      return &G->csr_edges[r];
    }

  private:
    const Graph* G;
    int l, r;
  };

  bool is_prepared() { return prepared; }

  Graph() : N(0), M(0), prepared(0) {}
  Graph(int N) : N(N), M(0), prepared(0) {}

  void build(int n) {
    N = n, M = 0;
    prepared = 0;
    edges.clear();
    indptr.clear();
    csr_edges.clear();
    vc_deg.clear();
    vc_indeg.clear();
    vc_outdeg.clear();
  }

  void add(int frm, int to, T cost = 1, int i = -1) {
    assert(!prepared);
    assert(0 <= frm && 0 <= to && to < N);
    if (i == -1) i = M;
    auto e = edge_type({frm, to, cost, i});
    edges.eb(e);
    ++M;
  }

#ifdef FASTIO
  // wt, off
  void read_tree(bool wt = false, int off = 1) { read_graph(N - 1, wt, off); }

  void read_graph(int M, bool wt = false, int off = 1) {
    for (int m = 0; m < M; ++m) {
      INT(a, b);
      a -= off, b -= off;
      if (!wt) {
        add(a, b);
      } else {
        T c;
        read(c);
        add(a, b, c);
      }
    }
    build();
  }
#endif

  void build() {
    assert(!prepared);
    prepared = true;
    indptr.assign(N + 1, 0);
    for (auto&& e: edges) {
      indptr[e.frm + 1]++;
      if (!directed) indptr[e.to + 1]++;
    }
    for (int v = 0; v < N; ++v) { indptr[v + 1] += indptr[v]; }
    auto counter = indptr;
    csr_edges.resize(indptr.back() + 1);
    for (auto&& e: edges) {
      csr_edges[counter[e.frm]++] = e;
      if (!directed) csr_edges[counter[e.to]++] = edge_type({e.to, e.frm, e.cost, e.id});
    }
  }

  OutgoingEdges operator[](int v) const {
    assert(prepared);
    return {this, indptr[v], indptr[v + 1]};
  }

  vc<int> deg_array() {
    if (vc_deg.empty()) calc_deg();
    return vc_deg;
  }

  pair<vc<int>, vc<int>> deg_array_inout() {
    if (vc_indeg.empty()) calc_deg_inout();
    return {vc_indeg, vc_outdeg};
  }

  int deg(int v) {
    if (vc_deg.empty()) calc_deg();
    return vc_deg[v];
  }

  int in_deg(int v) {
    if (vc_indeg.empty()) calc_deg_inout();
    return vc_indeg[v];
  }

  int out_deg(int v) {
    if (vc_outdeg.empty()) calc_deg_inout();
    return vc_outdeg[v];
  }

#ifdef FASTIO
  void debug() {
    print("Graph");
    if (!prepared) {
      print("frm to cost id");
      for (auto&& e: edges) print(e.frm, e.to, e.cost, e.id);
    } else {
      print("indptr", indptr);
      print("frm to cost id");
      FOR(v, N) for (auto&& e: (*this)[v]) print(e.frm, e.to, e.cost, e.id);
    }
  }
#endif

  vc<int> new_idx;
  vc<bool> used_e;

  // G における頂点 V[i] が、新しいグラフで i になるようにする
  // {G, es}
  // sum(deg(v)) の計算量になっていて、
  // 新しいグラフの n+m より大きい可能性があるので注意
  Graph<T, directed> rearrange(vc<int> V, bool keep_eid = 0) {
    if (len(new_idx) != N) new_idx.assign(N, -1);
    int n = len(V);
    FOR(i, n) new_idx[V[i]] = i;
    Graph<T, directed> G(n);
    vc<int> history;
    FOR(i, n) {
      for (auto&& e: (*this)[V[i]]) {
        if (len(used_e) <= e.id) used_e.resize(e.id + 1);
        if (used_e[e.id]) continue;
        int a = e.frm, b = e.to;
        if (new_idx[a] != -1 && new_idx[b] != -1) {
          history.eb(e.id);
          used_e[e.id] = 1;
          int eid = (keep_eid ? e.id : -1);
          G.add(new_idx[a], new_idx[b], e.cost, eid);
        }
      }
    }
    FOR(i, n) new_idx[V[i]] = -1;
    for (auto&& eid: history) used_e[eid] = 0;
    G.build();
    return G;
  }

  Graph<T, true> to_directed_tree(int root = -1) {
    if (root == -1) root = 0;
    assert(!is_directed && prepared && M == N - 1);
    Graph<T, true> G1(N);
    vc<int> par(N, -1);
    auto dfs = [&](auto& dfs, int v) -> void {
      for (auto& e: (*this)[v]) {
        if (e.to == par[v]) continue;
        par[e.to] = v, dfs(dfs, e.to);
      }
    };
    dfs(dfs, root);
    for (auto& e: edges) {
      int a = e.frm, b = e.to;
      if (par[a] == b) swap(a, b);
      assert(par[b] == a);
      G1.add(a, b, e.cost);
    }
    G1.build();
    return G1;
  }

  HashMap<int> MP_FOR_EID;

  int get_eid(u64 a, u64 b) {
    if (len(MP_FOR_EID) == 0) {
      MP_FOR_EID.build(N - 1);
      for (auto& e: edges) {
        u64 a = e.frm, b = e.to;
        u64 k = to_eid_key(a, b);
        MP_FOR_EID[k] = e.id;
      }
    }
    return MP_FOR_EID.get(to_eid_key(a, b), -1);
  }

  u64 to_eid_key(u64 a, u64 b) {
    if (!directed && a > b) swap(a, b);
    return N * a + b;
  }

private:
  void calc_deg() {
    assert(vc_deg.empty());
    vc_deg.resize(N);
    for (auto&& e: edges) vc_deg[e.frm]++, vc_deg[e.to]++;
  }

  void calc_deg_inout() {
    assert(vc_indeg.empty());
    vc_indeg.resize(N);
    vc_outdeg.resize(N);
    for (auto&& e: edges) { vc_indeg[e.to]++, vc_outdeg[e.frm]++; }
  }
};
#line 4 "library/graph/tree.hpp"

// HLD euler tour をとっていろいろ。
template <typename GT>
struct Tree {
  using Graph_type = GT;
  GT &G;
  using WT = typename GT::cost_type;
  int N;
  vector<int> LID, RID, head, V, parent, VtoE;
  vc<int> depth;
  vc<WT> depth_weighted;

  Tree(GT &G, int r = 0, bool hld = 1) : G(G) { build(r, hld); }

  void build(int r = 0, bool hld = 1) {
    if (r == -1) return; // build を遅延したいとき
    N = G.N;
    LID.assign(N, -1), RID.assign(N, -1), head.assign(N, r);
    V.assign(N, -1), parent.assign(N, -1), VtoE.assign(N, -1);
    depth.assign(N, -1), depth_weighted.assign(N, 0);
    assert(G.is_prepared());
    int t1 = 0;
    dfs_sz(r, -1, hld);
    dfs_hld(r, t1);
  }

  void dfs_sz(int v, int p, bool hld) {
    auto &sz = RID;
    parent[v] = p;
    depth[v] = (p == -1 ? 0 : depth[p] + 1);
    sz[v] = 1;
    int l = G.indptr[v], r = G.indptr[v + 1];
    auto &csr = G.csr_edges;
    // 使う辺があれば先頭にする
    for (int i = r - 2; i >= l; --i) {
      if (hld && depth[csr[i + 1].to] == -1) swap(csr[i], csr[i + 1]);
    }
    int hld_sz = 0;
    for (int i = l; i < r; ++i) {
      auto e = csr[i];
      if (depth[e.to] != -1) continue;
      depth_weighted[e.to] = depth_weighted[v] + e.cost;
      VtoE[e.to] = e.id;
      dfs_sz(e.to, v, hld);
      sz[v] += sz[e.to];
      if (hld && chmax(hld_sz, sz[e.to]) && l < i) { swap(csr[l], csr[i]); }
    }
  }

  void dfs_hld(int v, int &times) {
    LID[v] = times++;
    RID[v] += LID[v];
    V[LID[v]] = v;
    bool heavy = true;
    for (auto &&e: G[v]) {
      if (depth[e.to] <= depth[v]) continue;
      head[e.to] = (heavy ? head[v] : e.to);
      heavy = false;
      dfs_hld(e.to, times);
    }
  }

  vc<int> heavy_path_at(int v) {
    vc<int> P = {v};
    while (1) {
      int a = P.back();
      for (auto &&e: G[a]) {
        if (e.to != parent[a] && head[e.to] == v) {
          P.eb(e.to);
          break;
        }
      }
      if (P.back() == a) break;
    }
    return P;
  }

  int heavy_child(int v) {
    int k = LID[v] + 1;
    if (k == N) return -1;
    int w = V[k];
    return (parent[w] == v ? w : -1);
  }

  int e_to_v(int eid) {
    auto e = G.edges[eid];
    return (parent[e.frm] == e.to ? e.frm : e.to);
  }
  int v_to_e(int v) { return VtoE[v]; }
  int get_eid(int u, int v) {
    if (parent[u] != v) swap(u, v);
    assert(parent[u] == v);
    return VtoE[u];
  }

  int ELID(int v) { return 2 * LID[v] - depth[v]; }
  int ERID(int v) { return 2 * RID[v] - depth[v] - 1; }

  // 目標地点へ進む個数が k
  int LA(int v, int k) {
    assert(k <= depth[v]);
    while (1) {
      int u = head[v];
      if (LID[v] - k >= LID[u]) return V[LID[v] - k];
      k -= LID[v] - LID[u] + 1;
      v = parent[u];
    }
  }
  int la(int u, int v) { return LA(u, v); }

  int LCA(int u, int v) {
    for (;; v = parent[head[v]]) {
      if (LID[u] > LID[v]) swap(u, v);
      if (head[u] == head[v]) return u;
    }
  }

  int meet(int a, int b, int c) { return LCA(a, b) ^ LCA(a, c) ^ LCA(b, c); }
  int lca(int u, int v) { return LCA(u, v); }

  int subtree_size(int v, int root = -1) {
    if (root == -1) return RID[v] - LID[v];
    if (v == root) return N;
    int x = jump(v, root, 1);
    if (in_subtree(v, x)) return RID[v] - LID[v];
    return N - RID[x] + LID[x];
  }

  int dist(int a, int b) {
    int c = LCA(a, b);
    return depth[a] + depth[b] - 2 * depth[c];
  }

  WT dist_weighted(int a, int b) {
    int c = LCA(a, b);
    return depth_weighted[a] + depth_weighted[b] - WT(2) * depth_weighted[c];
  }

  // a is in b
  bool in_subtree(int a, int b) { return LID[b] <= LID[a] && LID[a] < RID[b]; }

  int jump(int a, int b, ll k) {
    if (k == 1) {
      if (a == b) return -1;
      return (in_subtree(b, a) ? LA(b, depth[b] - depth[a] - 1) : parent[a]);
    }
    int c = LCA(a, b);
    int d_ac = depth[a] - depth[c];
    int d_bc = depth[b] - depth[c];
    if (k > d_ac + d_bc) return -1;
    if (k <= d_ac) return LA(a, k);
    return LA(b, d_ac + d_bc - k);
  }

  vc<int> collect_child(int v) {
    vc<int> res;
    for (auto &&e: G[v])
      if (e.to != parent[v]) res.eb(e.to);
    return res;
  }

  vc<int> collect_light(int v) {
    vc<int> res;
    bool skip = true;
    for (auto &&e: G[v])
      if (e.to != parent[v]) {
        if (!skip) res.eb(e.to);
        skip = false;
      }
    return res;
  }

  vc<pair<int, int>> get_path_decomposition(int u, int v, bool edge) {
    // [始点, 終点] の"閉"区間列。
    vc<pair<int, int>> up, down;
    while (1) {
      if (head[u] == head[v]) break;
      if (LID[u] < LID[v]) {
        down.eb(LID[head[v]], LID[v]);
        v = parent[head[v]];
      } else {
        up.eb(LID[u], LID[head[u]]);
        u = parent[head[u]];
      }
    }
    if (LID[u] < LID[v]) down.eb(LID[u] + edge, LID[v]);
    elif (LID[v] + edge <= LID[u]) up.eb(LID[u], LID[v] + edge);
    reverse(all(down));
    up.insert(up.end(), all(down));
    return up;
  }

  // 辺の列の情報 (frm,to,str)
  // str = "heavy_up", "heavy_down", "light_up", "light_down"
  vc<tuple<int, int, string>> get_path_decomposition_detail(int u, int v) {
    vc<tuple<int, int, string>> up, down;
    while (1) {
      if (head[u] == head[v]) break;
      if (LID[u] < LID[v]) {
        if (v != head[v]) down.eb(head[v], v, "heavy_down"), v = head[v];
        down.eb(parent[v], v, "light_down"), v = parent[v];
      } else {
        if (u != head[u]) up.eb(u, head[u], "heavy_up"), u = head[u];
        up.eb(u, parent[u], "light_up"), u = parent[u];
      }
    }
    if (LID[u] < LID[v]) down.eb(u, v, "heavy_down");
    elif (LID[v] < LID[u]) up.eb(u, v, "heavy_up");
    reverse(all(down));
    concat(up, down);
    return up;
  }

  vc<int> restore_path(int u, int v) {
    vc<int> P;
    for (auto &&[a, b]: get_path_decomposition(u, v, 0)) {
      if (a <= b) {
        FOR(i, a, b + 1) P.eb(V[i]);
      } else {
        FOR_R(i, b, a + 1) P.eb(V[i]);
      }
    }
    return P;
  }

  // path [a,b] と [c,d] の交わり. 空ならば {-1,-1}.
  // https://codeforces.com/problemset/problem/500/G
  pair<int, int> path_intersection(int a, int b, int c, int d) {
    int ab = lca(a, b), ac = lca(a, c), ad = lca(a, d);
    int bc = lca(b, c), bd = lca(b, d), cd = lca(c, d);
    int x = ab ^ ac ^ bc, y = ab ^ ad ^ bd; // meet(a,b,c), meet(a,b,d)
    if (x != y) return {x, y};
    int z = ac ^ ad ^ cd;
    if (x != z) x = -1;
    return {x, x};
  }

  // uv path 上で check(v) を満たす最後の v
  // なければ （つまり check(v) が ng ）-1
  template <class F>
  int max_path(F check, int u, int v) {
    if (!check(u)) return -1;
    auto pd = get_path_decomposition(u, v, false);
    for (auto [a, b]: pd) {
      if (!check(V[a])) return u;
      if (check(V[b])) {
        u = V[b];
        continue;
      }
      int c = binary_search([&](int c) -> bool { return check(V[c]); }, a, b, 0);
      return V[c];
    }
    return u;
  }
};
#line 5 "main.cpp"

int A[110'000];
const int b_sz = 256;
int lazy[1000];

void solve() {
  LL(N, Q);
  Graph<int, 0> G(N);
  G.read_tree();

  Tree<decltype(G)> tree(G);
  auto& V = tree.V;
  FOR(i, N) A[i] = 1 + V[i];

  auto apply = [&](int l, int r, int x) -> void {
    int s = l / b_sz;
    int t = (r - 1) / b_sz + 1;
    FOR(b, s, t) {
      int L = max<int>(b * b_sz, l);
      int R = min<int>((b + 1) * b_sz, r);
      if (R - L == b_sz) {
        lazy[b] += x;
      } else {
        FOR(i, L, R) A[i] += x;
      }
    }
  };

  auto get = [&](int l, int r) -> int {
    int s = l / b_sz;
    int t = (r - 1) / b_sz + 1;
    FOR(b, s, t) {
      if (lazy[b] != 0) {
        FOR(i, b * b_sz, (b + 1) * b_sz) { A[i] += lazy[b]; }
        lazy[b] = 0;
      }
    }
    int ans = 0;
    FOR(i, l, r) ans ^= A[i];
    return ans;
  };

  FOR(Q) {
    STR(tp);
    INT(a, b);
    --a, --b;
    auto pd = tree.get_path_decomposition(a, b, false);
    for (auto& [s, t]: pd) {
      if (s > t) swap(s, t);
      ++t;
    }
    if (tp == "+") {
      INT(x);
      // add x
      for (auto& [s, t]: pd) {
        apply(s, t, x);
        // for (int i = s; i < t; ++i) A[i] += x;
      }
    } else {
      int ans = 0;
      for (auto& [s, t]: pd) {
        ans ^= get(s, t);
        // for (int i = s; i < t; ++i) ans ^= A[i];
      }
      print(ans);
    }
  }
}

signed main() { solve(); }