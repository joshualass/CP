#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int dsu[1000000];
int sizes[1000000];
int values[1000][1000];

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    if(sizes[x] == sizes[y]) {
        dsu[y] = x;
        sizes[x]++;
    } else if(sizes[x] < sizes[y]) {
        dsu[y] = x;
    } else {
        dsu[x] = y;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C; cin >> R >> C;
    for(int i = 0; i < R * C; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
    vector<vector<int>> queue(0); // value row col
    for(int r = 0; r < R; r++) {
        for(int c = 0; c < C; c++) {
            int num; cin >> num;
            values[r][c] = num;
            queue.push_back({num,r,c});
            if(r != 0 && (c == 0 || c == C - 1)) {
                // cout << "merging: " << r*C + c << " with " << (r-1)*C + c << "\n"; 
                merge(r*C + c,(r-1)*C + c);
            }
        }
    }

    sort(queue.begin(),queue.end());
    int min_length = 0;
    int i = 0;
    // cout << find(0) << " " << find(C - 1) << '\n';
    while(find(0) != find(C-1) && i < R * C) {
        vector<int> vals = queue[i];
        i++;
        min_length = vals[0];
        int r = vals[1];
        int c = vals[2];
        if(r != 0 && values[r-1][c] <= values[r][c]) {
            merge(r*C + c, (r-1)*C + c);
        }
        if(r != R - 1 && values[r+1][c] <= values[r][c]) {
            merge(r*C + c, (r+1)*C + c);
        }
        if(c != 0 && values[r][c-1] <= values[r][c]) {
            merge(r*C + c, r*C + c - 1);
        }
        if(c != C - 1 && values[r][c+1] <= values[r][c]) {
            merge(r*C + c, r*C + c + 1);
        }
    }
    cout << min_length;
    return 0;
}