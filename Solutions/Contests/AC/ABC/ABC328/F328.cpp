#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 2e5;
int dsu[N];
ll diffs[N]; //stores diff from node to the dsu[node] only 

int find(int x) {
    if(dsu[x] == x) {
        return x; //there is no diff from root
    }
    int old_dsu = dsu[x];
    ll old_diff = diffs[x];
    int new_dsu = find(dsu[x]);
    diffs[x] = diffs[old_dsu] + diffs[x];
    dsu[x] = new_dsu;
    return new_dsu;
}

void merge(int x, int y, ll diff) {
    //merge the x group into the y group
    int root_x = find(x);
    int root_y = find(y);
    diff -= diffs[x];
    diff += diffs[y];
    
    dsu[root_x] = root_y;
    diffs[root_x] = diff;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        diffs[i] = 0;
    }

    for(int i = 0; i < q; i++) {
        ll a, b, d; cin >> a >> b >> d;
        a--; b--;
        if(find(a) != find(b)) {
            merge(a,b,d);
            cout << i + 1 << " ";
        } else if(diffs[a] - diffs[b] == d) {
            cout << i + 1 << " ";
        }
        // cout << "i : " << i << '\n';
        // cout << "diffs :";
        // for(int i = 0; i < 5; i++) {
        //     cout << diffs[i] << " ";
        // }
        // cout << '\n';

    }
    cout << endl;
    return 0;
}