#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int maxdoubles(string s, int t) {
    int doubles = 0;
    for(int i = 1; i < s.size(); i++) {
        if(s[i] == t + '0' && s[i-1] == t + '0') {
            doubles++;
            i++;
        }
    }
    return min((int) s.size() / 4, doubles);
}

int dp(string s) {

    

}

int dpc(string s) {
    vector<vector<vector<int>>> dpc(s.size() + 1, vector<vector<int>>(s.size() / 2 + 1, vector<int>(s.size() / 4 + 1)));

    for(int i = 0; i < s.size(); i++) {
        for(int j = 0; j <= s.size() / 2; j++) {
            for(int k = 0; k <= s.size() / 4; k++) {
                if(j != s.size() / 2) {
                    dpc[i+1][j+1][k] = max(dpc[i+1][j+1][k], dpc[i][j][k] + (s[i] == '1'));
                }
                if(i + 1 < s.size() && k != s.size() / 4) {
                    dpc[i+2][j][k+1] = max(dpc[i+2][j][k+1], dpc[i][j][k] + (s[i] == '1' || s[i+1] == '1'));
                }
            }
        }
    }
    return dpc.back().back().back();
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 1 << 12; i++) {
        string s = "";
        string r = "";
        for(int j = 0; j < 12; j++) {
            if(i & (1 << j)) {
                s.push_back('1');
            } else {
                s.push_back('0');
            }
        }

        if(dpc(s) != greedy(s)) {
            cout << "s : " << s << " dpc : " << dpc(s) << " greedy : " << greedy(s) << '\n';
            return 0;
        }
    }
    
    // int n, m; cin >> n >> m;
    // int lo = 0, hi = 0;
    // for(int i = 0; i < n; i++) {
    //     string s; cin >> s;
    //     int countzero = count(s.begin(), s.end(), '0');
    //     int countone = count(s.begin(),s.end(), '1');
    //     lo += countone - maxdoubles(s,1); //find min that can be occupied
    //     hi += greedy(s);
    // }

    // cout << lo << " " << hi << '\n';

    return 0;
}