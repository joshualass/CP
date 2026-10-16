#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }

    vector<int> c, vis(n);
    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            int s = 0, x = i;
            while(vis[x] == 0) {
                vis[x] = 1;
                s++;
                x = a[x];
            }
            c.push_back(s);
        }
    }

    assert(accumulate(c.begin(), c.end(), 0) == n);

    if(*max_element(c.begin(), c.end()) > k + 1) {
        cout << "Bob\n";
    } else if(k == 1) {
        int ok = count(c.begin(), c.end(), 1) % 2 || count(c.begin(), c.end(), 2) == 0;
        cout << (ok ? "Alice" : "Bob") << '\n';
    } else if(*max_element(c.begin(), c.end()) == k + 1) {
        int rem = (k + 1) + k;
        for(int x : c) {
            if(x > 1) rem -= x;
        }
        int p = count(c.begin(), c.end(), 1) % (k + 1);
        int ok;
        if(rem == k) {
            ok = p != 0;
        } else {
            ok = p <= rem;
        }
        cout << (ok ? "Alice" : "Bob") << '\n';
    } else {
        //every size <= k :)
        int s = 0;
        for(int x : c) {
            if(x > 2) {
                s += x;
            }
        }
    
        if(s <= k) { //she can plug up everything larger than 2 and nothing is larger than size k. ok
            cout << "Alice\n";
            return;
        }
    
        vector<vector<int>> dp(k + 1, vector<int>(k + 1));
        dp[0][0] = 1;
        for(int x : c) {
            for(int i = k - x; i >= 0; i--) {
                for(int j = 0; j + x - 1 <= k; j++) {
                    if(dp[i][j]) {
                        dp[i + x][j + x - 1] = 1;
                    }
                }
            }
        }
    
        int mxrem = 0;
        for(int i = 0; i <= k; i++) {
            for(int j = 0; j <= k; j++) {
                if(dp[i][j]) mxrem = max(mxrem, j);
            }
        }
        assert(mxrem < k);
    
        int bad = n - sz(c);
        int left = bad - mxrem;
        assert(left >= 0);
    
        // cout << "mxrem : " << mxrem << " bad : " << bad << " left : " << left << endl;
    
        cout << (left <= k ? "Alice" : "Bob") << '\n';

    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}