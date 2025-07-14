#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
more work done 

here ... 

https://docs.google.com/spreadsheets/d/1HdAzKWMpNDDKN5KYokocMHBbarv-pguIgihsE-wSRPo/edit?gid=0#gid=0

we tried several constructions
the one that worked and AC is as follows

each nx value increases by 1 each time
then it can increase every l / 3^1, l / 3^1 and l / 3^2, l / 3^2 and l / 3^3, ... l / (l / 3) and l / l. 

works, not sure where people are getting this crazy intuition from. 

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

bad, a lot of columns are duplicated ex 1, 9, 19 only differ in the top row ... need a different type of construction
 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
 1  1  1  1  1  1  1  1  1  2  2  2  2  2  2  2  2  2  3  3  3  3  3  3  3  3  3
 1  1  1  2  2  2  3  3  3  1  1  1  2  2  2  3  3  3  1  1  1  2  2  2  3  3  3
 1  2  3  1  2  3  1  2  3  1  2  3  1  2  3  1  2  3  1  2  3  1  2  3  1  2  3
 1  2  3  3  1  2  2  3  1  1  2  3  3  1  2  2  3  1  1  2  3  3  1  2  2  3  1

rules we can observe for 27
 - for each triple, there must be a 1, 2, 3 in that for that triple. 
 - 
 
 1 2 3
 1 2 3
 1 3 2 
 1 2 3

1 2 3
1 2 3
2 1 3
2 3 1


 1  2  3  4 10 11 12 19 20 21
 1  1  1  1  2  2  2  3  3  3
 1  1  1  2  2  2  2  3  3  3
 1  2  3  1  2  3  1  3  1  2
 1  2  3  3  1  2  3  1  2  3
 1  4  7 10  2  5  8  3  6  9


1 1 1 2 2 2 3 3 3
1 2 3 1 2 3 1 2 3
1 2 3 3 1 2 2 3 1
A B C B C A C A B

1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3
1 1 1 2 2 2 3 3 3 1 1 1 2 2 2 3 3 3 1 1 1 2 2 2 3 3 3
1 2 3 1 2 3 1 2 3 1 2 3 1 2 3 1 2 3 1 2 3 1 2 3 1 2 3 

 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
 1  2  3  3  1  2  2  3  1  1  2  3  3  1  2  2  3  1  1  2  3  3  1  2  2  3  1
 1  2  3  1  2  3  1  2  3  1  2  3  1  2  3  1  2  3  1  2  3  1  2  3  1  2  3
 1  1  1  2  2  2  3  3  3  1  1  1  2  2  2  3  3  3  1  1  1  2  2  2  3  3  3
 1  1  1  1  1  1  1  1  1  2  2  2  2  2  2  2  2  2  3  3  3  3  3  3  3  3  3
 A           B           C     C           A  B              B  C           A   
          A                                                                      
          A           B     B                       A     A           B          
  1 15 26
  2 13 27
  3 14 25
  10 24 8

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x + 1 << " ";
    return os;
}

void check(int n, vector<array<vector<int>, 3>> res) {

    vector<vector<int>> c(n, vector<int>(n, -1));
    for(auto q : res) {
        for(int i = 0; i < 2; i++) {
            for(int j = i + 1; j < 3; j++) {
                for(int x: q[i]) for(int y : q[j]) c[min(x,y)][max(x,y)]++;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        cout << "c[i] : " << c[i] << '\n';
    }

}

void solve() {

    int n; cin >> n;

    int t = 3;
    int l = 1;
    while(t < n) {
        t *= 3;
        l++;    
    }
    vector<vector<int>> qs;
    // vector<int> a1 = {0, 1, 2, 2, 0, 1, 1, 2, 0}, a2 = {0, 5, 7, 1, 3, 8, 2, 4, 6};
    vector<int> a1 = {0, 1, 2, 2, 0, 1, 1, 2, 0}, a2 = {0, 2, 1, 1, 0, 2, 2, 1, 0};
    vector<array<vector<int>, 3>> b;

    int m0 = t, m1 = t * 3;

    for(int i = 0; i <= l; i++) {
        int cur = 0;
        b.push_back({});
        qs.push_back({});
        for(int j = 0; j < n; j++) {
            cur = (cur + 1) % 3;
            // for(int k = t, z = i, x = 2; z >= 0 && x >= 1; z--, k /= 3, x--) {
            //     if(j % k == 0 && !(i == l && k == t / 3)) cur = (cur + 1) % 3;
            // }
            if(j % m0 == 0) cur = (cur + 1) % 3;
            if(j % m1 == 0) cur = (cur + 1) % 3;
            if(j == 0) cur = 0;
            b.back()[cur].push_back(j);
            qs.back().push_back(cur);
        }
        m0 /= 3;
        m1 /= 3;
        // for(int k = t, z = i; z >= 0; z--, k /= 3) {
        //     cout << "i : " << i << " k : " << k << '\n';
        // }
    }

    //working version, but computing idxs may be redundant. 
    /*
    for(int div = 1, st = 1; st <= l; div *= 3, st++) {
        qs.push_back({});
        for(int i = 0; i < t; i++) {
            qs.back().push_back((i / div) % 3);
        }
    }

    qs.push_back({});
    for(int i = 1, cur = 0; i <= t; i++) {
        qs.back().push_back(cur);
        for(int j = 0, m = 1; j <= l; j++, m *= 3) {
            if(i % m == 0) cur = (cur + 1) % 3;
        }
    }
    */

    //old, bad version of qs
    /*

    qs.push_back({});
    for(int i = 0; i < t; i++) {
        qs.back().push_back(a1[i % 9]);
    }

    auto add_v = [&](vector<int> &v) -> void {
        for(int &x : v) x = (x + 1) % 3;
    };

    for(int div = 1, i = 1; i <= l; div *= 3, i++) {
        qs.push_back({});
        for(int i = 0; i < t; i++) {
            qs.back().push_back((i / div) % 3);
        }
    }
    */

    // for(int i = 0; i < qs.size(); i++) {
    //     cout << "i : " << i << " qs[i] : " << qs[i] << '\n';
    // }

    // vector<int> idxs;
    // if(n <= 3) {
    //     for(int i = 0; i < 3; i++) idxs.push_back(i);
    // } else {

    //     for(int i = 0; i < t / 9; i++) {
    //         vector<int> c;
    //         int s = i;
    //         for(int j = 1; j + 1 < l; j++) {
    //             c.push_back(s % 3);
    //             s /= 3;
    //         }
    //         c.push_back(0);

    //         for(int j = 0; j < 9; j++) {
    //             int idx = a2[j];
    //             if(j && j % 3 == 0) {
    //                 c[0] = (c[0] + 1) % 3;
    //             }
    //             for(int k = 1, m = 3; k < l; k++, m *= 3) {
    //                 idx += c[k-1] * m;
    //             }
    //             idxs.push_back(idx);
    //             // add_v(c);
    //         }

    //     }
    // }

    // cout << "idxs : " << idxs << '\n';

    // for(int i = 0; i < qs.size(); i++) {
    //     b.push_back({});
    //     for(int j = 0; j < n; j++) {
    //         // b.back()[qs[i][idxs[j]]].push_back(j);
    //         b.back()[qs[i][j]].push_back(j);
    //     }
    // }

    // check(n, b);

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

}

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

// vector<array<vector<int>, 3>> solve(int n) {
// // void solve() {
    
//     // int n; cin >> n;

//     int l = 1;
//     while(l < n) l *= 3;
//     vector<int> ids(l);
//     for(int i = 0; i < l; i++) {
//         ids[i % (l / 3) * 3  + i / (l / 3)] = i;
//         // cout << "id : " << i << " id : " << ((i * 3) + i / (l / 3)) % l << '\n';
//     }    

//     // cout << "ids : " << ids << '\n';

//     vector<int> p = {0, 1, 2, 2, 0, 1, 1, 2, 0};
//     vector<array<vector<int>, 3>> b;

//     b.push_back(array<vector<int>, 3>{});
//     for(int i = 0; i < l; i++) {
//         // b.back()[p[i%9]].push_back(i);
//         if(ids[i] < n) b.back()[p[i%9]].push_back(ids[i]);
//     }
    
//     for(int i = 1; i < l; i *= 3) {
//         b.push_back(array<vector<int>, 3>{});
//         for(int j = 0; j < l; j++) {
//             if(ids[j] < n) b.back()[(j / i + j / (l / 3)) % 3].push_back(ids[j]);
//         }
//     }

//     cout << b.size() << endl;

//     for(auto &q : b) {
//         // cout << "q : " << q << endl;
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

//     return b;

// }

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    // int casi; cin >> casi;
    // while(casi-->0) {
    //     int n; cin >> n;
    //     auto res = solve(n);
    //     check(n, res);
    // }

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