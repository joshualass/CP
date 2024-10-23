#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int ask(int l, int r) {
    cout << "? " << l + 1 << " " << r + 1 << endl;
    int res; cin >> res;
    return res;
}

int isimposterinrange(vector<int> &a, int l, int r) {
    int res = ask(r,l);
    return a[l] ^ a[r] ^ res ^ 1;
}

//Given that imposter is in range, finds the imposter of length 3-4 in 4 moves
int findfour(int n, vector<int> &a, int start) {

    for(int i = 0; i < 2; i++) {
        int res = ask(i + start, i + start + 1);
        a[i+start+1] = a[i+start] ^ res ^ 1;
    }

    int r1 = isimposterinrange(a, start, start + 1);
    int r2 = isimposterinrange(a, start + 1, start + 2);

    // cout << "a : " << a << '\n';
    // cout << "r1 : " << r1 << '\n';
    // cout << "r2 : " << r2 << '\n';

    if(r1 == 1 && r2 == 0) {
        return start;
    }
    if(r1 == 1 && r2 == 1) {
        return start + 1;
    }
    if(r1 == 0 && r2 == 1) {
        return start + 2;
    }
    if(r1 == 0 && r2 == 0) {
        return start + 3;
    }
}

//Given that the imposter is in range, finds the imposter of length 5 in 5 moves
int findfive(int n, vector<int> &a, int start) {
    for(int i = 0; i < 2; i++) {
        int res = ask(i + start, i + start + 1);
        a[i+start+1] = a[i+start] ^ res ^ 1;
    }

    int r0 = isimposterinrange(a, start, start + 2);
    if(r0) {
        int r1 = isimposterinrange(a, start, start + 1);
        int r2 = isimposterinrange(a, start + 1, start + 2);

        // cout << "a : " << a << '\n';
        // cout << "r1 : " << r1 << '\n';
        // cout << "r2 : " << r2 << '\n';

        if(r1 == 1 && r2 == 0) {
            return start;
        }
        if(r1 == 1 && r2 == 1) {
            return start + 1;
        }
        if(r1 == 0 && r2 == 1) {
            return start + 2;
        }
        if(r1 == 0 && r2 == 0) {
            return start + 3;
        }
    } else {
        int res = ask(start + 2, start + 3);
        a[start+3] = a[start+2] ^ res ^ 1;

        int r3 = isimposterinrange(a, start + 2, start + 3);
        if(r3 == 1) {
            return start + 3;
        } else {
            return start + 4;
        }
    }
}

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);

    int res = -1;

    for(int i = 0; i + 5 < n; i += 2) {
        int r1 = ask(i, i + 1);
        int r2 = ask(i + 1, i);

        if(r1 != r2) {
            res = findfour(n,a,i);
        }
    }

    if(res == -1) {
        if(n <= 4) {
            res = findfour(n,a,0);
        } else if(n & 1) {
            res = findfive(n, a, n - 5);
        } else {
            res = findfour(n, a, n - 4);
        }
    }

    cout << "! " << res + 1 << endl;

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
// const ll MOD = 998244353;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// int ask(int i, int j) {
//     cout << "? " << i + 1 << " " << j + 1 << endl;
//     int res; cin >> res;
//     return res;
// }

// void solve() {
//     int n; cin >> n;
//     vector<int> a(n);

//     a[0] = 1;

//     for(int i = 0; i < n - 1; i++) {
//         int res = ask(i,i+1);
//         a[i+1] = a[i] ^ res ^ 1;
//     }

//     // cout << "a : " << a << '\n';

//     int l = 0, r = n - 1;
//     while(l != r) {
//         // cout << "l : " << l << " r : " << r << '\n';
//         //case we have entire range. 
//         if(l == 0 && r == n - 1) {
//             int m = (l + r) / 2;
//             int res = ask(m,l);
//             if(res ^ 1 == a[l] ^ a[m]) { //not in the range [l,m]
//                 l = m + 1;
//             } else {
//                 r = m;
//             }
//         } else if(l != 0) { //case where we can query an extra guy on the left
//             int m = (l + r) / 2;
//             int res = ask(m,l-1);
//             if(res ^ 1 == a[l-1] ^ a[m]) { //not in the range [l-1,m]
//                 l = m + 1;
//             } else {
//                 r = m;
//             }
//         } else { //case where r is not at the end, so we can get an extra guy to the right
//             int m = (l + r) / 2 + 1;
//             int res = ask(r+1,m);
//             if(res ^ 1 == a[m] ^ a[r+1]) { //not in range [m,r+1]
//                 r = m - 1;
//             } else {
//                 l = m;
//             }
//         }
//     }

//     cout << "! " << l + 1 << endl;

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }