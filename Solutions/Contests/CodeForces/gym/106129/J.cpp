#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

map<string,string> pc;
map<string,string> rpc;

string min_rotate(string s) {
    string res = s;
    for(int i = 0; i < sz(s); i++) {
        string t = s.substr(i) + s.substr(0, i);
        res = min(res, t);
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    map<string,string> m23, m32;
    for(int i = 0; i < 8; i++) {
        string b2 = "", b3 = "";
        int t = i;
        for(int j = 0; j < 3; j++) {
            b2.push_back('0' + (t % 2));
            t /= 2;
        }
        t = i;
        for(int j = 0; j < 2; j++) {
            b3.push_back('0' + (t % 3));
            t /= 3;
        }
        m23[b2] = b3;
        m32[b3] = b2;
    }

    for(int i = 1; i <= 6; i++) {
        set<string> vis;
        int p = 0;
        for(int j = 0; j < 1 << i; j++) {
            string text = "";
            int t = j;
            for(int k = 0; k < i; k++) {
                text.push_back('0' + (t % 2));
                t /= 2;
            }

            string test;
            while(1) {
                t = p++;
                test = "";
                for(int k = 0; k < i; k++) {
                    test.push_back('0' + (t % 3));
                    t /= 3;
                }
                test = min_rotate(test);
                if(vis.count(test) == 0) {
                    vis.insert(test);
                    break;
                }
            }

            pc[text] = test;
            rpc[test] = text;
        }
    }

    string type; cin >> type;
    if(type == "Encode") {
        int n; cin >> n;
        string s; cin >> s;

        if(n <= 6) {
            cout << pc[s] << '\n';
        } else {
            string res = "22";
            res.append(m23[s.substr(0,3)]);
            res.append(m23[s.substr(3,3)]);
            res.append(s.substr(6));
            cout << res << '\n';
        }

    } else {
        int n; cin >> n;
        string s; cin >> s;
        if(n <= 6) {
            s = min_rotate(s);
            cout << rpc[s] << '\n';
        } else {
            int start = -1;
            for(int i = 0; i < n; i++) {
                if(s[i] == '2' && s[(i + 1) % n] == '2' && s[(i + n - 1) % n] != '2') {
                    assert(start == -1);
                    start = i;
                }
            }
            rotate(s.begin(), s.begin() + start, s.end());
            string res = "";
            res.append(m32[s.substr(2,2)]);
            res.append(m32[s.substr(4,2)]);
            res.append(s.substr(6));
            cout << res << '\n';
        }
    }

    return 0;
}
