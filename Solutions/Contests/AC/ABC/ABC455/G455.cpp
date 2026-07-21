#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int h = 3;

//balanced arrays where every element appears k times
ll solve_freq(int n, int k, vector<int> a) {
    
    vector<vector<int>> b(n);
    

}

ll solve_dist(int n, int k, vector<int> a) {

}

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a(n), b(k);
    for(int &x : a) {
        cin >> x;
        x--;
    }
    for(int &x : b) cin >> x;

    for(int i = 0; i < k; i++) {
        cout << solve_freq(n, k, a) << " " << solve_dist(n, k, q) << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}