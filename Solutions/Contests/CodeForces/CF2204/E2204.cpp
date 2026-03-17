#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

int use[10];

void solve() {
    
    string s; cin >> s;
    if(sz(s) == 1) {
        cout << s << '\n';
    } else {
        vector<int> cnts(10);
        for(char c : s) cnts[c - '0']++;
        int cur = 1;
        while(1) {
            for(int i = 0; i < 10; i++) use[i] = 0;
            int t = cur;
            while(1) {
                int tt = t;
                int s = 0;
                while(tt) {
                    use[tt%10]++;
                    s += tt % 10;
                    tt/= 10;
                }
                if(t < 10) break;
                t = s;
            }

            int ok = 1;
            int s = 0;
            for(int i = 0; i < 10; i++) {
                if(use[i] > cnts[i]) {
                    ok = 0;
                } else {
                    s += i * (cnts[i] - use[i]);
                }
            }

            if(ok && s == cur) {
                // cout << "found cur : " << cur << endl;
                for(int i = 9; i >= 0; i--) {
                    for(int j = 0; j < cnts[i] - use[i]; j++) cout << i;
                }
                int t = cur;
                while(1) {
                    int tt = t;
                    int s = 0;
                    while(tt) {
                        use[tt%10]++;
                        s += tt % 10;
                        tt/= 10;
                    }
                    cout << t;
                    if(t < 10) break;
                    t = s;
                }
                cout << '\n';
                return;
            } else {
                cur++;
            }
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}