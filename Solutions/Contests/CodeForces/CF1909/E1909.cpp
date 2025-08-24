#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int MAXN = 2e5;
int test[MAXN + 1];

/*
guess 1 - we try each of the button dependencies by themselves. 

Basis for the guess 
we should try to avoid pressing additional buttons. If these additional buttons were to decresae the lamp on count, then we should 
press these buttons by themselves. 

no dice.

first step is to implement the test correctly. then realize that the only lamps left on after all the buttons are pressed are the lamps with an odd number of factors or squres. 
Then, always possible for n >= 20, so we must bruteforce the other cases. Used editorial to make this observation. 

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<vector<int>> a[20];

void solve() {
    
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
    }
    vector<int> f;
    if(n >= 20) {
        for(int i = 0; i < n; i++) {
            f.push_back(i);
        }
    } else {
        for(auto s : a[n]) {
            // cout << "n : " << n << " s : " << s << '\n';
            int ok = 1;
            for(int i = 0; i < n; i++) {
                if(s[i]) {
                    for(int to : adj[i]) {
                        if(s[to] == 0) ok = 0;
                    }
                }
            }
            // cout << "ok : " << ok << '\n';
            if(ok) {
                for(int i = 0; i < n; i++) if(s[i]) f.push_back(i);
                break;
            }
        }
    }

    if(f.size()) {
        cout << f.size() << '\n';
        for(int i = 0; i < f.size(); i++) cout << f[i] + 1 << " \n"[i == f.size() - 1];
    } else {
        cout << "-1\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int i = 1; i <= MAXN; i++) {
    //     for(int j = i; j <= MAXN; j += i) {
    //         test[j] ^= 1;
    //     }
    // }

    // int cnt = 0;

    // for(int i = 1; i <= MAXN; i++) {
    //     cnt += test[i];
    //     cout << ((double) cnt) / i << " \n"[i == MAXN];
    // }

    for(int i = 1; i < 20; i++) {
        for(int bm = 1; bm < 1 << i; bm++) {
            if(__builtin_popcount(bm) <= i / 5) {
                vector<int> cur(i + 1);
                vector<int> s(i);
                for(int j = 0; j < i; j++) {
                    if((bm >> j) & 1) cur[j+1] = 1;
                }
                for(int j = 1; j <= i; j++) {
                    if(cur[j]) {
                        s[j-1] = 1;
                        for(int k = j; k <= i; k += j) cur[k] ^= 1;
                    }
                }
                a[i].push_back(s);
            }
        }
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}