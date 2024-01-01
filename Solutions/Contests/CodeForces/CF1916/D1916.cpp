#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

void solve() {
    int n; cin >> n;
    if(n == 1) {
        cout << "1\n";
        return;
    } else {
        // for(int i = 1; i <= n / 2; i++) {
        //     cout << "1";
        //     for(int j = 1; j <= )
        // }
        for(int i = 1; i <= n / 2; i++) {
            string str = "";
            for(int j = 0; j < n; j++) {
                str.push_back('0');
            }
            str[0] = '1';
            str[i] = '6';
            str[i * 2] = '9';
            cout << str << '\n';
        }
        for(int i = 1; i <= n / 2; i++) {
            string str = "";
            for(int j = 0; j < n; j++) {
                str.push_back('0');
            }
            str[0] = '9';
            str[i] = '6';
            str[i * 2] = '1';
            cout << str << '\n';
        }
        string str = "";
        for(int j = 0; j < n; j++) {
            str.push_back('0');
        }
        str[0] = '1';
        str[1] = '9';
        str[2] = '6';
        cout << str << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(ll i = 1; i <= 9; i += 2) {

    //     ll num = 1;
    //     map<vector<int>, vector<int>> m;
    //     while(true) {
    //         ll temp = num * num;
    //         vector<int> digits(10);
    //         int dig = 0;
    //         while(temp) {
    //             digits[temp % 10]++;
    //             temp /= 10;
    //             dig++;
    //         }
    //         if(dig == i) {
    //             if(m.find(digits) == m.end()) {
    //                 m[digits] = {};
    //             }
    //             m[digits].push_back(num * num);
    //         }
    //         if(dig > i) break;
    //         num++;
    //     }
    //     // cout << "m : " << m << '\n';
    //     for(auto p : m) {
    //         if(p.second.size() >= i) {
    //             cout << p << '\n';
    //         }
    //     }

    // }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}