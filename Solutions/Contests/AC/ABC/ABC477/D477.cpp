#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> hastile(n);
    vector<char> color(n, 'a');
    vector<int> latestaction(n);

    vector<pair<int,char>> colorings = {{-1, 'a'}};

    for(int i = 1; i <= q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int x; cin >> x;
            x--;
            if(hastile[x]) {
                hastile[x] = 0;
            } else {
                if(colorings.back().first > latestaction[x]) {
                    color[x] = colorings.back().second;
                }
                hastile[x] = 1;    
            }
            latestaction[x] = i;
        } else {
            char c; cin >> c;
            colorings.push_back({i, c});
        }
    }

    for(int i = 0; i < n; i++) {
        int x = i;
        if(hastile[x] == 0 && colorings.back().first > latestaction[x]) {
            color[x] = colorings.back().second;
        }
        cout << color[i];
    }

    cout << '\n';

    return 0;
}
