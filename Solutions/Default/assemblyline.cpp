#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dp[201][201][26];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    map<char,int> m;
    for(int i = 0; i < n; i++) {
        char c; cin >> c;
        int sz = m.size();
        m[c] = sz;
    }   

    vector<vector<array<int,2>>> merges(n,vector<array<int,2>>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            string merge; cin >> merge;
            int idx = -1;
            for(int k = 0; k < merge.size(); k++) {
                if(merge[k] == '-') {
                    idx = k;
                    break;
                }
            }
            int time = stoi(merge.substr(0,idx));
            int piece = m[merge[idx + 1]];
            merges[i][j] = {time, piece};
        }
    }

    int tc; cin >> tc;
    while(tc--) {
        string s; cin >> s;

        for(int i = 0; i <= s.size(); i++) {
            for(int j = 0; j <= s.size(); j++) {
                for(int k = 0; k < n; k++) {
                    dp[i][j][k] = -1;
                }
            }
        }

        for(int len = 1; len <= s.size(); len++) {
            for(int l = 0; l + len <= s.size(); l++) {
                int r = l + len;
                if(len == 1) {
                    dp[l][r][m[s[l]]] = 0;
                } else {
                    for(int m = l + 1; m < r; m++) {
                        for(int a = 0; a < n; a++) {
                            for(int b = 0; b < n; b++) {
                                if(dp[l][m][a] != -1 && dp[m][r][b] != -1) {
                                    array<int,2> res = {dp[l][m][a] + dp[m][r][b] + merges[a][b][0], merges[a][b][1]};
                                    if(dp[l][r][res[1]] == -1 || res[0] < dp[l][r][res[1]]) {
                                        dp[l][r][res[1]] = res[0];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        int best = 1e9;
        int best_idx = -1;
        for(int i = 0; i < n; i++) {
            if(dp[0][s.size()][i] != -1 && dp[0][s.size()][i] < best) {
                best = dp[0][s.size()][i];
                best_idx = i;
            }
        }

        cout << best << "-";
        for(auto [c, idx] : m) {
            if(idx == best_idx) cout << c << '\n';
        }

    }

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// using namespace std;

// map<string, pair<ll, char>> table;

// vector<map<char, ll>> merger(vector<map<char, ll>> parts, int size,
//                              string line) {
//     vector<map<char, ll>> result(0);
//     for (int i = 0; i < parts.size() - 1; i++) {
//         map<char, ll> temp;
//         for (pair<char, ll> p : parts[i]) {
//             string rec = string() + p.first + line[size - parts.size() + i + 1];
//             ll time = p.second + table[rec].first;
// //            cout << "rec: " << rec << '\n';
//             char c = table[rec].second;
//             if (temp.find(c) == temp.end()) {
// //                cout << "inserting value1: " << c << " " << time << '\n';
//                 temp.insert({c, time});
//             } else {
//                 temp[c] = min(temp[c], time);
//             }
//         }

//         for (pair<char, ll> p : parts[i + 1]) {
//             ll time = p.second + table[string() + line[i] + p.first].first;
//             char c = table[string() + line[i] + p.first].second;
//             if (temp.find(c) == temp.end()) {
// //                cout << "inserting value2: " << c << " " << time << '\n';
//                 temp.insert({c, time});
//             } else {
//                 temp[c] = min(temp[c], time);
//             }
//         }
//         result.push_back(temp);
//     }
//     // cout << "result: " << '\n';
//     // for (map<char, ll> p : result) {
//     //     for (pair<char, ll> pp : p) {
//     //         cout << "first: " << pp.first << " second: "
//     //              << "p.second " << pp.second << '\n';
//     //     }
//     // }
//     // cout << "MERGING new size - " << result.size() << '\n';

//     return result;
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int k;
//     cin >> k;
//     vector<char> sequence(k);
//     for (char &x : sequence) cin >> x;

//     string order = "";
//     for (char x : sequence) order += x;
//     for (int r = 0; r < k; r++) {
//         for (int c = 0; c < k; c++) {
//             string line;
//             cin >> line;
//             table.insert({string() + sequence[r] + sequence[c],
//                           {stoll(line.substr(0, line.size() - 2)),
//                            line[line.size() - 1]}});
//         }
//     }

//     // for(pair<string, pair<ll,char>> p : table) {
//     //     cout << "string: " << p.first << " ll: " << p.second.first << " char: " << p.second.second << '\n';
//     // }

//     int n;
//     cin >> n;
//     for (int i = 0; i < n; i++) {
//         string line;
//         cin >> line;
//         if (line.size() == 1) {
//             cout << "0-" << line[0] << '\n';
//         } else {
//             vector<map<char, ll>> parts(line.size() - 1);
//             for (int t = 0; t < line.size() - 1;
//                  t++) {  // do first operation already
//                 parts[t] = {{table[string() + line[t] + line[t + 1]].second, table[string() + line[t] + line[t + 1]].first}};
//                 // cout << "expr: " << table[string() + line[t] + line[t + 1]].second << " huh: " << table[string() + line[t] + line[t + 1]].first << '\n';
//             }

//             while (parts.size() != 1) {
//                 // cout << "starting position: " << '\n';
//                 // for (int i = 0; i < parts.size(); i++) {
//                 //     for (pair<char, ll> pp : parts[i]) {
//                 //         cout << "i: " << i << " first: " << pp.first
//                 //              << " second: " << pp.second << '\n';
//                 //     }
//                 // }
//                 // cout << '\n';
//                 parts = merger(parts, line.size(), line);
//             }
//             ll lowest = LLONG_MAX;
//             ll index = -1;
//             for (pair<char, ll> p : parts[0]) {
//                 // cout << "char: " << p.first << " time: " << p.second << '\n';
//                 if (p.second == lowest) {
//                     index = min(index, (ll)order.find(p.first));
//                 }
//                 if (p.second < lowest) {
//                     lowest = p.second;
//                     index = (ll)order.find(p.first);
//                 }
//             }

//             cout << lowest << '-' << order[index] << '\n';
//         }
//     }
//     int last;
//     cin >> last;
//     return 0;
// }