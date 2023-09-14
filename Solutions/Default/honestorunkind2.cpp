#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<map<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        for (int t = 0; t < a; t++) {
            int x, y;
            cin >> x >> y;
            v[i][x - 1] = y;
        }
    }
    int most = 0;
    for (int i = 0; i < pow(2, n); i++) { // 1 - honest, 2 - unkind
        bool flag = true;
        int count = 0;
        for (int t = 0; t < n && flag; t++) {
            if (i & 1 << t) {  // person is honest
                count++;
                for (pair<int, int> x : v[t]) {
                    if (x.second != (1 & i >> x.first)) {
                        // cout << "fail: " << i << " t: " << t << " first: " << x.first
                        //      << " second: " << x.second << " expression: " << (i & 1 << x.first) << '\n';
                        flag = false;
                        break;
                    }
                }
            }
        }
        if (flag) {
            most = max(most, count);
        }
    }
    cout << most;

    return 0;
}