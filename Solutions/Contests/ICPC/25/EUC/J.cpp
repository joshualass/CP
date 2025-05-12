#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<bool> vb;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int wcnt = 0;
        string s;
        cin >> s;
        for(int i = 0; i < n; i++) wcnt += s[i] == 'W';
        if(wcnt % 2) {
            cout << "NO\n";
            continue;
        }
        vi wl, wr, rl, rr;
        for(int i = 0; i < n; i++){
            if(s[i] == 'W') wl.push_back(i);
            else rl.push_back(i);
        }
        for(int i = n; i < 2 * n; i++){
            if(s[i] == 'W') wr.push_back(i);
            else rr.push_back(i);
        }
        vector<pair<int, int>> ord;
        for(int i = 0; i < rl.size(); i++) ord.push_back({rl[i], wr[i]});
        for(int i = 0; i < wl.size() / 2; i++) ord.push_back({wl[i], wl[wl.size() / 2 + i]});
        for(int i = 0; i < rr.size() / 2; i++) ord.push_back({rr[i], rr[rr.size() / 2 + i]});
        sort(ord.begin(), ord.end());
        bool is_valid = true;
        for(int i = 0; i < ord.size() - 1; i++) {
            if(ord[i].second > ord[i + 1].second) is_valid = false;
        }
        cout << (is_valid? "YES" : "NO") << "\n";
    }

    return 0;
}