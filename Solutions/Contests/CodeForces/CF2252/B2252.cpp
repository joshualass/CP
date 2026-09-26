#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    auto work = [&](int start, int stop) -> int {
        int cnt = 0;
        string elim;
        for(char c : s) {
            if((start ^ (cnt & 1)) == c - '0') {
                cnt++;
            } else {
                elim.push_back(c);
            }
        }
        
        if((start ^ stop) == (cnt & 1)) {
            if(cnt == 0) return 1e9;
            cnt--;
            elim.push_back('0' + (stop ^ 1));
        }
        // cout << "start : " << start << " stop : " << stop << " elim : " << elim << endl;
        if(abs(count(elim.begin(), elim.end(), '0') - count(elim.begin(), elim.end(), '1')) <= 1) {
            return sz(elim);
        } else {
            return 1e9;
        }
    };

    int res = 1e9;
    for(int start = 0; start < 2; start++) {
        for(int stop = 0; stop < 2; stop++) {
            res = min(res, work(start, stop));
        }
    }
    if(res == 1e9) res = -1;

    cout << res << '\n';

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