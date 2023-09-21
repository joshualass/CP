#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const int N = 501;
int dp[N][N];

void swappuh(int&x, int&y) {
    if(y<x) {
        swap(x,y);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for(int i = 0; i < N ;i++) {
        fill(begin(dp[i]),begin(dp[i])+N,1e9);
        dp[i][i] = 1;
    }
    for(int i = 1; i < N; i++) {
        for(int j = i+1; j < N; j++) {
            for(int c = 1; c < i; c++) {
                int x = c;
                int y = j;
                swappuh(x,y);
                int x1 = i-c;
                int y1 = j;
                swappuh(x1,y1);
                dp[i][j] = min(dp[i][j], dp[x][y] + dp[x1][y1]);
            }
            for(int c = 1; c < j; c++) {
                int x = c;
                int y = i;
                swappuh(x,y);
                int x1 = j-c;
                int y1 = i;
                swappuh(x1,y1);
                dp[i][j] = min(dp[i][j], dp[x][y] + dp[x1][y1]);
            }
        }
    }
    int a, b; cin >> a >> b;
    swappuh(a,b);
    cout << dp[a][b] - 1<< "\n";

    return 0;
}