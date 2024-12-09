#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

constexpr int P = 1000000007;
using Z = Mint<P>;

template<typename T>
struct GE {

    int r, c;
    vector<vector<T>> mat;
    vector<T> x;

    GE(vector<vector<T>> mat, vector<T> x) {
        this->mat = mat;
        this->x = x;
        r = mat.size();
        c = mat[0].size();
    }

    //does row operation row /= div
    void divideRow(int row, T div) {
        for(int i = 0; i < c; i++) {
            mat[row][i] /= div;
        }
        x[row] /= div;
    }

    //does row operation r2 = r2 + r1 * s
    void addRow(int r1, T s, int r2) {
        for(int i = 0; i < c; i++) {
            mat[r2][i] = mat[r2][i] + mat[r1][i] * s;
        }
        x[r2] = x[r2] + x[r1] * s;
    }

    void eliminate(bool print) {
        printMat(print);
        //first step of GE
        vector<int> visited_rows(r,-1);
        for(int col = 0; col < c; ++col) {
            for(int row = 0; row < r; ++row) {
                if(mat[row][col] != 0 && visited_rows[row] == -1) {
                    visited_rows[row] = col;
                    if(mat[row][col] != 1) {
                        divideRow(row, mat[row][col]);
                        printMat(print);
                    }
                    bool shouldprint = 0;
                    for(int row2 = 0; row2 < r; row2++) {
                        if(mat[row2][col] != 0 && row2 != row) {
                            shouldprint = 1;
                            addRow(row, -mat[row2][col], row2);
                        }
                    }
                    if(shouldprint) {
                        printMat(print);
                    }
                    break;
                }
            }
        }
        //second step of GE
        for(int col = c - 1; col >= 0; col--) {
            for(int row = 0; row < r; row++) {
                if(visited_rows[row] == col) {
                    bool shouldprint = 0;
                    for(int row2 = 0; row2 < r; row2++) {
                        if(mat[row2][col] != 0 && row2 != row) {
                            shouldprint = 1;
                            addRow(row, -mat[row2][col], row2);
                        }
                    }
                    if(shouldprint) {
                        printMat(print);
                    }
                }
            }
        }
        cout << "resulting matrix\n";
        printMat(1);
    }

    void printMat(bool print) {
        if(print) {
            for(int i = 0; i < r; i++) {
                cout << '[';
                for(int j = 0; j < c; j++) {
                    cout << mat[i][j] << ",|"[j == c - 1];
                }
                cout << x[i] << "]\n";
            }
        }
        cout << '\n';
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll r, c; cin >> r >> c;
    vector<vector<Z>> mat(r,vector<Z>(c));
    vector<Z> x(c);

    for(vector<Z> &row : mat) {
        for(Z &col : row) {
            cin >> col;   
        }
    }

    for(Z &val : x) {
        cin >> val;
    }

    GE<Z> ge(mat,x);

    ge.eliminate(1);

    return 0;
}

/*
3 3 
2 6 1
11 2 0
4 1 3
3030 6892 18312
*/

/*
3 3 
0 0 1
1 0 0
0 1 1
0 0 0
*/