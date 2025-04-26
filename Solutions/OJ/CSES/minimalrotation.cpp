#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    int a = 0, N = s.size(); s += s;
    for(int b = 0; b < N; b++) {
        for(int k = 0; k < N; k++) {
            if(a + k == b || s[a+k] < s[b+k]) {b += max(0, k - 1); break;}
            if(s[a+k] > s[b+k]) { a = b; break;}
        }
    }
    rotate(s.begin(), s.begin() + a, s.end());

    cout << s.substr(N) << '\n';

    return 0;
}


// //TLE
// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// struct SuffixArray {
//     string S;
//     int N;
//     vector<int> sa;
//     vector<int> isa;

//     SuffixArray() {}

//     SuffixArray(string _S) {
//         N = (S = _S).size() + 1;
//         genSa();
//     }

//     void init(string _S) {
//         N = (S = _S).size() + 1;
//         genSa();
//     }

//     void genSa() { //suffix array has size S.size() + 1, starts with s.size()
//         sa = vector<int>(N);
//         isa = vector<int>(N);
//         sa[0] = N-1;
//         iota(1 + sa.begin(), sa.end(), 0);
//         sort(1 + sa.begin(), sa.end(), [&](int a, int b) {
//             return S[a] < S[b]; 
//         });
// 		for(int i = 1; i < N; i++) { 
//             int a = sa[i-1];
//             int b = sa[i];
// 			isa[b] = i > 1 && S[a] == S[b] ? isa[a] : i; 
//         }
//         for(int len = 1; len < N; len *= 2) {
//             //by first len chars
//             vector<int> s(sa);
//             vector<int> is(isa);
//             vector<int> pos(N);
//             iota(pos.begin(), pos.end(),0);
//             for(auto &t : s) {
//                 int T = t - len;
//                 if(T >= 0) {
//                     sa[pos[isa[T]]++] = T;
//                 }
//             }
//             for(int i = 1; i < N; i++) {
//                 int a = sa[i - 1];
//                 int b = sa[i];
//                 isa[b] = is[a] == is[b] && is[a + len] == is[b + len]  ? isa[a] : i;
//             }
//         }
//     }
// };

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     string s; cin >> s;
    
//     int n = s.size();

//     for(int i = 0; i < n; i++) {
//         s.push_back(s[i]);
//     }

//     SuffixArray sa(s);

//     // cout << sa.sa << '\n';

//     for(int i = 0; i < n * 2; i++) {
//         if(sa.sa[i] < n) {
//             cout << s.substr(sa.sa[i], n) << '\n';
//             return 0;
//         }
//     }

//     return 0;
// }