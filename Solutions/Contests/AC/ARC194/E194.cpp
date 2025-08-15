#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*

X - 2, Y - 1

000111001 - START
 _____ _
011000011 - GOAL


000111001 - START
000100101
 ___
011011001
    ___
011000101
    ___
011011001
 ___
000111001

011000011 - GOAL

maybe solve with a stack
does greedy work?

If characters are matching, is there any reason to do an operation on these elements?
doesn't seem like it. 
nope. not hard after looking at example
00111. if we move the 00's, we won't really be able to use them. 

then, realize that these operations are reversible and we should try to find a canonical form for both of these strings
let's try making the canonical form be the lexicographically smallest string possible from these strings. 
how can we obtain this?

0c - 2, 1c - 1
000111001
000110011
000100111
000001111

1101101100100

gets 0011011011100

after modification, it's getting
1101101100100

easier tc

1100100

but after we move the pairs of 11 to the back, we could move them back again; the highway goes both ways. 

first, do 

*/

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

string canon(string s, int x, int y) {
    // cout << "s : " << s << " x : " << x << " y : " << y << '\n';
    vector<array<int,2>> a;
    char p = '\0';
    for(char c : s) {
        if(c == p) {
            a.back()[1]++;
        } else {
            a.push_back({c - '0', 1});
        }
        p = c;
    }

    // cout << "a : " << a << '\n';

    vector<array<int,2>> res;
    vector<array<int,2>> cur;

    auto append = [&](int type, int cnt) -> void {
        if(cnt) {
            if(res.size() && res.back()[0] == type) {
                res.back()[1] += cnt;
            } else {
                res.push_back({type, cnt});
            }
        }
    };

    auto work = [&]() -> int {
        for(auto [t, cnt] : cur) {
            if(t == 0) {
                append(0, cnt / x * x);
            }
        }
        for(auto [t, cnt] : cur) {
            if(t == 0) {
                append(0, cnt % x);
            } else {
                append(1, cnt);
            }
        }
        cur.clear();
        int c = 0;
        if(res.size() && res.back()[0] == 1) {
            c = res.back()[1];
            res.pop_back();
        }
        // cout << "c : " << " c : " << c << '\n';
        return c;
    };

    for(auto [t, cnt] : a) {
        // cout << "vis t : " << t << " cnt : " << cnt << '\n';
        if(t == 1 && cnt % y) {
            cnt += work();
            append(1, cnt % y);
            cur.push_back({1, cnt / y * y});
        } else {
            cur.push_back({t, cnt});
        }
    }
    int last = work();
    append(1, last);
    string res_str = "";
    for(auto [t, c] : res) res_str.append(string(c, '0' + t));
    // cout << "res_str : " << res_str << '\n';
    return res_str;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x, y; cin >> n >> x >> y;
    string s, t; cin >> s >> t;
    cout << (canon(s, x, y) == canon(t, x, y) ? "Yes" : "No") << '\n';

    return 0;
}
