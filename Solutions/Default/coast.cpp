#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int SIZE = 1002;
int ary[SIZE][SIZE];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M; cin >> N >> M;
    for (int r = 0; r < N; r++) {
        string line; cin >> line;
        for (int c = 0; c < M; c++) {
            ary[r + 1][c + 1] = (line[c] - 48);
        }
    }

    int length = 0;
    queue<pair<int, int>> q;
    q.push({0, 0});

    while (q.size()) {
        pair<int, int> p = q.front();
        q.pop();
        int r = p.first;
        int c = p.second;
        if (r == -1 || r == N + 2 || c == -1 || c == M + 2) {
            continue;
        }
        if (ary[r][c] == 1) {
            length++;
            continue;
        }
        if (ary[r][c] == 2) {
            continue;
        }
        if (ary[r][c] == 0) {
            ary[r][c] = 2;
            q.push({r - 1, c});
            q.push({r + 1, c});
            q.push({r, c - 1});
            q.push({r, c + 1});
        }
    }

    cout << length;

    return 0;
}