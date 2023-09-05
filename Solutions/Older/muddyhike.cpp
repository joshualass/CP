#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<vector<vector<int>>> god(
    1000,
    vector<vector<int>>(1000, vector<int>(6)));  // row col left right size mud
int R, C;

vector<int>& find(int r, int c) {
    if (god[r][c][0] == r && god[r][c][1] == c) {
        return god[r][c];
    }
    god[r][c] = find(god[god[r][c][0]][god[r][c][1]][0],
                     god[god[r][c][0]][god[r][c][1]][1]);
    return god[r][c];
}

void printV(vector<int>& x) {
    for (int y : x) {
        cout << y << ' ';
    }
    cout << '\n';
}

void merge(int r1, int c1, int r2, int c2) {
    vector<int>& find1 = find(r1, c1);
    vector<int>& find2 = find(r2, c2);
    // cout << "before: " ;
    // printV(find(r1,c1));
    // find1[5] = 123412;
    // cout << "after: " ;
    // printV(find(r1,c1));
    if (find1[0] == find2[0] && find1[1] == find2[1]) {
        return;
    }
    if (find1[4] == find2[4]) {
        find1[4]++;
        find2[0] = find1[0];
        find2[1] = find1[1];
        find1[2] |= find2[2];
        find1[3] |= find2[3];
    } else if (find1[4] < find2[4]) {
        find2[0] = find1[0];
        find2[1] = find1[1];
        find1[2] |= find2[2];
        find1[3] |= find2[3];
    } else {
        find1[0] = find2[0];
        find1[1] = find2[1];
        find2[2] |= find1[2];
        find2[3] |= find1[3];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C;
    vector<vector<int>> coords(0);
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            int num;
            cin >> num;
            coords.push_back({num, r, c});
            god[r][c][0] = r;
            god[r][c][1] = c;
            god[r][c][5] = num;
            if (c == 0) {
                god[r][c][2] = 1;
            }
            if (c == C - 1) {
                god[r][c][3] = 1;
            }
        }
    }
    sort(coords.begin(), coords.end());
    int ans = -1;

    for (int i = 0; i < coords.size(); i++) {
        vector<int> v = coords[i];
        int r = v[1];
        int c = v[2];
        if (r != 0 && god[r - 1][c][5] <= v[0]) {
            // cout << "merge1\n";
            merge(r, c, find(god[r-1][c][0],god[r-1][c][1])[0],find(god[r-1][c][0],god[r-1][c][1])[1]);
        }
        if (r != R - 1 && god[r + 1][c][5] <= v[0]) {
            // cout << "merge2\n";
            merge(r, c, find(god[r+1][c][0],god[r+1][c][1])[0],find(god[r+1][c][0],god[r+1][c][1])[1]);
        }
        if (c != 0 && god[r][c - 1][5] <= v[0]) {
            // cout << "merge3\n";
            merge(r, c, find(god[r][c-1][0],god[r][c-1][1])[0],find(god[r][c-1][0],god[r][c-1][1])[1]);
        }
        if (c != C - 1 && god[r][c + 1][5] <= v[0]) {
            // cout << "merge4\n";
            merge(r, c, find(god[r][c+1][0],god[r][c+1][1])[0],find(god[r][c+1][0],god[r][c+1][1])[1]);
        }
        vector<int> hold = find(r, c);
        // cout << "rh: " << r << " ch: " << c << '\n';
        // printV(v);
        // printV(hold);
        if (hold[2] && hold[3]) {
            ans = v[0];
            break;
        }
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                // cout << "rg: " << r << " cg: " << c << '\n';
                // printV(god[r][c]);
            }
        }
    }

    // for(int r = 0; r < R; r++) {
    //     for(int c = 0; c < C; c++) {
    //         cout << "r: " << r << " c: " << c << '\n';
    //         printV(god[r][c]);
    //     }
    // }
    cout << ans;

    return 0;
}