#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    multiset<int> ms;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        ms.insert(num);
    }
    for(int i = 0; i < m; i++) {
        int num; cin >> num;
        if(ms.size()) {
            if((*ms.begin()) > num) {
                cout << "-1\n";
                continue;
            }
            int val = (*--ms.upper_bound(num));
            cout << val << "\n";
            ms.erase(val);
        }
    }

    return 0;
}
