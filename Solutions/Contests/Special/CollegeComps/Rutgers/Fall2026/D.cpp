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

void solve() {
    int m, n; cin >> m >> n;
    vector<int> a(n); for (int i = 0; i < n; i++) cin >> a[i];

    vector<pair<int, int>> stack;
    int best = 0;
    int start_idx = 0; // start idx of the current matching
    for (int end_idx = 0; end_idx < n; end_idx++) {
        if (stack.size() == 0) {
            if (a[end_idx] != m) stack.push_back({a[end_idx], end_idx});
        }
        else {
            int top = stack.back().first;
            if (a[end_idx] == top + 1) {
                stack.back().first++;
                stack.back().second = end_idx;
                if (stack.back().first == m) stack.pop_back();
            }
            else if (a[end_idx] == 1) { 
                stack.push_back({1, end_idx});
            }
            else {
                start_idx = stack.back().second + 1;
                stack.clear();
                if (a[end_idx] != m) stack.push_back({a[end_idx], end_idx});
            }
        }

        int len = end_idx - start_idx + 1;
        best = max(best, len);
    }

    cout << best;

    // vector<bool> can_start(n, false);
    // for (int i = 0; i < n; i++) {
    //     if (a[i] >= 1 && a[i] <= m) can_start[i] = true;
    // }

    // vector<bool> can_continue(n, false);

    // for (int i = 1; i < n; i++) {
    //     if (!(a[i] >= 1 && a[i] <= m)) continue;
    //     bool cond1 = a[i] == 1;
    //     bool cond2 = (a[i - 1] + 1) == a[i];
    //     bool cond3 = (a[i - 1] == m);
    //     can_continue[i] = (cond1 || cond2 || cond3);
    // }   

    // vector<int> continue_length(n, 0);
    // for (int i = n - 1; i >= 0; i--) {
    //     if (can_continue[i] == false) continue;
    //     else if (i == (n - 1)) continue_length[i] = 1;
    //     else continue_length[i] = continue_length[i + 1] + 1;
    // }

    // int most = can_start[n - 1];
    // for (int i = 0; i < n - 2; i++) {
    //     if (!can_start[i]) continue;
    //     int start_here = can_start[i] + continue_length[i + 1];
    //     most = max(most, start_here);
    // }

    // cout << most;
}

int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0);

    int t; cin >> t;
    while (t--) {
        solve();
        cout << endl;
    }

    cout.flush();
    return 0;
}