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
        int n, k;
        cin >> n >> k;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        sort(a.begin(), a.end());
        int ans = 0;
        {
            int pcnt = 0;
            vb v(n, false);
            int ptr = n - 1;
            for(int i = 0; i < n; i++){
                while(ptr != -1 && a[i] + a[ptr] >= k) ptr --;
                if(ptr <= i) break;
                v[i] = true, v[ptr] = true;
                ans ++, pcnt ++;
                ptr --;
                if(pcnt == a.size() / 3) break;
            }
            // cout << "PCNT : " << pcnt << "\n";
            vi na(0);
            for(int i = 0; i < n; i++) if(!v[i]) na.push_back(a[i]);
            for(int i = 0; i < pcnt; i++) {
                if(na.size() == 0) break;
                na.pop_back();
            }
            a = na;
        }
        if(a.size() != 0) {
            int lcnt = 0;
            for(int i = 0; i < a.size(); i++) lcnt += a[i] < k;
            // cout << "LCNT : " << lcnt << "\n";
            lcnt = min(lcnt, (int) a.size() / 2);
            ans += a.size() - lcnt;
        }
        ans --;
        cout << ans << "\n";
    }

    return 0;
}