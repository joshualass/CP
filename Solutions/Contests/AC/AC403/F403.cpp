#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int inf = 10000;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    //-1 -> unvis state, -2 -> vis state but bad
    vector<array<int,4>> expr(n + 1, {inf, inf, inf, inf}), term(n + 1, {inf,inf,inf,inf}), factor(n + 1, {inf,inf,inf,inf}), number(n + 1, {inf,inf,inf,inf});
    auto upd = [&](int t, int x) -> void {
        if(t == 0) {
            //try converting to term
            if(term[x][0] < expr[x][0]) {
                expr[x][0] = term[x][0];
                expr[x][1] = 0;
            }

            //try doing all combinations of the sum
            for(int i = 1; i < x; i++) {
                if(expr[x][0] == -2 || 1 + expr[i][0] + term[x-i][0] < expr[x][0]) {
                    expr[x][0] = 1 + expr[i][0] + term[x-i][0];
                    expr[x][1] = 1;
                    expr[x][2] = i;
                    expr[x][3] = x - i;
                }
            }
        } else if(t == 1) {
            //converting to factor
            if(factor[x][0] <= term[x][0]) {
                term[x][0] = factor[x][0];
                term[x][1] = 0;
            }

            //try all possible products
            for(int i = 2; i < x; i++) {
                if(x % i == 0) {
                    int j = x / i;
                    if(1 + term[i][0] + factor[j][0] < term[x][0]) {
                        term[x][0] = 1 + term[i][0] + factor[j][0];
                        term[x][1] = 1;
                        term[x][2] = i;
                        term[x][3] = j;
                    }
                }
            }
        } else if(t == 2) {
            //try converting to number
            if(number[x][0] < factor[x][0]) {
                factor[x][0] = number[x][0];
                factor[x][1] = 0;
            }
            if(2 + expr[x][0] < factor[x][0]) {
                factor[x][0] = 2 + expr[x][0];
                factor[x][1] = 1;
                factor[x][2] = x;
            }
        } else if(t == 3) {
            string s = to_string(x);
            if(count(s.begin(), s.end(), '1') == s.size()) {
                number[x][0] = s.size();
                number[x][1] = x;
            } 
        }
    };

    // dfs(dfs, 0, n);
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 16; j++) {
            upd(j % 4, i);
        }
    }

    string res;

    auto dfsa = [&](auto self, int t, int x) -> void {
        if(t == 0) {
            if(expr[x][1] == 0) {
                self(self, 1, x);
            } else {
                self(self, 0, expr[x][2]);
                res.push_back('+');
                self(self, 1, expr[x][3]);
            }
        } else if(t == 1) {
            if(term[x][1] == 0) {
                self(self, 2, x);
            } else {
                self(self, 1, term[x][2]);
                res.push_back('*');
                self(self, 2, term[x][3]);
            }
        } else if(t == 2) {
            if(factor[x][1] == 0) {
                self(self, 3, x);
            } else {
                res.push_back('(');
                self(self, 0, x);
                res.push_back(')');
            }
        } else {
            res.append(to_string(number[x][1]));
        }
    };

    // for(int i = 1; i <= n; i++) {
    //     res = "";
    //     dfsa(dfsa, 0, i);
    //     cout << "i : " << i << " expr : " << res << '\n';
    // }

    dfsa(dfsa, 0, n);

    cout << res << '\n';

    // cout << expr[9] << '\n';
    // cout << term[9] << '\n';
    // cout << term[3] << '\n';
    // cout << factor[3] << '\n';

    return 0;
}
