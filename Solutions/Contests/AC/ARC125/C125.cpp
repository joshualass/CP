#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<int> a(k);
    vector<int> vis(n);
    for(int &x : a) {
        cin >> x;
        x--;    
        vis[x] = 1;
    }
    int p = 0;
    for(int i = 0; i < a.size(); i++) {
        if(i == a.size() - 1) { //i == k, insert descending before A_k
            for(int j = n - 1; j > a[i]; j--) {
                cout << j + 1 << " ";
                vis[j] = 1;
            }
        }
        cout << a[i] + 1 << " "; //add A_k
        vis[a[i]] = 1;
        if(i == a.size() - 1) { //i == k, insert descending after A_k
            for(int j = n - 1; j >= 0; j--) {
                if(vis[j] == 0) {
                    cout << j + 1 << " ";
                }
            }
        } else { //insert smallest element not present in A and P if it is smaller than A_k
            while(p != n && vis[p]) {
                p++;
            }
            if(p != n && p < a[i]) {
                cout << p + 1 << " ";
                vis[p] = 1;
            }
        }
    }

    cout << '\n';

    return 0;
}