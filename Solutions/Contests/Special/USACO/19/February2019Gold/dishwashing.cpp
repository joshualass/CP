#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const int MAXN = 1e5;

//let's binary search the prefix
//then use stacks to solve the prefix in linear time
//ff for now 

int ids[MAXN+1];

bool solve(vector<int> &v, int hi) {

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // freopen("dishes.in","r",stdin);
    // freopen("dishes.out","w",stdout);
    
    int n; cin >> n;
    vector<int> v(n);
    for(int &x : v) cin >> x;

    int l = 0, r = n - 1;
    while(r - l != 1) { //[l,r] binary search
        int m = l + (r - l + 1) / 2;
        if(solve(v,m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    return 0;
}