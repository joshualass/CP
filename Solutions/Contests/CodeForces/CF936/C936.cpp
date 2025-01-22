#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    string s, t; cin >> s >> t;
    vector<int> res;

    auto work = [&](int x) {
        res.push_back(x);
        string c = s.substr(n-x,x) + s.substr(0,n-x);
        reverse(c.begin(),c.begin() + x);
        s = c;
    };

    for(int i = 0; i < n; i++) {
        int f = -1;
        for(int j = n - 1; j >= 0; j--) {
            if(s[j] == t[n-i-1]) {
                f = j;
                break;
            }
        }
        if(f < i) { //either did not find a character or found character is already used
            cout << "-1\n";
            return 0;
        }
        work(n);
        work(f);
        work(1);
    }

    cout << res.size() << '\n';
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << " \n"[i == res.size() - 1];
    }

    return 0;
}