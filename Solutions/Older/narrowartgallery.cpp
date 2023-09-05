#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K; cin >> N >> K;
    vector<vector<int>> prevleft(N + 1,vector<int>(K + 1,0));
    vector<vector<int>> prevright(N + 1,vector<int>(K + 1,0));
    vector<vector<int>> prevboth(N + 1,vector<int>(K + 1,0));

    for(int i = 1; i <= N; i++) {
        int left, right; cin >> left >> right;
        for(int t = 1; t <= min(K, i); t++) {
            prevleft[i][t] = max(prevleft[i-1][t-1] , prevboth[i-1][t-1]) + right;
            prevright[i][t] = max(prevright[i-1][t-1], prevboth[i-1][t-1]) + left;
        }
        for(int t = 0; t <= min(K, i - 1); t++) {
            prevboth[i][t] = max(max(prevleft[i-1][t], prevright[i-1][t]), prevboth[i-1][t]) + left + right;
        }
        cout << '\n';
    }
    cout << max(max(prevleft[N][K],prevright[N][K]),prevboth[N][K]);

    int zero; cin >> zero >> zero;
    return 0;
}