#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    auto ask = [&](int i, int j) -> bool {
        cout << "? " << i << " " << j << endl;
        int res; cin >> res;
        return res;
    };

    auto dfs = [&](auto self, int l, int r) -> vector<int> {
        vector<int> res;
        if(l == r) {
            // cout << "vis l : " << l << " r : " << r << endl;
            res = {l};
        } else {
            // cout << "vis l : " << l << " r : " << r << endl;
            int mid = (l + r + 1) / 2;
            vector<int> lpart = self(self, l, mid - 1), rpart = self(self, mid, r);
            // cout << "lpart : " << lpart << " rpart : " << rpart << endl;
            int lp = 0, rp = 0;
            while(lp != sz(lpart) || rp != sz(rpart)) {
                if(lp == sz(lpart)) {
                    res.push_back(rpart[rp++]);
                } else if(rp == sz(rpart)) {
                    res.push_back(lpart[lp++]);
                } else {
                    int i = lpart[lp], j = rpart[rp];
                    // cout << "i : " << i << " j : " << j << endl;
                    int test = ask(i, j);
                    if(test) {
                        res.push_back(lpart[lp++]);
                    } else {
                        res.push_back(rpart[rp++]);
                    }
                }
            }
        }
        // cout << "l : " << l << " r : " << r << " res : " << res << endl;
        return res;
    };

    auto res = dfs(dfs, 1, n);
    cout << "! " << res << endl;

    return 0;
}
