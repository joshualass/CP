#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
TODO - write up a solution to this problem. 

The first thing to realize is that for a lot of these subsequences will cancel out - you can swap two elements 
and get a different subsequence and the duplicates will cancel out. 

First thing to figure out - when will a particular multiset of elements appear in an odd amount of sequences
Solution - When the frequencies of all the elements are disjoint, when represented in binary represented

This implies that the median element is always the maximum element, define it as z

Given that we have i elements smaller than z, how many ways are there to select these numbers and their frequences?
The number of ways to choose the digits is just z choose i and the number of ways to choose these sets is S_{pc, i + 1}, which we can use a 0/1 to see if it's even.
This will solve the easy version

To solve the hard version, we can observe that we can fix the number of elements prior i, and then count the choices of z such that z is disjoint to i (need m choose i to be odd)
and z < m. We use digit dp / make some observations to help us out here and solve this. 
*/

/*
output normal
1 - 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
2 - 0 1 1 0 1 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 
3 - 0 3 3 2 3 2 2 0 3 2 2 0 2 0 0 
4 - 0 0 0 2 0 2 2 3 0 2 2 3 
5 - 0 4 4 6 4 6 6 7 4 6 6 
6 - 0 1 1 6 1 6 6 7 1 
7 - 0 7 7 0 7 0 0 7 7 
8 - 0 0 0 0 0 0 0 0 
9 - 0 8 8 8 8 8 8 8 
10 - 0 1 1 8 1 8 8 8 
11 - 0 11 11 2 11 2 2 
12 - 0 0 0 2 0 2 2 
13 - 0 12 12 14 12 14 14 
14 - 0 1 1 14 1 14 14 
15 - 0 15 15 0 15 0 
16 - 0 0 0 0 0 0 
17 - 0 16 16 16 16 16 
18 - 0 1 1 16 1 16 
19 - 0 19 19 2 19 2 
20 - 0 0 0 2 0 2 
21 - 0 20 20 22 20 22 
22 - 0 1 1 22 1 22 
23 - 0 23 23 0 23 0 
24 - 0 0 0 0 0 0 
25 - 0 24 24 24 24 24 
26 - 0 1 1 24 1 
27 - 0 27 27 2 27 
28 - 0 0 0 2 0 
29 - 0 28 28 30 28 
30 - 0 1 1 30 1 
31 - 0 31 31 0 31 
32 - 0 0 0 0 0 
33 - 0 32 32 32 32 
34 - 0 1 1 32 1 
35 - 0 35 35 2 35 
36 - 0 0 0 2 0 
37 - 0 36 36 38 36 
38 - 0 1 1 38 1 
39 - 0 39 39 0 39 
40 - 0 0 0 0 0 
41 - 0 40 40 40 40 
42 - 0 1 1 40 1 
43 - 0 43 43 2 43 
44 - 0 0 0 2 0 
45 - 0 44 44 46 44 
46 - 0 1 1 46 1 
47 - 0 47 47 0 47 
48 - 0 0 0 0 0 
49 - 0 48 48 48 48 
50 - 0 1 1 48 1 
51 - 0 51 51 2 51 
52 - 0 0 0 2 0 
53 - 0 52 52 54 52 
54 - 0 1 1 54 1 
55 - 0 55 55 0 55 
56 - 0 0 0 0 0 
57 - 0 56 56 56 
58 - 0 1 1 56 
59 - 0 59 59 2 
60 - 0 0 0 2 
61 - 0 60 60 62 
62 - 0 1 1 62 
63 - 0 63 63 0 
64 - 0 0 0 0 
65 - 0 64 64 64 
66 - 0 1 1 64 
67 - 0 67 67 2 
68 - 0 0 0 2 
69 - 0 68 68 70 
70 - 0 1 1 70 
71 - 0 71 71 0 
72 - 0 0 0 0 
73 - 0 72 72 72 
74 - 0 1 1 72 
75 - 0 75 75 2 
76 - 0 0 0 2 
77 - 0 76 76 78 
78 - 0 1 1 78 
79 - 0 79 79 0 
80 - 0 0 0 0 
81 - 0 80 80 80 
82 - 0 1 1 80 
83 - 0 83 83 2 
84 - 0 0 0 2 
85 - 0 84 84 86 
86 - 0 1 1 86 
87 - 0 87 87 0 
88 - 0 0 0 0 
89 - 0 88 88 88 
90 - 0 1 1 88 
91 - 0 91 91 2 
92 - 0 0 0 2 
93 - 0 92 92 94 
94 - 0 1 1 94 
95 - 0 95 95 0 
96 - 0 0 0 0 
97 - 0 96 96 96 
98 - 0 1 1 96 
99 - 0 99 99 2 
100 - 0 0 0 2 

output & 1
1 - 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
2 - 0 1 1 0 1 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 
3 - 0 1 1 0 1 0 0 0 1 0 0 0 0 0 0 
4 - 0 0 0 0 0 0 0 1 0 0 0 1 
5 - 0 0 0 0 0 0 0 1 0 0 0 
6 - 0 1 1 0 1 0 0 1 1 
7 - 0 1 1 0 1 0 0 1 1 
8 - 0 0 0 0 0 0 0 0 
9 - 0 0 0 0 0 0 0 0 
10 - 0 1 1 0 1 0 0 0 
11 - 0 1 1 0 1 0 0 
12 - 0 0 0 0 0 0 0 
13 - 0 0 0 0 0 0 0 
14 - 0 1 1 0 1 0 0 
15 - 0 1 1 0 1 0 
16 - 0 0 0 0 0 0 
17 - 0 0 0 0 0 0 
18 - 0 1 1 0 1 0 
19 - 0 1 1 0 1 0 
20 - 0 0 0 0 0 0 
21 - 0 0 0 0 0 0 
22 - 0 1 1 0 1 0 
23 - 0 1 1 0 1 0 
24 - 0 0 0 0 0 0 
25 - 0 0 0 0 0 0 
26 - 0 1 1 0 1 
27 - 0 1 1 0 1 
28 - 0 0 0 0 0 
29 - 0 0 0 0 0 
30 - 0 1 1 0 1 
31 - 0 1 1 0 1 
32 - 0 0 0 0 0 
33 - 0 0 0 0 0 
34 - 0 1 1 0 1 
35 - 0 1 1 0 1 
36 - 0 0 0 0 0 
37 - 0 0 0 0 0 
38 - 0 1 1 0 1 
39 - 0 1 1 0 1 
40 - 0 0 0 0 0 
41 - 0 0 0 0 0 
42 - 0 1 1 0 1 
43 - 0 1 1 0 1 
44 - 0 0 0 0 0 
45 - 0 0 0 0 0 
46 - 0 1 1 0 1 
47 - 0 1 1 0 1 
48 - 0 0 0 0 0 
49 - 0 0 0 0 0 
50 - 0 1 1 0 1 
51 - 0 1 1 0 1 
52 - 0 0 0 0 0 
53 - 0 0 0 0 0 
54 - 0 1 1 0 1 
55 - 0 1 1 0 1 
56 - 0 0 0 0 0 
57 - 0 0 0 0 
58 - 0 1 1 0 
59 - 0 1 1 0 
60 - 0 0 0 0 
61 - 0 0 0 0 
62 - 0 1 1 0 
63 - 0 1 1 0 
64 - 0 0 0 0 
65 - 0 0 0 0 
66 - 0 1 1 0 
67 - 0 1 1 0 
68 - 0 0 0 0 
69 - 0 0 0 0 
70 - 0 1 1 0 
71 - 0 1 1 0 
72 - 0 0 0 0 
73 - 0 0 0 0 
74 - 0 1 1 0 
75 - 0 1 1 0 
76 - 0 0 0 0 
77 - 0 0 0 0 
78 - 0 1 1 0 
79 - 0 1 1 0 
80 - 0 0 0 0 
81 - 0 0 0 0 
82 - 0 1 1 0 
83 - 0 1 1 0 
84 - 0 0 0 0 
85 - 0 0 0 0 
86 - 0 1 1 0 
87 - 0 1 1 0 
88 - 0 0 0 0 
89 - 0 0 0 0 
90 - 0 1 1 0 
91 - 0 1 1 0 
92 - 0 0 0 0 
93 - 0 0 0 0 
94 - 0 1 1 0 
95 - 0 1 1 0 
96 - 0 0 0 0 
97 - 0 0 0 0 
98 - 0 1 1 0 
99 - 0 1 1 0 
100 - 0 0 0 0 



*/

int S[501][501];

void init_pc() {
    for(int n = 0; n <= 500; n++) {
        for(int k = 0; k <= n; k++) {
            if(n == 0) {
                S[n][k] = 1;
            } else {
                S[n][k] = (S[n-1][k-1] + k * S[n-1][k]) % 2;
            }
        }
    }
}

int choose(int n, int k) {
    return (k & (n - k)) == 0;
}

/*
init_fact()
*/

// //what was bro doing O_o
// int solveF1(int pc, int m) {
//     int res = 0;
//     for(int x = 0; x < m; x++) { //max value / median
//         for(int i = 0; i < pc; i++) { 
//             for(int j = i; j < pc; j++) { //
//                 // cout << "x : " << x << " i : " << i << " j : " << j << '\n';
//                 // cout << "p0 : " << choose(pc - 1, pc - 1 - j) << " p1 : " << S[j][i] << " p2 : " << choose(x, i) << '\n';
//                 if(choose(pc - 1, pc - 1 - j) * S[j][i] * choose(x, i)) {
//                     res ^= x;
//                     // cout << " xor hit!\n";
//                 }
//                 // cout << '\n';
//             }
//         }
//     }
//     return res;
// }

int solveF1V2(int pc, int m) {

    int res = 0;
    for(int i = 0; i < pc; i++) { //i previous elements. 
        if(S[pc][i + 1]) {
            cout << "i is good V2 : " << i << '\n';
            for(int x = 0; x < m; x++) { // median
                // cout << "x : " << x << " i : " << i << " c : " << choose(x, i) << " S : " << S[pc][i + 1] << endl;
                if(choose(x, i)) {
                    res ^= x;
                }
            }
        }
    }
    return res;
}

//given that we are chosing i elements and m is our last value, what is our xor contribution?
int _solveF2(int i, int m) {

    if(i >= m) return 0;

    int num = i;
    int true_num = 0;

    for(int bit = 29; bit >= 0; bit--) {
        if(((i >> bit) & 1) == 0) {
            true_num <<= 1;
            if(num + (1 << bit) < m) {
                num += 1 << bit;
                true_num++;
            }
        }
    }

    // cout << "true_num : " << true_num << '\n';

    int cnt = 0, res = 0;
    for(int bit = 0; bit < 30; bit++) {
        if(((i >> bit) & 1) == 0) {
            if(cnt) {
                if(((true_num >> cnt) & 1) && (true_num & 1) == 0) {
                    res += 1 << bit;
                }
            } else {
                if(true_num % 4 == 1 || true_num % 4 == 2) {
                    res += 1 << bit;
                }
                if(true_num % 2 == 0) res ^= i;
            }
            cnt++;
        }
    }
    // cout << "i : " << i << " m : " << m << " true_num : " << true_num << " res : " << res << '\n';
    return res;
}

int solveF2(int pc, int m) {
    int res = 0;
    for(int i = 1; i <= pc; i++) {
        //stirling number of (pc, i)
        int z = pc - (i + 2) / 2, w = (i - 1) / 2;
        
        if(choose(z, w)) {
            // cout << "i is good F2 : " << i - 1 << '\n';
            res ^= _solveF2(i - 1, m);
        }
    }
    return res;
}

void solve() {
    
    int k, m; cin >> k >> m;
    string n; cin >> n;
    int pc = count(n.begin(), n.end(), '1');
    // cout << solveF1(pc, m) << '\n';
    // cout << solveF1V2(pc, m) << '\n';
    cout << solveF2(pc, m) << '\n';

}

int solve_slow(int n, int m) {

    int res = 0;
    int stp = 1;
    for(int i = 0; i < n; i++) stp *= m;
    for(int i = 0; i < stp; i++) {
        vector<int> cnts(m);
        int t = i;
        for(int j = 0; j < n; j++) {
            cnts[t % m]++;
            t /= m;
        }
        int ok = 1, lo = 0;;
        for(int j = 0; j < m; j++) {
            if(cnts[j]) {
                if(cnts[j] < lo) ok = 0;
                lo = cnts[j];
            }
        }
        int med = INT_MAX;
        int need = (n + 1) / 2;
        for(int j = 0; j < m; j++) {
            need -= cnts[j];
            if(need <= 0) {
                med = j;
                break;
            }
        }
        // cout << "i : " << i << " ok : " << ok << " med : " << med << endl;
        if(ok) res ^= med;
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_pc();

    // while(1) {
    //     cout << "enter params n, m : " << endl;
    //     int n, m; cin >> n >> m;
    //     cout << "xor med = " << solve_slow(n, m) << endl;
    // }

    // int stop = 1e7;

    // for(int m = 1; m <= 100; m++) {
    //     cout << m << " - ";
    //     for(int n = 0; n <= 100; n++) {
    //         ll cnt = 1;
    //         for(int i = 0; i < n; i++) {
    //             cnt *= m;
    //             if(cnt > stop) break;    
    //         }
    //         if(cnt <= stop) {
    //             // cout << "n : " << n << " m : " << m << " solve : " << solve_slow(n, m) << '\n';
    //             cout << (solve_slow(n, m) & 1) << " ";
    //         }
    //     }
    //     cout << '\n';
    // }

    // for(int pc = 0; pc <= 100; pc++) {
    //     cout << "pc : " << pc << " - ";
    //     for(int m = 0; m <= 100; m++) {
    //         cout << solveF1(pc, m) << " ";
    //         // cout << ((solveF1(pc, m) & 1) ? '#' : '_') << " ";
    //     }
    //     cout << '\n';
    // }

    // for(int m = 0; m <= 100; m++) {
    //     cout << "m : " << (m < 10 ? " " : "") << m << " - ";
    //     for(int pc = 0; pc <= 100; pc++) {
    //         // cout << solveF1(pc, m) << " ";
    //         cout << ((solveF1(pc, m) & 1) ? '#' : '_') << " ";
    //     }
    //     cout << '\n';
    // }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}