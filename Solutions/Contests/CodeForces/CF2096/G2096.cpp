#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
2 3 4 5 6 7 8 9 10

1 3 6 10 15 21 28 36 45 55
  2 5  9 14 20 27 35 44 __

 1  2  3  4  5  6  7  8  9
 1  1  1  2  2  2  3  3  3
 1  2  3  1  2  3  1  2  3
 1  2  3  3  1  2  2  3  1
 ^              ^     ^
    ^     ^              ^
       ^     ^     ^
 

For 9, there is only 1 way to do this


 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
 1  1  1  1  1  1  1  1  1  2  2  2  2  2  2  2  2  2  3  3  3  3  3  3  3  3  3
 1  1  1  2  2  2  3  3  3  2  2  2  3  3  3  1  1  1  3  3  3  1  1  1  2  2  2
 1  2  3  1  2  3  1  2  3  2  3  1  2  3  1  2  3  1  3  1  2  3  1  2  3  1  2 
 1  2  3  3  1  2  2  3  1  1  2  3  3  1  2  2  3  1  1  2  3  3  1  2  2  3  1 

 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
 1  1  1  1  1  1  1  1  1  2  2  2  2  2  2  2  2  2  3  3  3  3  3  3  3  3  3
 1  1  1  2  2  2  3  3  3  1  1  1  2  2  2  3  3  3  1  1  1  2  2  2  3  3  3
 1  2  3  1  2  3  1  2  3  1  2  3  1  2  3  1  2  3  1  2  3  1  2  3  1  2  3
 1  2  3  3  1  2  2  3  1  1  2  3  3  1  2  2  3  1  1  2  3  3  1  2  2  3  1
 

 1  2  3  4 10 11 12 19 20 21
 1  1  1  1  2  2  2  3  3  3
 1  1  1  2  2  2  2  3  3  3
 1  2  3  1  2  3  1  3  1  2
 1  2  3  3  1  2  3  1  2  3
 1  4  7 10  2  5  8  3  6  9


*/



template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

vector<array<vector<int>, 3>> solve(int n) {
// void solve() {
    
    // int n; cin >> n;

    int l = 1;
    while(l < n) l *= 3;
    vector<int> ids(l);
    for(int i = 0; i < l; i++) {
        ids[i % (l / 3) * 3  + i / (l / 3)] = i;
        // cout << "id : " << i << " id : " << ((i * 3) + i / (l / 3)) % l << '\n';
    }    

    // cout << "ids : " << ids << '\n';

    vector<int> p = {0, 1, 2, 2, 0, 1, 1, 2, 0};
    vector<array<vector<int>, 3>> b;

    b.push_back(array<vector<int>, 3>{});
    for(int i = 0; i < l; i++) {
        // b.back()[p[i%9]].push_back(i);
        if(ids[i] < n) b.back()[p[i%9]].push_back(ids[i]);
    }
    
    for(int i = 1; i < l; i *= 3) {
        b.push_back(array<vector<int>, 3>{});
        for(int j = 0; j < l; j++) {
            if(ids[j] < n) b.back()[(j / i + j / (l / 3)) % 3].push_back(ids[j]);
        }
    }

    cout << b.size() << endl;

    for(auto &q : b) {
        // cout << "q : " << q << endl;
        if(q[0].size() == q[1].size()) {

        } else if(q[0].size() == q[2].size()) {
            swap(q[1], q[2]);
        } else if(q[1].size() == q[2].size()) {
            swap(q[0], q[2]);
        } else {
            assert(0);
        }

        cout << q[0].size() + q[1].size();
        for(int i = 0; i < 2; i++) for(int x : q[i]) cout << " " << x + 1;
        cout << endl;

    }

    vector<int> a(n);

    string res; cin >> res;
    for(int i = 0; i < b.size(); i++) {
        if(res[i] == '?') continue;
        int c;
        if(res[i] == 'L') {
            c = 0;
        } else if(res[i] == 'R') {
            c = 1;
        } else {
            c = 2;
        }
        for(int x : b[i][c]) a[x]++;
    }

    assert(count(a.begin(), a.end(), *max_element(a.begin(), a.end())) == 1);

    // cout << "a : " << a << '\n';

    int hi_idx = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] > a[hi_idx]) hi_idx = i;
    }

    cout << hi_idx + 1 << endl;

    return b;

}

void check(int n, vector<array<vector<int>, 3>> res) {

    vector<vector<int>> c(n, vector<int>(n));
    for(auto q : res) {
        for(int i = 0; i < 2; i++) {
            for(int j = i + 1; j < 3; j++) {
                for(int x: q[i]) for(int y : q[j]) c[min(x,y)][max(x,y)]++;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        cout << "i : " << i << " c[i] : " << c[i] << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int casi; cin >> casi;
    // while(casi-->0) solve();

    int casi; cin >> casi;
    while(casi-->0) {
        int n; cin >> n;
        auto res = solve(n);
        check(n, res);
    }

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
//     os << "[";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << arr[i];
//         if (i < N - 1) {
//             os << ", ";
//         }
//     }
//     os << "]";
//     return os;
// }

// void solve() {
    
//     int n; cin >> n;
//     vector<array<vector<int>, 3>> b;

//     vector<int> p = {0, 1, 2, 2, 0, 1, 1, 2, 0};
//     b.push_back(array<vector<int>, 3>{});

//     // for(int os = 0; os < 3; os++) {
//     //     int sz = (n + (2 - os)) / 3;
//     //     for(int i = 0; i < sz; i++) {
//     //         b.back()[(p[i % 9] + os) % 3].push_back(i + l);
//     //     }
//     //     l += sz;
//     // }

//     for(int i = 0; i < n; i++) {
//         b.back()[p[i % 9]].push_back(i);
//     }

//     b.push_back(array<vector<int>, 3>{});
//     for(int i = 0; i < n; i++) {
//         b.back()[i % 3].push_back(i);
//     }

//     int g = 3;

//     // cout << "start b back : " << b.back() << '\n';

//     while(g < n) {
//         b.push_back(array<vector<int>, 3>{});
//         int l = 0;
//         for(int os = 0; os < 3; os++) {
//             int sz = (n + (2 - os)) / 3;
//             int v = os;
//             for(int i = 0; i < sz; i++) {
//                 if(i && (i % g == 0)) v = (v + 1) % 3;
//                 b.back()[v].push_back(i + l);
//             }
//             l += sz;
//         }
//         // cout << "g : " << g << " b back : " << b.back() << '\n';
//         g *= 3;
//     }

//     cout << b.size() << endl;

//     for(auto &q : b) {
//         if(q[0].size() == q[1].size()) {

//         } else if(q[0].size() == q[2].size()) {
//             swap(q[1], q[2]);
//         } else if(q[1].size() == q[2].size()) {
//             swap(q[0], q[2]);
//         } else {
//             assert(0);
//         }

//         cout << q[0].size() + q[1].size();
//         for(int i = 0; i < 2; i++) for(int x : q[i]) cout << " " << x + 1;
//         cout << endl;

//     }

//     vector<int> a(n);

//     string res; cin >> res;
//     for(int i = 0; i < b.size(); i++) {
//         if(res[i] == '?') continue;
//         int c;
//         if(res[i] == 'L') {
//             c = 0;
//         } else if(res[i] == 'R') {
//             c = 1;
//         } else {
//             c = 2;
//         }
//         for(int x : b[i][c]) a[x]++;
//     }

//     assert(count(a.begin(), a.end(), *max_element(a.begin(), a.end())) == 1);

//     // cout << "a : " << a << '\n';

//     int hi_idx = 0;
//     for(int i = 0; i < n; i++) {
//         if(a[i] > a[hi_idx]) hi_idx = i;
//     }

//     cout << hi_idx + 1 << endl;

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }