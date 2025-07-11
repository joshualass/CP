#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int mx = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] < mx) {
            cout << "YES\n";
            cout << "2\n" << mx << " " << a[i] << '\n';
            return;
        }
        mx = max(mx, a[i]);
    }
    cout << "NO\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// void solve() {
    
//     int n; cin >> n;
//     vector<int> a(n);
//     for(int &x : a) cin >> x;
//     int f = 0;
//     for(int i = -1; i < n; i++) {
//         vector<int> b = a;  
//         if(i >= 0) b.erase(b.begin() + i);
//         vector<int> c = b;
//         sort(c.begin(), c.end());
//         int ok = 1;
//         for(int j = 0; j < b.size(); j++) {
//             if(b[j] == c[j]) ok = 0;
//         }
//         if(ok && b.size()) {
//             cout << "YES\n";
//             cout << b.size() << '\n';
//             for(int j = 0; j < b.size(); j++) {
//                 cout << b[j] << " \n"[j == b.size() - 1];
//             }
//             return;
//         }
//     }
//     cout << "NO\n";
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }