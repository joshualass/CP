#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, k;
        cin >> n >> k;
        ll ans = 0;
        //is k too small?
        if(k < n + n / 2) {
            ans = n - 1;
            k -= n;
            ans -= k * 2;
        }
        //casework on n
        else {
            if(n == 1){
                ans = 0;
            }
            else if(ans == 2){
                if(__builtin_popcountll(k) == 1) ans = 1;
                else ans = 0;
            }
            else if(n % 2){
                ans = 0;
            }
            else {
                if(k == n + n / 2 + 1) ans = 1;
                else ans = 0;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}