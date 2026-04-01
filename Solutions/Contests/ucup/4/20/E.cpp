#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    // {good, good + ending}
    vector<int> vis(n);
    auto work = [&](string test) -> array<int,2> {
        cout << "testing val : " << test << endl;
        fill(vis.begin(), vis.end(), 0);
        int p = 0, mx = -1; 
        for(int i = 0; i < n; i++) {
            if(p < sz(test) && s[i] == test[p]) {
                vis[i] = 1;
                p++;
                mx = i;
            }
        }
        if(p != sz(test)) {
            cout << "x not found" << endl;    
            return {0, 0};
        }
        p = 0;
        for(int i = 0; i < n; i++) {
            if(vis[i] == 0) {
                if(p < sz(test) && s[i] <= test[p]) {
                    p++;
                    vis[i] = 1;
                } else if(i < mx) {
                    cout << "hole; no good" << endl;
                    return {0, 0};
                }
            }
        }
        return {1, count(vis.begin(), vis.end(), 1) == n};
    };

    string res = "";
    while(1) {
        for(char c = 'a'; c <= 'z'; c++) {
            res.push_back(c);
            if(work(res)[0]) break;
            res.pop_back();
        }
        if(work(res)[1]) break;
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int n; cin >> n;
    // string s(n, '6');
    // for(int i = 0; i < n; i++) s[i] = rng() % 5 + 'a';
    // cout << s << '\n';

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}