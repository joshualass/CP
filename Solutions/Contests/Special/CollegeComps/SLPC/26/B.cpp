#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

int cdp(vector<string> &g) {
    set<string> pals;
    int n = sz(g);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            string s = "";
            for(int k = 0; j + k < n; k++) {
                s.push_back(g[i][j+k]);
                string t = s;
                reverse(t.begin(), t.end());
                if(s == t) pals.insert(t);
            }
        }
    }
    for(int j = 0; j < n; j++) {
        for(int i = 0; i < n; i++) {
            string s = "";
            for(int k = 0; i + k < n; k++) {
                s.push_back(g[i+k][j]);
                string t = s;
                reverse(t.begin(), t.end());
                if(s == t) pals.insert(t);
            }
        }
    }
    // cout << "pals : " << pals << endl;
    return sz(pals);
}


void testing() {

    int n = 3;
    vector<string> g(n, string(n, 'a'));
    vector<string> bg;
    int best = -1;
    for(int i = 0; i < 1 << (n * n); i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                g[j][k] = 'a' + ((i >> (j * 4 + k)) & 1);
            }
        }
        int p = cdp(g);
        if(p > best) {
            best = p;
            bg = g;
        }
    }

    cout << "best : " << best << endl;
    cout << "bg" << endl;
    for(auto x : bg) cout << x << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // testing();

    // vector<vector<int>> p = {
    //     {0, 1, 1, 0},
    //     {0, 0, 0, 0},
    //     {0, 1, 0, 1},
    //     {1, 1, 1, 1}
    // };

    // vector<string> g(100, string(100, 'a'));

    // for(int i = 0; i < 25; i++) {
    //     for(int j = 0; j < 25; j++) {
    //         for(int k = 0; k < 4; k++) {
    //             for(int l = 0; l < 4; l++) {
    //                 g[i*4+k][j*4+l] = 'a' + (p[k][l] ? i : j);
    //             }
    //         }
    //     }
    // }

    // vector<string> g = {
    //     "aaaa",
    //     "bbbb",
    //     "abcb",
    //     "bacd"
    // };

    // cout << cdp(g) << endl;

    vector<string> g(100, string(100, 'a'));

    for(int i = 0; i < 100; i++) {
        char f = 'a' + i / 10;
        char s = 'a' + 10;
        if((i / 10) % 2 == 0) {
            s += 9 - i % 10;
        } else {
            s += i % 10;
        }
        for(int j = 0; j < 100; j++) {
            g[i][j] = (j % 2 == 0 ? f : s);
        }
    }

    // for(auto x : g) cout << x << endl;

    int n; cin >> n;
    for(int i = 0; i < n; i++) cout << g[i].substr(0, n) << '\n';

    return 0;
}
