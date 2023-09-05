#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M; cin >> N >> M;
    vector<vector<char>> map(N,vector<char>(M));
    for(int r = 0; r < M; r++) {
        string word; cin >> word;
        for(int c = 0; c < N; c++) {
            map[r][c] = word[c];
        }
    }

    return 0;
}