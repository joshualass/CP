#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v);

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
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

void solve() {
    
    int n; cin >> n;
    Z res = 0, free = 2;
    for(Z i = 4; i.x <= n; i += 1) {
        // free += (i-2)*(i-1) / 2 - 1;
        // cout << "i : " << i << " free : " << free << '\n';
        res += free;
        // free *= (i+1);
        free = free * (i + 1) + (i - 1);
        
    }
    res += n - 1;
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // vector<set<vector<int>>> poss(10);
    // vector<int> frees(10);
    // poss[2].insert({0,1});

    // for(int i = 2; i < 9; i++) {
    //     int freecnt = 0;
    //     int zeroonecnt = 0;
    //     for(vector<int> v : poss[i]) {
    //         int inv = 0;
    //         int s = v.size();
    //         for(int i = 0; i < s; i++) {
    //             for(int j = i + 1; j < s; j++) {
    //                 if(v[i] > v[j]) {
    //                     inv++;
    //                 }
    //             }
    //         }
    //         if(find(v.begin(),v.end(),inv) == v.end()) {
    //             freecnt++;
    //         }
    //         if(*max_element(v.begin(),v.end()) <= 1) zeroonecnt++;
    //         for(int j = 0; j <= s; j++) {
    //             v.insert(v.begin() + j, inv);
    //             poss[i+1].insert(v);
    //             v.erase(v.begin() + j);
    //         }
    //     }
    //     cout << "i : " << i << " poss[i] : " << poss[i] << endl;
    //     cout << "free at i : " << freecnt << endl;
    //     cout << "zeroonecount at i : " << zeroonecnt << endl;
    //     frees[i] = freecnt;
    // }

    // for(int i = 2; i < 9; i++) {
    //     cout << "i : " << i << " free[i] : " << frees[i] << " leftover from last ? " << frees[i] - frees[i-1] * (i-1) + 1 << endl;
    // }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}