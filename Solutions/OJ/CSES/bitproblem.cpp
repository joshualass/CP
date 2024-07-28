#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int maxx = 20;

vector<int> calcor(vector<int> &a) {

    vector<int> dp(1 << maxx);
    for(int x : a) {
        dp[x]++;
    }

    for(int i = 0; i < maxx; i++) {
        for(int j = 0; j < 1 << maxx; j++) {
            if(j & (1 << i)) {
                dp[j] += dp[j ^ (1 << i)];
            }
        }
    }

    vector<int> res(a.size());
    for(int i = 0; i < a.size(); i++) {
        res[i] = dp[a[i]];
    }
    return res;
}

vector<int> calcand(vector<int> &a) {

    vector<int> dp(1 << maxx);
    for(int x : a) {
        dp[x]++;
    }

    for(int i = 0; i < maxx; i++) {
        for(int j = (1 << maxx) - 1; j >= 0; j--) {
            if((j & (1 << i)) == 0) {
                dp[j] += dp[j ^ (1 << i)];
            }
        }
    }

    vector<int> res(a.size());
    for(int i = 0; i < a.size(); i++) {
        res[i] = dp[a[i]];
    }
    return res;

}

vector<int> calcnot(vector<int> &a) {
 
 
    vector<int> dp(1 << maxx);
    for(int x : a) {
        dp[x]++;
    }

    for(int i = 0; i < maxx; i++) {
        for(int j = 0; j < 1 << maxx; j++) {
            if(j & (1 << i)) {
                dp[j] += dp[j ^ (1 << i)];
            }
        }
    }

    vector<int> res(a.size());
    for(int i = 0; i < a.size(); i++) {
        
        a[i] ^= (1 << maxx) - 1;
        // cout << "a[i] ? " << a[i] << '\n';
        res[i] = a.size() - dp[a[i]];

    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<int> one = calcor(a);
    vector<int> two = calcand(a);
    vector<int> three = calcnot(a);

    for(int i = 0; i < n; i++) {
        cout << one[i] << " " << two[i] << " " << three[i] << '\n';
    }

    return 0;
}