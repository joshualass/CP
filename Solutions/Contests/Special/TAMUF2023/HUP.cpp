#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 640000;
int dsu[N];
int depths[N];
int sizes[N];

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
        depths[x]++;
        sizes[x] += sizes[y];
    } else if(sizes[x] < sizes[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[x] = y;
        sizes[y] += sizes[x];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    for(int i = 0; i < n * n; i++) {
        dsu[i] = i;
        depths[i] = 1;
        sizes[i] = 1;
    }

    vector<string> board(n);
    vector<vector<int>> parents(n * n);

    for(auto &x: board) cin >> x;

    ll num_components = 0;

    for(int row = 0; row < n; row++) {
        vector<int> points;
        for(int col = 0; col < n; col++) {
            if(board[row][col] == 'P') {
                points.push_back(row * n + col);
                num_components++;
            }
        }
        if(points.empty()) {
            continue;
        }
        points.push_back(points.front());
        for(int i = 0; i < points.size() - 1; i++) {
            parents[points[i+1]].push_back(points[i]);
        }
    }

    for(int col = 0; col < n; col++) {
        vector<int> points;
        for(int row = 0; row < n; row++) {
            if(board[row][col] == 'P') {
                points.push_back(row * n + col);
            }
        }
        if(points.empty()) {
            continue;
        }
        points.push_back(points.front());
        for(int i = 0; i < points.size() - 1; i++) {
            parents[points[i+1]].push_back(points[i]);
        }
    }

    ll ans = 1;

    for(int i = 0; i < n * n; i++) {
        if(parents[i].size()) {
            int a = parents[i][0];
            int b = parents[i][1];
            if(find(a) != find(b)) {
                num_components--;
            }
            merge(a,b);
        }
    }

    for(int i = 0; i < num_components; i++) {
        ans *= 2;
    }

    cout << ans << '\n';

    return 0;
}