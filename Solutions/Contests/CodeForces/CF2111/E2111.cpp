#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, q; cin >> n >> q;
    string s; cin >> s;
    map<char, map<char, set<int>>> m;

    for(int i = 0; i < q; i++) {
        char a, b; cin >> a >> b;
        m[a][b].insert(i);
    }

    auto finder1 = [&](char a, char b) -> int {
        auto it = m[a][b].begin();
        if(it != m[a][b].end()) {
            m[a][b].erase(it);
            return 1;
        }
        return 0;
    };

    auto finder2 = [&](char a, char b, char c) -> int {
        auto it = m[a][b].begin();
        if(it != m[a][b].end()) {
            auto it2 = m[b][c].lower_bound(*it);
            if(it2 != m[b][c].end()) {
                m[a][b].erase(it);
                m[b][c].erase(it2);
                return 1;
            }
        }
        return 0;
    };

    for(int i = 0; i < n; i++) {
        if(s[i] == 'c') {
            if(finder1('c', 'a')) {
                s[i] = 'a';
                continue;
            }
            if(finder2('c', 'b', 'a')) {
                s[i] = 'a';
                continue;
            }
            if(finder1('c', 'b')) {
                s[i] = 'b';
                continue;
            }
            if(finder2('c', 'a', 'b')) {
                assert(0);
            }
        } else if(s[i] == 'b') {
            if(finder1('b', 'a')) {
                s[i] = 'a';
                continue;
            }
            if(finder2('b', 'c', 'a')) {
                s[i] = 'a';
                continue;
            }
        }
    }

    cout << s << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}