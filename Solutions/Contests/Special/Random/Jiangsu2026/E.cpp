#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void test() {
    int n; cin >> n;
    while(1) {
        string s; cin >> s;
        vector<int> nodes(n);
        for(int i = 0; i < n; i++) nodes[i] = s[i % sz(s)] - '0';
        vector<int> cnts(n / 2 + 1);
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                if(nodes[i] && nodes[j]) cnts[min(j - i, 8 - j + i)]++;
            }
        }
        for(int i = 0; i <= n / 2; i++) {
            cout << "i : " << i << " cnts[i] : " << cnts[i] << endl;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    test();

    return 0;
}
