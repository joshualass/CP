#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/*
n logn sqrt n vs dylan smith string problem
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

template<class T>
constexpr T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

//Modular Division currently uses Little Fermat's Theorem, so won't work for nonprime p. 
template<int P>
struct Mint {
    int x;
    constexpr Mint(): x{} {}
    constexpr Mint(ll x): x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if(P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if(x < 0) {
            x += getMod();
        }
        if(x >= getMod()) { //not sure why this is needed
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    constexpr Mint operator-() const {
        Mint res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr Mint inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr Mint &operator*=(Mint rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr Mint &operator+=(Mint rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr Mint &operator-=(Mint rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr Mint &operator/=(Mint rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr Mint operator*(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr Mint operator+(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Mint operator-(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr Mint operator/(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, Mint &a) {
        ll v;
        is >> v;
        a = Mint(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const Mint &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(Mint lhs, Mint rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(Mint lhs, Mint rhs) {
        return lhs.val() != rhs.val();
    }
};

constexpr int P = 998244353;
using Z = Mint<P>;
// using Z = double;
const int MAXN = 1e6;
Z fact[MAXN + 1], inv_fact[MAXN + 1];

Z choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] * inv_fact[n-k];
}

void init_fact(int n = MAXN) {
    fact[0] = Z(1);
    inv_fact[0] = Z(1);
    for(int i = 1; i <= n; i++) {
        fact[i] = fact[i-1] * i;
    }
    inv_fact[n] = 1 / fact[n];
    for(int i = n - 1; i >= 1; i--) {
        inv_fact[i] = inv_fact[i+1] * (i + 1);
    }
}

/*
init_fact()
*/

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
        //sa.erase(sa.begin());   //account for empty suffix
        //lcp.erase(lcp.begin());
	}
};

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node *l, *r;
    ll y, x, sum, size, ssum;

    Node(int val): l(nullptr), r(nullptr), y(rng()), x(val), sum(val), size(1), ssum(0) {}
};

void pull(Node *cur) {
    cur->size = 1 + (cur->l ? cur->l->size : 0) + (cur->r ? cur->r->size : 0);
    cur->sum = cur->x + (cur->l ? cur->l->sum : 0) + (cur->r ? cur->r->sum : 0);
    ll curr_size = 0;
    ll ssum = 0;
    if(cur->l) {
        ssum += cur->l->ssum;
        curr_size += cur->l->size;
    }
    ssum += cur->x * curr_size;
    curr_size++;
    if(cur->r) {
        ssum += cur->r->ssum;
        ssum += cur->r->sum * curr_size;
    }
    cur->ssum = ssum;
}

array<Node*, 2> split(Node* cur, int x) {
    if(!cur) return {nullptr, nullptr};

    array<Node*, 2> res;
    // cout << "node stats size : " << cur->size << " l size : " << (cur->l ? cur->l->size : 0) << " r size : " << (cur->r ? cur->r->size : 0) << endl;
    if(cur->x > x) {
        // cout << "do not include root into left partition" << endl;
        auto [lhs, rhs] = split(cur->l, x);
        cur->l = rhs;
        res = {lhs, cur};
    } else {
        // cout << "include root into left partition\n";
        auto [lhs, rhs] = split(cur->r, x);
        cur->r = lhs;
        res = {cur, rhs};
    }
    pull(cur);
    return res;
}

//push if it is not null. 
Node* merge(Node *lhs, Node *rhs) {
    // if(!lhs && !rhs) return nullptr;
    if(!lhs) return rhs;
    if(!rhs) return lhs;

    Node* res;
    if(lhs->y > rhs->y) {//make lhs the root. 
        Node* ch = merge(lhs->r, rhs);
        lhs->r = ch;
        res = lhs;
    } else {
        Node* ch = merge(lhs, rhs->l);
        rhs->l = ch;
        res = rhs;
    }
    pull(res);
    return res;
}

void printTree(Node* cur) {
    if(!cur) return;
    cout << "x : " << cur->x << " size : " << cur->size << " sum : " << cur->sum << " ssum : " << cur->ssum << " lsize : " << (cur->l ? cur->l->size : 0) << " rsize : " << (cur->r ? cur->r->size : 0) << endl;
    printTree(cur->l);
    printTree(cur->r);
}

// void inOrder(Node *cur) {
//     if(!cur) return;
//     // push(cur);
//     inOrder(cur->l);
//     cout << "cur val : " << cur->val << endl;
//     inOrder(cur->r);
// }

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    string s; cin >> s;
    SuffixArray sa(s);

    // cout << sa.sa << endl;
    // cout << sa.lcp << endl;

    vector<array<ll,3>> qs;
    stack<array<int,2>> st; // {index, height}

    for(int i = 1; i <= n; i++) {
        array<int,2> val = {};
        if(i == 1) {
            val = {i, 0};
        } else {
            val = {i, sa.lcp[i]};
            while(st.top()[1] > val[1]) {
                auto t = st.top();
                st.pop();
                qs.push_back({t[0] - 1, i, t[1] - max(val[1], st.top()[1])});
                val[0] = t[0];
            }
            if(st.top()[1] == val[1]) {
                val[0] = st.top()[0];
                st.pop();
            }
        }
        st.push(val);
    }

    while(sz(st) >= 2) {
        auto t = st.top();
        st.pop();
        qs.push_back({t[0] - 1, n + 1, t[1] - st.top()[1]});
    }

    // cout << "qs : " << qs << endl;
    int bs = sqrt(n);
    sort(qs.begin(), qs.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        int llb = lhs[0] / bs, lrb = lhs[1] / bs;
        int rlb = rhs[0] / bs, rrb = rhs[1] / bs;
        if(llb == rlb) {
            if(llb % 2 == 0) {
                return lrb < rrb;
            } else {
                return lrb > rrb;
            }
        } else {
            return llb < rlb;
        }
    });

    Z res = 0;
    int cl = 1, cr = 1;
    Node* cur = nullptr;

    auto add = [&](int idx) {
        int x = sa.sa[idx];
        // cout << "add idx : " << idx << " x : " << x << endl;
        auto [l, r] = split(cur, x);
        // cout << "print left x" << endl;
        // printTree(l);
        // cout << "print right x" << endl;
        // printTree(r);
        Node* add = new Node(x);
        Node* nl = merge(l, add);
        cur = merge(nl, r);
        // cout << "printing tree" << endl;
        // printTree(cur);
    };

    auto erase = [&](int idx) {
        int x = sa.sa[idx];
        // cout << "erase idx : " << idx << " x : " << x << endl;
        auto [l, r] = split(cur, x);
        auto [l1, r1] = split(l, x - 1);
        cur = merge(l1, r);
        // cout << "printing tree" << endl;
        // printTree(cur);
    };

    auto query = [&]() -> Z {
        // cout << "querying" << endl;
        // cout << "printing tree" << endl;
        // printTree(cur);
        if(cur) {
            return cur->ssum * 2 - cur->sum * (cur->size - 1);
        }
        return 0;
    };

    for(auto [l, r, cnt] : qs) {
        // cout << "l : " << l << " r : " << r << " cnt : " << cnt << endl;
        while(l < cl) {
            add(--cl);
        }
        while(r > cr) {
            add(cr++);
        }
        while(l > cl) {
            erase(cl++);
        }
        while(r < cr) {
            erase(--cr);
        }

        

        res += query() * cnt;
    }

    cout << res << '\n';

    return 0;
}
