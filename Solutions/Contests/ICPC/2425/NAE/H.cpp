#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const vector<int> PR = {2, 3, 5, 7, 11};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n + 1, -1);
    string tmp = "";
    for(int i = 0; i < n; i++) tmp.push_back('A' + i);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < tmp.size(); j++) {
            if(tmp[j] == s[i]) {
                a[n - i] = j;
                tmp = tmp.substr(0, j) + tmp.substr(j + 1);
            }
        }
    }
    int inc = 1;
    for(int i = 0; i < PR.size() && PR[i] <= n; i++) inc *= PR[i];
    int off = -1;
    for(int i = 0; i < inc; i++) {
        bool cvalid = true;
        for(int j = 0; j < PR.size() && PR[j] <= n; j++) {
            if(i % PR[j] != a[PR[j]]) cvalid = false; 
        }
        if(cvalid) {
            off = i;
            break;
        }
    }
    vector<int> c;
    for(int i = 1; i <= n; i++){
        if(i != 2 && i != 3 && i != 5 && i != 7 && i != 11) c.push_back(i);
    }
    int ans = -1;
    int ptr = off;
    while(ptr < 1e9) {
        bool cvalid = true;
        for(int i = 0; i < c.size(); i++) if(ptr % c[i] != a[c[i]]) cvalid = false;
        if(cvalid) {
            ans = ptr;
            break;
        }
        ptr += inc;
    }
    if(ans == -1) cout << "NO\n";
    else cout << "YES\n" << ans << "\n";

    return 0;
}