#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<string> board(n);
    int total = 0;
    for(int i = 0; i < n; i++) {
        cin >> board[i];
    }
    vector<vector<pair<int,int>>> streams(n+1, vector<pair<int,int>>(n));
    for(int i = 0; i < n; i++) {
        int flip = 0;
        for(int j = 0; j < n; j++) {
            flip += streams[i][j].first;
            flip -= streams[i][j].second;
            
            int cnt = board[i][j] - '0';
            cnt += flip;
                // cout << "adding? cnt: " << cnt << " i: " << i << " j: " << j << "\n";
            if(cnt % 2 == 1) {
                total++;
                streams[i+1][max(j-1,0)].first += 1;
                if(j + 2 < n) {
                    streams[i+1][j+2].second += 1;
                }
            }
            // cout << "make it here? i: " << i << " " << " j: " << j << "\n";
            streams[i+1][max(j-1,0)].first += streams[i][j].first;
            if(j + 1 < n) {
                streams[i+1][j+1].second += streams[i][j].second;
            }
        }
    }
    cout << total << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}