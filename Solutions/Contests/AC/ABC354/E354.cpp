#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int,int>> cards(n);
    for(auto &x : cards) cin >> x.first >> x.second;

    vector<int> winning(1 << n);

    for(int bm = 0; bm < 1 << n; bm++) {
        bool lossfound = 0;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                int to = bm ^ (1 << i) ^ (1 << j);
                if(((bm >> i) & 1) && ((bm >> j) & 1) && (cards[i].first == cards[j].first || cards[j].second == cards[i].second) && winning[to] == 0) {
                    lossfound = 1;
                    break;
                }
            }
        }
        winning[bm] = lossfound;
    }
    cout << (winning.back() ? "Takahashi" : "Aoki") << '\n';
    return 0;
}