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


//var 
LL n,m,q;
const LL B = 120;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0);

    cin >> n >> m >> q;
    vector<vector<LL>> adj(n + 1);
    for(int i = 0; i < m; i++){
        LL x,y; cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    vector<vector<LL>> d(min(B,n), vector<LL>(n + 1, 1e18));
    vector<LL> stuff;
    for(int i = 0; i < n; i++){
        stuff.pb(i);
    }
    shuffle(stuff.begin(), stuff.end(), rng);
    for(int i = 0; i < min(B,n); i++){
        LL center = stuff[i];
        queue<LL> q;
        q.push(center);
        d[i][center] = 0;
        vector<bool> v(n + 1);
        while(!q.empty()){
            LL curr = q.front();
            q.pop();
            for(auto u : adj[curr]){
                if(d[i][u] > d[i][curr]){
                    d[i][u] = d[i][curr] + 1;
                    q.push(u);
                }
            }
        }
    }
    for(int i = 0; i < q; i++){
        LL x,y; cin >> x >> y;
        bool small = false;
        for(int j = 0; j < min(B,n); j++){
            if(d[j][x] + d[j][y] <= 20000){
                small = true;
            }
        }
        if(small){
            cout << "NO\n";
        }else{
            cout << "YES\n";
        }
    }

    cout.flush();
    return 0;
}