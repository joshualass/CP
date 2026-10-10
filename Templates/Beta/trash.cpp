#include<bits/stdc++.h>
using namespace std;
typedef int64_t LL;
typedef vector<int> vi;
typedef pair<int,int> pii;
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lso(s) ((s) & -(s))
#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) "LAMELO > MJ"
#endif
int lg(LL s) { return s ? __builtin_clzll(1) - __builtin_clzll(s) : -1; }//lg(1)=0, lg(2)=1, lg(3)=1, lg(4)=2, ...
LL floor(LL a, LL b) { return a / b - (a % b < 0); }
LL ceil(LL a, LL b) { return a / b + (a % b > 0); }
template<typename T>
istream& operator>>(istream& in, vector<T> &vec){
    for(auto &x : vec){
        in>>x;
    }
    return in;
}
const LL MOD = 998244353;
struct mint {
  LL x;
  mint(LL x=0):x((x%MOD+MOD)%MOD){}
  mint& operator+=(const mint a) {if ((x += a.x) >= MOD) x -= MOD;return *this;}
  mint& operator-=(const mint a) {if ((x += MOD-a.x) >= MOD) x -= MOD;return *this;}
  mint& operator*=(const mint a) {(x *= a.x) %= MOD;return *this;}
  mint operator+(const mint a) const {mint res(*this);return res+=a;}
  mint operator-(const mint a) const {mint res(*this);return res-=a;}
  mint operator*(const mint a) const {mint res(*this);return res*=a;}
  mint pow(LL b) const {
    mint res(1), a(*this);
    while (b) {
      if (b & 1) res *= a;
      a *= a;
      b >>= 1;
    }
    return res;
  }
  // for prime MOD
  mint inv() const {return pow(MOD-2);}
  mint& operator/=(const mint a) {return (*this) *= a.inv();}
  mint operator/(const mint a) const {mint res(*this);return res/=a;}
};
ostream& operator<<(ostream& os, const mint& a) {os << a.x; return os;}


//var 
LL n;
const LL O = 30407279;
pii ordering[O];
int idx[10001][10001], val[O];
void farey(LL n){
    LL a = 0, b = 1, c = 1, d = n;
    ordering[0] = {b,a};
    int pos = 1;
    while(c <= n && c >= 0){
        LL k = (n + b) / d;
        LL na = c, nb = d, nc = k * c - a, nd = k * d - b;
        a = na; b = nb; c = nc; d = nd;
        ordering[pos] = {b,a};
        idx[b][a] = pos;
        pos++;
    }
}

int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0);

    cin >> n;
    vector<LL> a(n); cin >> a;
    const LL T = 10000;
    vector<LL> freq(T + 1);
    for(auto u : a){
        freq[u]++;
    }
    farey(T);
    for(int i = 1; i <= T; i++){
        for(int j = 1; j <= i; j++){
            LL m = gcd(i,j);
            val[idx[i/m][j/m]] += freq[i];
        }
    }
    auto cp = [&](pii x, pii y) -> bool {
        return x.f * y.s > x.s * y.f;
    };
    LL presses = n;
    pii ans = {1e9, 1};
    pii source = {-1,-1};
    for(int i = 1; i < O; i++){
        LL l = ordering[i].f + ordering[i].s, r = ordering[i].s;
        if(cp(ans, {l * presses,r})){
            source = {l,r};
            ans = {l * presses,r};
        }
        presses += val[i];
    }
    LL l = source.f, r = source.s;
    LL m = gcd(l,r);
    cout << l / m << "/" << r / m << "\n";

    cout.flush();
    return 0;
}