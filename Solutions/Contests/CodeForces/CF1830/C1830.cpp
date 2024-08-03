#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*

Chapter 2 of implementation school
very important to use segtree to handle merging of segments. std::set cannot handle all the cases

First try.
First, find a way to merge ranges that intersect with each other
To do this, we sort the ranges by right endpoint and store in a segment tree at each index, the maximum right endpoint.
Then, when we iterate over the edges in order of right endpoint, and we query the elements in the segtree whose left endpoint is left than the left endpoint of the current element
We find the maximum right endpoint from this range and merge while we can

Once we have our merged ranges or tree, we try to find the lengths of all the RBS, subtracting lengths from inner RBS lengths and we the product of the catalan numbers of these lengths

Can alternatively find groups using xor hashing

*/

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ll mod = 998244353;
vector<ll> fac;
map<pair<ll, ll>, ll> nckdp;

const int MAXN = 1e6;

ll add(ll a, ll b) {
    ll ret = a + b;
    while(ret >= mod) {
        ret -= mod;
    }
    return ret;
}

ll sub(ll a, ll b) {
    ll ans = a - b;
    while(ans < 0){
        ans += mod;
    }
    return ans;
}

ll mul(ll a, ll b) {
    return (a * b) % mod;
}

ll power(ll a, ll b) {
    ll ans = 1;
    ll p = a;
    while(b != 0){
        if(b % 2 == 1){
            ans = mul(ans, p);
        }
        p = mul(p, p);
        b /= 2;
    }
    return ans;
}

ll divide(ll a, ll b){
    return mul(a, power(b, mod - 2));
}

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

void fac_init() {
    fac = vector<ll>(MAXN + 1, 1);
    for(int i = 2; i < fac.size(); i++){
        fac[i] = mul(fac[i - 1], i);
    }
}

ll nck(ll n, ll k) {
    if(nckdp.find({n, k}) != nckdp.end()) {
        return nckdp.find({n, k}) -> second;
    }
    ll ans = divide(fac[n], mul(fac[k], fac[sub(n, k)]));
    nckdp.insert({{n, k}, ans});
    return ans;
}

//true if odd, false if even. 
bool nck_parity(ll n, ll k) {   
    return (n & (n - k)) == 0;
}

ll catalan(ll n){
    return sub(nck(2 * n, n), nck(2 * n, n + 1));
}

//cantor pairing function, uniquely maps a pair of integers back to the set of integers. 
ll cantor(ll a, ll b, ll m) {
    return ((a + b) * (a + b + 1) / 2 + b) % m;
}

ll extended_euclidean(ll a, ll b, ll& x, ll& y) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        ll q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

//modular inverse of a for any mod m. 
//if -1 is returned, then there is no solution. 
ll mod_inv(ll a, ll m) {
    ll x, y;
    ll g = extended_euclidean(a, m, x, y);
    if (g != 1) {
        return -1;
    }
    else {
        x = (x % m + m) % m;
        return x;
    }
}

//only works when all modulo is coprime. 
//if you want to do this with non-coprime modulos, then you need to factor all of the modulos, 
//and resolve the factors independently; converting them back to coprime. 
//it is not guaranteed that there is a solution if the modulos are not coprime. 
ll chinese_remainder_theorem(vector<ll>& modulo, vector<ll>& remainder) {
    if(modulo.size() != remainder.size()) {
        return -1;
    }
    ll M = 1;
    for(int i = 0; i < modulo.size(); i++){
        M *= modulo[i];
    }
    ll solution = 0;
    for(int i = 0; i < modulo.size(); i++){
        ll a_i = remainder[i];
        ll M_i = M / modulo[i];
        ll N_i = mod_inv(M_i, modulo[i]);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}

template<typename T>
struct Tree {
    static constexpr T base = {-1,-1,-1};
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return (a[0] > b[0] ? a : b);
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
            if(curr & 1) { //handles non-communative operations
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
};

const int N = 1e6;
int dsu[N];
int sizes[N];

void dsubuild(int n) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    if(sizes[x] == sizes[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[y] = x;
        sizes[x] += sizes[y];
    }
}

void solve() {
    
    int n, m; cin >> n >> m;

    vector<array<int,2>> ranges(1, {0, n});

    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        l--;
        ranges.push_back({l, r});
    }

    sort(ranges.begin(), ranges.end(), [](const auto &lhs, const auto &rhs) {
        return lhs[1] < rhs[1];
    });

    Tree<array<int,3>> tree(n); //{R, index in segtree/left endpoint, id of range}
    dsubuild(m + 1);

    // cout << "ranges : " << ranges << endl;

    for(int i = 0; i < m + 1; i++) {
        int minseen = ranges[i][0];
        while(tree.query(0, ranges[i][0] + 1)[0] > ranges[i][0]) { //querying all left indices <= left of current segment. Have to make sure right endpoint is > than current right of segment. 
            // cout << "query val that will merge : " << tree.query(0, ranges[i][0] + 1) << endl;
            auto [R, idx, id] = tree.query(0, ranges[i][0] + 1);
            minseen = min(minseen, idx);
            merge(i, id);

            // cout << "merging ranges : " << ranges[i] << " and : " << ranges[id] << endl;

            tree.update(idx, tree.base);
        }

        // cout << "i : " << i << " adding range back : " << minseen << ", " << ranges[i][1] << endl;

        tree.update(minseen, {ranges[i][1], minseen, i});
    }
    
    vector<vector<array<int,2>>> groups(m + 1);
    for(int i = 0; i < m + 1; i++) {
        groups[find(i)].push_back(ranges[i]);
    }

    vector<array<int,2>> newranges;
    vector<array<int,2>> events;
    int id = 1;

    for(int i = 0; i < m + 1; i++) {

        vector<int> pts;
        for(array<int,2> a : groups[i]) {
            pts.push_back(a[0]);
            pts.push_back(a[1]);
        }

        // cout << "group i : " << groups[i] << endl;

        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());

        // cout << "pts ? " << pts << endl;

        for(int j = 1; j < pts.size(); j++) {
            newranges.push_back({pts[j - 1], pts[j]});
            events.push_back({pts[j - 1], id});
            events.push_back({pts[j], -id});
            id++;
        }
    }

    sort(events.begin(), events.end());

    // cout << "events ok ? " << events << endl;
    // cout << "new ranges : " << newranges << endl;

    ll res = 1;
    stack<array<int,2>> s; //{id, length}

    int prev = -1;

    for(array<int,2> event : events) {
        if(s.size()) {
            array<int,2> a = s.top();
            s.pop();
            a[1] += event[0] - prev;
            s.push(a);
        }
        if(event[1] > 0) {
            s.push({event[1], 0});
        } else {
            assert(s.size());
            int length = s.top()[1];
            s.pop();
            // cout << "mult length : " << length << '\n';
            if(length & 1) {
                res = 0;
            } else {
                if(length / 2) {
                    res = (res * catalan(length / 2)) % MOD;
                }
            }
        }
        prev = event[0];
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    fac_init();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}