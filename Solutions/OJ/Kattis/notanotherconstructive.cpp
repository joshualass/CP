#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

unordered_map<int,char> dp[41][41][1601]; //idx, N, NA, {NAC : par}
int pc[41][41][401]; //length rem, N, NA

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    string s; cin >> s;
    if(k > 2366) {
        cout << "-1\n";
        return 0;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= n; j++) {
            for(int l = 0; l <= n * n; l++) {
                //place N
                if(j) {
                    pc[i+1][j-1][l] = max(pc[i+1][j-1][l], pc[i][j][l]);
                }
                //place A
                if(l - j >= 0) {
                    pc[i+1][j][l - j] = max(pc[i+1][j][l - j], pc[i][j][l]);
                }
                //place C
                pc[i+1][j][l] = max(pc[i+1][j][l], pc[i][j][l] + l);
            }
        }
    }

    dp[0][0][0][0] = '$';

    for(int i = 0; i < n; i++) { //idx
        for(int j = 0; j <= n; j++) { //N
            for(int l = 0; l <= n * n; l++) {//NA   
                for(auto [nac, p] : dp[i][j][l]) {
                    // cout << "vis i : " << i << " j : " << j << " l : " << l << " nac : " << nac << " p : " << p << endl;
                    if(nac + pc[n - i][j][l] < k || nac < k && nac + l > k) continue; //things are not possible here. 
                    if((s[i] == 'N' || s[i] == '?') && j + 1 <= n) {
                        dp[i+1][j+1][l][nac] = 'N';
                    }
                    if((s[i] == 'A' || s[i] == '?') && l + j <= n * n) {
                        dp[i+1][j][l + j][nac] = 'A';
                    }
                    if((s[i] == 'C' || s[i] == '?') && nac + l <= k) {
                        dp[i+1][j][l][nac + l] = 'C';
                    }
                    if(s[i] != 'N' && s[i] != 'A' && s[i] != 'C') {
                        dp[i+1][j][l][nac] = (s[i] == '?' ? 'B' : s[i]);
                    }
                }
            }
        }
    }

    array<int,3> st = {-1,-1,-1};
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n * n; j++) {
            if(dp[n][i][j].count(k)) st = {i, j, k};
        }
    }

    // cout << "st stores => {N, NA, NAC}" << endl;
    // cout << "st : " << st << endl;

    if(st[0] != -1) {
        string res = "";
        for(int i = n; i > 0; i--) {

            // cout << "i : " << i << " st : " << st << endl;
            if(dp[i][st[0]][st[1]].count(st[2]) == 0) {
                // cout << "buy your life gn" << endl;
                assert(dp[i][st[0]][st[1]].count(st[2]));
            }
            char c = dp[i][st[0]][st[1]][st[2]];
            res.push_back(c);

            if(c == 'N') {
                st = {st[0] - 1, st[1], st[2]};
            } else if(c == 'A') {
                st = {st[0], st[1] - st[0], st[2]};
            } else if(c == 'C') {
                st = {st[0], st[1], st[2] - st[1]};
            }
        }
        reverse(res.begin(), res.end());
        cout << res << '\n';
    } else {
        cout << "-1\n";
    }

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

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

// map<int,char> dp[41][2367][41]; //length, NAC cnt remaining, N, {NA : par}
// int pc[41][41][1601]; //length rem, N, NA

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, k; cin >> n >> k;
//     string s; cin >> s;
//     if(k > 2366) {
//         cout << "-1\n";
//         return 0;
//     }

//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j <= n; j++) {
//             for(int l = 0; l <= n * n; l++) {
//                 //place N
//                 if(j) {
//                     pc[i+1][j-1][l] = max(pc[i+1][j-1][l], pc[i][j][l]);
//                 }
//                 //place A
//                 if(l - j >= 0) {
//                     pc[i+1][j][l - j] = max(pc[i+1][j][l - j], pc[i][j][l]);
//                 }
//                 //place C
//                 pc[i+1][j][l] = max(pc[i+1][j][l], pc[i][j][l] + l);
//             }
//         }
//     }

//     dp[0][k][0][0] = '$';
//     for(int i = 0; i < n; i++) { //index
//         for(int j = 0; j <= k; j++) { //# NAC needed
//             for(int l = 0; l < n; l++) { //N count
//                 for(auto [na, p] : dp[i][j][l]) {
//                     if(pc[n - i][l][na] < j) continue;
//                     if(s[i] == 'N' || s[i] == '?') {
//                         dp[i+1][j][l+1][na] = 'N';
//                     }
//                     if(s[i] == 'A' || s[i] == '?') {
//                         dp[i+1][j][l][na + l] = 'A';
//                     }
//                     if((s[i] == 'C' || s[i] == 'C') && j - na >= 0) {
//                         dp[i+1][j - na][l][na] = 'C';
//                     }
//                     if(s[i] != 'N' && s[i] != 'A' && s[i] != 'C') {
//                         dp[i+1][j][l][na] = (s[i] == '?' ? 'B' : s[i]);
//                     }
//                 }
//             }
//         }
//     }

//     array<int,3> st = {-1,-1,-1};
//     for(int i = 0; i <= n; i++) {
//         for(auto [na, p] : dp[n][0][i]) {
//             st = {0, i, na};
//         }
//     }

//     // cout << "st stores => {NAC cnt rem, N, NA}" << endl;

//     if(st[0] != -1) {
//         string res = "";
//         for(int i = n; i > 0; i--) {
//             // cout << "i : " << i << " st : " << st << endl;
//             if(dp[i][st[0]][st[1]].count(st[2]) == 0) {
//                 // cout << "buy your life gn" << endl;
//                 assert(dp[i][st[0]][st[1]].count(st[2]));
//             }
//             char c = dp[i][st[0]][st[1]][st[2]];
//             res.push_back(c);
//             if(c == 'N') {
//                 st = {st[0], st[1] - 1, st[2]};
//             } else if(c == 'A') {
//                 st = {st[0], st[1], st[2] - st[1]};
//             } else if(c == 'C') {
//                 st = {st[0] + st[2], st[1], st[2]};
//             }
//         }
//         reverse(res.begin(), res.end());
//         cout << res << '\n';
//     } else {
//         cout << "-1\n";
//     }

//     return 0;
// }