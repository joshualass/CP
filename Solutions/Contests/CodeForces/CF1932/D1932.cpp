#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    map<char,int> m = {
        {'C',0},
        {'D',1},
        {'H',2},
        {'S',3}
    };
    string rev {"CDHS"};

    char t; cin >> t;
    int p = m[t];
    vector<vector<int>> cards(4);
    for(int i = 0; i < n * 2; i++) {
        string s; cin >> s;
        cards[m[s[1]]].push_back(s[0] - '0');
    }

    vector<pair<string,string>> ans;
    bool ok = 1;
    for(int i = 0; i < 4; i++) {
        if(i != p) {
            sort(cards[i].begin(),cards[i].end());
            while(cards[i].size() >= 2) {
                ans.push_back({});
                // ans.back().second = (((char) '0' + cards[i].back()) + rev[i]);
                ans.back().second.push_back('0' + cards[i].back());
                ans.back().second.push_back(rev[i]);
                cards[i].pop_back();
                ans.back().first.push_back('0' + cards[i].back());
                ans.back().first.push_back(rev[i]);
                cards[i].pop_back();
            }
            if(cards[i].size()) {
                if(cards[p].size()) {
                    ans.push_back({});
                    ans.back().second.push_back('0' + cards[p].back());
                    ans.back().second.push_back(rev[p]);
                    cards[p].pop_back();
                    ans.back().first.push_back('0' + cards[i].back());
                    ans.back().first.push_back(rev[i]);
                    cards[i].pop_back();
                } else {
                    ok = 0;
                }
            }
        }
    }
    sort(cards[p].begin(), cards[p].end());
    while(cards[p].size() >= 2) {
        ans.push_back({});
        ans.back().second.push_back('0' + cards[p].back());
        ans.back().second.push_back(rev[p]);
        cards[p].pop_back();
        ans.back().first.push_back('0' + cards[p].back());
        ans.back().first.push_back(rev[p]);
        cards[p].pop_back();
    }
    if(ok) {
        for(int i = 0; i < ans.size(); i++) {
            cout << ans[i].first << " " << ans[i].second << '\n';
        }
    } else {
        cout << "IMPOSSIBLE\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}