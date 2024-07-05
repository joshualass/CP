#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s; cin >> s;
    int n = s.size();
    vector<int> p(n);
    
    int prev = 0;
    int c = 0;
    int next = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') {
            next++;
        } else {
            if(prev == 0) {
                c++;
                prev = next - 1;
                next = 0;
            } else {
                prev--;
            }
        }
        p[c] = i;
    }
    
    vector<int> res;
    int ptr = 0;
    for(int i = 0; i < n; i++) {
        res.push_back(p[ptr]);
        int next = -1;
        if(s[p[ptr]] == '(') {
            next = ptr + 1;
        } else {
            next = ptr - 1;
        }
        p[ptr]--;
        ptr = next;
    }
    
    for(int i = 0; i < n; i++) {
        cout << s[res[i]];
    }
    
    cout << '\n';

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     string s; cin >> s;
//     vector<array<int,2>> a(s.size());
//     int curr = 0;
//     for(int i = 0; i < s.size(); i++) {
//         a[i] = {curr,i};
//         curr += s[i] == '(' ? 1 : -1;
//     }
//     sort(a.begin(), a.end(), [] (const auto &lhs, const auto &rhs) {
//         if(lhs[0] == rhs[0]) {
//             return lhs[1] > rhs[1];
//         } else {
//             return lhs[0] < rhs[0];
//         }
//     });
    
//     for(int i = 0; i < a.size(); i++) {
//         cout << s[a[i][1]];
//     }
//     cout << '\n';
//     return 0;
// }