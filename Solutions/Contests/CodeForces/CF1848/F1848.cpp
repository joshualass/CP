#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;



void simulate(int n) {

    vector<vector<string>> ops1(n + 1);
    for(int i = 0; i < 1 << n; i++) {
        vector<int> a(n);
        string s;
        for(int j = 0; j < n; j++) {
            if(i & (1 << j)) {
                a[j] = 1;
                s.push_back('1'); 
            } else {
                s.push_back('0');
            }
        }

        int ops = 0;

        while(accumulate(a.begin(), a.end(), 0) != 0) {
            vector<int> next(n);
            for(int i = 0; i < n; i++) {
                next[i] = a[i] ^ a[(i + 1) % n];
            }
            a = next;
            ops++;
        }
        // cout << "ops : " << ops << " s : " << s << '\n';
        ops1[ops].push_back(s);
    }

    for(int i = 0; i <= n; i++) {
        cout << "ops : " << i << '\n';
        for(string s : ops1[i]) {
            cout << s << '\n';
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    /*
    try simulating   
    */

    // int n; cin >> n;
    // vector<int> a(n);
    // for(int &x : a) cin >> x;
    // for(int x : a) cout << x;
    // cout << '\n';
    // int ops = 0;

    // while(1) {
    //     vector<int> next(n);
    //     for(int i = 0; i < n; i++) {
    //         next[i] = a[i] ^ a[(i + 1) % n];
    //     }
    //     a = next;
    //     for(int x : a) cout << x;
    //     cout << '\n';
    //     ops++;
    //     if(accumulate(a.begin(), a.end(), 0) == 0) break;
    // }
    // cout << "ops : " << ops << '\n';

    simulate(8);

    cerr << "ok\n";

    return 0;
}