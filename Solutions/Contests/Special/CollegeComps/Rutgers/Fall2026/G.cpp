#include<bits/stdc++.h>
using namespace std;
typedef int64_t LL;
typedef vector<int> vi;
typedef pair<LL,LL> pii;
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

int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0);

    LL t; cin >> t;
    while(t--){
        LL n; cin >> n;
        LL maxx = -1e18, minx = 1e18, maxy = -1e18, miny = 1e18;
        set<pii> stuff;
        for(int i = 0; i < n; i++){
            LL x,y; cin >> x >> y;
            maxx = max(x, maxx);
            maxy = max(y, maxy);
            minx = min(x, minx);
            miny = min(y, miny);
            stuff.insert({x,y});
        }
        bool works = true;
        if(!stuff.count({minx, miny})){
            works = false;
        }
        if(!stuff.count({minx, maxy})){
            works = false;
        }
        if(!stuff.count({maxx, miny})){
            works = false;
        }
        if(!stuff.count({maxx, maxy})){
            works = false;
        }
        if(works){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
    }

    cout.flush();
    return 0;
}