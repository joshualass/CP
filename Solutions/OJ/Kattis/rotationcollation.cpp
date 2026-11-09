#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int debug = 0;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

vector<int> kmp(string s) {
    int n = s.size();
    vector<int> b(n+1,-1);
    int i = 0, j = -1;
    while(i != n) {
        while(j != -1 && s[i] != s[j]) {
            j = b[j];
        }
        i++;
        j++;
        b[i] = j;
    }
    return b;
}

//finds all occurences of m in n with kmp array of m. 
vector<int> find_matches(string &n, string &m, vector<int> &a) {
    vector<int> matches;
    int i = 0;
    int j = 0;
    while(i < n.size()) {
        while(j == m.size() || (j != -1 && n[i] != m[j])) {
            j = a[j];
        }
        i++;
        j++;
        if(j == m.size()) {
            matches.push_back(i - m.size() + 1);
        }
    }
    return matches;
}

int work(string s, string t) {

    if(debug == 2) {
        cout << "cards : " << s << endl;
        cout << "program : " << t << endl;
    }

    int n; 
    if(debug == 0) {
        cin >> n;
    } else {
        n = sz(s);
    }
    vector<int> a(1, -1);

    auto ask = [&](int i, int j) -> int {
        i %= n;
        j %= n;
        assert(0 <= i && i < n && 0 <= j && j < n);
        cout << "? " << i + 1 << " " << j + 1 << endl;
        int res; 
        if(debug == 0) {
            cin >> res;
        } else {
            res = s[i] == t[j];
        }
        return res;
    };

    int res = -1;
    int left = 0, kmpj = -1;
    for(int i = 0; i < n * 2; i++) {
        int len = i - left;
        //learn more about hidden string 
        while(len != -1 && ask(len, i) == 0) {
            len = a[len];
            left = i - len;
        }
        len++;

        if(len == n) {
            res = (n * 2 - left) % n;
            break;
        }

        // cout << "i : " << i << " left : " << left << " kmpj : " << kmpj << endl;

        if(len == sz(a)) { //learn a new character
            //learn more about program
            while(kmpj != -1 && ask(kmpj, i) == 0) {
                kmpj = a[kmpj];
            }
            kmpj++;
            a.push_back(kmpj);
        }

        // cout << "final kmpj : " << kmpj << endl;
        // cout << "kmp : " << a << endl;
    }

    // cout << "! " << res << endl;
    return res;
}

set<int> work_slow(string s, string t) {
    int n = sz(s);
    set<int> res;
    for(int x = 0; x < n; x++) {
        int ok = 1;
        for(int i = 0; i < n; i++) {
            if(s[(i + x) % n] != t[i]) ok = 0;
        }
        if(ok) res.insert(x);
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(debug == 0) {
        int res = work("", "");
        cout << "! " << res << endl;
    } else {
        if(debug == 1) {
            for(int i = 0; i < 10000; i++) {
                string s = "";
                int n = rng() % 5 + 1;
                for(int j = 0; j < n; j++) {
                    s.push_back('a' + (rng() % 5));
                }
                string t = s;
                shuffle(t.begin(), t.end(), rng);
                auto solve = work(s, t);
                auto good = work_slow(s, t);
                int ok = 1;
                if(solve == -1) {
                    if(!good.empty()) {
                        ok = 0;
                    }
                } else {
                    if(good.count(solve) == 0) {
                        ok = 0;
                    }
                }
                if(!ok) {
                    cout << "BAD s : " << s << " t : " << t << endl;
                    cout << "fast sol : " << solve << " good : " << good << endl;
                    return 0;
                }
            }
        } else {
            work("aacca", "accaa");
        }
    }

    // string s = "amalgamate"; // cards
    // string t = "amateamzlg"; // program

    // cout << kmp("aacca") << endl;

    return 0;
}

/*
BAD s : aacca t : accaa
fast sol : -1 good : 1 
*/