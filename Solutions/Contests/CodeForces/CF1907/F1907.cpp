#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int try1(vector<int> &v, int lhs) {
    int ops = min(lhs + 2, (int) v.size() - lhs);
    bool issorted = 1;
    for(int i = 1; i < v.size(); i++) {
        int previdx = (i + lhs - 1) % v.size();
        int curridx = (i + lhs) % v.size();
        if(v[previdx] > v[curridx]) {
            issorted = 0;
        }
    }
    if(issorted) {
        return ops;
    } else {
        return -1;
    }
}

int try2(vector<int> &v, int lhs) {
    int ops = min(lhs, (int) v.size() - lhs);
    bool issorted = 1;
    for(int i = 1; i < v.size(); i++) {
        int previdx = (i + lhs - 1) % v.size();
        int curridx = (i + lhs) % v.size();
        if(v[previdx] > v[curridx]) {
            issorted = 0;
        }
    }
    if(issorted) {
        return ops;
    } else {
        return -1;
    }
}

void solve() {

    int n; cin >> n;
    vector<int> v(n);

    for(auto &x: v) cin >> x;

    int min_val = *min_element(v.begin(), v.end());
    int min_count = count(v.begin(), v.end(), min_val);
    int lorhs = -1, lolhs = -1;
    set<int> uniquesssss(v.begin(),v.end());
    if(uniquesssss.size() == 1) {
        cout << "0\n";
        return;
    }
    bool issorted = 1;
    for(int i = 1; i < n; i++) {
        if(v[i-1] > v[i]) issorted = 0;
    }
    if(issorted) {
        cout << "0\n";
        return;
    }
    if(v.front() == min_val && v.back() == min_val) {
        for(int i = 0; i < n; i++) {
            if(v[i] != min_val) {
                break;
            }
            lorhs = i;
        }
        for(int i = n - 1; i >= 0; i--) {
            if(v[i] != min_val) {
                break;
            }
            lolhs = i;
        }
    } else {
        for(int i = 0; i < n; i++) {
            if(v[i] == min_val) {
                if(lolhs == -1) {
                    lolhs = i;
                }
                lorhs = i;
            }
        }
    }

    int forward = try1(v,lolhs);
    reverse(v.begin(), v.end());
    lorhs = -1, lolhs = -1;
    if(v.front() == min_val && v.back() == min_val) {
        for(int i = 0; i < n; i++) {
            if(v[i] != min_val) {
                break;
            }
            lorhs = i;
        }
        for(int i = n - 1; i >= 0; i--) {
            if(v[i] != min_val) {
                break;
            }
            lolhs = i;
        }
    } else {
        for(int i = 0; i < n; i++) {
            if(v[i] == min_val) {
                if(lolhs == -1) {
                    lolhs = i;
                }
                lorhs = i;
            }
        }
    }
    int reverse = try2(v,lolhs);
    int ans = 42069;
    if(forward != -1 && reverse != -1) {
        ans = min(forward, reverse + 1);
    } else if(forward != -1) {
        ans = forward;
    } else if(reverse != -1) {
        ans = reverse + 1;
    } else {
        ans = -1;
    }
    cout << ans << '\n';

    //wtf     https://atcoder.jp/contests/arc132/submissions/47391572
    // int n; cin >> n;

    // int oneidx = -1;
    // int nidx = -1;

    // for(int i = 0; i < n; i++) {
    //     int num; cin >> num;
    //     if(num == 1) {
    //         oneidx = i;
    //     }
    //     if(num == n) {
    //         nidx = i;
    //     }
    // }

    // // cout << min(oneidx, 2 + n - oneidx) << '\n';

    // if((nidx + n - oneidx) % n == 1) { //n is after 1
    //     cout << min(oneidx + 2, n - oneidx);
    // } else {//n comes before 1
    //     cout << min(oneidx, 2 + n - oneidx);
    // }
    // cout << '\n';  
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}