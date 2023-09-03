#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, m, h; cin >> n >> m >> h;
    vector<pair<int,int>> results(n);
    for(int i = 0; i < n; i++) {
        vector<int> v(m);
        for(int &x: v) cin >> x;
        sort(v.begin(), v.end());
        int pen = 0;
        int time = 0;
        int probs = 0;
        for(int t = 0; t < m; t++) {
            if(time + v[t] > h) {
                break;
            } else {
                time += v[t];
                pen += time;
                probs++;
            }
        }
        results[i] = {probs,pen};
    } 
    int position = 1;
    for(int i = 1; i < n; i++) {
        if(results[i].first > results[0].first || results[i].first == results[0].first && results[i].second < results[0].second) {
            position++;
        }
    }
    cout << position << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}