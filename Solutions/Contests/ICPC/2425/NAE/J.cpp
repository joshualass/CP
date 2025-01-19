#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto make_prefix = [&](vector<ll> a) -> vector<ll> {
        for(int i = 1; i < a.size(); i++) {
            a[i] += a[i-1];
        }
        return a;
    };

    map<string,vector<ll>> m;

    vector<ll> a;
    for(int i = 0; i <= 1e6; i++) {
        if(i) {
            a.push_back(a.back() + 2);
        } else {
            a.push_back(1);
        }
    }   
    m["0000"] = a;
    a.clear();

    for(int i = 0; i <= 1e6; i++) {
        if(i == 0) a.push_back(1);
        else if(i <= 3) a.push_back(2);
        else a.push_back((i - 4) % 2 == 0? i - 1 : 2);
    }

    m["1000"] = make_prefix(a);
    a.clear();

    for(int i = 0; i <= 1e6; i++) {
        a.push_back((i + 1) / 2 + 1);
    }
    m["0100"] = make_prefix(a);
    m["1100"] = make_prefix(a);
    m["0010"] = make_prefix(a);
    m["1010"] = make_prefix(a);

    a.clear();
    for(int i = 0; i <= 1e6; i++) {
        a.push_back(1 << __builtin_popcount(i));
    }

    m["0110"] = make_prefix(a);
    a.clear();

    for(int i = 0; i <= 1e6; i++) {
        if(i & 1) {
            a.push_back(i + 1);
        } else {
            a.push_back(2 - (i==0));
        }
    }

    m["1110"] = make_prefix(a);
    a.clear();

    for(int i = 0; i <= 1e6; i++) {
        if(i) {
            a.push_back(a.back() + i + 1);
        } else {
            a.push_back(1);
        }
    }

    m["1"] = a;
    a.clear();

    // for(int r = 0; r < 10; r ++){
    //     for(int i = 0; i <= r; i++) {
    //         cout << (i == 0 || i == r || (r % 2 == 1)) << " ";
    //     }
    //     cout << "\n";
    // }
    // for(int i = 0; i < 10; i++){
    //     cout << m["0100"][i] << " ";
    // }
    // cout << "\n";

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        string type; cin >> type;
        char c; cin >> c;
        if(c == 'B') {
            int r, i; cin >> r >> i;
            r--; i--;
            if(type == "0000") {
                cout << (i == 0 || i == r) << '\n';
            } else if(type == "1000") {
                cout << (i == 0 || i == r || (i >= 2 && i <= r - 2 && (r % 2 == 0))) << '\n';
            } else if(type == "0100" || type == "1100") {
                cout << (i == r || (i % 2 == 0)) << '\n';
            } else if(type == "0010" || type == "1010") {
                cout << (i == 0 || i == r || (r - i) % 2 == 0) << '\n';
            } else if(type == "0110") {
                cout << !((bool) (i & (r - i))) << '\n';
            } else if(type == "1110") {
                cout << (i == 0 || i == r || (r % 2 == 1)) << '\n';
            } else {
                cout << 1 << '\n';
            }

        } else {
            int r; cin >> r;
            r--;
            if(type[3] == '1') {
                cout << m["1"][r] << '\n';
            } else {
                cout << m[type][r] << '\n';
            }
        }
    }

    return 0;
}