#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
(?)?



*/

const int debug = 0;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

bool solve(string s = "") {
    
    if(!debug) cin >> s;

    s.front() = '(';
    s.back() = ')';

    // int lo = 0, hi = 0;
    // for(char c : s) {
    //     if(c == '(') {
    //         lo++;
    //         hi++;
    //     }
    //     if(c == '?') {
    //         lo--;
    //         hi++;
    //     }
    // }

    auto work = [&]() -> bool {
        int open = 0, nc = 0;
        vector<int> qs;
        for(int i = 0; i < sz(s); i++) {
            // cout << "i : " << i << " open : " << open << " qs : " << qs << endl;
            if(s[i] == '(') {
                open++;
            }
            if(s[i] == '?') {
                qs.push_back(i);
            }
            if(s[i] == ')') {
                if(open) {
                    open--;
                } else {
                    nc++;
                }
            }
            if(open == 0 && nc + 1 >= sz(qs)) {
                open = sz(qs) - nc;
                nc = 0;
                for(int x : qs) s[x] = '(';
                qs.clear();
            }
        }
        return sz(qs) > open;
    };

    auto rev = [&]() -> void {
        for(char &c : s) {
            if(c == '(') {
                c = ')';
            } else if(c == ')') {
                c = '(';
            }
        }
        reverse(s.begin(), s.end());
    };

    work();
    // cout << "first iteration s : " << s << endl;
    rev();
    // cout << "start second iteration s : " << s << endl;
    work();
    // cout << "second iteration s : " << s << endl;
    rev();

    // cout << "resulting s : " << s << endl;

    // cout << "open : " << open << " qs : " << qs << endl;

    int open = count(s.begin(), s.end(), '('), close = count(s.begin(), s.end(), ')'), q = count(s.begin(), s.end(), '?');
    bool answer = abs(close - open) == q;
    if(!debug) {
        cout << (answer ? "YES" : "NO") << '\n';
    }
    return answer;
}

int solve_slow(string s) {
    int res = 0;
    auto dfs = [&](auto self, int idx) -> void {
        if(idx == sz(s)) {
            int ok = 1;
            int open = 0;
            for(char c : s) {
                if(c == '(') {
                    open++;
                }
                if(c == ')') {
                    open--;
                    if(open < 0) ok = 0;
                }
            }
            if(open) ok = 0;
            res += ok;
            return;
        }
        if(s[idx] == '?') {
            s[idx] = '(';
            self(self, idx + 1);
            s[idx] = ')';
            self(self, idx + 1);
            s[idx] = '?';
        } else {
            self(self, idx + 1);
        }
    };
    dfs(dfs, 0);
    return res;
}

void test(int n) {
    string cur = "";
    auto dfs = [&](auto self) -> void {
        if(sz(cur) == n) {
            int ways = solve_slow(cur);
            // cout << "cur : " << cur << " ways : " << ways << endl;
            if(ways) {
                bool res = solve(cur);
                int true_res = ways == 1;
                if(res != true_res) {
                    cout << "different answer with string : " << cur << endl;
                    cout << "res : " << res << endl;
                    cout << "true res : " << true_res << endl;
                    assert(0);
                } else {
                    // cout << "string cur : " << cur << " is ok!" << endl;
                }
            }
            return;
        } 
        cur.push_back('?');
        self(self);
        cur.pop_back();
        cur.push_back('(');
        self(self);
        cur.pop_back();
        cur.push_back(')');
        self(self);
        cur.pop_back();
    };
    dfs(dfs);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if(debug) {
        for(int i = 2; i <= 10; i += 2) {
            test(i);
        }
        cout << "all ok!" << endl;
    } else {
        int casi; cin >> casi;
        while(casi-->0) solve();
    }

    return 0;
}