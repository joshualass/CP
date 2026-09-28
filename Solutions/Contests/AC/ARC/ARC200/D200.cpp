#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
maybe hard to solve fast and in contest, but problem is not very bad when you break it down
mauybe not coming up with the even case without a bruteforce program. 
although cheese, it is necessary for these types of problems/contests :(
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

/*

 0  1  2  3  4  5  6  7  8  9

2 Solution makes 0, 5
 0              5
4 Solution is IMPOSSIBLE

6 Solution makes 0, 1, 2, 3, 4, 6
 0  1    3
8 Solution

10 Solution
 0 1 2 3 4 5 6 7 8 9 


*/

void solve() {
    
    int m, k; cin >> m >> k;

    vector<int> res;

    if(k & 1) {
        for(int i = 0; i <= (k - 1) / 2; i++) res.push_back(i);
    } else {
        if(k == 2) {
            if(m % 2 == 0) {
                res.push_back(0);
                res.push_back(m / 2);
            }
        } else if(k == 4) {
            if(m % 4 == 0) {
                res.push_back(0);
                res.push_back(m / 4);
                res.push_back(m / 2);
            }
        } else if(k == m) {
            for(int i = 0; i < m; i++) res.push_back(i);
        } else {
            for(int i = 0; i <= (k - 4) / 2; i++) res.push_back(i);
            res.push_back(k / 2);
        }
    }

    if(res.size()) {
        cout << "Yes\n";
        cout << res.size() << '\n';
        for(int i = 0; i < res.size(); i++) cout << res[i] << " \n"[i == res.size() - 1];
    } else {
        cout << "No\n";
    }

}

int get_cnt(int m, vector<int> a) {
    vector<int> vis(m);
    for(int i = 0; i < a.size(); i++) {
        for(int j = i; j < a.size(); j++) {
            vis[(a[i] + a[j]) % m] = 1;
        }
    }
    return count(vis.begin(), vis.end(), 1);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int targ; cin >> targ;

    // int m, targ; cin >> m >> targ;

    // for(int m = 1; m <= 16; m += 2) {
        // for(int targ = 4; targ <= 4; targ++) {
            // int found = 0;
            // for(int bm = 0; bm < 1 << m; bm++) {
            //     vector<int> a;
            //     for(int i = 0; i < m; i++) {
            //         if((bm >> i) & 1) a.push_back(i);
            //     }
            //     // cout << "testing a : " << a << '\n';
            //     // cout << "cnt : " << get_cnt(m, a) << '\n';
            //     if(get_cnt(m, a) == targ) {
            //         cout << targ << " HIT\n";
            //         cout << "a : " << a << '\n';
            //         cout << "good m : " << m << '\n';
            //         found = 1;
            //         break;
            //     }
            // }

            // // if(!found) cout << targ << " is no good\n";
            // if(!found) cout << "bad m : " << m << "\n";

        // }

    // }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}