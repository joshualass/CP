#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    map<string, int> m;
    vector<string> a;

    for(int i = 0; i < n; i++) {
        char c; cin >> c;
        if(c == 'E') {
            string e; cin >> e;
            m[e] = a.size();
            a.push_back(e);
        } else if(c == 'D') {
            int r; cin >> r;
            while(r--) {
                m.erase(a.back());
                a.pop_back();
            }
        } else {
            int k; cin >> k;
            int min_kill = 0;
            int prev_idx = -1;
            int ok = 1;
            for(int j = 0; j < k; j++) {
                string s; cin >> s;
                if(s[0] == '!') {
                    s = s.substr(1);
                    if(m.count(s)) {
                        min_kill = max(min_kill, ((int) a.size()) - m[s]);
                    }
                } else {
                    if(m.count(s)) {
                        int time = m[s];
                        if(time > prev_idx) {
                            prev_idx = time;
                        }
                    } else {
                        ok = 0;
                    }
                }
            }
            // cout << "min_kill : " << min_kill << " prev_idx : " << prev_idx << " ok : " << ok << '\n';
            
            if(ok && prev_idx < ((int) a.size()) - min_kill) {
                if(min_kill == 0) {
                    cout << "Yes" << '\n';
                } else {
                    cout << min_kill << " " << "Just A Dream" << '\n';
                }
            } else {
                cout << "Plot Error\n";
            }
        }
    }


    return 0;
}
