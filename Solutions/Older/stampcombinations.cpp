#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    cin >> m >> n;  // m stamps, n queries

    // sliding window

    vector<int> v(m + 1);
    int total = 0;
    for (int i = 1; i <= m; i++) {
        int num;
        cin >> num;
        v[i] = v[i - 1] + num;
        total += num;
    }
    // for(int x : v) {
    //     cout << x << " ";
    // } cout << "\n";
    if (m == 1) {
        for(int i = 0; i < n; i++) {
            int q; cin >> q;
            cout << (q == total ? "Yes" : "No") << "\n";
        }
    } else {
        for (int i = 0; i < n; i++) {
            int q;
            cin >> q;
            int a = 0;
            int b = 0;
            bool poss = false;
            while (b <= m) {
                int value = total - v[b] + v[a];
                // cout << value << " " << v[a] << " " << v[b] << "\n";
                if (value == q) {
                    poss = true;
                    break;
                }
                if(value < q && a < b) {
                    a++;
                } else {
                    b++;
                }
            }
            cout << (poss ? "Yes" : "No") << "\n";
        }
    }
    return 0;
}