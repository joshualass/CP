#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

// map<string,int> m;

// int check_slow(string s) {

//     if(m.count(s) == 0) {
//         if(sz(s) == 1) {
//             m[s] = 1;
//         } else {
//             int f = 0;
            
//             for(int i = 1; i < sz(s); i++) {
//                 if(s[i] == s[i-1]) {
//                     string nx = s;
//                     int c = s[i-1] - '0';
//                     nx.erase(nx.begin() + i - 1);
//                     nx.erase(nx.begin() + i - 1);
//                     nx.insert(nx.begin() + i - 1, '0' + (c ^ 1));
//                     if(check_slow(nx)) f = 1;
//                 }
//             }
        
//             m[s] = f;
//         }
//     }

//     return m[s];

// }

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    vector<vector<int>> p(3, vector<int>(n + 1));
    vector<int> a(n+1);

    int sum = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') {
            sum++;
        } else {
            sum += 2;
        }
        sum %= 3;
        p[sum][i+1]++;
        a[i+1] = sum;
    }

    for(int i = 0; i < 3; i++) {
        for(int j = 1; j <= n; j++) {
            p[i][j] += p[i][j-1];
        }
    }

    ll res = n;

    int la = n;

    for(int i = n - 2; i >= 0; i--) {
        if(s[i] == s[i+1]) {
            la = i + 1;
        }
        int add = (n - la) - (p[a[i]][n] - p[a[i]][la]);
        // cout << "i : " << i << " add : " << add << " la : " << la << " a[i] : " << a[i] << endl;
        res += add;
    }

    cout << res << '\n';

}


int check_fast(string s) {

    if(sz(s) == 1) return 1;

    int alt = 1;

    for(int i =1 ; i < sz(s); i++) {
        if(s[i] == s[i-1]) alt = 0;
    }

    return alt == 0 && count(s.begin(), s.end(), '0') % 3 != count(s.begin(), s.end(), '1') % 3;

    // vector<pair<char,int>> a;

    // for(char c : s) {
    //     if(a.empty() || c != a.back().first) {
    //         a.push_back({c, 0});
    //     }
    //     a.back().second++;
    // }

    // int tl = 0;
    // for(auto [c, len] : a) {
    //     while(len > 3) len -= 3;
    //     tl += len;
    // }

    

    // if(tl % 2 == 0) {
    //     return a.front().first == a.back().first;
    // } else {
    //     return a.front().first != a.back().first;
    // }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // auto dfs = [&](auto self, string s) -> void {
    //     if(sz(s) && check_slow(s) != check_fast(s)) {
    //         cout << "diff s : " << s << " slow : " << check_slow(s) << " fast : " << check_fast(s) << endl;
    //         assert(0);
    //     }

    //     if(sz(s) < 10) {
    //         s.push_back('0');
    //         self(self, s);
    //         s.pop_back();
    //         s.push_back('1');
    //         self(self, s);
    //     }
    // };

    // dfs(dfs, "");

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}