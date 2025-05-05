#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int inf = 10000;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    vector<array<int,4>> expr(n + 1, {-1,-1,-1,-1}), term(n + 1, {-1,-1,-1,-1}), factor(n + 1, {-1,-1,-1,-1}), number(n + 1, {-1,-1,-1,-1});

    auto dfs = [&](auto self, int t, int x) -> void {
        if(t == 0) {
            if(expr[0] == -1) {
                int best = -2;
                //try converting to term
                self(self, 1, x);
                if(term[x][0] >= 0) {
                    if(best == -2 || term[x][0] <= best) {
                        best = term[x][0];
                        expr[x][1] = 0;
                    }
                }
                //try doing all combinations of the sum
                for(int i = 1; i < x; i++) {
                    self(self, 0, i);
                    self(self, 1, x - i);
                    if(expr[i][0] >= 0 && term[x-i][0] >= 0) {
                        if(best == -2 || 1 + expr[i][0] + term[x-i][0] <= best) {
                            best = 1 + expr[i][0] + term[x-i][0];
                            expr[x][1] = 1;
                            expr[x][2] = i;
                            expr[x][3] = x - i;
                        }
                    }
                }
                expr[x][0] = best;
            }
        } else if(t == 1) {

            if(term[0] == -1) {
                int best = -2;
                self(self, 2, x);
                if(factor[x][0] >= 0) {
                    if(best == -2 || factor[x][0] <= best) {
                        best = factor[x][0];
                        term[x][1] = 0;
                    }
                }
                //try all possible products
                for(int i = 2; i < x; i++) {
                    if(x % i == 0) {
                        int j = x / i;
                        self(self, 1, i);
                        self(self, 2, j);
                        if(term[i][0] >= 0 && factor[j][0] >= 0) {
                            if(best == -2 || 1 + term[i][0] + factor[j][0] <= best) {
                                best = 1 + term[i][0] + factor[j][0];
                                term[x][1] = 1;
                                term[x][2] = i;
                                term[x][3] = j;
                            }
                        }
                    }
                }
                term[x][0] = best;
            }

        } else if(t == 2) {
            if(factor[x] == -1) {
                int best = -2;
                self(self, 3, x);
                if(number[x][0] >= 0) {
                    if(best == -2 || number[x][0] <= best) {
                        best = number[x][0];
                        factor[x][1] = 0;
                    }
                }
                self(self, 0, x);
                if(expr[x][0] >= 0) {
                    if(best == -2 || 2 + expr[x][0] <= best) {
                        factor[x][1] = 1;
                        factor[x][2] = x;
                    }
                }
                factor[x][0] = best;
            }
        } else if(t == 3) {
            if(number[x] == -1) {
                if(x == 1) {

                } else {

                    int best = -2;
                    string s = to_string(x);
                    if(s[0] != '1') {
                        s.erase(s.begin());
                        self
                    }
                }
            }
        }
    };



    return 0;
}
