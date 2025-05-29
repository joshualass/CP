#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;

signed main() {

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n), b(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i++) cin >> b[i];
        for(int i = 0; i < n; i++) a[i] --, b[i] --;
        vi bpos(n);
        for(int i = 0; i < n; i++) bpos[b[i]] = i;
        vector<pii> ans;
        bool is_valid = true;
        for(int i = 0; i < n; i++){
            // for(int j = 0; j < n; j++) cout << a[j] << " ";
            // cout << "\n";
            stack<pii> s;   //{val, ind}
            int tgt = bpos[i];
            int cloc = -1;
            for(int j = 0; j < n; j++){
                if(a[j] == i) {
                    cloc = j;
                    break;
                }
            }
            if(tgt > cloc) {
                is_valid = false;
                break;
            }
            if(tgt == cloc) continue;
            for(int j = cloc - 1; j >= tgt; j--){
                int val = a[j];
                if(a[j] < i) continue;
                while(s.size() != 0 && s.top().first > val) s.pop();
                s.push({val, j});
            }
            vi inds;
            while(s.size() != 0){
                inds.push_back(s.top().second);
                s.pop();
            }
            reverse(inds.begin(), inds.end());
            for(int ind : inds) {
                ans.push_back({ind, cloc});
                swap(a[cloc], a[ind]);
                cloc = ind;
            }
        }
        done: {}
        if(!is_valid) {
            cout << "-1\n";
            continue;
        }
        for(int i = 0; i < n; i++) assert(a[i] == b[i]);
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++) cout << ans[i].first + 1 << " " << ans[i].second + 1 << "\n";
    }

    return 0;
}