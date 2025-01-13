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

constexpr int P = 998244353;
using Z = Mint<P>;

vector<Z> fact(1,1);
vector<Z> inv_fact(1,1);

Z choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    while(fact.size() < n + 1) {
        fact.push_back(fact.back() * fact.size());
        inv_fact.push_back(1 / fact.back());
    }
    return fact[n] * inv_fact[k] * inv_fact[n-k];
}

template<typename T>
struct Matrix {
    static constexpr T base = 0;
    int r, c;
    vector<vector<T>> mat;
    Matrix(vector<vector<T>> _mat) {
        r = _mat.size();
        c = _mat[0].size();
        mat = _mat;
    }
    constexpr Matrix &operator+=(Matrix rhs) & {
        assert(r == rhs.r && c == rhs.c);
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                mat[i][j] += rhs.mat[i][j];
            }
        }
        return *this;
    }
    constexpr Matrix &operator*=(Matrix rhs) & {
        assert(c == rhs.r);
        vector<vector<T>> res(r,vector<T>(rhs.c));
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < rhs.c; j++) {
                for(int k = 0; k < c; k++) {
                    res[i][j] += mat[i][k] * rhs.mat[k][j];
                }
            }
        }
        c = rhs.c;
        mat = res;
        return *this;
    }
    friend constexpr Matrix operator+(Matrix lhs, Matrix rhs) {
        Matrix res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Matrix operator*(Matrix lhs, Matrix rhs) {
        Matrix res = lhs;
        res *= rhs;
        return res;
    }
};

void matpow(Matrix<Z> &base, Matrix<Z> a, ll b) {
    for(; b; b /= 2, a *= a) {
        if(b & 1) {
            base *= a;
        }
    }
}

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int n, m; cin >> n >> m;
    vector<int> a(n);
    Tree<ll> tree(n), cnts(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        tree.update(a[i], a[i]);
        cnts.update(a[i], 1);
    }

    vector<vector<Z>> transform(3, vector<Z>(3)); //setup the matrix as [from][to]
    //brute-force all swaps because there are not many cases to conside r. Sanity check is that the sum of all the swaps is N * (N - 1) / 2
    //case 0 at target indices. 
    transform[0][1] = 4; //4 ways to do this, 2 positions on the inside, 2 positions on the outisde 2 x 2 = 4.
    transform[0][0] = 1LL * n * (n - 1) / 2 - 4; //n * (n - 1) / 2 total swaps. 4 of them change the state, the rest don't
    //case 1 at target indices.
    transform[1][0] = n - 3; //1 way to select the index at the correct indices, n - 3 indices of the non target element to choose from
    transform[1][2] = 1; //1 way to do this
    transform[1][1] = 1LL * n * (n - 1) / 2 - (n - 3 + 1); //remainder from all possible swaps
    //case 2 at target indices
    transform[2][2] = 1 + 1LL * (n - 2) * (n - 3) / 2; //either select the 2 correct indices or select to outside indices
    transform[2][1] = 2 * (n - 2); //select one of the 2 correct indices. This and the above add to n * (n - 1) / 2

    vector<vector<Z>> base(3,vector<Z>(3));

    for(int i = 0; i < n - 1; i++) {
        Z sumdiff = 0; //stores the sum of the absolute differences for all elements after i
        sumdiff += tree.query(a[i] + 1, n) - a[i] * cnts.query(a[i] + 1, n);
        sumdiff += a[i] * cnts.query(0, a[i]) - tree.query(0,a[i]);

        //initially N - 1 - 4 pairs should have 0 target indices in common to start. The other 4 pairs normally have 1 in common
        base[0][0] += sumdiff * (n - 1 - 4);
        base[1][1] += sumdiff * 4;
        if(i == 0) { //i is at an end, so there is one less pair with 1 in common
            base[0][0] += sumdiff;
            base[1][1] -= sumdiff;
        }

        //undo adj of the next element where there are 2 correct at the start. 
        ll adjdiff = abs(a[i] - a[i+1]);
        base[1][1] -= adjdiff * 2;
        base[0][0] += adjdiff;
        base[2][2] += adjdiff;

        //update last endpoint
        adjdiff = abs(a[i] - a[n-1]);
        base[1][1] -= adjdiff;
        base[0][0] += adjdiff;

        tree.update(a[i],0);
        cnts.update(a[i],0);
    }

    Matrix<Z> tmat(transform);
    Matrix<Z> bmat(base);

    matpow(bmat, tmat, m);

    Z res = 0;
    for(int i = 0; i < 3; i++) {
        res += bmat.mat[i][2];
    }

    cout << res << '\n';

    return 0;
}