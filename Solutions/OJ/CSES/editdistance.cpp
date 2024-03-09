#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string a,b;cin >> a >> b;
    int n = a.size(); int m = b.size();
    vector<vector<int>> distances(n+1,vector<int>(m+1));
    for(int i = 0; i <= n; i++) {
        distances[i][0] = i;
    }
    for(int j = 0; j <= m; j++) {
        distances[0][j] = j;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            distances[i][j] = min({distances[i-1][j] + 1, distances[i][j-1] + 1, distances[i-1][j-1] + (a[i-1] == b[j-1] ? 0 : 1)});
        }
    }
    cout << distances[n][m] << "\n";
    return 0;
}