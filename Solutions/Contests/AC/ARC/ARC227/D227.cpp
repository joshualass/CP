#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
spent an eextraneous amount of time on this problem. 
primarily cuased by misreading

to solve prolems like these faster, can 
1) read and reread after some time
2) try to find some transformations for the problem to make thinking easier (hopefully)
3) try to find the minimal building blocks that enable a construction to slice
*/

int pc[500][500][2][2]; // [i][j] with i <= j

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q; cin >> n >> m >> q;

    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            for(int k = j; k < m; k++) {
                pc[j][k][s[j] - '0'][s[k] - '0'] = 1;
            }
        }
    }

    for(int qq = 0; qq < q; qq++) {
        string s; cin >> s;
        int ok = 1;
        for(int j = 0; j < m; j++) {
            for(int k = 0; k <= j; k++) {
                if(pc[k][j][s[k] - '0'][s[j] - '0'] == 0) ok = 0;
            }
        }
        cout << (ok ? "Yes" : "No") << '\n';
    }

    return 0;
}
