#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void printSet(set<int> s) {
    for(auto x : s) {
        cout << x << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m; cin >> n >> m;

    vector<pair<int,int>> scores(n);
    set<int> above;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--;
        scores[a].first++;
        scores[a].second += b;
        // printSet(above);
        if(a == 0) {
            vector<int> removes(0);
            for(int x : above) {
                if(scores[x].first < scores[a].first || scores[x].first == scores[a].first && scores[x].second >= scores[a].second) {
                    removes.push_back(x);
                }
            }
            for(int i = 0; i < removes.size(); i++) {
                // cout << "removing: " << removes[i] << "\n";
                above.erase(removes[i]);
            }
        } else {
            if(scores[a].first > scores[0].first || scores[a].first == scores[0].first && scores[a].second < scores[0].second) {
                above.insert(a);
            }
        }
        cout << 1 + above.size() << '\n';
    }


    return 0;
}