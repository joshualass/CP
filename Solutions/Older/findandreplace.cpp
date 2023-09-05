#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        string line; cin >> line;
        map<int,int> m;
        bool flag = true;
        for(int i = 0; i < line.size(); i++) {
            if(m.find(line[i]) == m.end()) {
                m.insert({line[i], i % 2});
            } else {
                if(m[line[i]] != i % 2) {
                    flag = false;
                    break;
                }
            }
        }
        cout << (flag ? "YES" : "NO") << "\n";
    }

    return 0;
}