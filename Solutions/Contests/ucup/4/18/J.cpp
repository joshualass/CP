/*
The 4th Universal Cup. Stage 18: Grand Prix of Hongō
J. Jelly
*/
// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// #define sz(x) (int) (x).size()

// template<typename T>
// ostream& operator<<(ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<int> pos, neg;
//     vector<int> d(n);
//     for(int i = 0; i < n; i++) {
//         int a, b; cin >> a >> b;
//         d[i] = b - a;
//     }
//     if(n & 1) d.push_back(0);
//     sort(d.begin(), d.end());
//     for(int i = 0; i < sz(d) / 2; i++) {
//         neg.push_back(d[i]);
//         pos.push_back(d[i + sz(d) / 2]);
//     }

//     cout << "pos : " << pos << endl;
//     cout << "neg : " << neg << endl;

//     // for(int i = 0; i < n; i++) {
//     //     int a, b; cin >> a >> b;
//     //     int d = b - a;
//     //     if(d > 0) pos.push_back(d);
//     //     if(d < 0) neg.push_back(d);
//     // }

//     // sort(pos.rbegin(), pos.rend());
//     // sort(neg.rbegin(), neg.rend());

//     // for(int i = 0; i < 1 && sz(pos) > sz(neg); i++) neg.push_back(0);
//     // for(int i = 0; i < 1 && sz(neg) > sz(pos); i++) pos.push_back(0);
    
//     while(sz(pos) > sz(neg)) pos.pop_back();
//     while(sz(neg) > sz(pos)) neg.pop_back();

//     cout << accumulate(pos.begin(), pos.end(), 0LL) - accumulate(neg.begin(), neg.end(), 0LL) << '\n';

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> d(n);
    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        d[i] = b - a;
    }
    sort(d.begin(), d.end());

    ll res = 0;

    auto work = [&](vector<ll> test) -> void {
        ll cur = 0;
        test.insert(test.begin(), 0);
        ll a = 0, b = 0;
        for(int i = 1; i < sz(test); i++) {
            if(test[i] >= 0) {
                ll nb = a + test[i];
                cur += max(0LL, nb - b);
                b = nb;
            } else {
                ll na = b - test[i];
                cur += max(0LL, na - a);
                a = na;
            }
            // cout << "i : " << i << " a : " << a << " b : " << b << endl;
        }
        cur -= min(a, b);
        // cout << "test : " << test << " cur : " << cur << endl;
        res = max(res, cur);
    };

    if(n % 2 == 0) {
        vector<ll> test;
        for(int i = 0; i < n / 2; i++) {
            test.push_back(d[n / 2 + i]);
            test.push_back(d[i]);
        }
        work(test);
    } else {    
        vector<ll> test1, test2;
        for(int i = 0; i < n / 2; i++) {
            test1.push_back(d[n / 2 + i]);
            test1.push_back(d[i]);

            test2.push_back(d[n / 2 - i]);
            test2.push_back(d[n - 1 - i]);
        }
        test1.push_back(d[n - 1]);
        test2.push_back(d[0]);
        work(test1);
        work(test2);
    }

    cout << res << '\n';

    return 0;
}
