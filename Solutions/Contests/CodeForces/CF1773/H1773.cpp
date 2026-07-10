#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
const int maxn = 1e6;

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

void solve(int actor, array<int,2> coord) {

    if(actor) {
        cout << "testing coord : " << coord << endl;
    }

    vector<array<int,2>> asks;
    int doneint = 0;
    map<string, string> translator;
    int ready = 0;
    int done = 0;

    auto check = [&](string s) -> bool {
        done = s.back() == '!';
        return s.back() == '!';
    };

    auto get_dist = [&](array<int,2> first, array<int,2> second) -> ll {
        return 1LL * (first[0] - second[0]) * (first[0] - second[0]) + 1LL * (first[1] - second[1]) * (first[1] - second[1]);
    };

    int askcount = 0;

    auto ask = [&](int x, int y) -> string {
        assert(askcount++ < 64);
        string res;
        if(doneint) {
            assert(0); //not done gang. 
        }
        if(actor) {
            if(coord == array<int,2>{x, y}) {
                res = "F!"; //found
                doneint = 1;
            } else if(sz(asks) == 0) {
                res = "M"; //miss
            } else {
                ll pd = get_dist(asks.back(), coord);
                ll cd = get_dist({x, y}, coord);
                if(pd < cd) {
                    res = "F"; //further
                } else if(pd == cd) {
                    res = "S"; //same dist
                } else {
                    res = "C"; //closer
                }
            }
        } else {
            cout << x << " " << y << endl;
            getline(cin, res);
            if(translator.count(res)) {
                res = translator[res];
            } else if(res.back() == '!') {
                res = "F!";
            } else if(ready) {
                translator[res] = "S";
                res = translator[res];
            }
        }
        asks.push_back({x, y});
        return res;
    };

    string first = ask(0, 0);
    if(check(first)) return;
    string second = ask(1, 0);
    if(check(second)) return;
    string third = ask(0, 0);
    assert(check(third) == 0);
    string fourth = ask(0, 1);
    if(check(fourth)) return;

    int xl, xh, yl, yh;

    auto narrow = [&]() -> void {
        int mx = (xl + xh) / 2, my = (yl + yh) / 2;
        if(xh - xl == 1 && yh - yl == 1) {
            string tone = ask(xl, yl);
            if(check(tone)) return;
            string ttwo = ask(xl + 1, yl);
            if(check(ttwo)) return;
            array<int,2> f;
            if(ttwo == "F") {
                f = {xl, yl + 1};
            } else {
                f = {xl + 1, yl + 1};
            }
            string last = ask(f[0], f[1]);
            assert(check(last));
        } else if(xl == xh) {
            if(yl == yh) {
                string last = ask(xl, yl);
                assert(check(last));
            } else {
                string tone = ask(mx, my);
                if(check(tone)) return;
                string ttwo = ask(mx, my + 1);
                if(check(ttwo)) return;
                if(ttwo == "C") {
                    yl = my + 1;
                } else {
                    yh = my;
                }
            }
        } else if(yl == yh) {
            string tone = ask(mx, my);
            if(check(tone)) return;
            string ttwo = ask(mx + 1, my);
            if(check(ttwo)) return;
            if(ttwo == "C") {
                xl = mx + 1;
            } else {
                xh = mx;
            }
        } else {
            string tone = ask(mx, my);
            if(check(tone)) return;
            string ttwo = ask(mx + 1, my);
            if(check(ttwo)) return;
            string tthree = ask(mx + 1, my + 1);
            if(check(tthree)) return;
            if(ttwo == "C") {
                xl = mx + 1;
            } else {
                xh = mx;
            }
            if(tthree == "C") {
                yl = my + 1;
            } else {
                yh = my;
            }
        }
    };

    if(second == fourth) {
        ready = 1;
        translator[second] = "C";
        translator[third] = "F";

        xl = 1, xh = maxn, yl = 1, yh = maxn;
    } else {
        string cone = ask(maxn, 0);
        if(check(cone)) return;

        string zfirst = ask(maxn, maxn);
        assert(check(zfirst) == 0);
        string zsecond = ask(maxn - 1, maxn);
        assert(check(zsecond) == 0);
        string zthird = ask(maxn, maxn);
        
        ready = 1;
        translator[zsecond] = "C";
        translator[zthird] = "F";

        if(second == zsecond) {
            xl = 1, xh = maxn, yl = 0, yh = 0;
        } else {
            xl = 0, xh = 0, yl = 1, yh = maxn;
        }
    }
    
    while(!done) {
        narrow();
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int testing = 0;

    if(testing) {
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                solve(1, {i, j});
                solve(1, {maxn - i, j});
                solve(1, {maxn - i, maxn - j});
                solve(1, {i, maxn - j});
            }
        }
    
        for(int i = 0; i < 100; i++) {
            solve(1, {(int) (rng() % 1000001), (int) (rng() % 1000001)});
        }
    } else {
        solve(0, {-1,-1});
    }


    return 0;
}
