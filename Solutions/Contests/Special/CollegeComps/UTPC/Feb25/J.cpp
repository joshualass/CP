#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

constexpr int P = 1e9 + 7;
using Z = Mint<P>;
// using Z = double;
const int MAXN = 1e6 + 1;
vector<Z> fact(MAXN), inv_fact(MAXN), res(MAXN), pows(MAXN);

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

struct TrieNode {
    TrieNode* a[10];
    int sameafter;
    TrieNode() {
        for(int i = 0; i < 10; i++) a[i] = nullptr;
        sameafter = 0;
    }
};

void insert(string s, TrieNode* root, set<string> &words) {
    TrieNode* curr = root;
    for(int i = 0; i < s.size(); i++) {
        char c = s[i];
        if(curr->a[c-'0'] == nullptr) {
            curr->a[c-'0'] = new TrieNode();
        }
        curr = curr->a[c-'0'];
        if(words.count(s.substr(i + 1))) {
            // cout << "s : " << s << " i : " << i << " add to sameafter\n";
            curr->sameafter++;
        }
    }
}

int query(string s, TrieNode* root) {
    TrieNode* curr = root;
    for(int i = 0; i < s.size(); i++) {
        char c = s[i];
        if(curr->a[c-'0'] == nullptr) {
            return 0;
        }
        curr = curr->a[c-'0'];
    }
    return curr->sameafter;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    int n; cin >> n;
    vector<string> a(n);
    set<string> words;

    for(auto &x : a) {
        cin >> x;
        words.insert(x);
    }

    TrieNode *root = new TrieNode();

    for(int i = 0; i < n; i++) {
        insert(a[i], root, words);
    }

    Z res = Z(n) * (n - 1) * (n - 2) * (n - 3) / 2;
    ll ties = 0;

    for(int i = 0; i < n; i++) {
        string word = a[i];
        for(int j = 1; j < word.size(); j++) {
            string b = word.substr(0,j);
            if(words.count(b)) {
                // cout << "query string : " << a[i].substr(j) << '\n';
                int cnt = query(a[i].substr(j), root);
                int aleft = word.size() - j;
                // cout << "word : " << word << " b : " << b << " cnt start : " << cnt << '\n';

                //try putting b on top again
                if(b.size() > aleft && b.substr(0,aleft) == word.substr(j) && words.count(b.substr(aleft))) {
                    // cout << "hit0\n";
                    cnt--;
                }
                //try putting a on top again
                if(word.substr(0,aleft) == word.substr(j) && words.count(word.substr(aleft))) {
                    // cout << "hit1\n";
                    cnt--;
                }
                //try putting a below
                if(words.count(word.substr(j) + word)) {
                    // cout << "hit2\n";
                    cnt--;
                }
                //try putting b below
                if(words.count(word.substr(j) + b)) {
                    // cout << "hit3\n";
                    cnt--;
                }
                //don't doublecount
                if(word + b == b + word) {
                    // cout << "hit4\n";
                    cnt++;
                }

                // cout << "cnt end : " << cnt << '\n';
                ties += cnt;
            }
        }
    }

    // for(int i = 0; i < 4; i++) {
    //     cout << "i : " << i << " sameafter : " << root->sameafter << '\n';
    //     root = root->a[1];
    // }

    // cout << "ties : " << ties << '\n';

    cout << res - ties << '\n';

    // int bruteforceres = 0;

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++) {
    //         for(int k = 0; k < n; k++) {
    //             for(int l = 0; l < n; l++) {
    //                 set<int> s = {i,j,k,l};
    //                 if(s.size() == 4) {
    //                     if(stoll(a[i] + a[j]) > stoll(a[k] + a[l])) {
    //                         bruteforceres++;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    // cout << "bruteforce res : " << bruteforceres << '\n';

    return 0;
}

/*

30 
1 2 11 22 12 21 111 112 121 122 211 212 221 222 1111 1112 1121 1122 1211 1212 1221 1222 2111 2112 2121 2122 2211 2212 2221 2222

*/