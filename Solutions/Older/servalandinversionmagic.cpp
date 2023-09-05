#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-->0) {

        int l; cin >> l;
        string line; cin >> line;
        bool start = false;
        bool stop = false;
        bool flag = true;
        for(int i = 0; i < l / 2; i++) {
            if(start && line[i] == line[l-i-1]) {
                stop = true;
            }
            if(line[i] != line[l-i-1]) {
                start = true;
                if(stop) {
                    flag = false;
                    break;
                }
            }
        }
        cout << (flag ? "Yes" : "No") << '\n';
    }

    return 0;
}